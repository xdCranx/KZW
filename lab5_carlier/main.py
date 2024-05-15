import copy
import time
import schrages
import heaps


def LoadData(filename):
    with open(filename, 'r') as file:
        file = file.readlines()
    dataset = {}
    while file:
        line = file.pop(0)
        if line.startswith("data."):
            num = line.split('data.')[1].strip(':\n')
            dataset[num] = {}
            i = int(file.pop(0))
            dataset[num]["tasks"] = {}
            for i in range(i):
                dataset[num]["tasks"][i] = list(map(int, file.pop(0).split()))

            while file and not line.startswith("carl"):
                line = file.pop(0)

            if not file:
                break

            dataset[num]["carl"] = []

            while file and line != "\n":
                line = file.pop(0)
                dataset[num]["carl"].extend(
                    list(map(int, line.split()))
                )
    return dataset

def FindA(lst, B, c_max):
    sum_val =0
    A = 0
    for i in range(0, B + 1):
        sum_val += lst[i][1]

    while A < B and not c_max == (lst[A][0] + lst[B][2] + sum_val):
        sum_val -= lst[A][1]
        A += 1
    return A

def FindC(list, A, B):
    for i in range(B - 1, A - 1, -1):
        if list[i][2] < list[B][2]:
            return i
    return None

def FindPath(subSet, B, C):
    r2 = subSet[C + 1][0]
    p2 = 0
    q2 = subSet[C + 1][2]

    for i in range(C + 1, B + 1):
        if subSet[i][2] < q2:
            q2 = subSet[i][2]

        if subSet[i][0] < r2:
            r2 = subSet[i][0]

        p2 += subSet[i][1]

    return r2, p2, q2

def Carlier(list):
    algotime = 0.15
    heap = heaps.Heap()
    solStart = schrages.Schrage(copy.deepcopy(list))
    lowerBoundStart = schrages.PrmtSchrage(copy.deepcopy(list))
    heap.PushItem((lowerBoundStart, list, solStart))
    cmaxResult = float('inf')

    while not heap.IsEmpty():
        if time.time() - start > algotime:
            return cmaxResult

        lowerBoundCurrent, _, solCurrent = heap.PopItem()
        listCurrent, Cmax, B = solCurrent

        if lowerBoundCurrent >= cmaxResult:
            continue

        if Cmax < cmaxResult:
            cmaxResult = Cmax

        A = FindA(listCurrent, B, Cmax)
        C = FindC(listCurrent, A, B)

        if C is None:
            continue

        r2, p2, q2 = FindPath(listCurrent, B, C)
        listModified = copy.deepcopy(listCurrent)
        listModified[C][0] = max(listModified[C][0], r2 + p2)
        lowerBound = schrages.PrmtSchrage(copy.deepcopy(listModified))
        heap.PushItem((lowerBound, listModified, schrages.Schrage(listModified)))
        listModified = copy.deepcopy(listCurrent)
        listModified[C][2] = max(listModified[C][2], q2 + p2)
        lowerBound = schrages.PrmtSchrage(copy.deepcopy(listModified))
        heap.PushItem((lowerBound, listModified, schrages.Schrage(listModified)))
    return cmaxResult

if __name__ == "__main__":
    data = LoadData("data.txt")
    for x in data.values():
        start = time.time()
        cmax = Carlier(x['tasks'])
        end = time.time()
        exe_time = end - start
        print(f'Result: {cmax}\t Time: {exe_time}')
