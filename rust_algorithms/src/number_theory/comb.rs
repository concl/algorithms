const N: usize = 100_000; // Maximum value of n
const MOD: i64 = 1_000_000_007; // Modulus for calculations
static mut factorial: [i64; N + 1] = [0; N + 1]; // Factorial array
static mut inverse_factorial: [i64; N + 1] = [0; N + 1]; // Inverse factorial array

fn mod_pow(base: i64, exp: i64) -> i64 {
    let mut result = 1;
    let mut base = base % MOD;
    let mut exp = exp;
    
    while exp > 0 {
        if exp % 2 == 1 {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp /= 2;
    }
    
    result
}

fn inv(x: i64) -> i64 {
    mod_pow(x, MOD - 2)
}


fn calculate_factorial() {
    unsafe {
        factorial[0] = 1;
        for i in 1..=N {
            factorial[i] = (factorial[i - 1] * i as i64) % MOD;
        }
        
        inverse_factorial[N] = inv(factorial[N]);
        for i in (1..=N).rev() {
            inverse_factorial[i - 1] = (inverse_factorial[i] * i as i64) % MOD;
        }
    }
}

fn comb(n: i32, k: i32) -> i64 {
    unsafe {
        if n < k || k < 0 {
            return 0;
        }
        (factorial[n as usize] * inverse_factorial[k as usize] % MOD * inverse_factorial[(n - k) as usize] % MOD) % MOD
    }
}