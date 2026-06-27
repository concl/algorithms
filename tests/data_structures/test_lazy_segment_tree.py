"""
Tests for LazySegmentTree (range add, range sum query).
"""

import random
import pytest
from tests.helpers import random_array, Harness


def _make_input(arr: list[int], queries: list[str]) -> str:
    lines = [str(len(arr)), " ".join(map(str, arr)), str(len(queries))]
    lines.extend(queries)
    return "\n".join(lines) + "\n"


def _run_queries(harness: Harness, arr: list[int], queries: list[str]) -> list[int]:
    result = harness.run(_make_input(arr, queries))
    out = result.stdout.strip()
    if not out:
        return []
    return [int(x) for x in out.splitlines()]


class TestLazySegmentTree:
    """Core correctness tests."""

    def test_single_element(self, lazy_segment_tree_harness: Harness):
        arr = [5]
        queries = [
            "query 0 1",
            "range_update 0 1 7",
            "query 0 1",
            "range_update 0 1 -20",
            "query 0 1",
        ]
        results = _run_queries(lazy_segment_tree_harness, arr, queries)
        assert results == [5, 12, -8]

    def test_full_range_and_subranges(self, lazy_segment_tree_harness: Harness):
        arr = [1, 2, 3, 4, 5, 6]
        queries = [
            "query 0 6",
            "range_update 0 6 10",
            "query 0 6",
            "query 0 3",
            "query 3 6",
            "range_update 2 5 -7",
            "query 0 6",
            "query 2 5",
        ]
        results = _run_queries(lazy_segment_tree_harness, arr, queries)
        assert results == [21, 81, 36, 45, 60, 21]

    def test_overlapping_updates(self, lazy_segment_tree_harness: Harness):
        arr = [0] * 8
        queries = [
            "range_update 0 8 5",
            "range_update 2 7 3",
            "range_update 4 8 -2",
            "query 0 8",
            "query 0 2",
            "query 2 4",
            "query 4 7",
            "query 7 8",
        ]
        results = _run_queries(lazy_segment_tree_harness, arr, queries)
        assert results == [47, 10, 16, 18, 3]

    def test_repeated_same_range(self, lazy_segment_tree_harness: Harness):
        arr = [10, -10, 10, -10, 10]
        queries = [
            "range_update 1 4 6",
            "range_update 1 4 6",
            "range_update 1 4 -3",
            "query 0 5",
            "query 1 4",
            "query 0 1",
            "query 4 5",
        ]
        results = _run_queries(lazy_segment_tree_harness, arr, queries)
        assert results == [37, 17, 10, 10]


class TestLazySegmentTreeRandom:
    """Randomized stress tests."""

    @pytest.mark.parametrize("n,q,seed", [
        (10, 100, 1),
        (50, 300, 2),
        (200, 500, 3),
    ])
    def test_random_ops(
        self, lazy_segment_tree_harness: Harness,
        n: int, q: int, seed: int,
    ):
        arr = random_array(n, -10**6, 10**6, seed)
        rng = random.Random(seed + 10000)
        queries = []
        expected = []
        current = arr.copy()

        for _ in range(q):
            if rng.random() < 0.5:
                l = rng.randint(0, n - 1)
                r = rng.randint(l + 1, n)
                val = rng.randint(-10**6, 10**6)
                queries.append(f"range_update {l} {r} {val}")
                for i in range(l, r):
                    current[i] += val
            else:
                l = rng.randint(0, n - 1)
                r = rng.randint(l + 1, n)
                queries.append(f"query {l} {r}")
                expected.append(sum(current[l:r]))

        results = _run_queries(lazy_segment_tree_harness, arr, queries)
        assert results == expected

    @pytest.mark.parametrize("seed", [10, 11, 20])
    def test_only_updates_then_queries(self, lazy_segment_tree_harness: Harness, seed: int):
        """Apply all updates first, then ask all queries."""
        n = 100
        arr = random_array(n, -100, 100, seed)
        rng = random.Random(seed + 20000)
        current = arr.copy()
        queries = []

        # 100 range updates
        for _ in range(100):
            l = rng.randint(0, n - 1)
            r = rng.randint(l + 1, n)
            val = rng.randint(-100, 100)
            queries.append(f"range_update {l} {r} {val}")
            for i in range(l, r):
                current[i] += val

        # 50 range queries
        expected = []
        for _ in range(50):
            l = rng.randint(0, n - 1)
            r = rng.randint(l + 1, n)
            queries.append(f"query {l} {r}")
            expected.append(sum(current[l:r]))

        results = _run_queries(lazy_segment_tree_harness, arr, queries)
        assert results == expected
