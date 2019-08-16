#include <iostream>
#include <set>
#include <queue>

using namespace std;

typedef long long ll;

int main(){
    int cases, n;
    ll atual;
    cin >> cases;
    while(cases--){
        int maior = 0;
        queue<int> fila;
        cin >> n;
        set<int> set;
        for(int i = 0; i < n; i++){
            cin >> atual;
            if(set.count(atual)){
                while(fila.front() != atual){
                    set.erase(fila.front());
                    fila.pop();
                }
                set.erase(atual);
                fila.pop();
            }
            fila.push(atual);
            set.insert(atual);
            if(fila.size() > maior){
                maior = fila.size();
            }
        }
        cout << maior << endl;
    }
    
}