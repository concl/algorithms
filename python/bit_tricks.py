
def is_power_of_2(n):
    return (n & (n - 1) == 0)

def next_power_of_2(n):
    '''
    Returns the smallest power of 2 greater than or equal to n

    args:
        n: int >= 0
    '''

    return 1 << (n - 1).bit_length()

