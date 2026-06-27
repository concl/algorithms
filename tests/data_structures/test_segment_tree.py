"""
Tests for SegmentTree (point update, range sum query).
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


class TestSegmentTree:
    """Core correctness tests for SegmentTree."""

    def test_single_element(self, segment_tree_harness: Harness):
        arr = [42]
        queries = [
            "query 0 1",
            "update 0 99",
            "query 0 1",
        ]
        results = _run_queries(segment_tree_harness, arr, queries)
        assert results == [42, 99]

    def test_small_array(self, segment_tree_harness: Harness):
        arr = [1, 2, 3, 4, 5]
        queries = [
            "query 0 5",
            "query 1 4",
            "update 2 10",
            "query 1 4",
            "query 0 5",
        ]
        results = _run_queries(segment_tree_harness, arr, queries)
        assert results == [15, 9, 16, 22]

    def test_all_single_element_queries(self, segment_tree_harness: Harness):
        """Every single-element subarray."""
        arr = [3, -7, 2, 8, -5, 1]
        queries = [f"query {i} {i+1}" for i in range(len(arr))]
        results = _run_queries(segment_tree_harness, arr, queries)
        assert results == arr

    def test_update_and_query_interleaved(self, segment_tree_harness: Harness):
        arr = [0] * 10
        queries = [
            "update 3 5",
            "update 7 12",
            "query 0 10",
            "update 3 -2",
            "query 3 8",
            "query 0 10",
        ]
        results = _run_queries(segment_tree_harness, arr, queries)
        expected = [
            5 + 12,          # after two updates: sum = 17
            (-2) + 0 + 0 + 0 + 12,  # query [3,8): 10
            17 - 5 - 2,      # query [0,10): 10  (5 was replaced by -2)
        ]
        assert results == [17, 10, 10]


class TestSegmentTreeRandom:
    """Randomized stress tests comparing against brute force."""

    @pytest.mark.parametrize("n,seed", [
        (1, 1), (2, 2), (10, 3), (50, 4), (200, 5),
    ])
    def test_only_queries(self, segment_tree_harness: Harness, n: int, seed: int):
        """Range queries on a static array (no updates)."""
        arr = random_array(n, -1000, 1000, seed)
        rng = random.Random(seed + 1000)
        queries = []
        expected = []
        for _ in range(100):
            l = rng.randint(0, n - 1)
            r = rng.randint(l + 1, n)
            queries.append(f"query {l} {r}")
            expected.append(sum(arr[l:r]))
        results = _run_queries(segment_tree_harness, arr, queries)
        assert results == expected

    @pytest.mark.parametrize("n,seed", [
        (5, 10), (20, 11), (100, 12),
    ])
    def test_updates_and_queries(self, segment_tree_harness: Harness, n: int, seed: int):
        """Interleave random point updates and range queries."""
        arr = random_array(n, -100, 100, seed)
        rng = random.Random(seed + 2000)
        queries = []
        expected = []
        current = arr.copy()
        for _ in range(200):
            if rng.random() < 0.3:
                idx = rng.randint(0, n - 1)
                val = rng.randint(-200, 200)
                queries.append(f"update {idx} {val}")
                current[idx] = val
            else:
                l = rng.randint(0, n - 1)
                r = rng.randint(l + 1, n)
                queries.append(f"query {l} {r}")
                expected.append(sum(current[l:r]))
        results = _run_queries(segment_tree_harness, arr, queries)
        assert results == expected
