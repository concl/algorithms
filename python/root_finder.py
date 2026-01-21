
from typing import Callable


def bisection_method(f: Callable[[float], float], left: float, right: float, eps = 1e-6) -> tuple[int]:
    """
    Uses the bisection method to find a root of the input function given an interval.
    Stops when the residual reaches below eps.
    
    Args:
        f (Callable[[float], float]): The input function
        left (float): The left endpoint of the interval
        right (float): The right endpoint of the interval
        eps (float, optional): The desired accuracy. Defaults to 1e-6.
    
    Returns:
        tuple[int]: A tuple containing the root found and the number of iterations taken to find it.
    """

    if f(left) * f(right) > 0:
        raise ValueError("The function must have different signs at the endpoints.")

    iterations = 0
    root = (left + right) / 2

    while abs(f(root)) > eps:
        if f(root) == 0:
            return root, iterations
        elif f(left) * f(root) < 0:
            right = root
        else:
            left = root
        
        root = (left + right) / 2
        iterations += 1

    return root, iterations

def regula_falsi_method(f: Callable[[float], float], left: float, right: float, eps = 1e-6) -> tuple[int]:
    """
    Uses the regula falsi (false position) method to find a root of the input function given an interval.
    Stops when the residual reaches below eps.
    
    Args:
        f (Callable[[float], float]): The input function
        left (float): The left endpoint of the interval
        right (float): The right endpoint of the interval
        eps (float, optional): The desired accuracy. Defaults to 1e-6.
    
    Returns:
        tuple[int]: A tuple containing the root found and the number of iterations taken to find it.
    """

    if f(left) * f(right) > 0:
        raise ValueError("The function must have different signs at the endpoints.")


    iterations = 0
    root = right - (f(right) * (left - right)) / (f(left) - f(right))
    while abs(f(root)) >= eps:
        if f(left) * f(root) < 0:
            right = root
        else:
            left = root
        root = right - (f(right) * (left - right)) / (f(left) - f(right))
        iterations += 1

    return root, iterations





def main():

    example = lambda x : (x - 1) * (x - 2) * (x - 3)
    left = 1.75
    right = 2.95

    root_bisection, iterations_bisection = bisection_method(example, left, right)
    print(f"Bisection Method: Root = {root_bisection}, Iterations = {iterations_bisection}")

    root_regula_falsi, iterations_regula_falsi = regula_falsi_method(example, left, right)
    print(f"Regula Falsi Method: Root = {root_regula_falsi}, Iterations = {iterations_regula_falsi}")

    example2 = lambda x : x**6 - x - 1

    left1 = 1.0
    right1 = 1.2

    root_bisection2, iterations_bisection2 = bisection_method(example2, left1, right1)
    print(f"Bisection Method (Example 2): Root = {root_bisection2}, Iterations = {iterations_bisection2}")
    root_regula_falsi2, iterations_regula_falsi2 = regula_falsi_method(example2, left1, right1)
    print(f"Regula Falsi Method (Example 2): Root = {root_regula_falsi2}, Iterations = {iterations_regula_falsi2}")

    left2 = 1.0
    right2 = 2.0
    root_bisection3, iterations_bisection3 = bisection_method(example2, left2, right2)
    print(f"Bisection Method (Example 2, wider interval): Root = {root_bisection3}, Iterations = {iterations_bisection3}")
    root_regula_falsi3, iterations_regula_falsi3 = regula_falsi_method(example2, left2, right2)
    print(f"Regula Falsi Method (Example 2, wider interval): Root = {root_regula_falsi3}, Iterations = {iterations_regula_falsi3}")




if __name__ == "__main__":
    main()