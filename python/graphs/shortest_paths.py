
from heapq import heappop, heappush


def shortest_paths(graph: list[dict[int, int]], start: int) -> list[int]:
    
    n = len(graph)
    res = [float("inf")] * n
    res[start] = 0
    
    pq = [(0, start)]
    while pq:
        dist, node = heappop(pq)
        
        if dist >= res[node]:
            continue
        res[node] = dist
        
        for nbr, weight in graph[node].items():
            new_dist = dist + weight
            
            if new_dist < res[nbr]:
                heappush(pq, (new_dist, nbr))
    return res
