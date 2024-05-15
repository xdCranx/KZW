import heapq

class PriorityQueue:
    def __init__(self, key_func, reverse, lst):
        self._key_func = key_func
        self._reverse = reverse
        if len(lst) == 0:
            self._items = []
        else:
            self._items = lst.sort(key=key_func, reverse=reverse)

    def Remove(self):
        self._items.pop(len(self._items) - 1)

    def Add(self, val):
        self._items.append(val)
        self._items.sort(key=self._key_func, reverse=self._reverse)

    def Display(self):
        print(self._items)

    def GetList(self):
        return self._items

    def IsEmpty(self):
        return len(self._items) == 0

    def GetLastItem(self):
        return self._items[len(self._items) - 1]

    def GetR(self, nb):
        return self._items[len(self._items) - 1][0]

class Heap:
    def __init__(self):
        self._heap = []

    def PushItem(self, item):
        heapq.heappush(self._heap, item)

    def PopItem(self):
        return heapq.heappop(self._heap)

    def IsEmpty(self):
        return len(self._heap) == 0