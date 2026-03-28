
import subprocess
import os

PATH = os.path.dirname(__file__)
TESTS = os.path.join(PATH, "tests/")

for (dirpath, dirnames, filenames) in os.walk(TESTS):
    for filename in filenames:
        if filename.endswith(".py") and not filename.startswith("test_"):
            continue
        if filename.endswith(".py") and filename.startswith("test_"):
            print(f"Running {filename}...")
            subprocess.run(["python", os.path.join(dirpath, filename)], check=True)

