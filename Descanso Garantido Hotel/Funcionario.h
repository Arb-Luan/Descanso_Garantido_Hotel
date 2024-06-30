#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>    // Necess�rio para std::numeric_limits
#include "Pessoa.h"
/*classe funcionario
Representa um funcion�rio, herda atributos da classe pessoa.
Ela gerencia as informa��es dos funcion�rios,como sal�rio,
matr�cula e cargo

*/
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
//Define a matr�cula do funcion�rio
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
//Obt�m a matr�cula do funcion�rio
    std::string getMatricula() const
    {
        return matricula;
    }
//Obt�m o cargo do funcionario
    std::string getCargo() const
    {
        return cargo;
    }
//Obt�m o o sal�rio do funcion�rio
    double getSalario() const
    {
        return salario;
    }
//Gera a matr�cula do funcion�rio
    void generateEmployeeMatricula()
    {
        std::ostringstream oss;
        oss << "EMP" << ++employeeCounter;
        matricula = oss.str();
    }
//Salva no arquivo os dados em um arquivo bin�rio
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
//Cadastra os dados do funcion�rio
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
//Exibe as informa��es do funcion�rio
    void exibirInformacoes()
    {
        std::cout << "Matr�cula: " << matricula << std::endl;
        std::cout << "Nome: " << getNome() << std::endl;
        std::cout << "Idade: " << getAge() << std::endl;
        std::cout << "Cargo: " << cargo << std::endl;
        std::cout << "Sal�rio: " << salario << std::endl;
    }
//Procura o funcion�rio com base na matr�cula
    bool searchFuncionario(const std::string &matriculaToFind)
    {
        return (matricula == matriculaToFind);
    }
//Exibe as informa��es do funcion�rio
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
    //Escreve as informa��es do funcion�rio no arquvio
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
