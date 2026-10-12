
import time
import os
from pathlib import Path
import subprocess

PATH = Path(__file__).parent
LATEX_FILE = PATH / "template.tex"


def compile_latex():
    subprocess.run(["pdflatex", "-interaction=nonstopmode", str(LATEX_FILE)])

def main():
    # compile the LaTeX file periodically
    while True:
        compile_latex()
        time.sleep(5)  # wait for 5 seconds before recompiling

if __name__ == "__main__":
    main()

