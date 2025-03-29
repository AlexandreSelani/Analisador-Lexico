#include <string>
#include <fstream>
#include <unordered_map>
class Analex{
    private:
        std::string atomo;
        char proximo;
        int contadorLinhas;
        int contadorDeIdentificadores;
        std::unordered_map<std::string, std::string> tabelaDeSimbolos;
        std::unordered_map<std::string, int> tabelaDeIdentificadores;
        std::ifstream programaFonte;
        std::ofstream programaEmCodigo;
        
        void pulaLinhas();
        void criaTabelaSimbolos();

        void traduzSimbolosEspeciais();
        void traduzNomes(std::string *token);
        void traduzNumeros(std::string *token);

        void PROXIMO();
        void ERRO(std::string atomo);//TEM QUE MUDAR
        void CODIGO(std::string *token);

        

    public:
        void traducao();
        Analex();
        void fechaArq();
        

};