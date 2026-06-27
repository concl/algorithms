"""
pytest fixtures: compiled C++ harnesses shared across all test modules.

Each fixture compiles a harness once per test session (scope="session"),
so repeated test functions reuse the same binary.
"""

import pytest
from pathlib import Path

from .helpers import Harness

HARNESS_DIR = Path(__file__).parent / "harnesses"


@pytest.fixture(scope="session")
def segment_tree_harness() -> Harness:
    """Segment tree: supports point update and range query."""
    h = Harness("segment_tree_harness.cpp")
    h.compile()
    return h


@pytest.fixture(scope="session")
def lazy_segment_tree_harness() -> Harness:
    """Lazy segment tree: range add update and range sum query."""
    h = Harness("lazy_segment_tree_harness.cpp")
    h.compile()
    return h


@pytest.fixture(scope="session")
def matrices_harness() -> Harness:
    """Matrices: solves linear system Ax=b and computes inverse via RREF."""
    h = Harness("matrices_harness.cpp")
    h.compile()
    return h


@pytest.fixture(scope="session")
def binary_jumping_harness() -> Harness:
    """Binary jumping: builds jump table and answers LCA queries."""
    h = Harness("binary_jumping_harness.cpp")
    h.compile()
    return h
