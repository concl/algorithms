
import time
import os

PATH = os.path.dirname(os.path.abspath(__file__))
LATEX_FILE = os.path.join(PATH, "template.tex")


def compile_latex():
    os.system(f"pdflatex -interaction=nonstopmode {LATEX_FILE}")

def main():
    # compile the LaTeX file periodically
    while True:
        compile_latex()
        time.sleep(5)  # wait for 5 seconds before recompiling

if __name__ == "__main__":
    main()

