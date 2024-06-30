#ifndef QUARTO_H_INCLUDED
#define QUARTO_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <string>
/*classe Quarto
Representa um quarto, com seus atributos n�mero, quantidade de h�spedes
valor da di�ria e se est� ou n�o ocupado
*/
class Quarto
{
private:
    std::string numeroQuarto;
    int quantidadeHospedes;
    double valorDiaria;
    bool ocupado;
    std::string codigoEstadia;

public:
    Quarto()//Construtor parametrizado(ou personalizado)
        : numeroQuarto(""), quantidadeHospedes(0), valorDiaria(0.0), ocupado(false), codigoEstadia("") {}
//define o n�mero do quarto
    void setNumeroQuarto(const std::string& num)
    {
        this->numeroQuarto = num;
    }
//Define a quantidade de Hospedes
    void setQuantidadeHospedes(int hospedes)
    {
        this->quantidadeHospedes = hospedes;
    }
//Define o Valor da di�ria
    void setValorDiaria(double valor)
    {
        this->valorDiaria = valor;
    }
//Define se est� ocupado ou n�o
    void setOcupado(bool estado)
    {
        this->ocupado = estado;
    }
//Define o c�digo da estadia
    void setCodigoEstadia(const std::string& cod)
    {
        this->codigoEstadia = cod;
        ocupado = !cod.empty(); // Se h� c�digo de estadia, o quarto est� ocupado
    }

    std::string getNumeroQuarto() const
    {
        return numeroQuarto;
    }
//Obt�m a quantidade de h�spedes
    int getQuantidadeHospedes() const
    {
        return quantidadeHospedes;
    }
//Obt�m o valor da Di�ria
    double getValorDiaria() const
    {
        return valorDiaria;
    }
//Obt�m o status se est� ocupado ou n�o
    bool getOcupado() const
    {
        return ocupado;
    }

    std::string getCodigoEstadia() const
    {
        return codigoEstadia;
    }
//Salva os dado no quarto no arquivo bin�rio
    void saveToFile(const std::string& filename)
    {
        FILE* outFile = fopen(filename.c_str(), "ab");
        if (!outFile)
        {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        writeString(outFile, numeroQuarto);
        fwrite(&quantidadeHospedes, sizeof(quantidadeHospedes), 1, outFile);
        fwrite(&valorDiaria, sizeof(valorDiaria), 1, outFile);
        fwrite(&ocupado, sizeof(ocupado), 1, outFile);
        writeString(outFile, codigoEstadia);

        fclose(outFile);
        std::cout << "Dados do quarto salvos com sucesso no arquivo " << filename << std::endl;
    }
//L� os dados do quarto em um arquivo bin�rio
    void readFromFile(const std::string& filename)
    {
        FILE* inFile = fopen(filename.c_str(), "rb");
        if (!inFile)
        {
            std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
            return;
        }

        while (!feof(inFile))
        {
            numeroQuarto = readString(inFile);
            fread(&quantidadeHospedes, sizeof(quantidadeHospedes), 1, inFile);
            fread(&valorDiaria, sizeof(valorDiaria), 1, inFile);
            fread(&ocupado, sizeof(ocupado), 1, inFile);
            codigoEstadia = readString(inFile);
        }

        fclose(inFile);
    }

private:
    //Escreve os dados no arquivo bin�rio
    void writeString(FILE* file, const std::string& str)
    {
        size_t length = str.size();
        fwrite(&length, sizeof(length), 1, file);
        fwrite(str.c_str(), sizeof(char), length, file);
    }
//L� os dados do quarto do arquivo bin�rio
    std::string readString(FILE* file)
    {
        size_t length;
        fread(&length, sizeof(length), 1, file);
        char* buffer = new char[length + 1];
        fread(buffer, sizeof(char), length, file);
        buffer[length] = '\0';
        std::string str(buffer);
        delete[] buffer;
        return str;
    }
};

#endif // QUARTO_H_INCLUDED
