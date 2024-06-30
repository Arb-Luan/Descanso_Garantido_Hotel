#ifndef ESTADIA_H_INCLUDED
#define ESTADIA_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstring>
/* classe Estadia
Representa uma estadia,
serve para gerenciar as
informa��es de uma estadia

*/
class Estadia
{
private:
    std::string codigoEstadia;
    std::string dataEntrada;
    std::string dataSaida;
    int quantidadeDiarias;
    std::string codigoCliente;
    static int estadiaCounter;

public:
    Estadia()//construtor padr�o
    {
        codigoEstadia = "";
        dataEntrada = "";
        dataSaida = "";
        quantidadeDiarias = 0;
        codigoCliente = "";
    }
//Define o codigo de uma estadia
    void setCodigoEstadia(const std::string &codigo)
    {
        this->codigoEstadia = codigo;
    }
//Define a data de entrada
    void setDataEntrada(const std::string &data)
    {
        this->dataEntrada = data;
    }
//Define a data de sa�da
    void setDataSaida(const std::string &data)
    {
        this->dataSaida = data;
    }
//Define a quantidade de diarias
    void setQuantidadeDiarias(int dias)
    {
        this->quantidadeDiarias = dias;
    }
//Define o c�digo do cliente
    void setCodigoCliente(const std::string &codigo)
    {
        this->codigoCliente = codigo;
    }
//Obt�m o c�digo da Estadia
    std::string getCodigoEstadia() const
    {
        return codigoEstadia;
    }
//Obt�m a data de entrada
    std::string getDataEntrada() const
    {
        return dataEntrada;
    }
//Obt�m a data de sa�da
    std::string getDataSaida() const
    {
        return dataSaida;
    }
//Obt�m a quantidade de di�rias
    int getQuantidadeDiarias() const
    {
        return quantidadeDiarias;
    }
//Obt�m o c�digo do cliente
    std::string getCodigoCliente() const
    {
        return codigoCliente;
    }
//Gera o c�digo da estadia
    void generateCodigoEstadia()
    {
        codigoEstadia = "EST" + std::to_string(++estadiaCounter);
    }
//Salva os dados da estadia no arquivo
    void saveToFile(const std::string &filename)
    {
        FILE *outFile = fopen(filename.c_str(), "ab");
        if (!outFile)
        {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        writeString(outFile, codigoEstadia);
        writeString(outFile, dataEntrada);
        writeString(outFile, dataSaida);
        fwrite(&quantidadeDiarias, sizeof(int), 1, outFile);
        writeString(outFile, codigoCliente);

        fclose(outFile);
        std::cout << "Dados de estadia salvos com sucesso no arquivo " << filename << std::endl;
    }

private:
    //Escreve os dados da estadias no arquivo
    void writeString(FILE *outFile, const std::string &str)
    {
        size_t length = str.size();
        fwrite(&length, sizeof(length), 1, outFile);
        fwrite(str.c_str(), sizeof(char), length, outFile);
    }
};

int Estadia::estadiaCounter = 0;

#endif // ESTADIA_H_INCLUDED
