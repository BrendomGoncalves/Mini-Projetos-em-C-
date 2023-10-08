// INCLUDES
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <regex>
// DEFINES
#ifdef _WIN32
    #define LIMPAR "cls"
    #define PAUSE "pause"
#else
    #define LIMPAR "clear"
    #define PAUSE "read -p \"Aperte ENTER para continuar...\" saindo"
#endif
// NAMESPACE
using namespace std;
/// CABEÇALHO DE CLASSES
class Aluguel;
class Cliente;
class Veiculo;
class Funcionario;
// CABEÇALHO DE FUNÇÕES
/**
 * @brief Função que limpa o terminal.
*/
static void limparTela();
/**
 * @brief Função que gera um comando no terminal linux para pausar o terminal. Semelhante ao system('pause') do windows.
*/
static void pausaTela();
/**
 * @brief Função que guarda os dados do cliente no arquivo clientes.txt.
 * @param novo Objeto do tipo Cliente com dados do cliente.
 * @param sobrescrever Variável do tipo boleana para controlar sobrescrita do arquivo.
*/
static void salvarCliente(Cliente novo, bool sobrescrever);
/**
 * @brief Função que recupera do arquivo todos os clientes salvos para um vector.
 * @param clientesEditar Posição para um Vector vazio do tipo Cliente para armazenar os dados do arquivo.
*/
static void buscaClientes(vector<Cliente>& clientes);
/**
 * @brief Função que retorna o tamanho do maior nome entre os clientes.
 * @param clientes Vector do tipo Cliente com os dados de todos os clientes cadastrados.
*/
static int maiorNome(vector<Cliente>& clientes);
// CLASSES
class Data {
    private:
      int dia, mes, ano;
    public:
      int getDia(){
          return dia;
      }
      int getMes(){
          return mes;
      }
      int getAno(){
          return ano;
      }
      string getDataString(){
          return to_string(this->dia) + "/" 
          + to_string(this->mes) + "/" 
          + to_string(this->ano);
      }
      void setDia(int _dia){
          this->dia = _dia;
      }
      void setMes(int _mes){
          this->mes = _mes;
      }
      void setAno(int _ano){
          this->ano = _ano;
      }
      void lerData(){
          do{
              limparTela();
              cout << "Digite a data:" << endl;
              cout << "Dia: ";
              cin >> this->dia;
              cout << "Mes: ";
              cin >> this->mes;
              cout << "Ano: ";
              cin >> this->ano;
          }while(!validaData());
      }
      bool validaData(){
          if (this->mes > 12){
              cout << "Mes invalido" << endl;
              pausaTela();
              return false;
          } else if (this->dia > 3000 || this->ano < 1900){
              cout << "Ano invalido" << endl;
              pausaTela();
              return false;
          } else if (this->mes == 2){
              if (this->ano % 4 == 0){
                  if (this->dia > 29){
                      cout << "Dia invalido para o mes" << endl;
                      pausaTela();
                      return false;
                  }
              } else if (this->dia > 28){
                  cout << "Dia invalido para o mes" << endl;
                  pausaTela();
                  return false;
              }
          } else if (this->mes < 7){
              if (this->mes % 2 == 0){
                  if (this->dia > 30){
                      cout << "Dia inválido para o mes" << endl;
                      pausaTela();
                      return false;
                  }
              } else if (this->dia > 31){
                  cout << "Dia invalido para o mes" << endl;
                  pausaTela();
                  return false;
              }
          } else if (this->mes > 6){
              if (this->mes % 2 == 0){
                  if (this->dia > 31){
                      cout << "Dia invalido para o mes" << endl;
                      pausaTela();
                      return false;
                  }
              } else if (this->dia > 30){
                  cout << "Dia invalido para o mes" << endl;
                  pausaTela();
                  return false;
              }
          }
          return true;
      }
      void imprimeData(){
          cout << this->getDataString() << endl;
      }
};
class Usuario {
    protected:
        string cpf;
        string nome;
        string endereco;
        string telefone;
    public:
        static bool validarCPF(string& cpf) {
            regex padrao("^\\d{3}\\.\\d{3}\\.\\d{3}-\\d{2}$");
            return regex_match(cpf, padrao);
        }
        static bool validarTelefone(string& telefone) {
            regex padrao("^\\(\\d{2}\\) \\d{5}-\\d{4}$"); // Exemplo: (13) 97456-7890
            return regex_match(telefone, padrao);
        }
};
class Cliente : Usuario{
    private:
        string habilitacao;
        vector<Aluguel> historicoAluguel;
    public:
        string getCpf(){
            return this->cpf;
        }
        string getNome(){
            return this->nome;
        }
        string getEndereco(){
            return this->endereco;
        }
        string getTelefone(){
            return this->telefone;
        }
        string getHabilitacao(){
            return this->habilitacao;
        }
        vector<Aluguel> getAlugueis(){
            return this->historicoAluguel;
        }
        void setCpf(string _cpf){
            this->cpf = _cpf;
        }
        void setNome(string _nome){
            this->nome = _nome;
        }
        void setEndereco(string _endereco){
            this->endereco = _endereco;
        }
        void setTelefone(string _telefone){
            this->telefone = _telefone;
        }
        void setHabilitacao(string _habilitacao){
            this->habilitacao = _habilitacao;
        }
        void menuPrincipal(){
            int op = 0;
            do{
                limparTela();
                cout << "** ESPAÇO DO CLIENTE **" << endl;
                cout << "1. Cotar Aluguel" << endl;
                cout << "2. Solicitar Aluguel" << endl;
                cout << "3. Devolver Veiculo" << endl;
                cout << "======= 0. Sair ========" << endl << "> ";
                cin >> op;
                switch(op){
                    case 1:
                        cotarAluguel(); // TODO criar essa função
                        break;
                    case 2:
                        solicitarAluguel(); // TODO criar essa função
                        break;
                    case 3:
                        devolverVeiculo(); // TODO criar essa função
                        break;
                    case 0:
                        cout << "Encerrando..." << endl;
                        break;
                }
                if(op > 3 || op < 0){
                    cout << "Opção inválida! Escolha 1, 2 ou 3" << endl;
                    pausaTela();
                }
            }while(op != 0);
        }
        void cotarAluguel(){}
        void solicitarAluguel(){}
        void devolverVeiculo(){}
        static void inserirCliente(){
            Cliente cliente;
            string cpf, nome, endereco, telefone, habilitacao;
            limparTela();
            cout << "** CADASTRO CLIENTE **" << endl;
            cout << "Nome: ";
            cin.ignore();
            getline(cin, nome);
            do{
                cout << endl << "[modelo: XXX.XXX.XXX-XX]" << endl;
                cout << "CPF: ";
                cin >> cpf;
                if(validarCPF(cpf)){
                    break;
                } else {
                    cout << "CPF inválido!" << endl;
                    pausaTela();
                    limparTela();
                }
            }while(true);
            cout << "Endereço: ";
            cin.ignore();
            getline(cin, endereco);
            do{
                cout << endl << "[modelo: (XX) XXXXX-XXXX]" << endl;
                cout << "Telefone: ";
                cin >> telefone;
                if(validarTelefone(telefone)){
                    break;
                } else {
                    cout << "Telefone inválido!" << endl;
                    pausaTela();
                    limparTela();
                }
            }while(true);
            cout << "Habilitação:";
            cin >> habilitacao;
            cliente.setCpf(cpf);
            cliente.setNome(nome);
            cliente.setEndereco(endereco);
            cliente.setTelefone(telefone);
            cliente.setHabilitacao(habilitacao);
            salvarCliente(cliente, false);
            pausaTela();
        }
        static void editarCliente(){
            string cpfEditar;
            bool clienteEncontrado = false;
            vector<Cliente> clientesDoArquivo;
            limparTela();
            cout << "** EDITAR CLIENTE **" << endl;
            cout << "Digite o CPF do cliente: ";
            cin >> cpfEditar;
            buscaClientes(clientesDoArquivo);
            cout << clientesDoArquivo.size() << endl;
            if(clientesDoArquivo.size() > 0){
                for(size_t i=0; i<clientesDoArquivo.size(); i++){
                    if(clientesDoArquivo[i].getCpf() == cpfEditar){
                        clienteEncontrado = true;
                        int op = 0;
                        string novo;
                        do{
                            cout << "** O QUE DESEJA EDITAR? **" << endl;
                            cout << "1. Editar Nome" << endl;
                            cout << "2. Editar Endereço" << endl;
                            cout << "3. Editar Telefone" << endl;
                            cout << "4. Editar Habilitação" << endl;
                            cout << "========= 0. Sair =========" << endl << "> ";
                            cin >> op;
                            switch(op){
                                case 1:
                                    novo = "";
                                    cout << "Mudar de " << clientesDoArquivo[i].getNome() << " para: ";
                                    cin.ignore();
                                    getline(cin, novo);
                                    clientesDoArquivo[i].setNome(novo);
                                    cout << "Nome alterado com sucesso!" << endl;
                                    pausaTela();
                                    break;
                                case 2:
                                    novo = "";
                                    cout << "Mudar de " << clientesDoArquivo[i].getEndereco() << " para: ";
                                    cin.ignore();
                                    getline(cin, novo);
                                    clientesDoArquivo[i].setEndereco(novo);
                                    cout << "Endereço alterado com sucesso!" << endl;
                                    pausaTela();
                                    break;
                                case 3:
                                    novo = "";
                                    do{
                                        cout << endl << "[modelo: (XX) XXXXX-XXXX]" << endl;
                                        cout << "Mudar de " << clientesDoArquivo[i].getTelefone() << " para: ";
                                        cin >> novo;
                                        if(validarTelefone(novo)){
                                            break;
                                        } else {
                                            cout << "Telefone inválido!" << endl;
                                            pausaTela();
                                            limparTela();
                                        }
                                    }while(true);
                                    clientesDoArquivo[i].setTelefone(novo);
                                    cout << "Telefone alterado com sucesso!" << endl;
                                    pausaTela();
                                    break;
                                case 4:
                                    novo = "";
                                    cout << "Mudar de " << clientesDoArquivo[i].getHabilitacao() << " para: ";
                                    cin.ignore();
                                    getline(cin, novo);
                                    clientesDoArquivo[i].setHabilitacao(novo);
                                    cout << "Habilitação alterada com sucesso!" << endl;
                                    pausaTela();
                                    break;
                                case 0:
                                    break;
                            }
                            if(op > 4 || op < 0){
                                cout << "Opção inválida! Escolha 1, 2 ou 3" << endl;
                                pausaTela();
                            }
                        }while(op != 0);
                        break;
                    }
                }

                salvarCliente(clientesDoArquivo[0], true);
                if(clientesDoArquivo.size() > 1){
                    for(size_t i=1; i<clientesDoArquivo.size(); i++){
                        salvarCliente(clientesDoArquivo[i], false);
                    }
                }

                if(!clienteEncontrado){
                    cout << "Cliente não encontrado! Verifique se digitou o CPF corretamente." << endl;
                    pausaTela();
                }
            } else {
                cout << "Nenhum cliente cadastrado!" << endl;
                pausaTela();
            }
        }
        static void excluirCliente(){
            string cpfExcluir;
            bool clienteEncontrado = false;
            vector<Cliente> clientesDoArquivo;
            limparTela();
            cout << "** EXCLUIR CLIENTE **" << endl;
            cout << "Digite o CPF do cliente: ";
            cin >> cpfExcluir;
            buscaClientes(clientesDoArquivo);
            if(clientesDoArquivo.size() > 0){
                for(size_t i=0; i<clientesDoArquivo.size(); i++){
                    if(cpfExcluir == clientesDoArquivo[i].getCpf()){
                        clienteEncontrado = true;
                        char resposta;
                        cout << "Confime novamente se deseja excluir (s/n): " << endl;
                        cin >> resposta;
                        if(resposta == 's') clientesDoArquivo.erase(clientesDoArquivo.begin() + i);
                        else {
                            pausaTela();
                            break;
                        }
                    }
                }
                if(clienteEncontrado){
                    salvarCliente(clientesDoArquivo[0], true);
                    if(clientesDoArquivo.size() > 1){
                        for(size_t i=1; i<clientesDoArquivo.size(); i++){
                            salvarCliente(clientesDoArquivo[i], false);
                        }
                    }
                } else {
                    cout << "Cliente não encotrado! Verifique se digitou o CPF corretamente" << endl;
                    pausaTela();
                }
            } else {
                cout << "Nenhum cliente cadastrado!" << endl;
                pausaTela();
            }
        }
        static void listarClientes(){
            vector<Cliente> clientesDoArquivo;
            int tamNomeM = 0;
            limparTela();
            buscaClientes(clientesDoArquivo);
            cout << "\t\t\t\t** LISTA DE CLIENTES **" << endl;
            if(clientesDoArquivo.size() > 0){
                tamNomeM = maiorNome(clientesDoArquivo);
                cout << "CPF\t\t\t" << "NOME\t\t\t"  << "ENDEREÇO\t\t\t" << "TELEFONE\t" << "HABILITAÇÃO" << endl;
                for(Cliente c : clientesDoArquivo){
                    cout << "(" << c.getCpf() << ")\t" 
                        << c.getNome() << setw(tamNomeM-c.getNome().length()) << "\t" 
                        << c.getEndereco() << setw(tamNomeM-c.getEndereco().length()) << "\t\t" 
                        << c.getTelefone() << "\t"
                        << c.getHabilitacao() << endl;
                }
                pausaTela();
            } else {
                cout << "Nenhum cliente cadastrado!" << endl;
                pausaTela();
            }
        }
};
class Funcionario : Usuario {
    private:
        vector<Aluguel> historicoAluguel;
    public:
        string getCpf(){
            return this->cpf;
        }
        string getNome(){
            return this->nome;
        }
        string getEndereco(){
            return this->endereco;
        }
        string getTelefone(){
            return this->telefone;
        }
        void setCpf(string _cpf){
            this->cpf = _cpf;
        }
        void setNome(string _nome){
            this->nome = _nome;
        }
        void setEndereco(string _endereco){
            this->endereco = _endereco;
        }
        void setTelefone(string _telefone){
            this->telefone = _telefone;
        }
        void menuPrincipal(){
            int op = 0;
            do{
                limparTela();
                cout << "** ESPAÇO DO FUNCIONARIO **" << endl;
                cout << "1. Controle de Clientes" << endl;
                cout << "2. Controle de Veiculos" << endl;
                cout << "3. Controle de Alugueis" << endl;
                cout << "========= 0. Sair =========" << endl << "> ";
                cin >> op;
                switch(op){
                    case 1:
                        menuGerenciaCliente();
                        break;
                    case 2:
                        menuGerenciaVeiculos();
                        break;
                    case 3:
                        menuGerenciaAlugueis();
                        break;
                    case 0:
                        cout << "Encerrando..." << endl;
                        break;
                }
                if(op > 3 || op < 0){
                    cout << "Opção inválida! Escolha 1, 2 ou 3" << endl;
                    pausaTela();
                }
            }while(op != 0);
        }
        void menuGerenciaCliente(){
            int op = 0;
            do{
                limparTela();
                cout << "** LOCADORA TIC CAR RENTAL (FUNCIONARIO) **" << endl;
                cout << "1. Inserir Cliente\t" << "2. Editar Cliente" << endl;
                cout << "3. Excluir Cliente\t" << "4. Listar Clientes" << endl;
                cout << "================ 0. Sair =================" << endl << "> ";
                cin >> op;
                switch(op){
                    case 1:
                        Cliente::inserirCliente();
                        break;
                    case 2:
                        Cliente::editarCliente();
                        break;
                    case 3:
                        Cliente::excluirCliente(); // TODO criar essa função
                        break;
                    case 4:
                        Cliente::listarClientes(); // TODO criar essa função
                    case 0:
                        cout << "Encerrando..." << endl;
                        break;
                }
                if(op > 4 || op < 0){
                    cout << "Opção inválida!" << endl;
                    pausaTela();
                }
            }while(op != 0);
        }
        void menuGerenciaVeiculos(){
            int op = 0;
            do{
                limparTela();
                cout << "** LOCADORA TIC CAR RENTAL (FUNCIONARIO) **" << endl;
                cout << "1. Inserir Veiculo\t" << "2. Editar Veiculo" << endl;
                cout << "3. Excluir Veiculo\t" << "4. Listar Veiculos" << endl;
                cout << "================ 0. Sair =================" << endl << "> ";
                cin >> op;
                switch(op){
                    case 1:
                        //inserirVeiculo(); // TODO criar essa função
                        break;
                    case 2:
                        //editarVeiculo(); // TODO criar essa função
                        break;
                    case 3:
                        //excluirVeiculo(); // TODO criar essa função
                        break;
                    case 4:
                        //listarVeiculos(); // TODO criar essa função
                    case 0:
                        cout << "Encerrando..." << endl;
                        break;
                }
                if(op > 4 || op < 0){
                    cout << "Opção inválida!" << endl;
                    pausaTela();
                }
            }while(op != 0);
        }
        void menuGerenciaAlugueis(){
            int op = 0;
            do{
                limparTela();
                cout << "** LOCADORA TIC CAR RENTAL (FUNCIONARIO) **" << endl;
                cout << "1. Cadastrar Aluguel\t" << "2. Editar Veiculo" << endl;
                cout << "3. Excluir Veiculo\t" << "4. Listar Veiculos" << endl;
                cout << "================ 0. Sair =================" << endl << "> ";
                cin >> op;
                switch(op){
                    case 1:
                        //inserirVeiculo(); // TODO criar essa função
                        break;
                    case 2:
                        //editarVeiculo(); // TODO criar essa função
                        break;
                    case 3:
                        //excluirVeiculo(); // TODO criar essa função
                        break;
                    case 4:
                        //listarVeiculos(); // TODO criar essa função
                    case 0:
                        cout << "Encerrando..." << endl;
                        break;
                }
                if(op > 4 || op < 0){
                    cout << "Opção inválida!" << endl;
                    pausaTela();
                }
            }while(op != 0);
        }
};
class Veiculo {
    protected:
        string identificador;
        string marca;
        string modelo;
        int anoFabricacao;
        float precoPorDia;
    public:
        string getIdentificador(){
            return this->identificador;
        }
        string getMarca(){
            return this->marca;
        }
        string getModelo(){
            return this->modelo;
        }
        int getAnoFabricacao(){
            return this->anoFabricacao;
        }
        float getPrecoPorDia(){
            return this->precoPorDia;
        }
};
class Aluguel {
    protected:
        string identificador;
        Veiculo veiculo;
        Cliente cliente;
        Funcionario funcionario;
        Data dataInicio;
        Data dataTermino;
        Data dataDevolucao;
        float desconto;
        float adicional;
    public:
        string getIdentificador(){
            return this->identificador;
        }
        string getIdentificadorVeiculo(){
            return this->veiculo.getIdentificador();
        }
        string getIdentificadorCliente(){
            return this->cliente.getCpf();
        }
        string getIdentificadorFuncionario(){
            return this->funcionario.getCpf();
        }
        string getDataInicio(){
            return this->dataInicio.getDataString();
        }
        string getDataTermino(){
            return this->dataTermino.getDataString();
        }
        string getDataDevolucao(){
            return this->dataDevolucao.getDataString();
        }
        float getDesconto(){
            return this->desconto;
        }
        float getAdicional(){
            return this->adicional;
        }
};
// INICIO
int main(){
    Funcionario funcionario;
    Cliente cliente;

    int op = 0;
    do{
        limparTela();
        cout << "****** LOCADORA TIC CAR RENTAL *******" << endl;
        cout << "1. Sou Funcionário\t2. Sou Cliente" << endl;
        cout << "============== 0. Sair ===============" << endl << "> ";
        cin >> op;
        switch(op){
            case 1:
                funcionario.menuPrincipal();
                break;
            case 2:
                cliente.menuPrincipal();
                break;
            case 0:
                cout << "Encerrando..." << endl;
                break;
            default:
                break;
        }
        if(op > 2 || op < 0){
            cout << "Opção inválida!" << endl;
            pausaTela();
        }
    }while(op != 0);
    
    return 0;
}
// FUNÇÕES
static void limparTela(){
    system(LIMPAR);
}
static void pausaTela(){
    cout << endl;
    system(PAUSE);
}
static int maiorNome(vector<Cliente>& clientes){
    size_t maior = clientes[0].getNome().length();
    for(Cliente c : clientes){
        if(c.getNome().length() > maior) maior = c.getNome().length();
    }
    return maior;
}
static void salvarCliente(Cliente novo, bool sobrescrever){
    ofstream arquivo;
    if(sobrescrever) arquivo.open("clientes.txt", ios_base::out);
    else arquivo.open("clientes.txt", ios_base::app);
    if(arquivo.is_open()){
        arquivo << novo.getCpf() << "|";
        arquivo << novo.getNome() << "|";
        arquivo << novo.getEndereco() << "|";
        arquivo << novo.getTelefone() << "|";
        arquivo << novo.getHabilitacao() << endl;
        arquivo.close();
        cout << "Cliente cadastrado com sucesso!" << endl;
    } else {
        cout << "Erro ao abrir arquivo!" << endl;
    }
}
static void buscaClientes(vector<Cliente>& clientes){
    ifstream arquivo;
    arquivo.open("./clientes.txt", ios_base::in);
    if(arquivo.is_open()){
        while(arquivo.eof()==false){
            Cliente cliente;
            string dadosCliente, delimiter = "|";
            vector<string> dadosSeparado;
            size_t pos;

            getline(arquivo, dadosCliente);
            if(!dadosCliente.empty()){
                while ((pos = dadosCliente.find(delimiter)) != string::npos) {
                    string token = dadosCliente.substr(0, pos);
                    dadosSeparado.push_back(token);
                    dadosCliente.erase(0, pos + delimiter.length());
                }
                dadosSeparado.push_back(dadosCliente);
                cliente.setCpf(dadosSeparado[0]);
                cliente.setNome(dadosSeparado[1]);
                cliente.setEndereco(dadosSeparado[2]);
                cliente.setTelefone(dadosSeparado[3]);
                cliente.setHabilitacao(dadosSeparado[4]);
                clientes.push_back(cliente);
            }
        }
        arquivo.close();
        
    } else {
        cout << "Erro ao abrir arquivo!" << endl;
        pausaTela();
    }
}