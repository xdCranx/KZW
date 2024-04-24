//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include "Task.h"
//#include <chrono>
//using namespace std;
//using namespace std::chrono;
//int Schrage(int n, Task* T, int* perm)
//{
//	int ND[100], D[100];
//	int nd = n, d = 0, w = 0;
//	int  t = 0, cmax = 0;
//	for (int i = 0; i < n; i++)
//	{
//		ND[i] = i;
//	}
//	for (int i = 0; i < n - 1; i++)
//	{
//		for (int j = 0; j < n - 1; j++)
//		{
//			if (T[ND[j]].r < T[ND[j + 1]].r)
//			{
//				swap(ND[j], ND[j + 1]);
//			}
//		}
//	}
//	while (w != n)
//	{
//		if (nd != 0)
//		{
//			if (T[ND[nd - 1]].r <= t)
//			{
//				D[d] = ND[nd - 1];
//				d++;
//				nd--;
//				for (int k = d - 1; k > 0; k--)
//				{
//					if (T[D[k]].q < T[D[k - 1]].q)
//					{
//						swap(D[k], D[k - 1]);
//					}
//				}
//				continue;
//			}
//		}
//		if (d != 0)
//		{
//			perm[w] = D[d - 1];
//			t += T[perm[w]].p;
//			cmax = max(cmax, t + T[perm[w]].q);
//			d--;
//			w++;
//			continue;
//		}
//		if (d == 0 && T[ND[nd - 1]].r > t)
//		{
//			t = T[ND[nd - 1]].r;
//		}
//	}
//	return cmax;
//}
//int prmtSchrage(int n, Task* T)
//{
//	int ND[100], D[100], pVals[100];
//	int nd = n, d = 0, w = 0;
//	int t = 0, cmax = 0;
//	int currentTask = 100;
//	int remainingTaskPTime = 0;
//	for (int i = 0; i < n; i++)
//	{
//		pVals[i] = T[i].p;
//	}
//	for (int i = 0; i < n; i++)
//	{
//		ND[i] = i;
//	}
//	for (int i = 0; i < n - 1; i++)
//	{
//		for (int j = 0; j < n - 1; j++)
//		{
//			if (T[ND[j]].r < T[ND[j + 1]].r)
//			{
//				swap(ND[j], ND[j + 1]);
//			}
//		}
//	}
//	while (nd != 0 || d != 0)
//	{
//		if (nd != 0)
//		{
//			if (T[ND[nd - 1]].r <= t)
//			{
//				D[d] = ND[nd - 1];
//				d++;
//				nd--;
//				for (int k = d - 1; k > 0; k--)
//				{
//					if (T[D[k]].q < T[D[k - 1]].q)
//					{
//						swap(D[k], D[k - 1]);
//					}
//				}
//				if (currentTask != 100)
//				{
//					if (T[D[d - 1]].q > T[currentTask].q)
//					{
//						D[d] = currentTask;
//						swap(D[d], D[d - 1]);
//						d++;
//						currentTask = 100;
//					}
//				}
//				continue;
//			}
//		}
//		if (d != 0)
//		{
//			if (currentTask == 100)
//			{
//				currentTask = D[d - 1];
//				d--;
//			}
//			if (nd != 0)
//			{
//				remainingTaskPTime = min(pVals[currentTask], T[ND[nd - 1]].r - t);
//			}
//			else
//			{
//				remainingTaskPTime = pVals[currentTask];
//			}
//			t += remainingTaskPTime;
//			pVals[currentTask] -= remainingTaskPTime;
//			if (pVals[currentTask] == 0)
//			{
//				cmax = max(cmax, t + T[currentTask].q);
//				currentTask = 100;
//			}
//			continue;
//		}
//		if (d == 0 && nd != 0)
//		{
//			if (T[ND[nd - 1]].r > t)
//			{
//				t = T[ND[nd - 1]].r;
//			}
//		}
//	}
//	return cmax;
//}
//int main()
//{
//	int perm[100];
//    int optPerm[100];
//    int n;
//	Task Tasks[100];
//    string numOfDataset, tempString;
//	ifstream f("data.txt");
//
//
//	int time[9][2];
//	int result[9][2];
//	for (int i = 0; i < 9; i++)
//	{
//		n=0;
//		numOfDataset = "data.00" + to_string(i) + ":";
//		while (tempString != numOfDataset)
//		{
//			f >> tempString;
//		}
//		f >> n;
//		
//		for (int j = 0; j < n; j++)	
//		{
//			Tasks[j].ID = j+1;
//			f >> Tasks[j].r >> Tasks[j].p >> Tasks[j].q;
//		}
//		
//		auto startSchr = high_resolution_clock::now();
//		result[i][0] = Schrage(n, Tasks, perm);
//		auto stopSchr = high_resolution_clock::now();
//		auto durationSchr = duration_cast<microseconds>(stopSchr - startSchr);
//		time[i][0] = durationSchr.count();
//
//		
//		
//		auto startPrtm = high_resolution_clock::now();
//		result[i][1] = prmtSchrage(n, Tasks);
//		auto stopPrtm = high_resolution_clock::now();
//		auto durationPrtm = duration_cast<microseconds>(stopSchr - startSchr);
//		time[i][1] = durationPrtm.count();
//
//		
//		//for (int i = 0; i < n; i++)
//  //      {
//  //          // if(X[i]+1 != perms[i])
//  //          // {
//  //              // cout << "Error = ["<< i << "]XID: " << X[i] + 1 << " " << "permID: " << perms[i] << endl;
//		//	cout << perm[i+1] << "|";
//  //          // }
//  //      }
//		
//	}
//
//	ofstream output("output.txt", ios::app);
//	ofstream outputTime("time.txt", ios::app);
//	for(int i=0; i<9; i++)
//	{
//		output << i << "\t"<<result[i][0]<< "\t" << result[i][1] << endl;
//		outputTime << i << "\t" << time[i][0] << "\t" << time[i][1] << endl;
//	}
//	output.close();
//	outputTime.close();
//	
//}