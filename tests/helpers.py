"""
Shared test utilities: C++ compilation, execution, random data generation.

All tests use this module instead of writing their own build/run boilerplate.
"""

import subprocess
import tempfile
import os
import random
import time
from pathlib import Path
from typing import Optional
from contextlib import contextmanager

ROOT = Path(__file__).parent.parent.resolve()
CPP_DIR = ROOT / "cpp"
HARNESS_DIR = Path(__file__).parent / "harnesses"
BUILD_DIR = ROOT / "build"

# ── compilation ──────────────────────────────────────────────────────────────

def compile_cpp(
    source: Path,
    output_name: Optional[str] = None,
    flags: Optional[list[str]] = None,
) -> Path:
    """Compile a .cpp file and return the path to the executable.

    Args:
        source: Path to the .cpp file.
        output_name: Basename of the executable (without extension).
                     Defaults to source stem + '_exe'.
        flags: Extra compiler flags. Defaults to ['-std=c++17', '-O2'].

    Returns:
        Path to the compiled executable.
    """
    BUILD_DIR.mkdir(parents=True, exist_ok=True)

    if output_name is None:
        output_name = source.stem + "_exe"
    exe_path = BUILD_DIR / (output_name + (".exe" if os.name == "nt" else ""))

    if flags is None:
        flags = ["-std=c++17", "-O2"]

    cmd = ["g++", *flags, str(source), "-o", str(exe_path)]
    result = subprocess.run(cmd, text=True, capture_output=True)
    if result.returncode != 0:
        raise RuntimeError(
            f"Compilation failed for {source.name}\n"
            f"Command: {' '.join(cmd)}\n"
            f"stderr:\n{result.stderr}"
        )
    return exe_path


# ── execution ────────────────────────────────────────────────────────────────

def run_exe(
    exe: Path,
    input_str: str = "",
    timeout: float = 30.0,
) -> subprocess.CompletedProcess:
    """Run an executable with the given input string.

    Args:
        exe: Path to the executable.
        input_str: Text to pipe to stdin.
        timeout: Maximum seconds to wait.

    Returns:
        The completed process with .stdout, .stderr, .returncode.
    """
    result = subprocess.run(
        [str(exe)],
        input=input_str,
        text=True,
        capture_output=True,
        timeout=timeout,
    )
    if result.returncode != 0:
        raise RuntimeError(
            f"Executable {exe.name} failed with code {result.returncode}\n"
            f"stderr:\n{result.stderr}\n"
            f"stdout:\n{result.stdout}"
        )
    return result


# ── harness context manager ──────────────────────────────────────────────────

class Harness:
    """Manages the lifecycle of a compiled C++ harness."""

    def __init__(self, harness_filename: str, extra_flags: Optional[list[str]] = None):
        self.source = HARNESS_DIR / harness_filename
        self.exe: Optional[Path] = None
        self.extra_flags = extra_flags or []

    def compile(self) -> Path:
        if self.exe is None:
            self.exe = compile_cpp(self.source, flags=["-std=c++17", "-O2"] + self.extra_flags)
        return self.exe

    def run(self, input_str: str = "", timeout: float = 30.0) -> subprocess.CompletedProcess:
        if self.exe is None:
            self.compile()
        return run_exe(self.exe, input_str, timeout)


# ── random generators ────────────────────────────────────────────────────────

def random_array(n: int, lo: int = -10**9, hi: int = 10**9, seed: Optional[int] = None) -> list[int]:
    """Generate a list of n random integers in [lo, hi]."""
    rng = random.Random(seed)
    return [rng.randint(lo, hi) for _ in range(n)]


def random_tree(
    n: int,
    root: int = 0,
    seed: Optional[int] = None,
) -> list[list[int]]:
    """Generate a random rooted tree with n nodes (0-indexed).

    Returns an adjacency list.  The tree is built by attaching each node
    i (i >= 1) to a uniformly random node in [0, i-1], which guarantees
    a connected tree with the given root.

    Args:
        n: Number of nodes.
        root: Root of the tree (must be 0 ≤ root < n).
        seed: Random seed.

    Returns:
        Adjacency list: graph[u] = list of neighbors of u.
    """
    rng = random.Random(seed)
    adj = [[] for _ in range(n)]
    # Build tree by connecting each node i to a random earlier node
    order = list(range(n))
    rng.shuffle(order)
    # ensure root is first in some sense — simplest: just build naturally
    for i in range(1, n):
        parent = rng.randint(0, i - 1)
        u, v = order[i], order[parent]
        adj[u].append(v)
        adj[v].append(u)
    return adj


def tree_depths_and_parents(
    adj: list[list[int]],
    root: int = 0,
) -> tuple[list[int], list[int]]:
    """BFS to compute depth and parent for each node.

    Returns (depth, parent) where parent[root] = -1.
    """
    n = len(adj)
    depth = [-1] * n
    parent = [-1] * n
    depth[root] = 0
    q = [root]
    for u in q:
        for v in adj[u]:
            if depth[v] == -1:
                depth[v] = depth[u] + 1
                parent[v] = u
                q.append(v)
    return depth, parent


def brute_lca(
    parent: list[int],
    depth: list[int],
    u: int,
    v: int,
) -> int:
    """O(n) LCA by climbing the deeper node one step at a time."""
    while depth[u] > depth[v]:
        u = parent[u]
    while depth[v] > depth[u]:
        v = parent[v]
    while u != v:
        u = parent[u]
        v = parent[v]
    return u


def random_pairs(
    n: int,
    k: int,
    seed: Optional[int] = None,
) -> list[tuple[int, int]]:
    """Generate k random pairs (u, v) with 0 ≤ u, v < n."""
    rng = random.Random(seed)
    return [(rng.randint(0, n - 1), rng.randint(0, n - 1)) for _ in range(k)]
