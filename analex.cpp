//ALEXANDRE LUIS FRATA SELANI
//RA: 231020759

#include "AUX.h"
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

class Analex{
    private:
        std::string atomo;
        char proximo;
        int contadorLinhas=1;
        int contadorDeIdentificadores = 1;

        std::unordered_map<std::string, std::string> tabelaDeSimbolos;
        std::unordered_map<std::string, int> tabelaDeIdentificadores;

        std::ifstream programaFonte;
        std::ofstream programaEmCodigo;

        void criaTabelaSimbolos(){
            tabelaDeSimbolos.insert({",", "V"}); // V DE VIRGULA
            tabelaDeSimbolos.insert({".", "P"}); // P DE PONTO
            tabelaDeSimbolos.insert({";", "PV"}); // PV DE PONTO E VIRGULA
            tabelaDeSimbolos.insert({"(", "PAREN"}); // PAREN (
            tabelaDeSimbolos.insert({")", "TESIS"}); // TESIS )
            tabelaDeSimbolos.insert({":", "DOISP"}); // DOISP DE DOIS PONTOS
            tabelaDeSimbolos.insert({"=", "IGUAL"}); // IGUAL DE IGUAL A 
            tabelaDeSimbolos.insert({"<", "ESQ"}); // ESQ DE SETA ESQUERDA
            tabelaDeSimbolos.insert({">", "DIR"}); // DIR DE SETA DIREITA
            tabelaDeSimbolos.insert({"+", "ADD"}); // ADD DE ADICAO
            tabelaDeSimbolos.insert({"-", "SUB"}); // SUB DE SUBTRACAO
            tabelaDeSimbolos.insert({"*", "MULT"}); // MULT DE MULTIPLICACAO
            tabelaDeSimbolos.insert({":=", "ATR"}); // ATR DE ATRIBUICAO
        }
        

        void criaTabelaIdentificadores(){

        }

    public:
        Analex(){
            criaTabelaSimbolos();
            criaTabelaIdentificadores();

            programaFonte.open("Trab1_Compiladores.txt");
            programaEmCodigo.open("Result.txt");

            if(!(programaFonte.is_open() && programaEmCodigo.is_open())){
                std::cout<< "erro na abertura de arquivos";
            }
            else{
                proximo = programaFonte.get();
                programaEmCodigo<<contadorLinhas<<"\t";
            }


        }

        void traducao(){
            

            while(proximo!=EOF){
                atomo = "";
                pulaLinhas();

                if(verificaSimbEspeciais(proximo)){
                    traduzSimbolosEspeciais();
                }

                else if(verificaSeEhLetra(proximo)){
                    traduzNomes(&atomo);

                    //if(verificaReservadas(atomo)) 
                    CODIGO(&atomo);
                    
                    //atomo="";//SE TIVER DANDO ERRADO PODE SER ISSO. EU QUE COLOQUEI
                    
                }

                else if(verificaSeEhDigito(proximo)){
                    traduzNumeros(&atomo);
                }
                else PROXIMO();
            }
        }

        void pulaLinhas(){
            while (proximo == '\n'){
                programaEmCodigo << std::endl;
                
                contadorLinhas++;
                PROXIMO();
                
                programaEmCodigo<<contadorLinhas<<"\t";
                
            }
           // std::cout<< "saiu";
        }

        void traduzSimbolosEspeciais(){
            
                std::string s;

                char temp = proximo;
                PROXIMO();

                s+=temp;

                if(temp==':' && proximo == '='){

                    s+=proximo;
                    PROXIMO();
                }
                
                CODIGO(&s);
            
        }

        void traduzNomes(std::string *token){
            do{
                
                *token+=proximo;
                PROXIMO();
            }while((verificaSeEhLetra(proximo) || verificaSeEhDigito(proximo)));

            
            
            //]std::cout<< "saiu";
        }

        void traduzNumeros(std::string *token){
            do{
                
                *token+=proximo;
                PROXIMO();
            }while(verificaSeEhDigito(proximo));

            if(verificaSeEhLetra(proximo)){
                std::string temp;
                temp+=proximo;
                ERRO(temp);}
        }

        void PROXIMO(){proximo = programaFonte.get();}

        void ERRO(std::string atomo){
            if(atomo.length()==1 && !(verificaSeEhDigito(atomo[0]) || verificaSeEhLetra(atomo[0]))) std::cout<<"!!! Simbolo nao reconhecido na linha " << contadorLinhas<<" !!!";

            
            fechaArq();
            remove("Result.txt");
            exit(EXIT_FAILURE);
        }

        void CODIGO(std::string *token){
            std::string codigo;
            std::cout << *token +" ";

            if(token->length()<=2 && (tabelaDeSimbolos.find(*token)!=tabelaDeSimbolos.end())){
                codigo=tabelaDeSimbolos[*token];
                std::cout<<"simbolo especial" << std::endl;
            }

            else if(verificaReservadas(*token)){
                codigo = *token;
                
                for(int i=0;i<codigo.length();i++){
                    codigo[i]=toupper(codigo[i]);
                }
                std::cout<<"reservada" << std::endl;
            }
            else{
                if(tabelaDeIdentificadores.empty() || tabelaDeIdentificadores.find(*token)==tabelaDeIdentificadores.end()){
                    tabelaDeIdentificadores.insert({*token,contadorDeIdentificadores});
                    std::cout<<"id novo" << std::endl;
                    
                    codigo = ("id" + std::to_string(contadorDeIdentificadores));
                    contadorDeIdentificadores++;

                    
                }else{
                    std::cout<<"id velho" << std::endl;
                    codigo = ("id" + std::to_string(tabelaDeIdentificadores.at(*token)));
                }
            }

            programaEmCodigo << codigo+" ";

        }

        void fechaArq(){
            programaEmCodigo.close();
            programaFonte.close();
        }

};

int main(){
    Analex analisador;
    analisador.traducao();
    analisador.fechaArq();
}