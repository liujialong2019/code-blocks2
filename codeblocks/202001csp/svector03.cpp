#include <bits/stdc++.h>

using namespace std;

int main() {
    int n,a,b,index,value;
    long long total = 0;
    //scanf("%d%d%d", &n, &a, &b);
    cin>>n>>a>>b;
    vector<pair<int,int>>v1,v2;
    for(int i=0;i<a;i++)
    {
        //scanf("%d%d", &index, &value);
        cin>>index>>value;
        v1.emplace_back(make_pair(index,value));
    }

    for(int i=0;i<b;i++)
    {
        //scanf("%d%d", &index, &value);
        cin>>index>>value;
        v2.emplace_back(make_pair(index,value));
    }
    for(int i = 0,j=0;i < v1.size()&&j<v2.size();)
        if (v1[i].first > v2[j].first)
            j++;
        else if (v1[i].first < v2[j].first)
            i++;
        else
            total += v1[i++].second * v2[j++].second;

    cout<<total;
    return 0;
}


