"""
Tests for Matrix (RREF, linear solve, inverse).

Uses numpy for reference solutions and the matrices_harness.cpp for C++ results.
"""

import numpy as np
import pytest
from tests.helpers import Harness


def _build_input(A: np.ndarray, b: np.ndarray) -> str:
    n = A.shape[0]
    lines = [str(n)]
    for i in range(n):
        lines.append(" ".join(f"{A[i, j]:.17g}" for j in range(n)))
    lines.append(" ".join(f"{b[i]:.17g}" for i in range(n)))
    return "\n".join(lines) + "\n"


def _run(matrices_harness: Harness, A: np.ndarray, b: np.ndarray):
    """Run the harness and return (solution x, inverse)."""
    result = matrices_harness.run(_build_input(A, b))
    out_lines = [line.strip() for line in result.stdout.splitlines() if line.strip()]
    n = A.shape[0]
    assert len(out_lines) == n + 1, (
        f"Expected {n+1} lines, got {len(out_lines)}\nstdout:\n{result.stdout}"
    )
    x = np.fromstring(out_lines[0], sep=" ")
    assert x.shape == (n,), f"Expected ({n},), got {x.shape}"
    inv_rows = [np.fromstring(out_lines[i + 1], sep=" ") for i in range(n)]
    inv = np.vstack(inv_rows)
    assert inv.shape == (n, n), f"Expected ({n},{n}), got {inv.shape}"
    return x, inv


def assert_solve(matrices_harness: Harness, A: np.ndarray, b: np.ndarray,
                 atol: float = 1e-7, rtol: float = 1e-7):
    x, inv = _run(matrices_harness, A, b)

    expected_x = np.linalg.solve(A, b)
    expected_inv = np.linalg.inv(A)

    assert np.allclose(x, expected_x, atol=atol, rtol=rtol), (
        f"Solve mismatch\nA=\n{A}\nb={b}\nexpected={expected_x}\ngot={x}"
    )
    assert np.allclose(A @ x, b, atol=atol, rtol=rtol), (
        f"Residual check failed\nA@x={A @ x}\nb={b}"
    )
    assert np.allclose(inv, expected_inv, atol=atol, rtol=rtol), (
        f"Inverse mismatch\nA=\n{A}\nexpected=\n{expected_inv}\ngot=\n{inv}"
    )
    eye = np.eye(A.shape[0])
    assert np.allclose(A @ inv, eye, atol=atol, rtol=rtol), "Right inverse check failed"
    assert np.allclose(inv @ A, eye, atol=atol, rtol=rtol), "Left inverse check failed"


class TestMatrices:
    """Core correctness tests."""

    def test_2x2_linear_system(self, matrices_harness: Harness):
        A = np.array([[2.0, 1.0], [1.0, 1.0]])
        b = np.array([5.0, 3.0])
        assert_solve(matrices_harness, A, b)

    def test_3x3_system(self, matrices_harness: Harness):
        A = np.array([
            [3.0, -1.0, 2.0],
            [2.0, 4.0, -1.0],
            [1.0, -3.0, 5.0],
        ])
        b = np.array([10.0, 1.0, -4.0])
        assert_solve(matrices_harness, A, b)

    def test_4x4_system(self, matrices_harness: Harness):
        A = np.array([
            [1.0, 2.0, 3.0, 4.0],
            [2.0, 1.0, 2.0, 3.0],
            [3.0, 2.0, 1.0, 2.0],
            [4.0, 3.0, 2.0, 1.0],
        ])
        b = np.array([30.0, 22.0, 18.0, 20.0])
        assert_solve(matrices_harness, A, b)

    def test_diagonal(self, matrices_harness: Harness):
        A = np.diag([2.0, 3.0, 5.0, 7.0])
        b = np.array([4.0, 9.0, 25.0, 49.0])
        assert_solve(matrices_harness, A, b)


class TestMatricesRandom:
    """Randomized tests."""

    @pytest.mark.parametrize("n,seed", [
        (2, 100), (3, 101), (5, 102), (8, 103),
    ])
    def test_random_invertible(self, matrices_harness: Harness, n: int, seed: int):
        rng = np.random.default_rng(seed)
        for _ in range(20):
            A = rng.integers(-9, 10, size=(n, n)).astype(np.float64)
            A += np.eye(n) * (n + 3)  # ensure invertible
            b = rng.integers(-20, 21, size=n).astype(np.float64)
            assert_solve(matrices_harness, A, b)

    @pytest.mark.parametrize("seed", [200, 201, 202])
    def test_near_singular(self, matrices_harness: Harness, seed: int):
        rng = np.random.default_rng(seed)
        for n in [3, 4, 5, 6]:
            for _ in range(5):
                A = rng.normal(size=(n, n))
                A += np.eye(n) * 1e-2
                b = rng.normal(size=n)
                if np.linalg.cond(A) < 1e10:
                    assert_solve(matrices_harness, A, b, atol=1e-5, rtol=1e-5)
