#include <iostream>
#include <limits>
#include "Funcionario.h"
#include "Client.h"
#include "Quarto.h"
#include "Estadia.h"

void menu();
void cadastrarCliente();
void cadastrarFuncionario();
void registrarDiaria(Quarto quartos[], int numQuartos);
void pesquisarCliente();
void pesquisarFuncionario();

int main()
{
    Quarto quartos[20];
    for (int i = 0; i < 20; ++i)
    {
        std::string num = "Q" + std::to_string(i + 1);
        quartos[i].setNumeroQuarto(num);
        quartos[i].setQuantidadeHospedes(2); // Exemplo de capacidade
        quartos[i].setValorDiaria(100.0); // Exemplo de valor da di�ria
    }

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
            registrarDiaria(quartos, 20);
            break;
        case 4:
            pesquisarCliente();
            break;
        case 5:
            pesquisarFuncionario();
            break;
        case 0:
            std::cout << "Saindo do programa." << std::endl;
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
    std::cout << "Op��o 4 - Pesquisar Cliente" << std::endl;
    std::cout << "Op��o 5 - Pesquisar Funcion�rio" << std::endl;
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

void registrarDiaria(Quarto quartos[], int numQuartos)
{
    Estadia estadia;
    std::string dataEntrada, dataSaida, codigoCliente;
    int quantidadeDiarias;
    std::string numeroQuarto;

    estadia.generateCodigoEstadia();

    std::cout << "Digite a data de entrada (dd/mm/aaaa): ";
    std::getline(std::cin, dataEntrada);
    estadia.setDataEntrada(dataEntrada);

    std::cout << "Digite a data de sa�da (dd/mm/aaaa): ";
    std::getline(std::cin, dataSaida);
    estadia.setDataSaida(dataSaida);

    std::cout << "Digite o c�digo do cliente: ";
    std::getline(std::cin, codigoCliente);
    estadia.setCodigoCliente(codigoCliente);

    std::cout << "Digite a quantidade de di�rias: ";
    std::cin >> quantidadeDiarias;
    estadia.setQuantidadeDiarias(quantidadeDiarias);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Digite o n�mero do quarto: ";
    std::getline(std::cin, numeroQuarto);

    bool quartoEncontrado = false;
    for (int i = 0; i < numQuartos; ++i)
    {
        if (quartos[i].getNumeroQuarto() == numeroQuarto)
        {
            if (quartos[i].getOcupado())
            {
                std::cout << "Quarto j� est� ocupado." << std::endl;
            }
            else
            {
                quartos[i].setCodigoEstadia(estadia.getCodigoEstadia());
                quartos[i].setOcupado(true);
                std::cout << "Estadia registrada com sucesso para o quarto " << numeroQuarto << std::endl;
            }
            quartoEncontrado = true;
            break;
        }
    }

    if (!quartoEncontrado)
    {
        std::cout << "N�mero do quarto n�o encontrado." << std::endl;
    }

    std::string filename = "estadias.dat";
    estadia.saveToFile(filename);

    // Adicionar pontos de fidelidade para o cliente
    Client cliente;
    cliente.readFromFile("clientes.dat");
    cliente.addPontosFidelidade(quantidadeDiarias * 10); // Exemplo: 10 pontos por di�ria
    cliente.saveToFile("clientes.dat");
}

void pesquisarCliente()
{
    std::string keyword;
    std::cout << "Digite o nome ou c�digo do cliente: ";
    std::getline(std::cin, keyword);

    Client cliente;
    if (cliente.searchClient(keyword))
    {
        std::cout << "\nCliente encontrado:" << std::endl;
        cliente.showInfo();
    }
    else
    {
        std::cout << "\nCliente n�o encontrado." << std::endl;
    }
}

void pesquisarFuncionario()
{
    std::string keyword;
    std::cout << "Digite o nome ou matr�cula do funcion�rio: ";
    std::getline(std::cin, keyword);

    Funcionario funcionario;
    if (funcionario.searchFuncionario(keyword))
    {
        std::cout << "\nFuncion�rio encontrado:" << std::endl;
        funcionario.showInfo();
    }
    else
    {
        std::cout << "\nFuncion�rio n�o encontrado." << std::endl;
    }
}
