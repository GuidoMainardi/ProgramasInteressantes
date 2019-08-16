#include <iostream>

using namespace std;

int ackermann(int a, int b){
    if(a == 0){
        return b + 1;
    }
    if(b == 0){
        return ackermann(a - 1, 1);
    }

    return ackermann(a - 1, ackermann(a, b -1));
}

int main(){
    int m, n;
    
    cout << "Digite o valor de m";
    cin >> m;
    
    cout << "Digite o valor de n";
    cin >> n;

    cout << ackermann(m ,n) << endl;

    return 0;
}