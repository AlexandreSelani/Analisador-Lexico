#include "AUX.h"
#include <unordered_set>
#include <string>

std::unordered_set<char> simbolosEspeciais{',','.',';','(',')',':','=','<','>','+','-','*'};
std::unordered_set<std::string> palavrasReservadas{"program", "label", "var", "procedure", "function", "begin", "end", "if", "then", "else", "while", "do", "or", "and", "div", "not"};
bool verificaSimbEspeciais(char caracter){ 

    return simbolosEspeciais.find(caracter)!= simbolosEspeciais.end(); 
    //se caracter estiver na lista de simbolos, true. Senao, false    
}

bool verificaSeEhDigito(char caracter){
    return (caracter >= 48 && caracter<= 57);    
    
}

bool verificaReservadas(std::string atomo){
    return palavrasReservadas.find(atomo)!= palavrasReservadas.end(); 
}

bool verificaSeEhLetra(char caracter){
    return ((caracter>=65 && caracter <= 90) || (caracter>=97 && caracter<=122));
}

