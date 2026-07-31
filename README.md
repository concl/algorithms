# algorithms
This repository contains various algorithms and data structures implementations

Main Directory: General programs useful for various tasks, pdf template.

problems: Solutions to previous competitive programming problems.


## PDF code template

To build the template, run:
```
pdflatex -shell-escape template.tex
```
The command might need to be run twice to produce the final template.

## Tests

The test suite is pytest-based and targets the C++ implementations. Python tests drive compiled C++ "harnesses" through stdin/stdout and check the results against brute-force or NumPy reference solutions.

### Layout

```
tests/
├── conftest.py            # session-scoped fixtures: compile each harness once per run
├── helpers.py             # shared utilities (compile/run, random generators, brute-force oracles)
├── harnesses/             # C++ stdin/stdout drivers, one per implementation
│   ├── segment_tree_harness.cpp
│   ├── lazy_segment_tree_harness.cpp
│   ├── matrices_harness.cpp
│   └── binary_jumping_harness.cpp
├── data_structures/       # test_*.py modules grouped by category
├── graphs/
└── math/
```

Test modules are grouped by category (`data_structures/`, `graphs/`, `math/`), mirroring `cpp/` and `python/`. Each harness includes the implementation from `cpp/` (e.g. `segment_tree_harness.cpp` includes `cpp/data_structures/segment_tree.cpp`), reads commands from stdin, and writes one result per line to stdout. Harnesses are compiled once per pytest session by the `conftest.py` fixtures into `build/`; tests then pipe generated inputs into the same binary.

### Running

Requirements: `g++` on PATH and Python (>= 3.14). Install the test dependency:

```
uv sync --extra test        # or: pip install -e ".[test]"
```

Then run pytest — the root `pyproject.toml` already sets `testpaths`, discovery patterns, and default flags:

```
pytest                      # full suite
pytest tests/graphs         # one category
pytest tests/data_structures/test_segment_tree.py -k random   # one file / filtered tests
```

### Adding a new test

1. **Implementation** — put the algorithm in `cpp/<category>/<name>.cpp`.
2. **Harness** — write `tests/harnesses/<name>_harness.cpp`: `#include` the implementation, document the I/O format in a header comment (see the existing harnesses), parse stdin commands, and print one result per line.
3. **Fixture** — register the harness in `tests/conftest.py` with a session-scoped fixture that builds a `Harness("<name>_harness.cpp")` and calls `compile()`.
4. **Tests** — create `tests/<category>/test_<name>.py`. Build input strings, run them through the harness fixture, and compare against a reference: hand-computed values for small cases, brute-force or NumPy for randomized stress tests. Use the generators in `tests/helpers.py` (`random_array`, `random_tree`, ...) and `pytest.mark.parametrize` over sizes/seeds for coverage.

## Suggested Keybinds

Add `code_template/tasks.json` to .vscode to make the following keybinds work:

`ctrl+alt+r` - Run the current C++ file with the tester.py script on testcases in the workspace/input folder.
```
{
    "key": "ctrl+alt+r",
    "command": "workbench.action.tasks.runTask",
    "args": "Run c++ file with the tester.py script on testcases"
}
```

