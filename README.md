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

