import sys
import subprocess
import os

def run_program(executable, input_file):
    try:
        with open(input_file, 'r') as infile:
            output = subprocess.check_output([executable], stdin=infile, text=True)
        return output
    except subprocess.CalledProcessError as e:
        print(f"Error during program execution: {e}")
        return None
    except FileNotFoundError:
        print(f"Executable '{executable}' not found.")
        return None

def verify_output(verifier_script, output):
    try:
        # Use 'python3' on Unix-like systems, 'python' on Windows
        python_command = 'python3' if os.name != 'nt' else 'python'
        verifier_output = subprocess.check_output([python_command, verifier_script], input=output, text=True)
        return verifier_output.strip()
    except subprocess.CalledProcessError as e:
        print(f"Verification failed: {e}")
        return None
    except FileNotFoundError:
        print(f"Verifier script '{verifier_script}' not found.")
        return None

def compile_source(source_file, executable_file, is_windows):
    # Compile the source file using g++
    compile_command = ['g++', source_file, '-o', executable_file]
    platform = "Windows" if is_windows else "Unix-like system"
    print(f"Compiling {source_file} with g++ on {platform}...")
    result = subprocess.run(compile_command)
    if result.returncode != 0:
        print("Compilation failed.")
        return False
    else:
        print("Compilation succeeded.")
        return True

def main():
    import argparse

    # Set up argument parser
    parser = argparse.ArgumentParser(description="Run and optionally compile a C++ program with input and verification.")
    parser.add_argument('executable_name', help="Name of the executable or C++ source file (with .cpp extension).")
    parser.add_argument('input_file', help="Path to the input file.")
    parser.add_argument('-v', '--verifier', dest='verifier_script', help="Path to the verifier script.")
    parser.add_argument('-s', '--skip-compile', action='store_true', help="Skip recompilation if executable exists.")
    
    args = parser.parse_args()

    executable_name = args.executable_name
    input_file = args.input_file
    verifier_script = args.verifier_script
    skip_compile = args.skip_compile

    # Determine the platform
    is_windows = os.name == 'nt'
    executable_ext = '.exe' if is_windows else ''
    source_ext = '.cpp'

    # Adjust executable and source file names
    if executable_name.endswith(source_ext):
        base_name = executable_name[:-len(source_ext)]
        source_file = executable_name
    else:
        base_name = executable_name
        source_file = base_name + source_ext

    executable_file = base_name + executable_ext

    # Determine executable path
    if is_windows:
        executable_path = executable_file
    else:
        # On Unix-like systems, prefix with './' if not absolute path
        if not os.path.isabs(executable_file) and not executable_file.startswith('./'):
            executable_path = './' + executable_file
        else:
            executable_path = executable_file

    # Handle compilation
    if not skip_compile:
        # Always compile the source file
        if not os.path.isfile(source_file):
            print(f"Source file '{source_file}' does not exist.")
            return

        success = compile_source(source_file, executable_file, is_windows)
        if not success:
            return
    else:
        # Skip compilation, ensure executable exists
        if not os.path.isfile(executable_file) or not os.access(executable_file, os.X_OK):
            print(f"Executable '{executable_file}' not found or is not executable. Consider compiling it first.")
            return
        else:
            print(f"Skipping compilation. Using existing executable '{executable_file}'.")

    # Run the program
    output = run_program(executable_path, input_file)

    if output is not None:
        print("Program output:")
        print(output)

        # Handle verification if verifier script is provided
        if verifier_script:
            verification_result = verify_output(verifier_script, output)
            if verification_result is not None:
                print("Verification result:")
                print(verification_result)

        # Save output to a file
        with open("output", "w") as file:
            file.write(output)

if __name__ == "__main__":
    main()
