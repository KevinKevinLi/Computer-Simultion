#include<iostream>
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
long long outcircle = 0;
long long incircle = 0;
long long crosscircle = 0;

class Coordinate
{
public:
	double x, y, z,h,g;
	Coordinate(double xx, double yy, double zz,double hh,double gg)
	{
		x = xx;
		y = yy;
		z = zz;
		h = hh;
		g = gg;
	}
};
//initialize small cube coordinate
Coordinate cube(-1.0, 1.0, -1.0,1.0,-1.0);

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

void nextcube1()//dimention 1
{
	cube.x += smallcube;	
}

void ifincircle1()
{
	act_dis = abs(cube.x);//no sqrt
	if (act_dis <= 1.0)
	{
		incircle++;
	}
	else if (act_dis >= dis)
	{
		outcircle++;
	}
}

void CubeSim1()
{
	ifincircle1();
	nextcube1();
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
	if (cube.x - 1.0<-EPSILON)
	{
		cube.x += smallcube;
	}
	else//cube.x==1.0-halfcube
	{
		cube.x = -1.0;
		if (cube.y + 1.0> EPSILON)//cube.y > -1.0
		{
			cube.y -= smallcube;
		}
		else
		{
			cube.z += smallcube;
			cube.y = 1.0;
		}
	}
	if (cube.x <= EPSILON&&cube.x >= -EPSILON)//judge cube.x==0?
	{
		cube.x += smallcube;
	}
	if (cube.y <= EPSILON&&cube.y >= -EPSILON)
	{
		cube.y -= smallcube;
	}
	if (cube.z <= EPSILON&&cube.z >= -EPSILON)
	{
		cube.z += smallcube;
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
	else
	{
		double l = cube.x - posnegcal(cube.x)*smallcube;
		double m = cube.y - posnegcal(cube.y)*smallcube;
		double n = cube.z - posnegcal(cube.z)*smallcube;
		double o = l*l + m*m + n*n;

		if (o < 1.0)
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
	if (cube.x - 1.0<-EPSILON)
	{
		cube.x += smallcube;
	}
	else//cube.x==1.0-halfcube
	{
		cube.x = -1.0;
		if (cube.y + 1.0> EPSILON)//cube.y > -1.0
		{
			cube.y -= smallcube;
		}
		else
		{
			cube.y = 1.0;
			if (cube.z - 1.0 < -EPSILON)
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
	if (cube.x <= EPSILON&&cube.x >= -EPSILON)//judge cube.x==0?change vertex
	{
		cube.x += smallcube;
	}
	if (cube.y <= EPSILON&&cube.y >= -EPSILON)
	{
		cube.y -= smallcube;
	}
	if (cube.z <= EPSILON&&cube.z >= -EPSILON)
	{
		cube.z += smallcube;
	}
	if (cube.h <= EPSILON&&cube.h >= -EPSILON)
	{
		cube.h -= smallcube;
	}
}

void ifincircle4()
{
	act_dis = cube.x*cube.x + cube.y*cube.y + cube.z*cube.z+cube.h*cube.h;// dis square
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
		double p = l*l + m*m + n*n+o*o;

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
	if (cube.x - 1.0<-EPSILON)
	{
		cube.x += smallcube;
	}
	else//cube.x==1.0-halfcube
	{
		cube.x = -1.0;
		if (cube.y + 1.0> EPSILON)//cube.y > -1.0
		{
			cube.y -= smallcube;
		}
		else
		{
			cube.y = 1.0;
			if (cube.z - 1.0 < -EPSILON)
			{
				cube.z += smallcube;
			}
			else
			{
				cube.z = -1.0;
				if (cube.h + 1.0 > EPSILON)
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
	if (cube.x <= EPSILON&&cube.x >= -EPSILON)//judge cube.x==0?change vertex
	{
		cube.x += smallcube;
	}
	if (cube.y <= EPSILON&&cube.y >= -EPSILON)
	{
		cube.y -= smallcube;
	}
	if (cube.z <= EPSILON&&cube.z >= -EPSILON)
	{
		cube.z += smallcube;
	}
	if (cube.h <= EPSILON&&cube.h >= -EPSILON)
	{
		cube.h -= smallcube;
	}
	if (cube.g <= EPSILON&&cube.g >= -EPSILON)
	{
		cube.g += smallcube;
	}
}

void ifincircle5()
{
	act_dis = cube.x*cube.x + cube.y*cube.y + cube.z*cube.z + cube.h*cube.h+cube.g*cube.g;// dis square
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
		double q = l*l + m*m + n*n + o*o+p*p;

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
	double accurate ;
	if (d == 1)
	{
		min = 2.0*incircle / runtimes;
		max = 2.0*(incircle + crosscircle) / runtimes;
		accurate = 2.0*(incircle + crosscircle / 2) / runtimes;
	}
	if (d == 2)
	{
		min = 4.0*incircle / runtimes;
		max = 4.0*(incircle + crosscircle) / runtimes;
		accurate = 4.0*(incircle + crosscircle / 2) / runtimes;
	}
	if (d == 3)
	{
		min = 8.0*incircle / runtimes;
		max = 8.0*(incircle + crosscircle) / runtimes;
		accurate= 8.0*(incircle + crosscircle/2) / runtimes;
	}
	if (d == 4)
	{
		min = 16.0*incircle / runtimes;
		max = 16.0*(incircle + crosscircle) / runtimes;
		accurate = 16.0*(incircle + crosscircle / 2) / runtimes;
	}
	if (d == 5)
	{
		min = 32.0*incircle / runtimes;
		max = 32.0*(incircle + crosscircle) / runtimes;
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
	if (d == 1)
	{
		//initialize cube coordinate from left-up
		runtimes = 1000000;
		smallcube = 2 / runtimes;
		halfcube = 1 / runtimes;
		dis = 1.0;
		for (int i = 0; i < runtimes; i++)
		{
			CubeSim1();
		}
		finish = clock();
	}
	if (d == 2)
	{
		//initialize cube coordinate from left-up
		runtimes = 1000000;
		smallcube = 2 / sqrt(runtimes);
		halfcube = 1 / sqrt(runtimes);
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
		runtimes = 1000000;
		double st = 100.0;
		smallcube = 2.0 / st;
		halfcube = 1.0 / st;
		dis = (1.0 + sqrt(3 * smallcube* smallcube))*(1.0 + sqrt(3 * smallcube* smallcube));
		for (int i = 0; i < runtimes; i++)
		{
			CubeSim3();
		}
		finish = clock();
	}
	if (d == 4)
	{
		//initialize cube coordinate from back-left-up
		runtimes = 1000000;
		smallcube = 2.0 / sqrt(sqrt(runtimes));
		halfcube = 1.0 / sqrt(sqrt(runtimes));
		dis = (1.0 + sqrt(4 * smallcube* smallcube))*(1.0 + sqrt(4 * smallcube* smallcube));
		for (int i = 0; i < runtimes; i++)
		{
			CubeSim4();
		}
		cout << sqrt(sqrt(runtimes));
		finish = clock();
	}
	if (d == 5)
	{
		//initialize cube coordinate from back-left-up
		runtimes = 1048576;
		double st = 16.0;
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
}
