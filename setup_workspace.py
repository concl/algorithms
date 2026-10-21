"""Reset the contest workspace.

Wipes everything in workspace/ (except .gitignore) and recreates the A-H
problem files from the chosen language template, plus placeholder
input/output files.  Only writes inside workspace/.

By default the C++ template gets the Codeforces test-case loop ("cf_test"
snippet) inserted into main(); pass --no-cf-test to write it verbatim.
"""

import argparse
import shutil
from dataclasses import dataclass
from pathlib import Path

ROOT = Path(__file__).parent
WORKSPACE_PATH = ROOT / "workspace"
TEMPLATE_DIR = ROOT / "code_template"

# Files always kept during cleanup.
KEEP = {".gitignore"}

# Placeholder files recreated after cleanup.
PLACEHOLDER_FILES = [
    "input.txt",
    "output.txt",
    "sample_out.txt",
]

# Codeforces test-case loop (matches the "cf_test" snippet in
# code_template/snippets.code-snippets), indented for main().
CF_TEST_SNIPPET = [
    "    int t;",
    "    cin >> t;",
    "    while (t--) {",
    "        solve();",
    "    }",
]


@dataclass(frozen=True)
class Language:
    """A problem-file language: its template, extension, and features."""

    template: Path
    extension: str
    cf_test: bool = False  # supports inserting the cf_test loop


# To add a language, add a Language entry here and a template file.
LANGUAGES = {
    "cpp": Language(TEMPLATE_DIR / "cp_template.cpp", ".cpp", cf_test=True),
    "python": Language(TEMPLATE_DIR / "py_cp_template.py", ".py"),
}


def insert_cf_test(source: str) -> str:
    """Return the source with the cf-test loop inserted into main()."""
    lines = source.splitlines()
    if "    int t;" in lines:
        return source  # already inserted
    try:
        idx = lines.index("    cin.tie(NULL);")
    except ValueError:
        print("warning: could not find 'cin.tie(NULL);' in the template; skipping cf-test snippet")
        return source
    # Insert mid-body: right after the fast-io setup, replacing the blank
    # lines that follow it.
    j = idx + 1
    while j < len(lines) and lines[j].strip() == "":
        j += 1
    lines[idx + 1:j] = CF_TEST_SNIPPET
    return "\n".join(lines) + "\n"


def build_source(language: Language, cf_test: bool) -> str:
    """Return the problem-file source for a language."""
    source = language.template.read_text(encoding="utf-8")
    if language.cf_test and cf_test:
        source = insert_cf_test(source)
    return source


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "-l",
        "--lang",
        choices=LANGUAGES,
        default="cpp",
        help="language for the problem files (default: cpp)",
    )
    parser.add_argument(
        "--no-cf-test",
        action="store_true",
        help="do not insert the Codeforces test-case loop into the C++ template (default: off)",
    )
    parser.add_argument(
        "-f",
        "--files",
        help="range of problem files to create (default: A-H, e.g. A-D or C-F; can be a single letter). can be general ascii range, e.g. a-d or 1-5",
        default="A-H",
    )
    return parser.parse_args(argv)

def parse_files_arg(files_arg: str) -> list[str]:
    if "-" in files_arg:
        start, end = files_arg.split("-")
        return [chr(i) for i in range(ord(start), ord(end) + 1)]
    else:
        return [files_arg]

def main() -> None:
    args = parse_args()
    language = LANGUAGES[args.lang]

    if not WORKSPACE_PATH.is_dir():
        raise SystemExit(f"workspace directory not found: {WORKSPACE_PATH}")
    if not language.template.is_file():
        raise SystemExit(f"template not found: {language.template}")

    # Remove everything except the keep-list.  shutil.rmtree / Path.unlink
    # raise on failure, so errors are reported instead of silently swallowed.
    for entry in WORKSPACE_PATH.iterdir():
        if entry.name in KEEP:
            continue
        if entry.is_dir() and not entry.is_symlink():
            shutil.rmtree(entry)
        else:
            entry.unlink()
        print(f"removed {entry.name}")

    source = build_source(language, cf_test=not args.no_cf_test)

    # Recreate the problem files from the template.
    for name in parse_files_arg(args.files):
        path = WORKSPACE_PATH / f"{name}{language.extension}"
        path.write_text(source, encoding="utf-8")
        print(f"created {path.name}")

    # Recreate the placeholder files (empty).
    for name in PLACEHOLDER_FILES:
        path = WORKSPACE_PATH / name
        path.touch()
        print(f"created {path.name}")


if __name__ == "__main__":
    main()
