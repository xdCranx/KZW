import heaps
from operator import itemgetter


def Schrage(data):
    t = 0
    k = 0
    b = 0
    N = heaps.PriorityQueue(itemgetter(0), True, [])
    G = heaps.PriorityQueue(itemgetter(2), False, [])
    C_max = 0
    pi = []

    for i in range(0, len(data)):
        N.Add([int(data[i][0]), int(data[i][1]), int(data[i][2])])

    while G.IsEmpty() is False or N.IsEmpty() is False:
        while N.IsEmpty() is False and int(N.GetR(0)) <= t:
            e = N.GetLastItem()
            G.Add(e)
            N.Remove()
        if G.IsEmpty() is True:
            t = int(N.GetR(0))
        else:
            e = G.GetLastItem()
            G.Remove()
            pi.append(e)
            t += int(e[1])
            if C_max <= int(t + int(e[2])):
                C_max = int(t + int(e[2]))
                b = k
            k += 1

    return pi, C_max, b

def PrmtSchrage(data):
    n = len(data)
    t = 0
    N = heaps.PriorityQueue(itemgetter(0), True, [])
    G = heaps.PriorityQueue(itemgetter(2), False, [])

    C_max = 0
    pi = []
    machine = [0, 0, 500]

    for i in range(0, n):
        N.Add([int(data[i][0]), int(data[i][1]), int(data[i][2])])

    while G.IsEmpty() is False or N.IsEmpty() is False:
        while N.IsEmpty() is False and int(N.GetR(0)) <= t:
            e = N.GetLastItem()
            G.Add(e)
            N.Remove()
            if e[2] > machine[2]:
                machine[1] = t - e[0]
                t = e[0]
                if machine[1] > 0:
                    G.Add(machine)

        if G.IsEmpty() is True:
            t = int(N.GetR(0))
        else:
            e = G.GetLastItem()
            G.Remove()
            machine = e
            pi.append(e)
            t += int(e[1])
            C_max = max(C_max, int(t+int(e[2])))

        if not G.IsEmpty() and e[0] > t:
            continue

        if not G.IsEmpty() and e[2] < C_max - t:
            continue

    return C_max