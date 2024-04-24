//#include <iostream>
//#include "HeapMaxQ.h"
//#include "HeapMinR.h"
//#include "Task.h"
//
//int main() 
//{
//    int n = 10;
//    Task task1 = {1, 0, 10, 15};
//    Task task2 = {2, 140, 11, 16};
//    Task task3 = {3, 14, 12, 17};
//    Task task4 = {4, 133, 13, 18};
//    HeapMinR qHeap(n);
//    
//    qHeap.push(task2);
//    qHeap.push(task3);
//    qHeap.push(task4);
//    qHeap.push(task1);
//
//    qHeap.printHeap();
//    for(int i = 0; i < 4; i++)
//    {
//        std::cout << qHeap.returnTop().r << "\t";
//        std::cout << qHeap.pop().ID << std::endl;
//    }
//    // std::cout << qHeap.pop().ID << std::endl;
//    // std::cout << qHeap.pop().ID << std::endl;
//    // std::cout << qHeap.pop().ID << std::endl;
//    // std::cout << qHeap.pop().ID << std::endl;
//    // qHeap.printHeap();
//
//    return 0;
//}