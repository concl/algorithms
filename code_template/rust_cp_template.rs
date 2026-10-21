// Rust competitive-programming template.

#![allow(dead_code)]

use std::io::{self, Read, Write};
use std::collections::*;
use std::cmp::*;

/// Whitespace-token scanner over the whole of stdin.
struct Scanner {
    tokens: std::vec::IntoIter<String>,
}

impl Scanner {
    fn new() -> Self {
        let mut buf = String::new();
        io::stdin()
            .read_to_string(&mut buf)
            .expect("failed to read stdin");
        Self {
            tokens: buf
                .split_whitespace()
                .map(str::to_owned)
                .collect::<Vec<_>>()
                .into_iter(),
        }
    }

    /// Next token, parsed as `T`.
    fn next<T: std::str::FromStr>(&mut self) -> T {
        self.tokens
            .next()
            .expect("unexpected end of input")
            .parse()
            .ok()
            .expect("failed to parse token")
    }

    /// Next token as a `Vec<char>` (byte-safe for non-ASCII input).
    fn next_chars(&mut self) -> Vec<char> {
        self.next::<String>().chars().collect()
    }

    /// Next token as bytes, for byte-wise string processing.
    fn next_bytes(&mut self) -> Vec<u8> {
        self.next::<String>().into_bytes()
    }
}

#[allow(unused_variables)]
fn solve(scan: &mut Scanner, out: &mut impl Write) {
    
}

fn main() {
    let mut scan = Scanner::new();
    let stdout = io::stdout();
    let mut out = io::BufWriter::new(stdout.lock());

    // Multi-test input for CF
    // let t: usize = scan.next();
    // for _ in 0..t {
    //     solve(&mut scan, &mut out);
    // }

    solve(&mut scan, &mut out);
    out.flush().unwrap();
}
