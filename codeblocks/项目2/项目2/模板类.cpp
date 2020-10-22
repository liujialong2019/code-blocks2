#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class Array
{
public:
    vector<T> a;
    Array(int n) {}
    void input(int n)
    {
        for(int i=0; i<n; i++)
        {
            T tmp;
            cin>>tmp;
            a.push_back(tmp);
        }
    }
    T& operator[](int n)
    {
        return a[n];
    }
};
int cccc(int a,int b)

{
    if(b==0)
        return a;
    else
        return cccc(b,a%b);
}
class Fract{
public:
    int n,m;
    Fract(int a=0,int b=1):n(a),m(b)
    {
        int Max,Min,c,x,y;
        if(a<0) a*=-1;
        if(b<0) b*=-1;
        c=cccc(max(a,b),min(a,b));
        if(m<0)
        {
            n*=-1;
            m*=-1;
        }
        if(c!=1)
        {
            n/=c;
            m/=c;
        }
    }
    void show()
    {
        if(n==0||m==1)
            cout<<n<<endl;
        else
        {
            cout<<n<<"/"<<m<<endl;
        }
    }
    Fract &operator +=(Fract &x){
        Fract y(x.n*m+x.m*n,x.m*m);
        return *this=y;

    }
    operator double()
    {
        return (double)n/m*1.0;
    }
    friend istream &operator>>(istream &is,Fract &f)
    {
        is>>f.n>>f.m;
        return is;
    }
};
Fract operator *(Fract f1,Fract f2)

{

    Fract f(f1.n*f2.n,f1.m*f2.m);

    return f;

}
int main()
{
    unsigned int n;
    cin >> n;
    Array<double> db(n);
    db.input(n);
    double dbsum(0.0);
    for (unsigned int i = 0; i < n; i++)
        dbsum += db[i];
    cout << dbsum << endl;

    cin >> n;
    Array<Fract> fr(n);
    fr.input(n);
    Fract frsum(0, 1);
    for (unsigned int i = 0; i < n; i++)
        frsum += fr[i];
    frsum.show();
}

