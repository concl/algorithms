
# Problem 98B
# Rating: 2200
# Note that CodeForces sucks for old problems, so this will TLE. (The asymptotic time complexity is ok)
# Instead of returning rationals mod p, this problem forces you to use a rational class with large precision
# ^ this is very stupid
# no way youre implementing karasuba multiplication in cpp

from fractions import Fraction

def ceil_div(a, b):
    """Compute ceil(a/b) for nonnegative integers a, b."""
    return (a + b - 1) // b

def log2_ceil(x):
    """
    Returns the smallest integer k such that 2^k >= x,
    assuming x > 0.
    """
    if x <= 1:
        return 0
    # (x-1).bit_length() is effectively ceil(log2(x))
    return (x - 1).bit_length()

def solve(n):
    exp = Fraction(0, 1)
    current_prob = Fraction(1, 1)

    # seen[residue] = index into state probabilities if we've seen 'residue' before
    seen = {1:0}
    flip_history = []
    additions = []
    fail_probs = []
    state_probs = [Fraction(1,1)]

    flipped = 0
    residue = 1

    while residue != 0:

        # Number of coin flips required given the residue
        flips = log2_ceil(ceil_div(n, residue))

        # Total number of flips
        flipped += flips
        flip_history.append(flipped)

        range_ = residue * (1 << flips)
        new_residue = range_ % n
        residue = new_residue

        # Probability of rolling a knight
        knight_prob = Fraction(n, range_)
        fail_prob = Fraction(1,1) - knight_prob

        # Add to the expected probability
        addition = current_prob * knight_prob * flipped

        exp += addition

        # Lower the probability
        current_prob *= fail_prob
        fail_probs.append(fail_prob)
        additions.append(addition)
        state_probs.append(current_prob)

        if new_residue in seen:
            start = seen[residue]
            state_prob = state_probs[start]
            flipped_before = 0
            if start - 1 >= 0:
                flipped_before = flip_history[start - 1]
            
            # Cost for 1 session
            expected_value = Fraction(0,1)

            # Probability that the session selects a knight
            r = 1 - (state_probs[-1] / state_prob)

            curr = Fraction(1,1)

            for i in range(start, len(state_probs) - 1):
                exp -= additions[i]
                flip_term = flip_history[i]
                if i - 1 >= 0:
                    flip_term -= flip_history[i - 1]
                expected_value += flip_term * curr
                curr *= fail_probs[i]

            exp += (expected_value / r) * state_prob + flipped_before * state_prob
            break
        seen[new_residue] = len(state_probs) - 1

    return exp

def main():
    n = int(input())

    answer = solve(n)
    print("{}/{}".format(answer.numerator, answer.denominator))

if __name__ == "__main__":
    main()