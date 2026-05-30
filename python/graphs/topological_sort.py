def topological_sort(graph: list[list[int]]) -> list[int]:

    n = len(graph)
    degree = [0] * n
    for node in graph:
        for neighbor in node:
            degree[neighbor] += 1

    q = [i for i, d in enumerate(degree) if d == 0]
    res = []
    while q:
        node = q.pop()
        res.append(node)

        for neighbor in graph[node]:
            degree[neighbor] -= 1
            if degree[neighbor] == 0:
                q.append(neighbor)

    return res if len(res) == n else []
