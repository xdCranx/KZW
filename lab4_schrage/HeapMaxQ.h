#pragma once
#include <iostream>
#include "Task.h"
class HeapMaxQ {
private:
    Task* heapArray;

    int capacity;

    void swap(Task& a, Task& b) {
        Task temp = a;
        a = b;
        b = temp;
    }

    void shiftDown(int node) {
        int next = 2 * node;
        while (next <= heapSize) {
            if ((next < heapSize) && (heapArray[next].q < heapArray[next + 1].q))
                next++;
            if (heapArray[node].q < heapArray[next].q) {
                swap(heapArray[node], heapArray[next]);
                node = next;
                next *= 2;
            }
            else {
                next = heapSize + 1;
            }
        }
    }

    void shiftUp(int node) {
        int next = node / 2;
        while ((node > 1) && (heapArray[next].q < heapArray[node].q)) {
            swap(heapArray[node], heapArray[next]);
            node = next;
            next /= 2;
        }
    }

public:
    
    int heapSize; 
    HeapMaxQ(int maxCapacity) {
        capacity = maxCapacity;
        heapArray = new Task[capacity + 1];
        heapSize = 0;
    }

    ~HeapMaxQ() {
        delete[] heapArray;
    }

    void push(Task value) {
        if (heapSize >= capacity) {
            std::cerr << "Heap overflow: Cannot insert more elements.\n";
            return;
        }
        heapArray[++heapSize] = value;
        shiftUp(heapSize);
    }

    Task pop() {
    //    if (heapSize <= 0) {
    //        std::cerr << "Heap underflow: Cannot remove elements from an empty heap.\n";
    //        return;
    //    }
       Task result = heapArray[1];
       swap(heapArray[1], heapArray[heapSize--]);
       shiftDown(1);
       return result;
    }

    Task returnTop() {
        return heapArray[1];
    }

    void printHeap() const {
        std::cout << "Heap elements: ";
        for (int i = 1; i <= heapSize; i++) {
            std::cout << heapArray[i].ID << " ";
        }
        std::cout << std::endl;
    }
};

