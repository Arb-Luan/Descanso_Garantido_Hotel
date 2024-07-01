#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>    // Necessário para std::numeric_limits
#include "Pessoa.h"
/*
* NAME: Funcionario.h
* DESCRIPTION: Classe para objetos do tipo funcionário herdando atributos da classe Pessoa
* PROCESS: 
*    [1]    Gerando variáveis para armazenar informações (nome, endereço, código ou matrícula, idade e cargo)
*    [2]    Gera código ID para cada Funcionário
*    [3]    Grava dados em arquivos binários
*    [4]    Controle de salário, alterando e salvando dados do salário
*/
class Funcionario : public Pessoa
{
private:
        //variáveis para armazenamento dos dados
    std::string matricula;
    std::string cargo;
    double salario;
    static int employeeCounter;

public:
    Funcionario() //construtor padrão
    {
        matricula = "";
        cargo = "";
        salario = 0.0;
    }
//Define a matrícula do funcionário
    void setMatricula(const std::string &m)
    {
        this->matricula = m;
    }
//Define o cargo do funcionario
    void setCargo(const std::string &c)
    {
        this->cargo = c;
    }
//Define o salario do funcionario
    void setSalario(double s)
    {
        this->salario = s;
    }
//Obtém a matrícula do funcionário
    std::string getMatricula() const
    {
        return matricula;
    }
//Obtém o cargo do funcionario
    std::string getCargo() const
    {
        return cargo;
    }
//Obtém o o salário do funcionário
    double getSalario() const
    {
        return salario;
    }
//Gera a matrícula do funcionário
    void generateEmployeeMatricula()
    {
        std::ostringstream oss;
        oss << "EMP" << ++employeeCounter;
        matricula = oss.str();
    }
//Salva no arquivo os dados em um arquivo binário
    void saveToFile(const std::string &filename)
    {
        std::ofstream outFile(filename, std::ios::binary | std::ios::app);
        if (!outFile)
        {
            std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
            return;
        }

        writeString(outFile, getNome());
        int idade = getAge();
        outFile.write(reinterpret_cast<const char*>(&idade), sizeof(idade));
        writeString(outFile, matricula);
        writeString(outFile, cargo);
        outFile.write(reinterpret_cast<const char*>(&salario), sizeof(salario));

        outFile.close();
        std::cout << "Dados salvos com sucesso no arquivo " << filename << std::endl;
    }
//Cadastra os dados do funcionário
    void cadastrarFuncionario()
    {
        cadastrarC();
        generateEmployeeMatricula();
            //Solicitando dados para o usuário
        std::cout << "Digite o cargo do funcionário: ";
        std::getline(std::cin, cargo);

        std::cout << "Digite o salário do funcionário: ";
        std::cin >> salario;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Limpa o buffer de entrada

        std::cout << "\nCadastro de funcionário realizado com sucesso!" << std::endl;
    }
//Exibe as informações do funcionário
    void exibirInformacoes()
    {
        //imprimindo informações do funcionário, caso de pesquisa
        std::cout << "Matrícula: " << matricula << std::endl;
        std::cout << "Nome: " << getNome() << std::endl;
        std::cout << "Idade: " << getAge() << std::endl;
        std::cout << "Cargo: " << cargo << std::endl;
        std::cout << "Salário: " << salario << std::endl;
    }
//Procura o funcionário com base na matrícula
    bool searchFuncionario(const std::string &matriculaToFind)
    {
        return (matricula == matriculaToFind);
    }
//Exibe as informações do funcionário
    void showInfo()
    {
        std::cout << "Informações do Funcionário:" << std::endl;
        std::cout << "Matrícula: " << matricula << std::endl;
        std::cout << "Nome: " << getNome() << std::endl;
        std::cout << "Idade: " << getAge() << std::endl;
        std::cout << "Cargo: " << cargo << std::endl;
        std::cout << "Salário: " << salario << std::endl;
    }

private:
    //Escreve as informações do funcionário no arquvio
    void writeString(std::ofstream &outFile, const std::string &str)
    {
        size_t length = str.size();
        outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
        outFile.write(str.c_str(), length);
    }
};

// Inicialização do contador estático
int Funcionario::employeeCounter = 0;

#endif // FUNCIONARIO_H_INCLUDED
