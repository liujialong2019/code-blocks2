#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
string Delete_Space(string str)
{
    str.erase(0,str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ')+1);
    return str;
}
int main()
{
    ios::sync_with_stdio(false);
    int w,ans = 0;
    bool flag = false;
    string str = "";
    vector<pair<string,int>> vec;
    cin>>w;
    while(getline(cin,str)){
        if(str.size()==count(str.begin(),str.end(),' '))
           flag = true;
        else{
            if(flag||vec.empty())
            {
                if(str.size()>=2&&str.substr(0,2)==("* "))
                   vec.push_back(make_pair(Delete_Space(str.substr(2)),1));
                else
                   vec.push_back(make_pair(Delete_Space(str),3));
                flag = false;
            }
            else
            {
                pair<string,int>& last = vec.back();
                if(last.second<=2){
                    if(str.size()>=2&&str[0]==' '&&str[1]==' '){
                        last.first+=" ";
                        last.first+=Delete_Space(str.substr(2));
                    }
                    else if(str.size()>=2&&str[0]=='*'&&str[1]==' ')
                        vec.push_back(make_pair(Delete_Space(str.substr(2)),2));
                    else
                        vec.push_back(make_pair(Delete_Space(str),3));
                }
                else{
                    if(str.size()>=2&&str[0]=='*'&&str[1]==' ')
                        vec.push_back(make_pair(Delete_Space(str.substr(2)),1));
                    else{
                        last.first+=" ";
                        last.first+=Delete_Space(str);
                    }
                }
            }
        }
    }
    for(int i=0;i<vec.size();i++){
        string str = vec[i].first;
        if(vec[i].second!=2&&i>0)
            ans++;
        if(vec[i].second<=2){
            if(str.size()==0)
                ans++;
        else{
            for(int i=0;i<str.size();i+=(w-3))
            {
                while(i<str.size()&&str[i]==' ')
                    i++;
                ans++;
            }
        }
    }
    else{
        for(int i=0;i<str.size();i+=w)
        {
            while(i<str.size()&&str[i]==' ')
                i++;
            ans++;
        }
    }
  }
  cout<<ans<<endl;
  return 0;
}
