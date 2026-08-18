"""Reset the contest workspace.

Wipes everything in workspace/ (except .gitignore) and recreates the
A-H.cpp problem files from the contest template, plus placeholder
input/output files.  Only writes inside workspace/.

By default the Codeforces test-case loop ("cf_test" snippet) is added to
main() of each problem file; pass --no-cf-test to write the template
verbatim.
"""

import argparse
import shutil
from pathlib import Path

WORKSPACE_PATH = Path(__file__).parent / "workspace"
CP_TEMPLATE_PATH = Path(__file__).parent / "code_template" / "cp_template.cpp"

# Files always kept during cleanup.
KEEP = {".gitignore"}

# Problem files created from the contest template.
PROBLEM_FILES = ["A.cpp", "B.cpp", "C.cpp", "D.cpp", "E.cpp", "F.cpp", "G.cpp", "H.cpp"]

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


def build_source(template: str, cf_test: bool) -> str:
    """Return the problem-file source: the template, optionally with the
    cf-test loop inserted into main()."""
    if not cf_test:
        return template
    lines = template.splitlines()
    if "    int t;" in lines:
        return template  # already inserted
    try:
        idx = lines.index("    cin.tie(NULL);")
    except ValueError:
        print("warning: could not find 'cin.tie(NULL);' in the template; skipping cf-test snippet")
        return template
    # Insert mid-body: right after the fast-io setup, replacing the blank
    # lines that follow it.
    j = idx + 1
    while j < len(lines) and lines[j].strip() == "":
        j += 1
    lines[idx + 1:j] = CF_TEST_SNIPPET
    return "\n".join(lines) + "\n"


def parse_args(argv: list[str] | None = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--cf-test",
        action=argparse.BooleanOptionalAction,
        default=True,
        help="add the Codeforces test-case loop to main() of each problem file (default: on)",
    )
    return parser.parse_args(argv)


def main() -> None:
    args = parse_args()

    if not WORKSPACE_PATH.is_dir():
        raise SystemExit(f"workspace directory not found: {WORKSPACE_PATH}")
    if not CP_TEMPLATE_PATH.is_file():
        raise SystemExit(f"template not found: {CP_TEMPLATE_PATH}")

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

    source = build_source(CP_TEMPLATE_PATH.read_text(), args.cf_test)

    # Recreate the problem files from the template.
    for name in PROBLEM_FILES:
        path = WORKSPACE_PATH / name
        if not path.exists():
            path.write_text(source)
            print(f"created {name}")

    # Recreate the placeholder files (empty).
    for name in PLACEHOLDER_FILES:
        path = WORKSPACE_PATH / name
        if not path.exists():
            path.touch()
            print(f"created {name}")


if __name__ == "__main__":
    main()
