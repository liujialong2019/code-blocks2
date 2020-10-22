#include<iostream>
#include<string>
#include<map>
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    int n,s;
    cin>>n>>s;
    string s_sum = to_string(s);
    string str_map[1000];
    str_map[0] = string("1");
    str_map[1] = string("2");
    str_map[2] = string("4");
    str_map[3] = string("16");
    for(int i=4;i<=n;i++)
        str_map[i] = str_map[i-3] + str_map[i-1].substr(str_map[i-4].size()) + str_map[i-2];
    int pos = 0,ans = 0;
    string str = str_map[n];
    while(1){
        pos = str.find(s_sum,pos);
        if(pos==-1)
            break;
        pos++;
        ++ans;
        if(ans>=998244353)
            ans %=998244353;
    }
    cout<<ans<<endl;
    return 0;
}
