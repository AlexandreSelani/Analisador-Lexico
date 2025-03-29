#include <string>
#include <fstream>
class Analex{
    private:
        std::string atomo;
        char proximo;
        int contadorLinhas;

        std::ifstream programaFonte;
        std::ofstream programaEmCodigo;

        Analex();

    public:
        void traducao();
        void PROXIMO();
        void ERRO();
        void CODIGO(std::string atomo);

};