#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Task.h"
#include "HeapMaxQ.h"
#include "HeapMinR.h"
#include <chrono>
using namespace std;
using namespace std::chrono;

int Schrage(int n, Task* T, int* perm)
{
    HeapMinR ND(n);
    HeapMaxQ D(n);
    int k = 1, t = 0, cmax = 0;

	//copy to heap
    for (int i = 0; i < n; i++)
    {
        ND.push(T[i]);
    }

	Task task;
    while (ND.heapSize > 0 || D.heapSize > 0)
    {
        while (ND.heapSize > 0 && ND.returnTop().r <= t)
        {
			task = ND.pop();
            D.push(task);
        }

        if (D.heapSize == 0)
        {
			t = ND.returnTop().r;
			continue;
		}

		task = D.pop();
		perm[k] = task.ID;
		k++;
		t +=task.p;
		cmax = max(cmax, t + task.q);

    }

    return cmax;
}

int prmtSchrage(int n, Task* T)
{
	HeapMinR ND(n);
    HeapMaxQ D(n);
	Task l = {0,0,0,0};
    int t = 0, cmax = 0;

	//copy to heap
    for (int i = 0; i < n; i++)
    {
        ND.push(T[i]);
    }

	Task task;
    while (ND.heapSize > 0 || D.heapSize > 0)
    {
        while (ND.heapSize > 0 && ND.returnTop().r <= t)
        {
			task = ND.pop();
            D.push(task);

			if(task.q > l.q) 
			{
				l.p = t - task.r;
				t = task.r;
			
				if (l.p > 0)
				{
				D.push(l);
				}
			}
        }

        if (D.heapSize == 0)
        {
			t = ND.returnTop().r;
			continue;
		}

		task = D.pop();
		l = task;
		t +=task.p;
		cmax = max(cmax, t + task.q);

    }

    return cmax;
}
int main()
{
	int perm[100];
	int optPerm[100];
	int n;
	Task Tasks[100];
	string numOfDataset, tempString;
	ifstream f("data.txt");


	int time[9][2];
	int result[9][2];
	for (int i = 0; i < 9; i++)
	{
		n = 0;
		numOfDataset = "data.00" + to_string(i) + ":";
		while (tempString != numOfDataset)
		{
			f >> tempString;
		}
		f >> n;

		for (int j = 0; j < n; j++)
		{
			Tasks[j].ID = j + 1;
			f >> Tasks[j].r >> Tasks[j].p >> Tasks[j].q;
		}

		auto startSchr = high_resolution_clock::now();
		result[i][0] = Schrage(n, Tasks, perm);
		auto stopSchr = high_resolution_clock::now();
		auto durationSchr = duration_cast<microseconds>(stopSchr - startSchr);
		time[i][0] = durationSchr.count();



		auto startPrtm = high_resolution_clock::now();
		result[i][1] = prmtSchrage(n, Tasks);
		auto stopPrtm = high_resolution_clock::now();
		auto durationPrtm = duration_cast<microseconds>(stopSchr - startSchr);
		time[i][1] = durationPrtm.count();


		//for (int i = 0; i < n; i++)
  //      {
  //          // if(X[i]+1 != perms[i])
  //          // {
  //              // cout << "Error = ["<< i << "]XID: " << X[i] + 1 << " " << "permID: " << perms[i] << endl;
		//	cout << perm[i+1] << "|";
  //          // }
  //      }

	}

	ofstream output("output_heap.txt", ios::app);
	ofstream outputTime("time_heap.txt", ios::app);
	for (int i = 0; i < 9; i++)
	{
		output << i << "\t" << result[i][0] << "\t" << result[i][1] << endl;
		outputTime << i << "\t" << time[i][0] << "\t" << time[i][1] << endl;
	}
	output.close();
	outputTime.close();

}