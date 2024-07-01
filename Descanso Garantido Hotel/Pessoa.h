#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#include <iostream>
#include <string>
#include <stdexcept>  // Necessário para std::invalid_argument
#include <limits>     // Necessário para std::numeric_limits
/
* NAME: Pessoa.h
* DESCRIPTION: uperclasse do sistema tendo atributos gerais para pessoa (Cliente ou Funcionário)
* PROCESS: 
*    [1]    Gerando variáveis para armazenar informações
*    [2]    Construtor padrão para verificar idades válidas
*    [3]    Grava dados de nome e idade no sistema
*/
class Pessoa
{
private:
    std::string nome;
    int idade;

public://consturor padrão
    Pessoa()
    {
        nome = "Sem nome";
        idade = 0;
    }
//Define o nome
    void setNome(std::string n)
    {
        this->nome = n;
    }
//Define a idade de uma
    void setAge(int a)
    {
        if (a < 0 || a < 18)
        {
            throw std::invalid_argument("Idade inválida. Deve ser maior ou igual a 18.");
        }
        this->idade = a;
    }
//Obtém o nome
    std::string getNome()
    {
        return nome;
    }
//obtém a idade
    int getAge()
    {
        return idade;  // Corrigido: retornar 'idade' em vez de 'age'
    }
    //Método que obtém e define os dados do objeto pessoa
    void cadastrarC()
    {
        std::cout << "Digite o nome da pessoa:" << std::endl;
        std::getline(std::cin >> std::ws, nome);  // std::ws ignora espaços em branco iniciais

        bool ageValid = false;
        while (!ageValid)
        {
            try
            {
                std::cout << "Digite a idade:" << std::endl;
                std::cin >> idade;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Limpa o buffer de entrada
                setAge(idade);
                ageValid = true;
            }
            catch (const std::invalid_argument &e)
            {
                std::cout << e.what() << std::endl;  // Imprime a mensagem de erro
            }
        }
    }
};

#endif // PESSOA_H_INCLUDED
