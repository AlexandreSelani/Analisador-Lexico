#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream arq;
    arq.open("Trab1_Compiladores.txt");

    if(!arq) cout << "ohsfdasuio";
    char c = arq.get();

    while(c!=EOF){
        cout<<(int)c<<endl;
        c = arq.get();
    }
}