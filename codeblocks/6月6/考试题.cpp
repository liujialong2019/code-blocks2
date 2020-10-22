//根据点的定义，写出线段和三角形的定义，并通过主程序进行验证
//mypoint.h
//在住函数之前加上
#include<cmath>
#include<iostream>
using namespace std;
class  myPoint
{
public:
        myPoint();
        myPoint(double x, double  y);
        double  getX();
        double  getY();
private:
        double  mX,mY;
};
//请补充myPoint类的实现部分
myPoint::myPoint()
{
    mX = 0;
    mY = 0;
}
myPoint::myPoint(double x,double y)
{
    mX = x;
    mY = y;
}
double myPoint::getX()
{
    return mX;
}
double myPoint::getY()
{
    return mY;
}
//请补充线段类和三角形类的设计
class Line
{
private:
    myPoint p1,p2;
public:
    Line(myPoint p11,myPoint p22);
    double GetDistance();
};
Line::Line(myPoint p11,myPoint p22)
{
    p1=p11;
    p2=p22;
}
double Line::GetDistance()
{
    double x1,y1;
    double x2,y2;
    x1 = p1.getX();
    y1 = p1.getY();
    x2 = p2.getX();
    y2 = p2.getY();
    return abs(sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)));
}
class Triangle
{
private:
    myPoint p1,p2,p3;
public:
    Triangle(myPoint p11,myPoint p22,myPoint p33);
    double getGirth();
    double getArea();
};
Triangle::Triangle(myPoint p11,myPoint p22,myPoint p33)
{
    p1=p11;
    p2=p22;
    p3=p33;
}
double Triangle::getGirth()
{
    Line l1(p1,p2),l2(p1,p3),l3(p2,p3);
    return l1.GetDistance()+l2.GetDistance()+l3.GetDistance();
}
double Triangle::getArea()
{
    Line l1(p1,p2),l2(p1,p3),l3(p2,p3);
    double p = (l1.GetDistance()+l2.GetDistance()+ l3.GetDistance())/2;
    return sqrt(p*(p-l1.GetDistance())*(p-l2.GetDistance())*(p-l3.GetDistance()));
}
int  main()
{
        double x1, x2, x3, y1, y2, y3;
        cout  <<  "请输入点1的x的值：";
        cin  >>  x1;
        cout  <<  "请输入点1的y的值：";
        cin  >>  y1;
        cout  <<  "请输入点2的x的值：";
        cin  >>  x2;
        cout  <<  "请输入点2的y的值：";
        cin  >>  y2;
        cout  <<  "请输入点3的x的值：";
        cin  >>  x3;
        cout  <<  "请输入点3的y的值：";
        cin  >>  y3;
        cout  <<  "点1的坐标为：("  <<  x1  <<  ","  <<  y1  <<  ")"  <<  endl;
        cout  <<  "点2的坐标为：("  <<  x2  <<  ","  <<  y2  <<  ")"  <<  endl;
        cout  <<  "点3的坐标为：("  <<  x3  <<  ","  <<  y3  <<  ")"  <<  endl;
        myPoint p1(x1, y1),  p2(x2,  y2),  p3(x3,  y3);
        Line    line1(p1,p2);
        cout<<"线长度:"<<line1.GetDistance()<<endl;
        Triangle  t(p1,  p2,  p3);
        cout  <<  "该三角形的周长为："  <<  t.getGirth()  <<  endl;
        cout  <<  "该三角形的面积为："  <<  t.getArea()  <<  endl;
        return  0;
}
