#include <iostream>
using namespace  std;
//请在这里补充CPoint，CRectangle类的定义
class CPoint
{
private:
    int x,y;
public:
    CPoint();
    CPoint(int x1,int y1);
    CPoint(CPoint &C);
    int getx(){return x;}
    int gety(){return y;}
};
CPoint::CPoint(CPoint &C)
{
    x = C.x;
    y = C.y;
    cout<<"CPoint copy constructor is called."<<endl;
}
CPoint::CPoint()
{
    x = 0;
    y = 0;
    cout <<"CPoint constructor with default value(0,0) is called."<<endl;//"<<x<<","<<y<<"
}
CPoint::CPoint(int x1,int y1)
{
    x = x1;
    y = y1;
    cout <<"CPoint constructor with default value(0,0) is called."<<endl;
}
class CRectangle
{
private:
    int a,b,c,d;
public:
    CRectangle();
    CRectangle(CPoint p1,CPoint p2);
    CRectangle(int a1,int a2,int a3,int a4);
    int GetArea();
    CRectangle(CRectangle &CR);
};
CRectangle::CRectangle()
{
    CPoint p1,p2;
    a = p1.getx();
    c = p1.gety();
    b = p2.getx();
    d = p2.gety();
    cout<<"CRectangle default contstructor is called."<<endl;
}
CRectangle::CRectangle(CPoint p1,CPoint p2)
{
    CPoint p11 = p1;
    CPoint p22 = p2;
    a = p11.getx();
    c = p11.gety();
    b = p22.getx();
    d = p22.gety();
    cout<<"CRectangle contstructor with (CPoint,CPoint) is called."<<endl;
}
CRectangle::CRectangle(int a1,int a2,int a3,int a4)
{
    //CPoint(a1,a2);
    //CPoint(a3,a4);
    a = a1;
    c = a2;
    b = a3;
    d = a4;
    cout <<"CRectangle contstructor with (int,int,int,int) is called."<<endl;
}
CRectangle::CRectangle(CRectangle &rec)
{
    a = rec.a;
    b = rec.b;
    c = rec.c;
    d = rec.d;
    cout <<"CPoint copy contstructor is called."<<endl;
    cout <<"CPoint copy contstructor is called."<<endl;
    cout <<"CRectangle copy contstructor is called."<<endl;
}
int CRectangle::GetArea()
{
    return (b-a)*(d - c);
}
int main()
{
    int a=1, b=1, c=6, d=11;
    cout<<"# Define p1 ######"<<endl;
    CPoint p1;
    cout<<"# Define p2 ######"<<endl;
    CPoint p2(10,20);
    cout<<"# Define rect1 ######"<<endl;
    CRectangle rect1;
    cout<<"# Define rect2 ######"<<endl;
    CRectangle rect2(p1, p2);
    cout<<"# Define rect3 ######"<<endl;
    CRectangle rect3(a, b, c, d);
    cout<<"# Define rect4 ######"<<endl;
    CRectangle rect4(rect2);
    cout<<"# Calculate area ######"<<endl;
    cout << "rect1面积为" << rect1.GetArea() << endl;
    cout << "rect2面积为" << rect2.GetArea() << endl;
    cout << "rect3面积为" << rect3.GetArea() << endl;
    cout << "rect4面积为" << rect4.GetArea() << endl;
    //system("pause");
    return 0;
}
