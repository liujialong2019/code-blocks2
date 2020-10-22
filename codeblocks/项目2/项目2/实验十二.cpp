/*#include <iostream>
#include <exception>
#include <typeinfo>
using namespace std;

class MyException1:public exception
{
public:
	MyException1() {};
    ~MyException1() {};
	void what() {cout << "exception: 12MyException1" << endl <<"Return to main()"<<endl;};
};
class MyException2:public exception
{
public:
	MyException2() {};
    ~MyException2() {};
	void what() {cout << "exception: 12MyException2" << endl <<"Return to main()"<<endl;};
};
int divide(int a,int b)
{
    if(b==0)
        throw b;
    return a/b;
}

int  main()
{
        int  id,k;
        cin>>id;
        char  a;
        string  s="hello";
          try
        {
                switch  (id)
                {
                case  1:
                        throw  MyException1();
                        break;
                case  2:
                        throw  MyException2();
                        break;
                case  3:
                        k=divide(8,0);
                        break;
                case  4:
                        a=s.at(10);
                        cout<<a<<endl;
                        break;
                default:
                        break;
                }
        }
        catch  (MyException1  &e)
        {
              cout  <<  "exception:  "<<e.what()<<  endl;
        }
        catch  (MyException2  &e)
        {
                cout  <<  "exception:  "<<e.what()<<  endl;
        }
        catch  (int  &e)
        {
                cout  <<  "exception:  "<<e<<  endl;
        }
        catch(exception  &e)
        {
              cout  <<  "exception:  "<<e.what()<<  endl;
        }
        cout<<"Return  to  main()"<<endl;
        return  0;
}*/

#include <iostream>
#include<exception>//这是下面要继承的类库
#include <typeinfo>//包含typeid函数，返回当前类的运行时的类型。
using namespace std;
class MyException1:public exception//继承自exception类
{
public:
    MyException1() {};//构造函数
    ~MyException1() {};//析构函数
    const char* what() { return typeid(MyException1).name(); }
    //返回当前类的运行时的类型
};
class MyException2:public exception
{
public:
    MyException2() {};//构造函数
    ~MyException2() {};//析构函数
    const char* what() { return typeid(MyException2).name(); }
     //返回当前类的运行时的类型
};
int divide(int a, int b)
{
    if (b == 0)throw b;
    //如果分母为0，就用throw抛出异常（int型的异常），保护程序
    //执行了throw就不会执行throw后面的代码
    return a/b ;
}//除法运算函数
int  main()
{
    int  id, k;
    cin >> id;//从键盘读入数字
    char  a;
    string  s = "hello";
    try
    {
        switch (id)//选择函数根据不同的数字执行不同的命令
        {
        case  1:
            throw  MyException1();//抛出MyException1型的异常
            break;
        case  2:
            throw  MyException2();//MyException2型的异常
            break;
        case  3:
            k = divide(8, 0);//分母为0的情况
            break;
        case  4:
            a = s.at(10);
            //s.at(10)返回下标为10的元素的引用
            //但是用at会抛出异常(exception型）
            //因为字符串s只有6位，但是s(5)好像也会出错
            cout << a << endl;
            break;
        default:
            break;
        }
    }
    catch (MyException1& e)
    {
        cout << "exception:  " << e.what() << endl;
    }//抓住MyException1型的异常并且执行上面的操作
    catch (MyException2& e)
    {
        cout << "exception:  " << e.what() << endl;
    }//抓住MyException2型的异常并且执行上面的操作
    catch (int& e)
    {
        cout << "exception:  " << e << endl;
    }//抓住int型的异常并且执行上面的操作
    catch (exception& e)
    {
        cout << "exception:  " << e.what() << endl;
    }//抓住exception型的异常并且执行上面的操作
    cout << "Return  to  main()" << endl;
    return  0;
}


