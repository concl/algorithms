

def bs(arr, x, lower_bound=True):
    '''
    Arguments:
        arr: A sorted array of elements
        x: The element to search for
        lower_bound: If set to True, finds the first element >= x, else finds the first element > x
    Returns:
        The index of the found element, or the length of the array if not found
    '''

    hi = len(arr)
    lo = 0
    mid = (hi + lo) // 2

    while hi > lo:
        if (lower_bound and arr[mid] >= x) or (not lower_bound and arr[mid] > x):
            hi = mid
        else:
            lo = mid + 1
        mid = (hi + lo) // 2
    
    return mid


def main():

    return 0

if __name__ == "__main__":
    main()
