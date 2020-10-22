#include<iostream>
using namespace std;

class Boat;//前置声明
class Car
{
	private:
		int weight;
	public:
		Car(int weight1);
		//声明友元函数
		friend int totalweight(Boat &b,Car &c);
};
class Boat
{
	private:
		int weight;
	public:
		Boat(int weight1);
		//同时声明友元函数
		friend int totalweight(Boat &b,Car &c);
 };
 Boat::Boat(int weight1)
 {
 	weight = weight1;
 }

Car::Car(int weight1)
{
	weight = weight1;
}
int totalweight(Boat &b,Car &c)
{
	return b.weight+c.weight;
}
int  main()
{
        Boat  b(100);
        Car  c(200);
        cout<<totalweight( b,c)<<endl;
        return  0;
}
