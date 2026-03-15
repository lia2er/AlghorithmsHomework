def LinearSearch(ar, n, target):
    for i in range(n):
        if ar[i] == target:
            return i
    return -1        
def LinearSearchWithBarrier(ar, n, target):
    lastValue = target
    ar[n-1] = target

    i = 0
    while ar[i] != target:
        i += 1
    ar[n-1] = lastValue
    if i < n - 1 or ar[n-1] == target:
        return i
    else:
        return -1

def CheckReturn(result, target):
    if result != -1:
        print(f"Value {target} was found")
    else:
        print(f"Value {target} was`nt found")


