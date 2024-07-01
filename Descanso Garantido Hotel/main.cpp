/*H**********************************************************************
* FILENAME : Descanso_Garantido_Hotel DESIGN 
*
* DESCRIPTION :
* Sistema de controle de cadastros e reservas do Hotel "Descanso Garantido"
*
* PUBLIC FUNCTIONS :
* void menu()
* void cadastrarCliente()
* void cadastrarFuncionario();
* void registrarDiaria(Quarto quartos[], int numQuartos);
* void pesquisarCliente();
* void pesquisarFuncionario();
*
*
* NOTES :
* Sistema de controle e cadastro de clientes funcional e dinâmica
* Não utilizamos Funções dentro do código principal, apenas nas classes
*
* AUTHOR(s) : 
*    LUAN HENRIQUE GOIANA de MELO
*    LAMÔNI LEAL PEREIRA
*Other START DATE : 17 de JUN de 2024
*
* CHANGES :
* 17Jun2024 - Inicializando contrução do código e das classes
* 25Jun2024 - Continuando contrução das classes
* 26Jun2024 - Finalizando código de classes
* 28Jun2024 - Contruindo Menu e procedimentos do código
* 30Jun2024 - Finalizando código, reparando erros e documentando código
*H*/

#include <iostream>
#include <limits>
#include "Funcionario.h"
#include "Client.h"
#include "Quarto.h"
#include "Estadia.h"

/*Declarando os procedimentos utilizados para leitura do código
no compilador, organização do código*/
void menu();
void cadastrarCliente();
void cadastrarFuncionario();
void registrarDiaria(Quarto quartos[], int numQuartos);
void pesquisarCliente();
void pesquisarFuncionario();

int main()
{
    Quarto quartos[20];                //Vetor de armazenamento de quartos
    for (int i = 0; i < 20; ++i)        //Repetição para cadastro de todos os quartos no sistema
    {
        std::string num = "Q" + std::to_string(i + 1);    //Gerando código dos quartos com inicial "Q", separar ID para quartos
        quartos[i].setNumeroQuarto(num);                
        quartos[i].setQuantidadeHospedes(2); // Exemplo de capacidade
        quartos[i].setValorDiaria(100.0); // Exemplo de valor da diária
    }

    int opt;        //Variável para seleção de opções dentro do Menu
    do
    {
        menu();            //Procedimento de impressão das opções de menu
        std::cout << "Inserir opcao: ";        //Solicitando ao usuário
        std::cin >> opt;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpa o buffer de entrada

        switch (opt)
        {
        case 1:
            cadastrarCliente();
            std::cout << "Cliente cadastrado com sucesso";
            break;
        case 2:
            cadastrarFuncionario();
            std::cout << "Funcionario cadastrado com sucesso";
            break;
        case 3:
            registrarDiaria(quartos, 20);
            std::cout << "Diaria registrada.\nSeja Bem vindo! Garantimos o seu Descanso!";
            break;
        case 4:
            pesquisarCliente();
            break;
        case 5:
            pesquisarFuncionario();
            break;
        case 0:
            std::cout << "Saindo do programa. Volte Sempre" << std::endl;
            break;
        default:
            std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
    } while (opt != 0);

    return 0;
}

void menu()
{
            //Impressão de um menu escrito e descritivo para o usuário, expecificando opções de escolha.
    std::cout << "Bem Vindo ao Descanso Garantido Hotel\n" << std::endl;
    std::cout << "--------------------------------------\n" << std::endl;
    std::cout << "Opção 1 - Cadastrar Cliente\n" << std::endl;
    std::cout << "Opção 2 - Cadastrar Funcionario\n" << std::endl;
    std::cout << "Opção 3 - Registrar diaria\n" << std::endl;
    std::cout << "Opção 4 - Pesquisar Cliente\n" << std::endl;
    std::cout << "Opção 5 - Pesquisar Funcionario\n" << std::endl;
    std::cout << "Opção 0 - Sair\n\n" << std::endl;
    std::cout << "--------------------------------------" << std::endl;
}

void cadastrarCliente()
{
            //Precedimento para salvar e arquivar dados dos Clientes
    Client cliente;                //criando objeto da classe
    cliente.cadastrarCliente();    //chamando método de cadastro "Get-Set" implementado no objeto

    std::string filename = "clientes.dat";        //String criada para nomear arquivo binário
    cliente.saveToFile(filename);                //procedimento para arquivar dados do cliente no arquivo "clientes.dat"
}

void cadastrarFuncionario()
{
        //Precedimento para salvar e arquivar dados dos funcionários
    Funcionario funcionario;                //criando objeto da classe
    funcionario.cadastrarFuncionario();        //chamando método de cadastro "Get-Set" implementado no objeto

    std::string filename = "funcionarios.dat";     //String criada para nomear arquivo binário
    funcionario.saveToFile(filename);                //procedimento para arquivar dados do cliente no arquivo "funcionarios.dat"
}

void registrarDiaria(Quarto quartos[], int numQuartos)
{
/* 
* NAME: void registrarDiaria(Quarto quartos[], int numQuartos)
* DESCRIPTION: Procedimento de pesquisa e comparação dentro do sistema para registro de estadia do cliente
* INPUTS : PARAMETERS:
*    Quarto quartos[]                    Vetor da classe quarto
*        
*    int numQuartos                      Valor inteiro para pesquisa de quartos
* PROCESS: 
*    [1] Solicita dados p/ armazenar em variáveis auxiliares e no objeto da classe Estadia
*    [2] Repetir por - Pesquisa de todos quartos - "i< numQuartos"
*    [3] Procurar por quarto selecionado
*    [4] Verificar ocupação do quarto (Ocupado/Desocupado)
*    [5] Gravar e salvar quarto junto ao numero de dias da estadia
*    [6] Fechar Repetição
*    [7] Gravar e salvar cliente junto a estadia + anexar pontos de fidelidade
* NOTES:
*     Procedimento mais estenso do código que vincula a maioria dos objetos utilizados;
*     Procedimento central para funcionamento do sistema de cadastro e funcionalidade do hotel.
*/
    Estadia estadia;
    std::string dataEntrada, dataSaida, codigoCliente;
    int quantidadeDiarias;
    std::string numeroQuarto;

    estadia.generateCodigoEstadia();

    std::cout << "Digite a data de entrada (dd/mm/aaaa): ";
    std::getline(std::cin, dataEntrada);
    estadia.setDataEntrada(dataEntrada);

    std::cout << "Digite a data de saída (dd/mm/aaaa): ";
    std::getline(std::cin, dataSaida);
    estadia.setDataSaida(dataSaida);

    std::cout << "Digite o código do cliente: ";
    std::getline(std::cin, codigoCliente);
    estadia.setCodigoCliente(codigoCliente);

    std::cout << "Digite a quantidade de diárias: ";
    std::cin >> quantidadeDiarias;
    estadia.setQuantidadeDiarias(quantidadeDiarias);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Digite o número do quarto: ";
    std::getline(std::cin, numeroQuarto);

    bool quartoEncontrado = false;
    for (int i = 0; i < numQuartos; ++i)
    {
        if (quartos[i].getNumeroQuarto() == numeroQuarto)
        {
            if (quartos[i].getOcupado())
            {
                std::cout << "Quarto já está ocupado." << std::endl;
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
        std::cout << "Número do quarto não encontrado." << std::endl;
    }

    std::string filename = "estadias.dat";
    estadia.saveToFile(filename);

    // Adicionar pontos de fidelidade para o cliente
    Client cliente;
    cliente.readFromFile("clientes.dat");
    cliente.addPontosFidelidade(quantidadeDiarias * 10); // Exemplo: 10 pontos por diária
    cliente.saveToFile("clientes.dat");
}

void pesquisarCliente()
{
/*
* NAME:  void pesquisarCliente()
* DESCRIPTION: Procedimento para pesquisar clientes pelo código gerado no sistema
* INPUTS: 
*        string keyword                String solicitada dentro do procedimento
*                                        gerada por código de cadastro de Cliente
* PROCESS:
*    [1] Solicitação de Código ao usuário
*    [2] Criação de objeto cliente
*    [3] Pesquisa por meio de método implementado no objeto da classe Clientes - "searchClient"
*    [4] Impressao do resultado(Encontrado + Nome/Não encontrado)
*/
    std::string keyword;
    std::cout << "Digite o nome ou código do cliente: ";
    std::getline(std::cin, keyword);

    Client cliente;
    if (cliente.searchClient(keyword))
    {
        std::cout << "\nCliente encontrado:" << std::endl;
        cliente.showInfo();
    }
    else
    {
        std::cout << "\nCliente não encontrado." << std::endl;
    }
}

void pesquisarFuncionario()
{
/*
* NAME:  void pesquisarFuncionario()
* DESCRIPTION: Procedimento para pesquisar funcionário pelo código gerado no sistema
* INPUTS: 
*        string keyword                String solicitada dentro do procedimento
*                                        gerada por código de cadastro de funcionarios
* PROCESS:
*    [1] Solicitação de Código ao usuário
*    [2] Criação de objeto Funcionario
*    [3] Pesquisa por meio de método implementado no objeto da classe Funcionário - "searchFuncionario"
*    [4] Impressao do resultado(Encontrado + Nome/Não encontrado)
*/
    std::string keyword;
    std::cout << "Digite o nome ou matrícula do funcionario: ";
    std::getline(std::cin, keyword);

    Funcionario funcionario;
    if (funcionario.searchFuncionario(keyword))
    {
        std::cout << "\nFuncionário encontrado:" << std::endl;
        funcionario.showInfo();
    }
    else
    {
        std::cout << "\nFuncionário não encontrado." << std::endl;
    }
}
