
import os
import time
import random
import subprocess

PATH = os.path.abspath(os.path.dirname(__file__))
CODE_FILE = "../cpp/data_structures/lazy_segment_tree.cpp"
EXECUTABLE_FILE = "../build/lazy_segment_tree"


def run_case(arr, queries, expected_answers):
    with open(os.path.join(PATH, "input.txt"), "w") as f:
        f.write(f"{len(arr)}\n")
        f.write(" ".join(map(str, arr)) + "\n")
        f.write(f"{len(queries)}\n")
        for query in queries:
            f.write(query + "\n")

    with open(os.path.join(PATH, "input.txt"), "r") as f:
        start = time.perf_counter()
        result = subprocess.run(
            [os.path.join(PATH, EXECUTABLE_FILE)],
            input=f.read(),
            text=True,
            capture_output=True,
        )
        end = time.perf_counter()

    assert result.returncode == 0, (
        f"Executable failed with code {result.returncode}\n"
        f"stderr:\n{result.stderr}\nstdout:\n{result.stdout}"
    )

    out = result.stdout.strip()
    if expected_answers:
        output_answers = [int(x) for x in out.splitlines() if x.strip()]
    else:
        output_answers = []
    assert output_answers == expected_answers, (
        f"Expected {expected_answers}, got {output_answers}\n"
        f"stderr:\n{result.stderr}"
    )
    return end - start

def test_only_queries():
    min = 0
    max = 10
    n = 10**2
    arr = [random.randint(min, max) for _ in range(n)]
    q = 10**2
    queries = []
    answers = []
    for _ in range(q):
        l = random.randint(0, n-1)
        r = random.randint(l + 1, n)
        queries.append(f"query {l} {r}")
        answers.append(sum(arr[l:r]))
    
    time_taken = run_case(arr, queries, answers)
    print(f"Test passed! Time taken: {time_taken:.2f} seconds")


def test_seeded_random():

    random.seed(42)

    min = -10**9
    max = 10**9
    n = 10**4
    q = 10**4


    arr = [random.randint(min, max) for _ in range(n)]
    original_arr = arr.copy()
    queries = []
    answers = []
    for _ in range(q):
        query_type = random.choice(["range_update", "query"])
        if query_type == "range_update":
            l = random.randint(0, n-1)
            r = random.randint(l + 1, n)
            value = random.randint(min, max)
            queries.append(f"range_update {l} {r} {value}")
            for i in range(l, r):
                arr[i] += value
        else:
            l = random.randint(0, n - 1)
            r = random.randint(l + 1, n)
            queries.append(f"query {l} {r}")
            answers.append(sum(arr[l:r]))


    time_taken = run_case(original_arr, queries, answers)

    print(f"Test passed! Time taken: {time_taken:.2f} seconds")


def test_single_element_boundaries():
    arr = [5]
    queries = [
        "query 0 1",
        "range_update 0 1 7",
        "query 0 1",
        "range_update 0 1 -20",
        "query 0 1",
    ]
    answers = [5, 12, -8]
    time_taken = run_case(arr, queries, answers)
    print(f"Test passed! Time taken: {time_taken:.2f} seconds")


def test_full_range_and_subranges():
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
    answers = [21, 81, 36, 45, 60, 21]
    time_taken = run_case(arr, queries, answers)
    print(f"Test passed! Time taken: {time_taken:.2f} seconds")


def test_overlapping_updates_then_queries():
    arr = [0, 0, 0, 0, 0, 0, 0, 0]
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
    answers = [47, 10, 16, 18, 3]
    time_taken = run_case(arr, queries, answers)
    print(f"Test passed! Time taken: {time_taken:.2f} seconds")


def test_repeated_same_range_updates():
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
    answers = [37, 17, 10, 10]
    time_taken = run_case(arr, queries, answers)
    print(f"Test passed! Time taken: {time_taken:.2f} seconds")



def run_tests():

    # make build
    result = os.system(f"g++ -o \"{os.path.join(PATH, EXECUTABLE_FILE)}\" \"{os.path.join(PATH, CODE_FILE)}\" -O2")
    print("Build result:", result)

    test_only_queries()
    test_single_element_boundaries()
    test_full_range_and_subranges()
    test_overlapping_updates_then_queries()
    test_repeated_same_range_updates()
    test_seeded_random()


if __name__ == "__main__":
    run_tests()
