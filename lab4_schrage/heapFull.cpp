#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Task.h"
#include "HeapMaxQ.h"
#include "HeapMinR.h"

using namespace std;

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



	for (int i = 0; i < 9; i++)
	{
		n=0;
		numOfDataset = "data.00" + to_string(i) + ":";
		while (tempString != numOfDataset)
		{
			f >> tempString;
		}
		f >> n;
		for (int j = 0; j < n; j++)	
		{
			Tasks[j].ID = j+1;
			f >> Tasks[j].r >> Tasks[j].p >> Tasks[j].q;
		}

		cout << "| " << numOfDataset << " |" << endl;
		cout << "prmtS: " << prmtSchrage(n, Tasks) << endl;
		cout << "Schrage: " << Schrage(n, Tasks, perm) << endl;
		cout << "Diff: " << Schrage(n, Tasks, perm) - prmtSchrage(n, Tasks) << endl;
		for (int i = 0; i < n; i++)
        {
            // if(X[i]+1 != perms[i])
            // {
                // cout << "Error = ["<< i << "]XID: " << X[i] + 1 << " " << "permID: " << perms[i] << endl;
			cout << perm[i+1] << "|";
            // }
        }
		cout <<endl<< "===========================================" << endl;
	}
}