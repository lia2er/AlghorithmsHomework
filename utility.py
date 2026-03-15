from sorting import *
from search import *

def ChooseSortMethod(ar, size):
    choice = int(input("Now choose sorting alghorithm:\n1 - selection sort\n2 - bubble sort\n3 - merge sort\n4 - paste sort\n5 - quick sort\n6 - shell sort\n7 - shaker sort\n8 - heap sort\n $ "))
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
    elif choice == 7:
        ShakerSort(ar, size)
    elif choice == 8:
        HeapSort(ar, size)
        print("Your array now sorted!")
        print(ar)
    else:
        print("Wrong option")

def ChooseSearchMethod(ar, size):
    target = int(input("Enter our target: "))
    choice = int(input("Now choose search method:\n1 - linear search\n2 - linear search with barrier\n $ "))
    if choice == 1:
        result = LinearSearch(ar, size, target)
        CheckReturn(result, target)
    elif choice == 2:
        result = LinearSearchWithBarrier(ar, size, target)
        CheckReturn(result, target)
    else:
        print("Wrong option")

def ChooseOperation(ar, size):
    option = int(input("What should we do:\n1 - sorting\n2 - search\n $ "))
    if option == 1:
        ChooseSortMethod(ar, size)
    elif option == 2:
        ChooseSearchMethod(ar, size)
    else:
        print("Wrong operation")

def CheckReturn(result, target):
    if result != -1:
        print(f"Value {target} was found")
    else:
        print(f"Value {target} was not found")

def ArrGen(size):
    ar = [0]*size
    for i in range(size):
        ar[i] = random.randint(1,20)
    print("Your new array:")
    print(ar)
    ChooseOperation(ar,size)

def ArrMan(size):
    ar = [0]*size
    for i in range(size):
        ar[i] = int(input(f"Element num {i+1}: "))
    ChooseOperation(ar,size)



def Program():
    size = int(input("Enter size of an array: "))
    option = input("Should we generate arra(y), or enter it ma(n)ually? [y/n]: ")
    if option == 'y' or option == 'Y':
        ArrGen(size)
    elif option == 'n' or option == 'N':
        ArrMan(size)
    else:
        print("Invalid option selected.")
