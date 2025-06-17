
// Returns the index of the first element not less than x
fn bs<T: PartialOrd>(arr: &Vec<T>, x: T) -> usize {

    let mut hi: usize = arr.len();
    let mut lo: usize = 0;

    let mut mid = (hi + lo) / 2;

    while hi > lo {

        if arr[mid] >= x {
            hi = mid;
        } else {
            lo = mid + 1;
        }
        mid = (hi + lo) / 2;

    }
    mid
}

