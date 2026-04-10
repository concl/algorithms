import os
import subprocess
import tempfile
import numpy as np

PATH = os.path.abspath(os.path.dirname(__file__))
HARNESS_SRC = os.path.join(PATH, "matrices_harness.cpp")


def build_harness():
    fd, exe_path = tempfile.mkstemp(prefix="matrices_harness_", suffix=".exe", dir=PATH)
    os.close(fd)
    os.unlink(exe_path)

    compile_cmd = [
        "g++",
        "-std=c++17",
        "-O2",
        HARNESS_SRC,
        "-o",
        exe_path,
    ]
    result = subprocess.run(compile_cmd, text=True, capture_output=True)
    assert result.returncode == 0, (
        "Failed to build matrices harness\n"
        f"stdout:\n{result.stdout}\n"
        f"stderr:\n{result.stderr}"
    )
    return exe_path


def run_case(exe_path, A, b):
    n = A.shape[0]
    lines = [str(n)]
    for i in range(n):
        lines.append(" ".join(f"{A[i, j]:.17g}" for j in range(n)))
    lines.append(" ".join(f"{b[i]:.17g}" for i in range(n)))
    payload = "\n".join(lines) + "\n"

    result = subprocess.run(
        [exe_path],
        input=payload,
        text=True,
        capture_output=True,
    )
    assert result.returncode == 0, (
        f"Harness failed with code {result.returncode}\n"
        f"stdout:\n{result.stdout}\n"
        f"stderr:\n{result.stderr}"
    )

    out_lines = [line.strip() for line in result.stdout.splitlines() if line.strip()]
    assert len(out_lines) == n + 1, (
        f"Expected {n + 1} lines, got {len(out_lines)}\n"
        f"stdout:\n{result.stdout}\n"
        f"stderr:\n{result.stderr}"
    )

    x = np.fromstring(out_lines[0], sep=" ")
    assert x.shape[0] == n, f"Expected {n} solution entries, got {x.shape[0]}"

    inv_rows = [np.fromstring(out_lines[i + 1], sep=" ") for i in range(n)]
    inv = np.vstack(inv_rows)
    assert inv.shape == (n, n), f"Expected inverse shape {(n, n)}, got {inv.shape}"

    return x, inv


def assert_case(exe_path, A, b, atol=1e-7, rtol=1e-7):
    x, inv = run_case(exe_path, A, b)

    expected_x = np.linalg.solve(A, b)
    expected_inv = np.linalg.inv(A)

    assert np.allclose(x, expected_x, atol=atol, rtol=rtol), (
        "Linear solve mismatch\n"
        f"A=\n{A}\n"
        f"b={b}\n"
        f"expected={expected_x}\n"
        f"got={x}"
    )

    assert np.allclose(A @ x, b, atol=atol, rtol=rtol), (
        "Residual check failed for linear solve\n"
        f"A=\n{A}\n"
        f"b={b}\n"
        f"x={x}\n"
        f"A@x={A @ x}"
    )

    assert np.allclose(inv, expected_inv, atol=atol, rtol=rtol), (
        "Inverse mismatch\n"
        f"A=\n{A}\n"
        f"expected=\n{expected_inv}\n"
        f"got=\n{inv}"
    )

    eye = np.eye(A.shape[0])
    assert np.allclose(A @ inv, eye, atol=atol, rtol=rtol), (
        "Right inverse check failed\n"
        f"A@inv=\n{A @ inv}"
    )
    assert np.allclose(inv @ A, eye, atol=atol, rtol=rtol), (
        "Left inverse check failed\n"
        f"inv@A=\n{inv @ A}"
    )


def test_small_handcrafted(exe_path):
    A = np.array([[2.0, 1.0], [1.0, 1.0]], dtype=np.float64)
    b = np.array([5.0, 3.0], dtype=np.float64)
    assert_case(exe_path, A, b)

    A = np.array(
        [
            [3.0, -1.0, 2.0],
            [2.0, 4.0, -1.0],
            [1.0, -3.0, 5.0],
        ],
        dtype=np.float64,
    )
    b = np.array([10.0, 1.0, -4.0], dtype=np.float64)
    assert_case(exe_path, A, b)


def test_random_invertible(exe_path, seed=20260409):
    rng = np.random.default_rng(seed)

    for n in range(2, 9):
        for _ in range(30):
            A = rng.integers(-9, 10, size=(n, n)).astype(np.float64)
            A += np.eye(n) * (n + 3)
            b = rng.integers(-20, 21, size=n).astype(np.float64)
            assert_case(exe_path, A, b)


def test_near_singular_but_invertible(exe_path, seed=7):
    rng = np.random.default_rng(seed)

    for n in [3, 4, 5, 6]:
        for _ in range(10):
            A = rng.normal(size=(n, n))
            A += np.eye(n) * 1e-2
            b = rng.normal(size=n)
            if np.linalg.cond(A) < 1e10:
                assert_case(exe_path, A, b, atol=3e-6, rtol=3e-6)


def run_tests():
    exe_path = build_harness()
    try:
        test_small_handcrafted(exe_path)
        test_random_invertible(exe_path)
        test_near_singular_but_invertible(exe_path)
    finally:
        if os.path.exists(exe_path):
            os.remove(exe_path)

    print("All matrix solve/inverse tests passed")


if __name__ == "__main__":
    run_tests()
