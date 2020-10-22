#include<iostream>
using namespace std;
static void Main(string args[]){
        int s = 0;
        for(int i=1;;i++)
        {
            if(s>50){
                Console.WriteLine("i="+i);
                break;
            }
            if(i%2==0)
            {
                s+=i;
            }
        }
        Console.WriteLine("s="+s);
        Console.ReadLine();
}
int main()
{
    string s1;
    Main(s1);
    return 0;
}
