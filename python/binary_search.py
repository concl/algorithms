
def bs(arr, x):

    hi = len(arr)
    lo = 0
    mid = (hi + lo) // 2

    while hi > lo:
        if arr[mid] >= x:
            hi = mid
        else:
            lo = mid + 1
        mid = (hi + lo) // 2
    
    return mid


def main():

    return 0

if __name__ == "__main__":
    main()
