#ifndef PESSOA_H_INCLUDED
#define PESSOA_H_INCLUDED

#include <iostream>
#include <string>
#include <stdexcept>  // Necess�rio para std::invalid_argument
#include <limits>     // Necess�rio para std::numeric_limits
/*classe Pessoa
Essa classe  representa os dados de uma pessoa.
� a superclasse do sistema tendo atributos de idade
e nome

*/
class Pessoa
{
private:
    std::string nome;
    int idade;

public://consturor padr�o
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
            throw std::invalid_argument("Idade inv�lida. Deve ser maior ou igual a 18.");
        }
        this->idade = a;
    }
//Obt�m o nome
    std::string getNome()
    {
        return nome;
    }
//obt�m a idade
    int getAge()
    {
        return idade;  // Corrigido: retornar 'idade' em vez de 'age'
    }
    //M�todo que obt�m e define os dados do objeto pessoa
    void cadastrarC()
    {
        std::cout << "Digite o nome da pessoa:" << std::endl;
        std::getline(std::cin >> std::ws, nome);  // std::ws ignora espa�os em branco iniciais

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
