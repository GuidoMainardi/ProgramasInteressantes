#include <iostream>
#include <tuple>
#include <map>

using namespace std;

typedef long long double ll;

map<tuple<ll, ll>, ll> M;


int ackermann(ll a, ll b){

    //cout << a << " " << b << endl;

    ll res;

    tuple<ll, ll> t = make_tuple(a, b);

    if (M.count(t)) {
        return M[t];
    } else {
        if(a == 0){
            res = b + 1;
        }
        else if(b == 0){
            res = ackermann(a - 1, 1);
        } else {
            res = ackermann(a - 1, ackermann(a, b -1));
        }
        M[t] = res;
        return res;
    }
}

void pre_process() {
    for (int i = 0; i < 3; ++i)
        for(int j = 0; j < (int)10e4; ++j)
            ackermann(i, j);
}


int main(){
   ll m, n;
    /*
    cout << "Digite o valor de m: ";
    cin >> m;
    
    cout << "Digite o valor de n: ";
    cin >> n;

    cout << ackermann(m, n) << endl;
    */
   m = 4;
   n = 2;
   //pre_process();
   cout << ackermann(m, n) << endl;
   return 0;
}