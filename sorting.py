import random

def SelectionSort(ar, size):
    for i in range(size-1):
        temp = i
        for j in range(i+1, size):
            if ar[j] < ar[temp]:
                temp = j
        temp = ar.pop(temp)
        ar.insert(i, temp)
    print("Your array now sorted!")
    print(ar)

def BubbleSort(ar, size):
    for i in range(size):
        for j in range(0, size-i-1):
            if ar[j] > ar[j+1]:
                ar[j], ar[j+1] = ar[j+1], ar[j]
    print("Your array now sorted!")
    print(ar)


def merge(ar, left, mid, right):
    n1 = mid - left + 1
    n2 = right - mid

    L = [0] * n1
    R = [0] * n2

    for i in range(n1):
        L[i] = ar[left + i]
    for j in range(n2):
        R[j] = ar[mid + 1 + j]
        
    i = 0  
    j = 0  
    k = left  

    while i < n1 and j < n2:
        if L[i] <= R[j]:
            ar[k] = L[i]
            i += 1
        else:
            ar[k] = R[j]
            j += 1
        k += 1

    while i < n1:
        ar[k] = L[i]
        i += 1
        k += 1

    while j < n2:
        ar[k] = R[j]
        j += 1
        k += 1

def MergeSort(ar, left, right):
    if left < right:
        mid = (left + right) // 2

        MergeSort(ar, left, mid)
        MergeSort(ar, mid + 1, right)
        merge(ar, left, mid, right)
    
def PasteSort(ar, size):
    for j in range(1, size):
        for i in range(j):
            el = ar[j]
            if ar[i]>=el:
                ar[j] = ar[i]
                ar[i] = el
    print("Your array now sorted!")
    print(ar)

def partition(ar, low, high):
    pivot = ar[high]
    i = low - 1
    for j in range(low, high, 1):
        if ar[j] <= pivot:
            i += 1
            ar[i], ar[j] = ar[j], ar[i]
    ar[i+1], ar[high] = ar[high], ar[i+1]
    return i+1

def QuickSort(ar, low, high):
    if low < high:
        pivotIndex = partition(ar, low, high)
        QuickSort(ar, low, pivotIndex - 1)
        QuickSort(ar, pivotIndex + 1, high)
            
def ShellSort(ar, n):
    gap = n // 2
    while gap > 0:
        for i in range(gap, n):
            temp = ar[i]   
            j = i
            while j >= gap and ar[j - gap] > temp:
                ar[j] = ar[j - gap]
                j -= gap
            ar[j] = temp
        gap //= 2
    print("Your array now sorted!")
    print(ar)

def ArrGen(size):
    ar = [0]*size
    for i in range(size):
        ar[i] = random.randint(1,20)
    print("Your new array:")
    print(ar)
    ChooseSortMethod(ar,size)

def ArrMan(size):
    ar = [0]*size
    for i in range(size):
        ar[i] = int(input(f"Element num {i+1}: "))
    ChooseSortMethod(ar,size)

def ChooseSortMethod(ar, size):
    choice = int(input("Now choose sorting alghorithm:\n1 - selection sort\n2 - bubble sort\n3 - merge sort\n4 - paste sort\n5 - quick sort\n6 - shell sort\n"))
    if choice == 1:
        SelectionSort(ar, size)
    elif choice == 2:
        BubbleSort(ar, size)
    elif choice == 3:
        MergeSort(ar, 0, size - 1)
        print("Your array now sorted!")
        print(ar)
    elif choice == 4:
        PasteSort(ar, size)
    elif choice == 5:
        QuickSort(ar, 0, size - 1)
        print("Your array now sorted!")
        print(ar)
    elif choice == 6:
        ShellSort(ar, size)
    else:
        print("Wrong option")

def Program():
    size = int(input("Enter size of an array: "))
    option = input("Should we generate arra(y), or enter it ma(n)ually? [y/n]: ")
    if option == 'y' or option == 'Y':
        ArrGen(size)
    elif option == 'n' or option == 'N':
        ArrMan(size)
    else:
        print("Invalid option selected.")
