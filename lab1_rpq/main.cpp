#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;
struct task {
	int id;
	int r;
	int p;
	int q;

};

void Load(string name, vector<task>& tasks)
{
	int r;
	int p;
	int q;
	int length;
	ifstream load(name + ".txt");
	load >> length;
	for (int i = 0; i < length; i++)
	{
		task temp;
		temp.id = i + 1;
		load >> temp.r;
		load >> temp.p;
		load >> temp.q;
		tasks.push_back(temp);


	}
}

int Cmax(vector<task>data)
{
	int t = 0, c = 0;
	for (int i = 0; i < data.size(); i++)
	{
		t = max(t, data[i].r) + data[i].p;
		c = max(c, t + data[i].q);
	}
	return c;

}

void Sort(vector<task>& data)
{
	int size = data.size();
	int c = Cmax(data);
	int c2;
	for (int k = 0; k < 5; k++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				iter_swap(data.begin() + i, data.begin() + j);
				c2 = Cmax(data);
				if (c2 > c)
				{
					iter_swap(data.begin() + i, data.begin() + j);
				}
				else
				{
					c = c2;
				}
			}
		}
	}

}

void PrintOrder(vector<task>data)
{
	for (int i = 0; i < data.size(); i++)
	{
		cout << data[i].id << "\t";
	}
}



int main()
{
	vector<vector<task>>data;

	int c[4];
	int cTotal = 0;
	for (int i = 0; i < 4; i++)
	{
		vector<task> a;
		Load("data" + to_string(i + 1), a);
		Sort(a);
		c[i] = Cmax(a);
		cTotal += c[i];
		data.push_back(a);

	}
	for (int i = 0; i < 4; i++)
	{
		cout << "Kolejnosc elementow zbioru " << i + 1 << ":\n";
		PrintOrder(data[i]);
		cout << "\nWartosc Cmax dla zbioru " << i + 1 << ": " << c[i] << "\n";
	}
	cout << "Wartosc sumy c wszystkich elementow: " << cTotal;


}