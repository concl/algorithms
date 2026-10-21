
// creates a partial match table using the KMP algorithm
fn create_pmt(pattern: &str) -> Vec<usize> {
    let n = pattern.len();
    
    let patt: Vec<char> = pattern.chars().collect();
    let mut pmt = vec![0; n];
    let mut j = 0;
    for i in 1..n {
        while j > 0 && patt[i] != patt[j] {
            j = pmt[j - 1];
        }
        if (patt[i] == patt[j]) {
            j += 1;
        }
        pmt[i] = j;
    }
    pmt
}

