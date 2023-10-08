// INCLUDES
#include <iostream>
#include <vector>
#include <fstream>
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
*/
static void salvarCliente(Cliente novo);
static void lerCliente(string identificador, Cliente &cliente, vector<Aluguel> &historicoAlugueis);
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
            cout << "Nome:";
            cin.ignore();
            getline(cin, nome);
            cout << "CPF:";
            cin >> cpf;
            cout << "Endereço:";
            cin.ignore();
            getline(cin, endereco);
            cout << "Telefone:";
            cin >> telefone;
            cout << "Habilitação:";
            cin >> habilitacao;
            cliente.setCpf(cpf);
            cliente.setNome(nome);
            cliente.setEndereco(endereco);
            cliente.setTelefone(telefone);
            cliente.setHabilitacao(habilitacao);
            // TODO Chamar função para salvar cliente
            cout << "Cliente cadastrado com sucesso!" << endl;
            pausaTela();
        }
        static void editarCliente(){}
        static void excluirCliente(){}
        static void listarClientes(){}
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
                        Cliente::editarCliente(); // TODO criar essa função
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
    system(PAUSE);
}
static void salvarCliente(Cliente novo){
    ofstream arquivo;
    arquivo.open("clientes.txt", ios_base::app);
    if(arquivo.is_open()){
        arquivo << novo.getCpf() << "|";
        arquivo << novo.getNome() << "|";
        arquivo << novo.getEndereco() << "|";
        arquivo << novo.getTelefone() << "|";
        arquivo << novo.getHabilitacao() << endl;
        arquivo.close();
    } else {
        cout << "Erro ao abrir arquivo!" << endl;
        pausaTela();
    }
}
/*static void lerCliente(string identificador, Cliente &cliente, vector<Aluguel> &historicoAlugueis){
    ifstream arquivo;
    arquivo.open("clientes.txt", ios_base::in);
    if(arquivo.is_open()){
        string cpfCliente, nomeCliente, endCliente, telCliente, habiCliente;
        getline(arquivo, cpfCliente);
        getline(arquivo, nomeCliente);
        getline(arquivo, endCliente);
        getline(arquivo, telCliente);
        getline(arquivo, habiCliente);
        while (arquivo.eof()==false){
            Aluguel aluguel;
            string aluguelCliente;
            getline(arquivo, aluguelCliente);
            vector<string> dadosSeparado{};
            string delimiter = "|";
            size_t pos;
            while ((pos = aluguelCliente.find(delimiter)) != string::npos) {
                dadosSeparado.push_back(aluguelCliente.substr(0, pos));
                aluguelCliente.erase(0, pos + delimiter.length());
            }
            if(identificador == cpfCliente) historicoAlugueis.push_back(aluguel);
        }
        if(identificador == cpfCliente){
            cliente.setCpf(cpfCliente);
            cliente.setNome(nomeCliente);
            cliente.setEndereco(endCliente);
            cliente.setTelefone(telCliente);
            cliente.setHabilitacao(habiCliente);
        }
        arquivo.close();
    }
}*/