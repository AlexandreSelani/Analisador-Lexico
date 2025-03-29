//ALEXANDRE LUIS FRATA SELANI
//RA: 231020759

#include "AUX.h"
#include <iostream>
#include <string>
#include <fstream>


class Analex{
    private:
        std::string atomo;
        char proximo;
        int contadorLinhas=1;
        int codigo;

        std::ifstream programaFonte;
        std::ofstream programaEmCodigo;

    public:
        Analex(){
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
                    traduzNomes();

                    //if(verificaReservadas(atomo)) 
                    CODIGO(atomo);
                    
                    //atomo="";//SE TIVER DANDO ERRADO PODE SER ISSO. EU QUE COLOQUEI
                    
                }

                else if(verificaSeEhDigito(proximo)){
                    traduzNumeros();
                }
                else if(proximo ==' ' || proximo=='\t') PROXIMO();
                else{
                    atomo+=proximo;
                    ERRO(atomo);
                }  
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
                std::cout << s<<" ";
                CODIGO(s);
            
        }

        void traduzNomes(){
            do{
                std::cout<< proximo;
                atomo+=proximo;
                PROXIMO();
            }while((verificaSeEhLetra(proximo) || verificaSeEhDigito(proximo)));
            
            //]std::cout<< "saiu";
        }

        void traduzNumeros(){
            do{
                std::cout<< proximo;
                atomo+=proximo;
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

        void CODIGO(std::string atomo){
            std::string codigo;

            if(atomo.length()==1 && verificaSimbEspeciais(atomo[0])){
                switch(atomo[0]){
                    case ',': codigo = "V"; break; //V DE VIRGULA
                    case '.': codigo = "P"; break; //P DE PONTO
                    case ';': codigo = "PV"; break; //PV DE PONTO E VIRGULA
                    case '(': codigo = "PAREN"; break;//PAREN (
                    case ')': codigo = "TESIS"; break;//TESIS )
                    case ':': codigo = "DOISP"; break;//DOISP DE DOIS PONTOS
                    case '=': codigo = "IGUAL"; break;//IGUAL DE IGUAL A 
                    case '<': codigo = "ESQ";break;//ESQ DE SETA ESQUERDA
                    case '>': codigo = "DIR"; break; //DIR DE SETA DIREITA
                    case '+': codigo = "ADD"; break; //ADD DE ADICAO
                    case '-': codigo = "SUB"; break; //SUB DE SUBTRACAO
                    case '*': codigo = "MULT"; break; //MULT DE MULTIPLICACAO

                }
            }else if(atomo[0]==':' && atomo[1]=='=') codigo="ATR"; //atr de atribuicao

            else{
                codigo = atomo;
                
                for(int i=0;i<codigo.length();i++){
                    codigo[i]=toupper(codigo[i]);
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