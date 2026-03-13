
from math import nan

def newtons_method(f, f_prime, x0, eps=1e-10, upper_bound=1e5):
    """
    Uses Newton's method to find the roots of the input function
    f, given its derivative f_prime and an initial guess

    Args:
        f (Callable[float, float]): The function for which we want to find a root
        f_prime (Callable[float, float]): The derivative of f
        x0 (float): The initial guess for the root
        eps (float): The algorithm terminates when f(x) < eps
        upper_bound (float): The algorithm terminates when f(x) > upper_bound

    Returns:
        tuple[float, int]: The first element is the root, and the second is the
        number of iterations. If the upper bound is surpassed, returns (NaN, -1)
    """

    it = 0
    x = x0
    while abs(f(x)) >= eps:
        if abs(f(x)) > upper_bound:
            return nan, -1

        x = x - f(x) / f_prime(x)
        it += 1
    
    return x, it




