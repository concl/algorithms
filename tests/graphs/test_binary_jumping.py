"""
Tests for Binary Jumping (binary lifting / LCA).

Strategy:
  1. Test the preprocessing jump table directly against known values.
  2. Test LCA against a brute-force LCA on random trees.
"""

import random
import pytest
from tests.helpers import (
    Harness,
    random_tree,
    tree_depths_and_parents,
    brute_lca,
    random_pairs,
)


def _make_input(adj: list[list[int]], root: int,
                queries: list[tuple[int, int]]) -> str:
    """Build the input string for the binary_jumping_harness."""
    n = len(adj)
    lines = [f"{n} {root}"]
    # Emit each undirected edge once
    seen = set()
    for u in range(n):
        for v in adj[u]:
            if (v, u) not in seen:
                seen.add((u, v))
                lines.append(f"{u} {v}")
    lines.append(str(len(queries)))
    for a, b in queries:
        lines.append(f"{a} {b}")
    return "\n".join(lines) + "\n"


def _run_lca_queries(
    harness: Harness,
    adj: list[list[int]],
    root: int,
    queries: list[tuple[int, int]],
) -> list[int]:
    result = harness.run(_make_input(adj, root, queries))
    out = result.stdout.strip()
    if not out:
        return []
    return [int(x) for x in out.splitlines()]


class TestBinaryJumping:
    """Hand-crafted tests with known answers."""

    #  Tree:
    #     0
    #    / \
    #   1   2
    #  / \
    # 3   4
    #     |
    #     5
    LINE_TREE_ADJ = [
        [1, 2],       # 0
        [0, 3, 4],    # 1
        [0],          # 2
        [1],          # 3
        [1, 5],       # 4
        [4],          # 5
    ]

    @pytest.mark.parametrize("u,v,expected", [
        (3, 5, 1),   # LCA of leaves in left subtree = 1
        (3, 2, 0),   # LCA of left leaf and right leaf = 0
        (5, 4, 4),   # LCA of node and its parent = parent
        (3, 3, 3),   # LCA of node with itself = node
        (1, 5, 1),   # LCA of internal and leaf = 1
        (0, 5, 0),   # LCA of root and anything = root
        (2, 2, 2),   # self
        (3, 4, 1),   # siblings
    ])
    def test_line_tree(self, binary_jumping_harness: Harness,
                       u: int, v: int, expected: int):
        result = _run_lca_queries(
            binary_jumping_harness,
            self.LINE_TREE_ADJ, 0,
            [(u, v)],
        )
        assert result[0] == expected, (
            f"LCA({u}, {v}) = {result[0]}, expected {expected}"
        )

    def test_star_tree(self, binary_jumping_harness: Harness):
        """Root 0 connected to all others: LCA of any two leaves is 0."""
        n = 20
        adj = [[] for _ in range(n)]
        for i in range(1, n):
            adj[0].append(i)
            adj[i].append(0)
        queries = [(1, 2), (5, 10), (19, 3), (0, 7), (7, 7)]
        expected = [0, 0, 0, 0, 7]
        result = _run_lca_queries(binary_jumping_harness, adj, 0, queries)
        assert result == expected

    def test_chain(self, binary_jumping_harness: Harness):
        """0-1-2-3-4-5 linear chain."""
        n = 6
        adj = [[] for _ in range(n)]
        for i in range(n - 1):
            adj[i].append(i + 1)
            adj[i + 1].append(i)
        queries = [
            (5, 5), (0, 5), (4, 5), (2, 3),
            (1, 5), (0, 3), (3, 5),
        ]
        expected = [5, 0, 4, 2, 1, 0, 3]
        result = _run_lca_queries(binary_jumping_harness, adj, 0, queries)
        assert result == expected

    def test_binary_tree(self, binary_jumping_harness: Harness):
        """Complete binary tree with 7 nodes (0-6, root 0)."""
        adj = [
            [1, 2],       # 0
            [0, 3, 4],    # 1
            [0, 5, 6],    # 2
            [1],          # 3
            [1],          # 4
            [2],          # 5
            [2],          # 6
        ]
        queries = [
            (3, 4), (3, 5), (3, 6),
            (5, 6), (1, 5), (3, 1),
        ]
        expected = [1, 0, 0, 2, 0, 1]
        result = _run_lca_queries(binary_jumping_harness, adj, 0, queries)
        assert result == expected


class TestBinaryJumpingRandom:
    """Random tree tests comparing against brute-force LCA."""

    @pytest.mark.parametrize("n,seed", [
        (5, 1), (10, 2), (50, 3), (200, 4), (500, 5),
    ])
    def test_random_trees(self, binary_jumping_harness: Harness,
                          n: int, seed: int):
        adj = random_tree(n, root=0, seed=seed)
        _, parent = tree_depths_and_parents(adj, root=0)
        depth, _ = tree_depths_and_parents(adj, root=0)

        queries = random_pairs(n, k=min(200, n * 4), seed=seed + 1000)
        expected = [brute_lca(parent, depth, u, v) for u, v in queries]

        result = _run_lca_queries(binary_jumping_harness, adj, 0, queries)
        assert len(result) == len(expected), (
            f"Got {len(result)} results, expected {len(expected)}"
        )
        for i, (got, exp) in enumerate(zip(result, expected)):
            u, v = queries[i]
            assert got == exp, (
                f"Mismatch at query {i}: LCA({u},{v}) = {got}, expected {exp}\n"
                f"tree: n={n}, seed={seed}"
            )

    @pytest.mark.parametrize("seed", [10, 20, 30])
    def test_large_trees(self, binary_jumping_harness: Harness, seed: int):
        """Larger trees to catch performance or scaling issues."""
        n = 2000
        adj = random_tree(n, root=0, seed=seed)
        _, parent = tree_depths_and_parents(adj, root=0)
        depth, _ = tree_depths_and_parents(adj, root=0)

        queries = random_pairs(n, k=100, seed=seed + 5000)
        expected = [brute_lca(parent, depth, u, v) for u, v in queries]

        result = _run_lca_queries(binary_jumping_harness, adj, 0, queries)
        assert result == expected

    @pytest.mark.parametrize("seed", [100, 101, 102])
    def test_different_roots(self, binary_jumping_harness: Harness, seed: int):
        """Test with roots other than 0."""
        n = 50
        rng = random.Random(seed + 10000)
        root = rng.randint(0, n - 1)
        adj = random_tree(n, root=root, seed=seed)
        depth, parent = tree_depths_and_parents(adj, root=root)

        queries = random_pairs(n, k=100, seed=seed + 20000)
        expected = [brute_lca(parent, depth, u, v) for u, v in queries]

        result = _run_lca_queries(binary_jumping_harness, adj, root, queries)
        assert result == expected
