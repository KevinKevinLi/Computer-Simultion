/*#include<iostream>
using namespace std;
#include "math.h"
#include "time.h"

//just cal the far distance from circle

#define EPSILON 0.000000001

double d;//dimention
long long runtimes;//cube number
clock_t start, finish;//time

double smallcube;//cube edge length
double halfcube;//half cube edge length

//use square to compare, more fast and accurate
double act_dis; //actuall distance
double dis; //judge dis
double diagonal;//little cube diagonal
long long outcircle = 0;
long long incircle = 0;
long long crosscircle = 0;

class Coordinate
{
public:
	double x, y, z, h, g;
	Coordinate(double xx, double yy, double zz, double hh, double gg)
	{
		x = xx;
		y = yy;
		z = zz;
		h = hh;
		g = gg;
	}
};
//initialize small cube coordinate
Coordinate cube(-1.0, 1.0, -1.0, 1.0, -1.0);

//return positive or negative
double posnegcal(double temp)
{
	if (temp<0)
	{
		return -1.0;
	}
	else if (temp>0)
	{
		return 1.0;
	}
	return 0.0;
}

void nextcube2()
{
	if (cube.x - 1.0<-EPSILON)//cube.x<1.0
	{
		cube.x += smallcube;
	}
	else//cube.x==1.0-halfcube
	{
		cube.x = -1.0;
		cube.y -= smallcube;
	}
	if (cube.x <= EPSILON&&cube.x >= -EPSILON)//judge cube.x==0?
	{
		cube.x += smallcube;
	}
	if (cube.y <= EPSILON&&cube.y >= -EPSILON)
	{
		cube.y -= smallcube;
	}
}

void ifincircle2()
{
	act_dis = cube.x*cube.x + cube.y*cube.y;//no sqrt
	if (act_dis <= 1.0)
	{
		incircle++;
	}
	else if (act_dis >= dis)
	{
		outcircle++;
	}
	else//more accurate
	{
		double l = cube.x - posnegcal(cube.x)*smallcube;
		double m = cube.y - posnegcal(cube.y)*smallcube;
		double n = l*l + m*m;

		if (n < 1.0)
		{
			crosscircle++;
		}
		else
		{
			outcircle++;
		}
	}
}

void CubeSim2()
{
	ifincircle2();
	nextcube2();
}

void nextcube3()
{
	if (cube.x <-smallcube - EPSILON)
	{
		cube.x += smallcube;
	}
	else//cube.x==1.0-halfcube
	{
		cube.x = -1.0;
		if (cube.y > smallcube +EPSILON)//cube.y > -1.0
		{
			cube.y -= smallcube;
		}
		else
		{
			cube.z += smallcube;
			cube.y = 1.0;
		}
	}
}

void ifincircle3()
{
	act_dis = cube.x*cube.x + cube.y*cube.y + cube.z*cube.z;// dis square
	if (act_dis <= 1.0)
	{
		incircle++;
	}
	else if (act_dis > dis)
	{
		outcircle++;
	}
	else//more accurate
	{
		double l = cube.x - posnegcal(cube.x)*smallcube;
		double m = cube.y - posnegcal(cube.y)*smallcube;
		double o = cube.z - posnegcal(cube.z)*smallcube;
		double n = l*l + m*m+o*o;

		if (n < 1.0)
		{
			crosscircle++;
		}
		else
		{
			outcircle++;
		}
	}
}

void CubeSim3()
{
	ifincircle3();
	nextcube3();
}

void nextcube4()
{
	if (cube.x <-smallcube - EPSILON)
	{
		cube.x += smallcube;
	}
	else//cube.x==1.0-halfcube
	{
		cube.x = -1.0;
		if (cube.y > smallcube+EPSILON)//cube.y > -1.0
		{
			cube.y -= smallcube;
		}
		else
		{
			cube.y = 1.0;
			if (cube.z <-smallcube - EPSILON)
			{
				cube.z += smallcube;
			}
			else
			{
				cube.z = -1.0;
				cube.h -= smallcube;
			}
		}
	}
}

void ifincircle4()
{
	act_dis = cube.x*cube.x + cube.y*cube.y + cube.z*cube.z + cube.h*cube.h;// dis square
	if (act_dis <= 1.0)
	{
		incircle++;
	}
	else if (act_dis > dis)
	{
		outcircle++;
	}
	else
	{
		double l = cube.x - posnegcal(cube.x)*smallcube;
		double m = cube.y - posnegcal(cube.y)*smallcube;
		double n = cube.z - posnegcal(cube.z)*smallcube;
		double o = cube.h - posnegcal(cube.h)*smallcube;
		double p = l*l + m*m + n*n + o*o;

		if (p < 1.0)
		{
			crosscircle++;
		}
		else
		{
			outcircle++;
		}
	}
}

void CubeSim4()
{
	ifincircle4();
	nextcube4();
}

void nextcube5()
{
	if (cube.x <-smallcube-EPSILON)
	{
		cube.x += smallcube;
	}
	else//cube.x==1.0-halfcube
	{
		cube.x = -1.0;
		if (cube.y >smallcube+ EPSILON)//cube.y > -1.0
		{
			cube.y -= smallcube;
		}
		else
		{
			cube.y = 1.0;
			if (cube.z <-smallcube -EPSILON)
			{
				cube.z += smallcube;
			}
			else
			{
				cube.z = -1.0;
				if (cube.h>smallcube+ EPSILON)
				{
					cube.h -= smallcube;
				}
				else
				{
					cube.h = 1.0;
					cube.g += smallcube;
				}
			}
		}
	}
}

void ifincircle5()
{
	act_dis = cube.x*cube.x + cube.y*cube.y + cube.z*cube.z + cube.h*cube.h + cube.g*cube.g;// dis square
	if (act_dis <= 1.0)
	{
		incircle++;
	}
	else if (act_dis > dis)
	{
		outcircle++;
	}
	else
	{
		double l = cube.x - posnegcal(cube.x)*smallcube;
		double m = cube.y - posnegcal(cube.y)*smallcube;
		double n = cube.z - posnegcal(cube.z)*smallcube;
		double o = cube.h - posnegcal(cube.h)*smallcube;
		double p = cube.g - posnegcal(cube.g)*smallcube;
		double q = l*l + m*m + n*n + o*o + p*p;

		if (q < 1.0)
		{
			crosscircle++;
		}
		else
		{
			outcircle++;
		}
	}
}

void CubeSim5()
{
	ifincircle5();
	nextcube5();
}


void statistics()
{
	double min;
	double max;
	double accurate;
	crosscircle = runtimes - incircle-outcircle;
	if (d == 2)
	{
		min = 4.0*incircle / runtimes;
		max = 4.0*(runtimes - outcircle) / runtimes;
		accurate=4.0*(incircle + crosscircle / 2) / runtimes;
	}
	if (d == 3)
	{
		min = 8.0*incircle / runtimes;
		max = 8.0*(runtimes- outcircle) / runtimes;
		accurate = 8.0*(incircle + crosscircle/2) / runtimes;
	}
	if (d == 4)
	{
		min = 16.0*incircle / runtimes;
		max = 16.0*(runtimes - outcircle) / runtimes;
		accurate = 16.0*(incircle + crosscircle / 2) / runtimes;
	}
	if (d == 5)
	{
		min = 32.0*incircle / runtimes;
		max = 32.0*(runtimes - outcircle) / runtimes;
		accurate = 32.0*(incircle + crosscircle / 2) / runtimes;
	}
	cout << "(Cube Based) The volume of " << (int)d << "-dimensional (hyper-)sphere of redius r=1 centered on the origin is between " << min << "-" << max<<" ("<<accurate<<") " << endl;
	cout << "Run time: " << (double)(finish - start) / CLOCKS_PER_SEC << endl;
}

void main()
{
	cout << "(Cube Based) Insert the dimension: ";
	cin >> d;
	start = clock();
	if (d == 2)
	{
		//initialize cube coordinate from left-up
		runtimes = 225000000;// you need to put total runtimes/4 here
		double st = 15000.0;// the k value
		smallcube = 2 / st;
		halfcube = 1 / st;
		dis = (1.0 + sqrt(2 * smallcube*smallcube))*(1.0 + sqrt(2 * smallcube*smallcube));//no sqrt, more accurate and fast
		for (int i = 0; i < runtimes; i++)
		{
			CubeSim2();
		}
		finish = clock();
	}
	if (d == 3)
	{
		//initialize cube coordinate from back-left-up
		runtimes = 125000000; // you need to put total runtimes/8 here
		double st = 1000.0;// the k value
		smallcube = 2.0 / st;
		halfcube = 1.0 / st;
		diagonal = sqrt(3 * smallcube*smallcube);
		dis = (1.0 + sqrt(3 * smallcube* smallcube))*(1.0 + sqrt(3 * smallcube* smallcube));
		for (;cube.z<0.0;)
		{
			CubeSim3();
		}
		finish = clock();
	}
	if (d == 4)
	{
		//initialize cube coordinate from back-left-up
		runtimes = 1600000000;// you need to put total runtimes/16 here
		double st = 400.0;
		smallcube = 2.0 / st;
		halfcube = 1.0 / st;
		dis = (1.0 + sqrt(4 * smallcube* smallcube))*(1.0 + sqrt(4 * smallcube* smallcube));
		for (int i = 0; i < runtimes; i++)
		{
			CubeSim4();
		}
		finish = clock();
	}
	if (d == 5)
	{
		//initialize cube coordinate from back-left-up
		runtimes = 10000000000;// you need to put total runtimes/32 here
		double st = 200.0;
		smallcube = 2.0 / st;
		halfcube = 1.0 / st;
		dis = (1.0 + sqrt(5 * smallcube* smallcube))*(1.0 + sqrt(5 * smallcube* smallcube));
		for (int i = 0; i < runtimes; i++)
		{
			CubeSim5();
		}
		finish = clock();
	}
	statistics();
	system("Pause");
}*/