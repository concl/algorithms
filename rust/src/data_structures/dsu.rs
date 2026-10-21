
/// Finds the representative element of the set a given node is a part of.
pub fn find(dsu: &mut Vec<usize>, node: usize) -> usize {
    if dsu[node] != node {
        dsu[node] = find(dsu, dsu[node]);
    }
    dsu[node]
}

pub fn union_sets(dsu: &mut Vec<usize>, sizes: &mut Vec<i32>, a: usize, b: usize) {

    let x = find(dsu, a);
    let y = find(dsu, b);
    if x == y {
        return;
    }
    
    if sizes[x] >= sizes[y] {
        sizes[x] += sizes[y];
        dsu[y] = x;
    } else {
        sizes[y] += sizes[x];
        dsu[x] = y;
    }
}


