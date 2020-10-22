#include<iostream>
using namespace std;
int main()
{
    int a,b;
    cin >> a>> b;
    if (b == 0)
        cout << "0 0";
    else
        cout << a * b <<" " << b - 1;
    while(cin>>a>>b)
    {
        if(b!=0)
            cout<<" "<<a*b<<" "<<b-1;

    }
    return 0;
}
/*/*
#include <iostream>
using namespace std;

int main() {
		int a1;
		int a2;
		cin >> a1 >> a2;
		if (a2 == 0){
			cout << "0 0";
			return 0;
		}
		else{
			cout << a1 * a2 << ' ' << a2 - 1;
		}
		while (cin >> a1 >> a2) {
			if (a2 != 0) cout << ' ' << a1 * a2 << ' ' << a2 - 1;
		}
}
*/
