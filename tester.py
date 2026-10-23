"""Compile and run a solution against an input file.

Optionally compares the program output against a sample file and pipes it
through a verifier script.
"""

import argparse
import os
import subprocess
from pathlib import Path

WORKSPACE_PATH = Path(__file__).parent / "workspace"

LANGUAGE_EXTENSIONS = {
    ".cpp": "C++",
    ".c++": "C++",
    ".py": "Python",
}

CPP_SOURCE_EXT = ".cpp"

# Verifier scripts are run with python3 on Unix-like systems, python on Windows.
VERIFIER_PYTHON = "python3" if os.name != "nt" else "python"


def detect_language(name: str) -> str | None:
    """Return the language for a file name, or None if unknown."""
    return next(
        (lang for ext, lang in LANGUAGE_EXTENSIONS.items() if name.endswith(ext)),
        None,
    )


def run_program(
    command: list[str], input_file: str, output_file: str | Path | None = None
) -> str | None:
    """Run command with input_file on stdin, returning its stdout.

    If output_file is given, stdout is also tee'd into it.  Returns None if
    the program could not be started or exited non-zero.
    """
    try:
        with open(input_file, "r") as infile:
            # stdout goes into a pipe, so we can collect it as a string.
            process = subprocess.Popen(
                command, stdin=infile, stdout=subprocess.PIPE, text=True
            )

            if output_file:
                # Tee: every line goes to the output file and into output.
                chunks = []
                with open(output_file, "w") as outfile:
                    for line in process.stdout:
                        chunks.append(line)
                        outfile.write(line)
                output = "".join(chunks)
            else:
                output = process.stdout.read()

            process.wait()
            if process.returncode != 0:
                print(
                    f"Error during program execution: exit code {process.returncode}"
                )
                return None
            return output
    except FileNotFoundError:
        print(f"Program (or input file) '{command[-1]}' not found.")
        return None


def verify_output(verifier_script: str, output: str) -> str | None:
    """Run verifier_script on output and return its stripped stdout."""
    try:
        verifier_output = subprocess.check_output(
            [VERIFIER_PYTHON, verifier_script], input=output, text=True
        )
        return verifier_output.strip()
    except subprocess.CalledProcessError as error:
        print(f"Verification failed: {error}")
        return None
    except FileNotFoundError:
        print(f"Verifier script '{verifier_script}' not found.")
        return None


def compile_source(source_file: str, executable_file: str, is_windows: bool) -> bool:
    """Compile source_file with g++, returning whether it succeeded."""
    compile_command = [
        "g++",
        "-D",
        "TTL",
        source_file,
        "-o",
        executable_file,
        "-std=c++23",
    ]
    platform = "Windows" if is_windows else "Unix-like system"
    print(f"Compiling {source_file} with g++ on {platform}...")
    result = subprocess.run(compile_command)
    if result.returncode != 0:
        print("Compilation failed.")
        return False
    print("Compilation succeeded.")
    return True


def cpp_artifact_paths(
    executable_name: str, is_windows: bool
) -> tuple[str, str, str]:
    """Return the (source, executable, runnable) paths for a C++ run."""
    if executable_name.endswith(CPP_SOURCE_EXT):
        base_name = executable_name[: -len(CPP_SOURCE_EXT)]
        source_file = executable_name
    else:
        base_name = executable_name
        source_file = base_name + CPP_SOURCE_EXT

    executable_file = base_name + (".exe" if is_windows else "")

    # On Unix-like systems the executable is run from the current directory.
    if (
        is_windows
        or os.path.isabs(executable_file)
        or executable_file.startswith("./")
    ):
        executable_path = executable_file
    else:
        executable_path = "./" + executable_file

    return source_file, executable_file, executable_path


def ensure_executable(
    source_file: str,
    executable_file: str,
    *,
    skip_compile: bool,
    is_windows: bool,
) -> bool:
    """Make sure the executable is ready to run, compiling it if needed."""
    if skip_compile:
        if not os.path.isfile(executable_file) or not os.access(
            executable_file, os.X_OK
        ):
            print(
                f"Executable '{executable_file}' not found or is not executable. "
                "Consider compiling it first."
            )
            return False
        print(f"Skipping compilation. Using existing executable '{executable_file}'.")
        return True

    if not os.path.isfile(source_file):
        print(f"Source file '{source_file}' does not exist.")
        return False
    return compile_source(source_file, executable_file, is_windows)


def run_cpp(
    executable_name: str,
    input_file: str,
    output_file: str | Path,
    *,
    skip_compile: bool,
    is_windows: bool,
) -> str | None:
    """Compile (unless skipped) and run a C++ solution."""
    source_file, executable_file, executable_path = cpp_artifact_paths(
        executable_name, is_windows
    )
    if not ensure_executable(
        source_file,
        executable_file,
        skip_compile=skip_compile,
        is_windows=is_windows,
    ):
        return None
    return run_program(executable_path, input_file, output_file)


def compare_with_sample(is_windows: bool) -> None:
    """Diff workspace/output.txt against a non-empty sample_out.txt, if any."""
    sample_output_file = WORKSPACE_PATH / "sample_out.txt"
    if not sample_output_file.exists() or sample_output_file.stat().st_size == 0:
        return

    output_file = WORKSPACE_PATH / "output.txt"
    diff_command = [
        "fc" if is_windows else "diff",
        str(sample_output_file),
        str(output_file),
    ]
    result = subprocess.run(diff_command, capture_output=True, text=True, shell=True)
    if result.returncode == 0:
        print("Output matches the sample output.")
    else:
        print("Output differs from the sample output:")
        print(result.stdout)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=(
            "Run and optionally compile a C++ program with input and verification."
        )
    )
    parser.add_argument(
        "executable_name",
        help=(
            "Name of the executable, C++ source file (with .cpp extension), "
            "or python script (with .py extension)."
        ),
    )
    parser.add_argument("input_file", help="Path to the input file.")
    parser.add_argument(
        "-o",
        "--output",
        default=WORKSPACE_PATH / "output.txt",
        dest="output_file",
        help="Path to save the program output.",
    )
    parser.add_argument(
        "-v",
        "--verifier",
        dest="verifier_script",
        help="Path to the verifier script.",
    )
    parser.add_argument(
        "-s",
        "--skip-compile",
        action="store_true",
        help="Skip recompilation if executable exists.",
    )
    return parser.parse_args()


def main() -> None:
    args = parse_args()
    is_windows = os.name == "nt"

    if detect_language(args.executable_name) == "C++":
        output = run_cpp(
            args.executable_name,
            args.input_file,
            args.output_file,
            skip_compile=args.skip_compile,
            is_windows=is_windows,
        )
    else:
        # Python scripts (and anything unrecognized) run through python.
        output = run_program(
            ["python", args.executable_name], args.input_file, args.output_file
        )

    if output is None:
        return

    print("Program output:")
    print(output)

    if args.verifier_script:
        verification_result = verify_output(args.verifier_script, output)
        if verification_result is not None:
            print("Verification result:")
            print(verification_result)

    compare_with_sample(is_windows)


if __name__ == "__main__":
    main()
