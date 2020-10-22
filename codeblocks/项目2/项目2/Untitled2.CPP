#include<iostream>
using namespace std;
class Base
{
    int a,b;
public:
    Base(int x,int y){a = x;b = y;};
    void show(){cout<<a<<","<<b<<endl;};
};
class Derived:public Base
{
    int c,d;
public:
    Derived(int x,int y,int z,int m):Base(x,y){c = z;d = m;};
    void show(){cout<<c<<","<<d<<endl;};
};
int main()
{
    Base B1(50,50),*pb;
    Derived D1(10,20,30,40);
    pb=&D1;
    pb->show();
    return 0;
}
