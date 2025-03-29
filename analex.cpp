//ALEXANDRE LUIS FRATA SELANI - BCC
//RA: 231020759
//Linux Mint 22.1
//g++ (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0

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

        void pulaLinhas(){
            programaEmCodigo << std::endl;
            
            contadorLinhas++;
            PROXIMO();
            
            programaEmCodigo<<contadorLinhas<<"\t";

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

        }

        void traduzNumeros(std::string *token){
            do{   
                *token+=proximo;
                PROXIMO();
            }while(verificaSeEhDigito(proximo));

            if(verificaSeEhLetra(proximo)){
                std::string temp;
                temp+=proximo;
                ERRO(temp);
            }
            else{
                CODIGO(token);
            }

        }

        void PROXIMO(){proximo = programaFonte.get();}

        void ERRO(std::string atomo){
            std::cout<<"ERRO LEXICO NA LINHA "<<contadorLinhas<<"\n";
            
            fechaArq();
            remove("Result.txt");
            exit(EXIT_FAILURE);
        }

        void CODIGO(std::string *token){
            std::string codigo;

            if(token->length()<=2 && (tabelaDeSimbolos.find(*token)!=tabelaDeSimbolos.end())){
                codigo=tabelaDeSimbolos[*token];
            }

            else if(verificaReservadas(*token)){
                codigo = *token;
                
                for(int i=0;i<codigo.length();i++){
                    codigo[i]=toupper(codigo[i]);
                }
                
            }
            else if(verificaSeEhDigito(*token)){
                codigo = "NUM_INTEIRO";
            }
            else{
                if(tabelaDeIdentificadores.empty() || tabelaDeIdentificadores.find(*token)==tabelaDeIdentificadores.end()){
                    tabelaDeIdentificadores.insert({*token,contadorDeIdentificadores});
                    
                    codigo = ("id" + std::to_string(contadorDeIdentificadores));
                    contadorDeIdentificadores++;

                }else{
                    codigo = ("id" + std::to_string(tabelaDeIdentificadores.at(*token)));
                }
            }

            programaEmCodigo << codigo+" ";

        }
    
    public:
        Analex(){
            criaTabelaSimbolos();
            

            programaFonte.open("Trab1_Compiladores.txt");
            programaEmCodigo.open("Resultado.txt");

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
                if(proximo==13){
                    pulaLinhas();}

                else if(verificaSimbEspeciais(proximo)){
                    traduzSimbolosEspeciais();
                }

                else if(verificaSeEhLetra(proximo)){
                    traduzNomes(&atomo);
                    CODIGO(&atomo);
                }

                else if(verificaSeEhDigito(proximo)){
                    traduzNumeros(&atomo);
                }

                else if(proximo==' '||proximo=='\t'||proximo==10) PROXIMO();

                else ERRO(atomo);
            }
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