/*#include<iostream>
using namespace  std;
class myCArray
{
private:
    int* p_arr;
    int  size;
public:
    myCArray();//缺省构造函数
    myCArray(int* p_a,int s);//构造函数
    myCArray(const myCArray &r_other);//复制构造函数
    ~myCArray();//析构函数
    int operator[](int  pos)  const;//访问数组元素值的下标运算符重载函数
    int&operator[](int  pos);//设置数组元素值的下标运算符重载函数
    void  print()  const;
    myCArray operator + (const myCArray & r_other);
};
myCArray::myCArray()
{
    p_arr=0;
    size = 0;
}
myCArray(int *p_a,int s)
{
    if(s>0)
    {
        size = s;
        p_arr = new int [size];
        for(int i=0;i<size;i++)
            p_arr[i] = p_a[i];
    }
    else
    {
        p_arr=0;
        size = 0;
    }
}
myCArray::myCArray(const myCArray &r_other)
{
    size = r_other.size;
    if(size)
    {
        p_arr = new int[size];
        for(int i=0;i<size;i++)
            p_arr[i] = r_other.p_arr[i];
    }
}
myCArray::~myCArray()
{
    if(p_arr)
        delete[]p_arr;
}
myCArray myCArray::operator+(const myCArray &r_other)
{
    int *tt;
    tt = new int[size];
    myCArray temp(tt,size);
    for(int i=0;i<size;i++)
        temp.p_arr[i] = p_arr[i]+r_other.p_arr[i];
    return temp;
}
int myCArray::operator[](int pos)const {
	if(pos<0 || pos>=size){
    cout <<"Error!\n";
    exit(1);
  }
  return p_arr[pos];
}
int& CArray::operator[](int pos)
{
	if(pos<0 || pos>=size){
    cout <<"Error!\n";
    exit(1);
  }
  return p_arr[pos];

}
void myCArray::print()  const
    {
            for(int  i=0;i<this->size  ;i++)
                    cout<<this->p_arr[i]<<"    ";
            cout<<endl;

    }
int main()
    {      int  a[5]={1,2,3,4,5},b[5]={1,1,1,1,1};
            myCArray  t1(a,5),t2(b,5),t3;
              t3=t1+t2;
              t3.print();
              t3=t1-t2;
        //      t3[4]=1000;
          //    t3.print();
              return  0;
    }
*/
#include<iostream>
using namespace std;
class myCArray
{
private:
    int *p_arr;
    int  size;
public:
    myCArray();  //缺省构造函数
    myCArray(int*  p_a,int  s);  //构造函数
    myCArray(const  myCArray  &r_other);//复制构造函数
    ~myCArray();       //析构函数
    int  operator[](int  pos)  const;  //访问数组元素值的下标运算符重载函数
    int&  operator[](int  pos);  //设置数组元素值的下标运算符重载函数

	myCArray operator+(const myCArray& zou)
	{
		int* temp = new int[size];
		for (int i = 0;i < size;i++)
			temp[i] = p_arr[i] + zou[i];
		int s = size;
		myCArray tmp(temp, s);
		delete[] temp;
		return tmp;
	}

	myCArray operator-(const myCArray& zou)
	{
		int* temp = new int[size];
		for (int i = 0;i < size;i++)
			temp[i] = p_arr[i] - zou[i];
		int s = size;
		myCArray tmp(temp, s);
		delete[] temp;
		return tmp;
	}
    void  print()  const;
};

myCArray::myCArray(){}

myCArray::~myCArray(){}

myCArray::myCArray(int *p_a, int s)
{
	size = s;
	p_arr = new int[size];
	for (int i = 0;i < size;i++)
		p_arr[i] = p_a[i];
}
myCArray::myCArray(const myCArray &r_other)
{
	size = r_other.size;
	p_arr = new int[size];
	for (int i = 0;i < size;i++)
		p_arr[i] = r_other.p_arr[i];
}

int myCArray::operator[](int pos) const
{
	return p_arr[pos];
}

int& myCArray::operator[](int pos)
{
	if(pos<0 || pos>4)
	{
		cout<<"error";
	}
	return this->p_arr[pos];
}


void  myCArray::print()  const
{
    for(int  i=0;i<this->size  ;i++)
        cout<<this->p_arr[i]<<"    ";
    cout<<endl;
}

int  main()
{   int  a[5]={1,2,3,4,5},b[5]={1,1,1,1,1};
    myCArray  t1(a,5),t2(b,5),t3;
    t3=t1+t2;
    t3.print();
    t3=t1-t2;
    //   t3[4]=1000;
    //   t3.print();
    return  0;
}
