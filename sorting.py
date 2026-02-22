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
        swapped = False
        for j in range(0, size-i-1):
            if ar[j] > ar[j+1]:
                ar[j], ar[j+1] = ar[j+1], ar[j]
                swapped = True
        if (swapped == False):
            break
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
    
def InsertSort(ar, size):
    for i in range(1, size):
        key = ar[i]
        j = i - 1
        while j >= 0 and key < ar[j]:
            ar[j + 1] = ar[j]
            j -= 1
        ar[j + 1] = key
    print("Your array now sorted!")
    print(ar)

def ArrGen(size):
    ar = [0]*size
    for i in range(size):
        ar[i] = random.randint(1,20)
    print("Your new array:")
    print(ar)
    ChooseSort(ar,size)

def ArrMan(size):
    ar = [0]*size
    for i in range(size):
        ar[i] = int(input(f"Element num {i+1}: "))
    ChooseSort(ar,size)

def ChooseSort(ar, size):
    choice = input("Now choose sorting alghorithm:\ns - selection sort\nb - bubble sort\nm - merge sort\ni - insert sort\n")
    
    if choice == 's' or choice == 'S':
        SelectionSort(ar, size)
    elif choice == 'b' or choice == 'B':
        BubbleSort(ar, size)
    elif choice == 'm' or choice == 'M':
        MergeSort(ar, 0, size - 1)
        print("Your array now sorted!")
        print(ar)
    elif choice == 'i' or choice == 'I':
        InsertSort(ar, size)
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
