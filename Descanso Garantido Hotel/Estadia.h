#ifndef ESTADIA_H_INCLUDED
#define ESTADIA_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <cstring>
/* 
* NAME: Client.h
* DESCRIPTION: Classe para objetos do tipo cliente herdando atributos da classe Pessoa
* PROCESS: 
*    [1]    Gerando variáveis para armazenar informações
*    [2]    Gera código ID para cada estadia ou reserva criada
*    [4]    Grava dados em arquivos binários
* NOTES:
*     Estadia é a classe que é vinculada em procedimentos a todos os outros objetos 
*/
class Estadia
{
private:
        //Variáveis para guardar dados e informações da estadia
    std::string codigoEstadia;
    std::string dataEntrada;
    std::string dataSaida;
    int quantidadeDiarias;
    std::string codigoCliente;
    static int estadiaCounter;

public:
    Estadia()//construtor padrão
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
//Define a data de saída
    void setDataSaida(const std::string &data)
    {
        this->dataSaida = data;
    }
//Define a quantidade de diarias
    void setQuantidadeDiarias(int dias)
    {
        this->quantidadeDiarias = dias;
    }
//Define o código do cliente
    void setCodigoCliente(const std::string &codigo)
    {
        this->codigoCliente = codigo;
    }
//Obtém o código da Estadia
    std::string getCodigoEstadia() const
    {
        return codigoEstadia;
    }
//Obtém a data de entrada
    std::string getDataEntrada() const
    {
        return dataEntrada;
    }
//Obtém a data de saída
    std::string getDataSaida() const
    {
        return dataSaida;
    }
//Obtém a quantidade de diárias
    int getQuantidadeDiarias() const
    {
        return quantidadeDiarias;
    }
//Obtém o código do cliente
    std::string getCodigoCliente() const
    {
        return codigoCliente;
    }
//Gera o código da estadia
    void generateCodigoEstadia()
    {
        codigoEstadia = "EST" + std::to_string(++estadiaCounter);
    }
~Estadia()
{
        std::cout<<"Baixa na estadia registrada com sucesso!\n";
}
//Salva os dados da estadia no arquivo
    void saveToFile(const std::string &filename)
    {
        //Abrindo arquivo para leitura e alteração 
        FILE *outFile = fopen(filename.c_str(), "ab");
        if (!outFile)
        {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }
        //Anexando dados ao arquivo ja existente
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
