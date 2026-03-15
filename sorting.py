import random
from utility import *

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

def ShakerSort(ar, n):
    swapped = True
    while swapped:
        swapped = False
        for i in range(n - 1):
            if ar[i] > ar[i + 1]:
                ar[i], ar[i + 1] = ar[i + 1], ar[i]
                swapped = True
        if not swapped:
            break
        swapped = False
        for i in range(n - 1, 0, -1):
            if ar[i - 1] > ar[i]:
                ar[i - 1], ar[i] = ar[i], ar[i - 1]
                swapped = True
    print("Your array now sorted!")
    print(ar)

def heapify(arr, n, i):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2
    if l < n and arr[l] > arr[largest]:
        largest = l
    if r < n and arr[r] > arr[largest]:
        largest = r
    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]
        heapify(arr, n, largest)

def HeapSort(arr, n):
    for i in range(n // 2 - 1, -1, -1):
        heapify(arr, n, i)
    for i in range(n - 1, 0, -1):
        arr[0], arr[i] = arr[i], arr[0]
        heapify(arr, i, 0)

