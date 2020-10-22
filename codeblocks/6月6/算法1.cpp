#include <iostream>
using namespace std;
int D[100][100];
int num;
//自底向下
int MaxSum(int num){
    int i, j , x;
    for(i = num - 1; i >= 1; i --)
        for(j = 1; j <= i; j ++){
            D[i][j] = max(D[i+1][j],D[i+1][j+1]) + D[i][j];
        }
    return D[1][1];
}
int main(int argc, char const *argv[])
{
    int i,j;
    int count1=0;//cout<<"输入总测试数目"<<endl;

    cin>>count1;
    for(int k=0;k<count1;k++)
    {
        //cout<<"这是第"<<(k+1)<<"组测试样例"<<endl;
    cin >> num;
    for(i = 1; i <= num; i ++)
        for(j = 1; j <= i; j ++)
            cin >> D[i][j];
            //cout<<"通过的路径为："<<endl;
    cout <<endl<< MaxSum(num) << endl;//"路径的总长度为："
    }
    return 0;
}
/*
5
7
3  8
8  1  0
2  7  4  4
4  5  2  6  5
*/
