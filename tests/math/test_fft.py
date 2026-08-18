"""
Tests for FFT (forward DFT via cpp/math/fft.cpp).

The C++ ``fft`` returns the N-point DFT with a positive-exponent kernel,

    A[k] = sum_j a[j] * exp(2*pi*i*j*k/N),

where N is the next power of two >= n (and N = 1 when n == 1).  NumPy's
``ifft`` uses the same positive-exponent kernel divided by N, so the reference
is ``N * np.fft.ifft(padded)``.
"""

import re

import numpy as np
import pytest

from tests.helpers import Harness


def _fft_length(n: int) -> int:
    """Length of the FFT output for an input of length n."""
    if n <= 1:
        return 1
    return 1 << (int(np.log2(n - 1)) + 1)


def _build_input(a: np.ndarray) -> str:
    a = np.asarray(a, dtype=np.float64)
    lines = [str(a.size)]
    lines.append(" ".join(f"{x:.17g}" for x in a))
    return "\n".join(lines) + "\n"


_FLOAT = r"[-+]?(?:\d+\.?\d*|\.\d+)(?:[eE][-+]?\d+)?"
_TOKEN = re.compile(rf"\(\s*({_FLOAT})\s*,\s*({_FLOAT})\s*\)")


def _parse_dft(stdout: str) -> np.ndarray:
    """Parse the harness output (space-separated ``(x, y)`` pairs)."""
    values = []
    for tok in stdout.split():
        m = _TOKEN.fullmatch(tok)
        assert m, f"Unparseable DFT token: {tok!r}"
        values.append(complex(float(m.group(1)), float(m.group(2))))
    return np.asarray(values, dtype=np.complex128)


def _run(fft_harness: Harness, a: np.ndarray) -> np.ndarray:
    result = fft_harness.run(_build_input(a))
    return _parse_dft(result.stdout)


def _reference(a: np.ndarray) -> np.ndarray:
    a = np.asarray(a, dtype=np.float64)
    n = a.size
    n_fft = _fft_length(n)
    padded = np.zeros(n_fft, dtype=np.complex128)
    padded[:n] = a
    return n_fft * np.fft.ifft(padded)


def assert_fft(fft_harness: Harness, a, atol: float = 1e-8, rtol: float = 1e-8):
    a = np.asarray(a, dtype=np.float64)
    got = _run(fft_harness, a)
    expected = _reference(a)
    assert got.shape == expected.shape, (
        f"Expected output length {expected.size}, got {got.size}"
    )
    assert np.allclose(got, expected, atol=atol, rtol=rtol), (
        f"DFT mismatch\ninput={a}\nexpected={expected}\ngot={got}"
    )


class TestFFT:
    """Small hand-verifiable cases."""

    def test_single_element(self, fft_harness: Harness):
        assert_fft(fft_harness, [3.5])

    def test_two_elements(self, fft_harness: Harness):
        assert_fft(fft_harness, [1.0, 2.0])

    def test_three_elements_padded(self, fft_harness: Harness):
        assert_fft(fft_harness, [1.0, 2.0, 3.0])

    def test_four_elements(self, fft_harness: Harness):
        assert_fft(fft_harness, [1.0, -2.0, 3.0, -4.0])

    def test_power_of_two(self, fft_harness: Harness):
        assert_fft(fft_harness, [2.0, -1.0, 3.0, 0.5, -3.5, 4.0, 1.0, -2.0])

    def test_non_power_of_two(self, fft_harness: Harness):
        assert_fft(fft_harness, [0.5, -1.25, 2.0, 3.75, -4.0, 5.0, 6.5])

    def test_zeros(self, fft_harness: Harness):
        assert_fft(fft_harness, [0.0] * 8)

    def test_delta(self, fft_harness: Harness):
        # DFT of a unit impulse is the all-ones vector.
        assert_fft(fft_harness, [1.0] + [0.0] * 7)

    def test_constant(self, fft_harness: Harness):
        assert_fft(fft_harness, [2.0] * 8)

    def test_output_length_padded(self, fft_harness: Harness):
        got = _run(fft_harness, np.array([1.0, 2.0, 3.0]))
        assert got.size == 4

    def test_linearity(self, fft_harness: Harness):
        a = np.array([1.0, -2.0, 3.0, 4.0])
        b = np.array([5.0, 0.5, -1.0, 2.0])
        got = _run(fft_harness, a + b)
        got_a = _run(fft_harness, a)
        got_b = _run(fft_harness, b)
        assert np.allclose(got, got_a + got_b, atol=1e-8, rtol=1e-8)


class TestFFTRandom:
    """Randomized tests across power-of-two and non-power-of-two sizes."""

    @pytest.mark.parametrize("n,seed", [
        (1, 300), (2, 301), (3, 302), (4, 303),
        (5, 304), (7, 305), (8, 306), (16, 307),
        (31, 308), (32, 309), (33, 310), (64, 311),
        (100, 312), (128, 313), (129, 314), (200, 315),
    ])
    def test_random(self, fft_harness: Harness, n: int, seed: int):
        rng = np.random.default_rng(seed)
        for _ in range(5):
            a = rng.uniform(-100.0, 100.0, size=n)
            assert_fft(fft_harness, a)

    @pytest.mark.parametrize("n,seed", [
        (16, 400), (64, 401), (256, 402),
    ])
    def test_random_integers(self, fft_harness: Harness, n: int, seed: int):
        rng = np.random.default_rng(seed)
        a = rng.integers(-1000, 1001, size=n).astype(np.float64)
        assert_fft(fft_harness, a)
