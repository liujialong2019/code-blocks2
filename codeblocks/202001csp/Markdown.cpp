#include<iostream>
#include<cstring>
using namespace std;
string Delete_Space(string str);
int main()
{
    cout<<"start:"<<endl;
    string s;
    getline(cin,s);
    cout<<s<<"||"<<endl;
    cout<<Delete_Space(s)<<"||";
    return 0;
}
string Delete_Space(string str) {
	str.erase(0, str.find_first_not_of(' '));
	str.erase(str.find_last_not_of(' ') + 1);
	return str;
}
