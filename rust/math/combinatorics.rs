

const MOD: i64 = 1_000_000_007;

fn pow_mod(base: i64, exp: i64, modulus: i64) -> i64 {
    let mut res = 1;
    let mut b = base % modulus;
    let mut e = exp;

    while e > 0 {
        if e % 2 == 1 {
            res = (res * b) % modulus;
        }
        b = (b * b) % modulus;
        e /= 2;
    }
    res
}

fn inv(a: i64) -> i64 {
    pow_mod(a, MOD - 2, MOD)
}

fn factorial(factorial_table: &mut Vec<i64>, n: usize) -> i64 {
    if factorial_table.len() == 0 {
        factorial_table.push(1); // 0! = 1
    }

    for i in factorial_table.len()..=n {
        factorial_table.push((factorial_table[i - 1] * i as i64) % MOD);
    }
    factorial_table[n]
}

fn comb(factorial_table: &mut Vec<i64>, n: usize, k: usize) -> i64 {
    if k > n || k < 0 {
        return 0;
    }

    let numerator = factorial(factorial_table, n);
    let denominator = factorial_table[k] * factorial_table[n - k] % MOD;
    (numerator * inv(denominator)) % MOD
}
