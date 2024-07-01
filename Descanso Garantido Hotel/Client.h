#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <iostream>
#include <cstdio>
#include <string>
#include "Pessoa.h"
/*
* NAME: Client.h
* DESCRIPTION: Classe para objetos do tipo cliente herdando atributos da classe Pessoa
* PROCESS: 
*    [1]    Gerando variáveis para armazenar informações
*    [2]    Gera código ID para cada Cliente
*    [3]    Calcula e soma pontos de Fidelidade para cada cliente(em estadia)
*    [4]    Grava dados em arquivos binários
*/
class Client : public Pessoa
{
private:
    std::string code;
    std::string address;
    std::string contact;
    int pontosFidelidade;
    static int clientCounter;

public:
    Client()//Construtor padrão
    {
        code = "";
        address = "";
        contact = "";
        pontosFidelidade = 0;
    }
//Define  o código do cliente
    void setCode(const std::string &c)
    {
        this->code = c;
    }
//Define o endereço do cliente
    void setAddress(const std::string &a)
    {
        this->address = a;
    }
//Define o contato do cliente
    void setContact(const std::string &c)
    {
        this->contact = c;
    }
//Obtém o código do cliente
    std::string getCode() const
    {
        return code;
    }
//Obtém o endereço do cliente
    std::string getAddress() const
    {
        return address;
    }
//Obtém o contato do cliente
    std::string getContact() const
    {
        return contact;
    }
//Obtém o numero dos pontos de fidelidade
    int getPontosFidelidade() const
    {
        return pontosFidelidade;
    }
//Soma pontos de fidelidade
    void addPontosFidelidade(int pontos)
    {
        pontosFidelidade += pontos;
    }
//Gera o código de Cliente
    void generateClientCode()
    {
        clientCounter++;
        code = "CL" + std::to_string(clientCounter);
    }
//Salva os dados do cliente num arquivo binário
    void saveToFile(const std::string &filename)
    {
        FILE *outFile = fopen(filename.c_str(), "ab");
        if (!outFile)
        {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        writeString(outFile, getNome());
        int idade = getAge();
        fwrite(&idade, sizeof(idade), 1, outFile);
        writeString(outFile, code);
        writeString(outFile, address);
        writeString(outFile, contact);
        fwrite(&pontosFidelidade, sizeof(pontosFidelidade), 1, outFile);

        fclose(outFile);
        std::cout << "Dados salvos com sucesso no arquivo " << filename << std::endl;
    }
//Cadastra o cliente
    void cadastrarCliente()
    {
        cadastrarC();
        generateClientCode();

        std::cout << "Digite o endereço do cliente: ";
        std::getline(std::cin, address);

        std::cout << "Digite o contato do cliente: ";
        std::getline(std::cin, contact);

        std::cout << "\nCadastro de cliente realizado com sucesso!" << std::endl;
    }
//Lê os dados do cliente em um arquivo
    void readFromFile(const std::string &filename)
    {
        FILE *inFile = fopen(filename.c_str(), "rb");
        if (!inFile)
        {
            std::cerr << "Erro ao abrir o arquivo para leitura." << std::endl;
            return;
        }

        while (!feof(inFile))
        {
            std::string nome = readString(inFile);
            setNome(nome);

            int idade;
            fread(&idade, sizeof(idade), 1, inFile);
            setAge(idade);

            std::string code = readString(inFile);
            setCode(code);

            std::string address = readString(inFile);
            setAddress(address);

            std::string contact = readString(inFile);
            setContact(contact);

            int pontosFidelidade;
            fread(&pontosFidelidade, sizeof(pontosFidelidade), 1, inFile);
            addPontosFidelidade(pontosFidelidade);
        }

        fclose(inFile);
    }
//mostra as informações de um cliente
    void showInfo()
    {
        std::cout << "\nInformações do Cliente:" << std::endl;
        std::cout << "\nNome: " << getNome() << std::endl;
        std::cout << "\nIdade: " << getAge() << std::endl;
        std::cout << "\nCódigo: " << code << std::endl;
        std::cout << "\nEndereço: " << address << std::endl;
        std::cout << "\nContato: " << contact << std::endl;
        std::cout << "nPontos de Fidelidade: " << pontosFidelidade << std::endl;
    }
//Procura um cliente com base no critério inserido
    bool searchClient(const std::string &searchTerm)
    {
        return (code == searchTerm || getNome() == searchTerm);
    }

private:
    //Escreve no arquivo salvando os dados em código binário
    void writeString(FILE *file, const std::string &str)
    {
        size_t length = str.size();
        fwrite(&length, sizeof(length), 1, file);
        fwrite(str.c_str(), sizeof(char), length, file);
    }
//Lê as strings no arquivo binário
    std::string readString(FILE *file)
    {
        size_t length;
        fread(&length, sizeof(length), 1, file);
        char *buffer = new char[length + 1];
        fread(buffer, sizeof(char), length, file);
        buffer[length] = '\0';
        std::string str(buffer);
        delete[] buffer;
        return str;
    }
};

int Client::clientCounter = 0;

#endif // CLIENT_H_INCLUDED
