#include <iostream>
#include "Funcionario.h"
#include "Client.h"
#include "Quarto.h"

void menu();
void cadastrarCliente();
void cadastrarFuncionario();
void registrarDiaria();

int main()
{
    int opt;
    do
    {
        menu();
        std::cout << "Inserir op��o: ";
        std::cin >> opt;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer de entrada

        switch (opt)
        {
        case 1:
            cadastrarCliente();
            break;
        case 2:
            cadastrarFuncionario();
            break;
        case 3:
            registrarDiaria();
            break;
        default:
            std::cout << "Op��o inv�lida. Tente novamente." << std::endl;
        }
    } while (opt != 0);

    return 0;
}

void menu()
{
    std::cout << "Bem Vindo ao Descanso Garantido Hotel" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
    std::cout << "Op��o 1 - Cadastrar Cliente" << std::endl;
    std::cout << "Op��o 2 - Cadastrar Funcion�rio" << std::endl;
    std::cout << "Op��o 3 - Registrar di�ria" << std::endl;
    std::cout << "Op��o 0 - Sair" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

void cadastrarCliente()
{
    Client cliente;
    cliente.cadastrarCliente();

    std::string filename = "clientes.dat";
    cliente.saveToFile(filename);
}

void cadastrarFuncionario()
{
    Funcionario funcionario;
    funcionario.cadastrarFuncionario();

    std::string filename = "funcionarios.dat";
    funcionario.saveToFile(filename);
}

void registrarDiaria()
{
    Quarto quarto;
    std::string num;
    int hospedes;
    double diaria;
    bool estado;
    std::string codigo;

    std::cout << "Digite o n�mero do quarto: ";
    std::getline(std::cin, num);
    quarto.setNumeroQuarto(num);

    std::cout << "Digite a quantidade de h�spedes: ";
    std::cin >> hospedes;
    quarto.setQuantidadeHospedes(hospedes);

    std::cout << "Digite o valor da di�ria: ";
    std::cin >> diaria;
    quarto.setValorDiaria(diaria);

    std::cout << "O quarto est� ocupado? (1 para sim, 0 para n�o): ";
    std::cin >> estado;
    quarto.setOcupado(estado);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer de entrada

    std::cout << "Digite o c�digo de estadia: ";
    std::getline(std::cin, codigo);
    quarto.setCodigoEstadia(codigo);

    std::string filename = "quartos.dat";
    quarto.saveToFile(filename);
}
