
import os
import time
import random
import subprocess

PATH = os.path.abspath(os.path.dirname(__file__))
CODE_FILE = "../cpp/data_structures/lazy_segment_tree.cpp"
EXECUTABLE_FILE = "../builds/lazy_segment_tree"

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
    
    with open("input.txt", "w") as f:
        f.write(f"{n}\n")
        f.write(" ".join(map(str, arr)) + "\n")
        f.write(f"{q}\n")
        for query in queries:
            f.write(query + "\n")

    with open("input.txt", "r") as f:
        result = subprocess.run(
            [os.path.join(PATH, EXECUTABLE_FILE)], 
            input=f.read(), 
            text=True, 
            capture_output=True
        )

    output = result.stdout.strip().split("\n")
    output_answers = list(map(int, output))
    assert output_answers == answers, f"Expected {answers}, got {output_answers}"
    print("Test passed!")


def test_seeded_random():

    # random.seed(42)

    min = 0
    max = 10
    n = 10
    q = 10


    arr = [random.randint(min, max) for _ in range(n)]
    queries = []
    answers = []
    for _ in range(q):
        query_type = random.choice(["range_update", "query"])
        if query_type == "range_update":
            l = random.randint(5, n-1)
            r = random.randint(l + 1, n)
            value = random.randint(min, max)
            queries.append(f"range_update {l} {r} {value}")
            for i in range(l, r):
                arr[i] += value
            print(f"Range update: {queries[-1]}")
        else:
            l = random.randint(0, 3)
            r = random.randint(l + 1, 5)
            queries.append(f"query {l} {r}")
            answers.append(sum(arr[l:r]))
            print(f"Query: {queries[-1]}, Answer: {answers[-1]}")

    with open("input.txt", "w") as f:
        f.write(f"{n}\n")
        f.write(" ".join(map(str, arr)) + "\n")
        f.write(f"{q}\n")
        for query in queries:
            f.write(query + "\n")

    with open("input.txt", "r") as f:
        result = subprocess.run(
            [os.path.join(PATH, EXECUTABLE_FILE)], 
            input=f.read(), 
            text=True, 
            capture_output=True
        )
    
    output = result.stdout.strip().split("\n")
    output_answers = list(map(int, output))
    assert output_answers == answers, f"Expected {answers}, got {output_answers}"
    print("Test passed!")
    


def run_tests():

    # make build
    result = os.system(f"g++ -o {os.path.join(PATH, EXECUTABLE_FILE)} {os.path.join(PATH, CODE_FILE)} -O2")
    print("Build result:", result)

    test_only_queries()
    test_seeded_random()


if __name__ == "__main__":
    run_tests()
