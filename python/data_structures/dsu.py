
def find(parent, i):
    if parent[i] == i:
        return i
    parent[i] = find(parent, parent[i])
    return parent[i]

def union_sets(parent, sizes, x, y):
    x = find(parent, x)
    y = find(parent, y)

    if x == y: return

    if sizes[x] < sizes[y]:
        x, y = y, x
    parent[y] = x
    sizes[x] += sizes[y]

