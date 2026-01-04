
// use std::collections::Vec;

// Returns a vector where each index i stores a prime factor of i.
// The vector contains all numbers up to and including n.
// 0 and 1 should be ignored
fn factors(n: usize) -> Vec<i32> {

    let mut res: Vec<i32> = (0..(n as i32 + 1)).collect::<Vec<i32>>();

    for i in 2..=n {

        if res[i] == i as i32 {
            for j in ((i * i)..=n).step_by(i) {
                res[j] = i as i32;
            }
        }
    }
    res
}
