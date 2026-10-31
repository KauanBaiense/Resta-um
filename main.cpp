#include "player.hpp"
#include <fstream>
#include "nomes.hpp"



void menu();
void submenu();
void Carregarhumanos(vector<string>& Mankind, vector<Player>& humanos);
void Salvarhumanos(vector<string>& Mankind, vector<Player>& humanos);
void Removerhumano(vector<string>& Mankind, vector<Player>& humanos);
void AdicionarHumano(vector<string>& Mankind, vector<Player>& humanos);
void Luta(vector<Player>& humanos);
void ListarHumanos(vector<Player>& humanos);


vector<string> Mankind;
vector<Player> humanos;



int main()
{

    Carregarhumanos(Mankind, humanos);

    srand(time(0));

    menu();
            return 0;
}



        void Luta(vector<Player>& humanos)
        {
            while(humanos.size() > 1)
            {
                size_t i=rand()%humanos.size();
                size_t j=rand()%humanos.size();

                if(i==j) continue;

                cout << "Lutador " << humanos[i].lutador.Getname() << " atacando " <<  humanos[j].lutador.Getname() << "....";
                bool status = humanos[i].Attack(humanos[j]);

                if(status == true)
                {
                    cout << "ataque bem sucedido" << endl;

                    if(humanos[j].lutador.Getlife()<=0)
                    {
                        cout << " Dead: " << humanos[j].lutador.Getname() << endl ;
                        humanos.erase(humanos.begin()+j);
                    }
                }

                else
                    cout << "vida restante: " <<humanos[j].lutador.Getlife() << endl;
            }

            //vencedor
            cout << "WINNER: " << humanos[0].lutador.Getname() << endl;
        }





        void menu()

        {
            int opt;
            submenu();
            while (opt != 5)
            {

                cin >> opt;
                cin.ignore();


                switch(opt)
                {
                    case 1: //colocar nome novo no humaninho
                    {
                        system("clear");
                        AdicionarHumano(Mankind, humanos);
                        submenu();
                        break;
                    }

                    case 2: //colocar nome novo pros orcs
                    {
                        system("clear");
                        string filename_orc;
                        ofstream orcs("orcs.txt", ios::app);
                        cout << "entre com o nome do bicho: ";
                        getline(cin, filename_orc);
                        orcs << filename_orc << endl;
                        orcs.close();
                        submenu();
                        break;
                    }


                    case 3: //mostrar todos os lutadores
                    {
                        system("clear");
                        ListarHumanos(humanos);
                        submenu();
                        break;
                    }


                    case 4:
                    {
                        system("clear");
                        Removerhumano(Mankind, humanos);
                        submenu();
                        break;
                    }
                    default:
                    break;

                }
            }

        }




        void submenu()
        {

            cout << "1.Adicione um novo lutador para a humanidade" << endl;
            cout << "2.Adicione um novo lutador para a orda" << endl;
            cout << "3.Mostrar todos os guerreiros da humanidade"<< endl;
            cout << "4. obliterar um guerreiro humano" << endl;

        }




        void AdicionarHumano(vector<string>& Mankind, vector<Player>& humanos)
        {
            string nome, nomeArma, Escnome;

            float life, attack, defense, esquiva, danoArma, criticoArma, velocidade, Escblock, Escdefesa, Escvida;

            cout << "Nome do humano: ";
            getline(cin, nome);


            life = rand()%1;
            attack = rand()%1;
            defense = rand()%1;
            esquiva = rand()%1;

            cout <<  "Qual sera o nome da arma ? ";
            getline(cin, nomeArma);
            danoArma = rand()%1;
            criticoArma = rand()%1;
            velocidade = rand()%1;

            cout << "Qual sera o nome do escudo ?";
            getline(cin, Escnome);
            Escblock = rand()%1;
            Escdefesa = rand()%1;
            Escvida = rand()%1;

            Mankind.push_back(nome);

            humanos.emplace_back
            (
                nome, life, attack, defense,
                nomeArma, danoArma, criticoArma,
                esquiva, velocidade,
                Escnome, Escblock, Escdefesa, Escvida);


             Salvarhumanos(Mankind, humanos);
            system("clear");
            cout << "         ESTÁ BRINCANDO DE DEUS ? 0_0 " << endl;
        }


        void Carregarhumanos(vector<string>& Mankind, vector<Player>& humanos)
        {
            ifstream arquivo("humanos.txt");
            int indice;

            string nome, nomeArma, nomeEscudo;

            float life, attack, defense, esquiva;
            float danoArma, criticoArma, velocidade;
            float Escblock, Escdefesa, Escvida;

            while(arquivo >> indice >> nome >> life >> attack >> defense >> esquiva >> nomeArma >> danoArma >> criticoArma >> velocidade >> nomeEscudo >> Escblock >> Escdefesa >> Escvida)
            {
                Mankind.push_back(nome);

                humanos.emplace_back(
                    nome, life, attack, defense,
                    nomeArma, danoArma, criticoArma,
                    esquiva, velocidade,
                    nomeEscudo, Escblock, Escdefesa, Escvida);
            }

            arquivo.close();
        }



        void Salvarhumanos(vector<string>& Mankind, vector<Player>& humanos)
        {
            ofstream arquivo("humanos.txt");

            for(size_t i = 0; i < humanos.size(); i++)
            {
                arquivo << i << " "<< humanos[i].lutador.Getname() << " " << humanos[i].lutador.Getlife() << " " << humanos[i].lutador.Getattack() << " " << humanos[i].lutador.Getdefense() << " " << humanos[i].lutador.Getesquiva() << " " << humanos[i].arma.GetnomeArma() << " " << humanos[i].arma.GetdanoArma() << " " << humanos[i].arma.GetcriticoArma() << " " << humanos[i].arma.GetvelocidadeArma() << " " << humanos[i].escudo.GetEscnome() << " " << humanos[i].escudo.GetEscblock() << " " << humanos[i].escudo.GetEscdefesa() << " " << humanos[i].escudo.GetEscvida() << endl;
            }

            arquivo.close();
        }


        void Removerhumano(vector<string>& Mankind, vector<Player>& humanos)
        {
            int ind;

            for(size_t i = 0; i < humanos.size(); i++)
            {
                cout << i << " - "
                << humanos[i].lutador.Getname() << endl;
            }

            ListarHumanos(humanos);
            cout << "O humano de qual posicao sera obliterado? ";
            cin >> ind;

            if(ind >= 0 && ind < humanos.size())
            {
                Mankind.erase(Mankind.begin() + ind);
                humanos.erase(humanos.begin() + ind);

                Salvarhumanos(Mankind, humanos);

                cout << "Humano removido!" << endl << endl;
            }
            else
            {
                cout << "Indice invalido!" << endl;
            }
        }

        void ListarHumanos(vector<Player>& humanos)
        {
            for(size_t i = 0; i < humanos.size(); i++)
            {
                cout << endl << "Nome: " << humanos[i].lutador.Getname() << endl;

                cout << "/-------------------Status -------------------/" << endl;

                cout << "Vida: " << humanos[i].lutador.Getlife() << ", ";
                cout << "Ataque: " << humanos[i].lutador.Getattack() << ", ";
                cout << "Defesa: " << humanos[i].lutador.Getdefense() << endl;

                cout << "/-------------------Equipamento --------------/" << endl;

                cout << "Arma: " << humanos[i].arma.GetnomeArma() << ", ";
                cout << "Dano: " << humanos[i].arma.GetdanoArma() << ", ";
                cout << "Velocidade: " << humanos[i].arma.GetvelocidadeArma() << ", ";
                cout << "Critico: " << humanos[i].arma.GetcriticoArma() << endl;

                cout << "Escudo: " << humanos[i].escudo.GetEscnome() << ", ";
                cout << "Defesa: " << humanos[i].escudo.GetEscdefesa() << ", ";
                cout << "Block: " << humanos[i].escudo.GetEscblock() << endl;
            }
        }



























