
import subprocess
import os

path = os.path.dirname(__file__)
tests_path = os.path.join(path, "tests/")

for (dirpath, dirnames, filenames) in os.walk(tests_path):
    pass
