#include<iostream>
#include<fstream>
using namespace std;
struct student
{
    short stu_id,score;
};
int main()
{
    int n;
    ofstream out1("out.txt",ios::binary);
    cin>>n;
    student *a = new student[n];
    student *b = new student[n];
    for(int i=0;i<n;i++)
    {
        cin>>a[i].stu_id;
        cin>>a[i].score;
    }
    if(out1)
    {
        out1.write((char*)a,sizeof(a));
    }
    out1.close();
    ifstream out2("out.txt",ios::binary);
    if(out2)
    {
        for(int i=0;i<n;i++)
            out2.read((char*)(b+i),sizeof(student));
    }
    out2.close();
    ofstream out3("out.txt",ios::app);
    if(out3)
    {
        out3.write((char*)b,sizeof(a));
    }
    out3.close();
    delete[] a;
    delete[] b;
    return 0;
}
