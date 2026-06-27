"""
Run all tests using pytest.

Usage:
    python run_template_tests.py            # run all tests
    python run_template_tests.py -k "segment"  # filter by keyword
    python run_template_tests.py tests/math/   # run a specific directory
"""

import sys
import subprocess
import os

PATH = os.path.dirname(os.path.abspath(__file__))

# Forward all arguments to pytest
args = sys.argv[1:] if len(sys.argv) > 1 else []
cmd = [sys.executable, "-m", "pytest", *args]
print(f"Running: {' '.join(cmd)}")
result = subprocess.run(cmd, cwd=PATH)
sys.exit(result.returncode)

