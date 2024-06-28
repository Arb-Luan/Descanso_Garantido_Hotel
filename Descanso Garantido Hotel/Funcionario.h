#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>    // Necess�rio para std::numeric_limits
#include "Pessoa.h"

class Funcionario : public Pessoa
{
private:
    std::string matricula;
    std::string cargo;
    double salario;
    static int employeeCounter;

public:
    Funcionario()
    {
        matricula = "";
        cargo = "";
        salario = 0.0;
    }

    void setMatricula(const std::string &m)
    {
        matricula = m;
    }

    void setCargo(const std::string &c)
    {
        cargo = c;
    }

    void setSalario(double s)
    {
        salario = s;
    }

    std::string getMatricula() const
    {
        return matricula;
    }

    std::string getCargo() const
    {
        return cargo;
    }

    double getSalario() const
    {
        return salario;
    }

    void generateEmployeeMatricula()
    {
        std::ostringstream oss;
        oss << "EMP" << ++employeeCounter;
        matricula = oss.str();
    }

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

    void cadastrarFuncionario()
    {
        cadastrarC();
        generateEmployeeMatricula();

        std::cout << "Digite o cargo do funcion�rio: ";
        std::getline(std::cin, cargo);

        std::cout << "Digite o sal�rio do funcion�rio: ";
        std::cin >> salario;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Limpa o buffer de entrada

        std::cout << "\nCadastro de funcion�rio realizado com sucesso!" << std::endl;
    }

    void exibirInformacoes()
    {
        std::cout << "Matr�cula: " << matricula << std::endl;
        std::cout << "Nome: " << getNome() << std::endl;
        std::cout << "Idade: " << getAge() << std::endl;
        std::cout << "Cargo: " << cargo << std::endl;
        std::cout << "Sal�rio: " << salario << std::endl;
    }

    bool searchFuncionario(const std::string &matriculaToFind)
    {
        return (matricula == matriculaToFind);
    }

    void showInfo()
    {
        std::cout << "Informa��es do Funcion�rio:" << std::endl;
        std::cout << "Matr�cula: " << matricula << std::endl;
        std::cout << "Nome: " << getNome() << std::endl;
        std::cout << "Idade: " << getAge() << std::endl;
        std::cout << "Cargo: " << cargo << std::endl;
        std::cout << "Sal�rio: " << salario << std::endl;
    }

private:
    void writeString(std::ofstream &outFile, const std::string &str)
    {
        size_t length = str.size();
        outFile.write(reinterpret_cast<const char*>(&length), sizeof(length));
        outFile.write(str.c_str(), length);
    }
};

// Inicializa��o do contador est�tico
int Funcionario::employeeCounter = 0;

#endif // FUNCIONARIO_H_INCLUDED
