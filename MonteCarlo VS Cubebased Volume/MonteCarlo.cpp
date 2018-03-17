/*#include<iostream>
using namespace std;
#include "math.h"
#include "time.h"

static double d;
static double runtimes;
int timesin = 0;//in circle times

clock_t start, finish;//clock

//for statistic
double mean = 0.0;
double sum = 0.0;
double var = 0.0;
double wide = 0.0;

int listtimes = 0;//times of each "big" run
double lower = 0.0;
double higher = 0.0;

//simple list
class arraylist
{
private:
	int n;//present number
	double *list;
public:
	arraylist(int temp)
	{
		list = new double[temp];
		n = 0;
	}
	void addLast(double temp)
	{
		list[n] = temp;
		n++;
	}
	double getLast()
	{
		return list[n-1];
	}
	double get(int number)
	{
		return list[number];
	}
};
arraylist List(1000000);

//1-dimension
bool ifincircle1(double temp)
{
	if (temp >= -1.0&&temp <= 1.0)
	{
		return true;
	}
	return false;
}

void MontePointd1()
{
	for (int i = 0; i < runtimes; i++)
	{
		double temp = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);
		if (ifincircle1(temp))
		{
			timesin++;
		}
	}
}

//2-dimension
bool ifincircle2(double tempx, double tempy)
{
	if (tempx*tempx + tempy*tempy <= 1.0)
	{
		return true;
	}
	return false;
}

void MontePointd2()
{
	for (int i = 0; i < runtimes; i++)
	{
		double x = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);
		double y = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);
		if (ifincircle2(x, y))
		{
			timesin++;
		}
	}
}

//3-dimension
bool ifincircle3(double tempx, double tempy, double tempz)
{
	if ((tempx*tempx) + (tempy*tempy) + (tempz*tempz) <= 1.0)
	{
		return true;
	}
	return false;
}

void MontePointd3()
{
	for (int i = 0; i < runtimes; i++)
	{
		double x = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);
		double y = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);
		double z = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);

		if (ifincircle3(x, y, z))
		{
			timesin++;
		}
	}
}

//4-dimension
bool ifincircle4(double tempx, double tempy, double tempz,double tempo)
{
	if ((tempx*tempx) + (tempy*tempy) + (tempz*tempz) +(tempo*tempo)<= 1.0)
	{
		return true;
	}
	return false;
}

void MontePointd4()
{
	for (int i = 0; i < runtimes; i++)
	{
		double x = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);
		double y = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);
		double z = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);
		double o = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);

		if (ifincircle4(x, y, z,o))
		{
			timesin++;
		}
	}
}

//5-dimension
bool ifincircle5(double tempx, double tempy, double tempz, double tempo,double tempq)
{
	if ((tempx*tempx) + (tempy*tempy) + (tempz*tempz) + (tempo*tempo)+(tempq*tempq) <= 1.0)
	{
		return true;
	}
	return false;
}

void MontePointd5()
{
	for (int i = 0; i < runtimes; i++)
	{
		double x = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);
		double y = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);
		double z = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);
		double o = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);
		double q = (-1.0 + ((float)rand() / (RAND_MAX + 1)) * 2);

		if (ifincircle5(x, y, z, o,q))
		{
			timesin++;
		}
	}
}


void statistics()
{
	double temp = 0.0;
	if (d == 1)
	{
		temp = (timesin / runtimes)*2.0;
	}
	else if (d == 2)
	{
		temp = (timesin / runtimes)*4.0;
	}
	else if (d==3)
	{
		temp = (timesin / runtimes)*8.0;
	}
	else if (d==4)
	{
		temp = (timesin / runtimes)*16.0;
	}
	else if (d == 5)
	{
		temp = (timesin / runtimes)*32.0;
	}
	cout << "The volume of " << (int)d << "-dimensional (hyper-)sphere of redius r=1 centered on the origin is "   << temp << endl;
	List.addLast(temp);
}

void main()
{
	cout << "(Monte Carlo):Insert the dimension you want to calculate:";
	cin >> d;
	start = clock();
	//define runtimes
	if (d == 1)
	{
		runtimes = 1000000;
	}
	else if (d == 2)
	{
		runtimes = 1000000;
	}
	else if (d == 3)
	{
		runtimes = 1000000;
	}
	else if (d == 4)
	{
		runtimes = 1000000;
	}
	else if (d == 5)
	{
		runtimes = 1000000;
	}
	bool iffirsttime = true;
		
	for (;iffirsttime == true || ((int)(higher * 10000000) != (int)(lower * 10000000));)
	{
		if (d == 1)
		{
			MontePointd1();
		}
		else if (d == 2)
		{
			MontePointd2();
		}
		else if (d == 3)
		{
			MontePointd3();
		}
		else if (d == 4)
		{
			MontePointd4();
		}
		else if (d == 5)
		{
			MontePointd5();
		}

		statistics();
		sum += List.getLast();
		listtimes++;

		mean = sum / listtimes;

		for (int i = 0; i<listtimes; i++)
		{
			var += (List.get(i) - mean)*(List.get(i) - mean);
		}
		var = var / listtimes;

		lower = mean - 2.58*sqrt(var / listtimes);
		higher = mean + 2.58*sqrt(var / listtimes);
		cout <<"interval:"<< lower << "-" << higher << endl;

		timesin = 0;//initialize
		if (listtimes > 1)
		{
			iffirsttime = false;
		}
	}
	finish = clock();
	cout<< "The volume of " << (int)d << "-dimensional (hyper-)sphere of redius r=1 centered on the origin with 99% confidence is " <<lower<<"-"<<higher<<"  acuurate result:"<< mean<<endl;
	cout << "Run Times:" << listtimes << endl;
	cout << "Run Time is:" << (double)(finish - start) / CLOCKS_PER_SEC << "s" << endl;
	system("Pause");
}
*/