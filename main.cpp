#include "player.hpp"
#include <fstream>
#include "nomes.hpp"



void menu();
void submenu();


void CarregarHumanos(vector<string>& Mankind, vector<Player>& humanos);
void CarregarOrcs(vector<string>& Horde, vector<Player>& orcs);

void SalvarHumanos(vector<string>& Mankind, vector<Player>& humanos);
void SalvarOrcs(vector<string>& Horde, vector<Player>& orcs);

void RemoverHumano(vector<string>& Mankind, vector<Player>& humanos);
void RemoverOrcs(vector<string>& Horde, vector<Player>& orcs);

void AdicionarHumano(vector<string>& Mankind, vector<Player>& humanos);
void AdicionarOrc(vector<string>& Horde, vector<Player>& orcs);

void Luta(vector<Player>& humanos, vector<Player>& orcs);




void ListarHumanos(vector<Player>& humanos);
void ListarOrcs(vector<Player>& orcs);

vector<string> Mankind;
vector<Player> humanos;
vector<string> Horde;
vector<Player> orcs;



int main()
{

    CarregarHumanos(Mankind, humanos);
    CarregarOrcs(Horde, orcs);

    srand(time(0));

    menu();
            return 0;
}


void Luta(vector<Player>& humanos, vector<Player>& orcs)
{
    while (!humanos.empty() && !orcs.empty())
    {
        size_t i = rand() % humanos.size();
        size_t j = rand() % orcs.size();

        Player& humano = humanos[i];
        Player& orc = orcs[j];

        auto humanoAtaca = [&]()
        {
            cout << "Lutador " << humano.lutador.Getname()
            << " atacando " << orc.lutador.Getname() << "....";

            bool status = humano.Attack(orcs, j);

            if (status)
            {
                cout << "ataque bem-sucedido" << endl;

                if (orc.lutador.Getlife() <= 0)
                {
                    cout << "Fera abatida: "
                    << orc.lutador.Getname() << endl;
                    orcs.erase(orcs.begin() + j);
                    return;
                }

                cout << "vida restante: "
                << orc.lutador.Getlife() << endl;
            }
        };

        auto orcAtaca = [&]()
        {
            cout << "Lutador " << orc.lutador.Getname()
            << " atacando " << humano.lutador.Getname() << "....";

            bool status = orc.Attack(humanos, i);

            if (status)
            {
                cout << "ataque bem-sucedido" << endl;

                if (humano.lutador.Getlife() <= 0)
                {
                    cout << "Humano abatido: "
                    << humano.lutador.Getname() << endl;
                    humanos.erase(humanos.begin() + i);
                    return;
                }

                cout << "vida restante: "
                << humano.lutador.Getlife() << endl;
            }
        };

        if (humano.arma.GetvelocidadeArma() >=
            orc.arma.GetvelocidadeArma())
        {
            humanoAtaca();

            if (!orcs.empty() && !humanos.empty())
                orcAtaca();
        }
        else
        {
            orcAtaca();

            if (!humanos.empty() && !orcs.empty())
                humanoAtaca();
        }
    }

    if (humanos.empty())
        cout << "WINNER: Orcs" << endl;
    else
        cout << "WINNER: " << humanos[0].lutador.Getname() << endl;
}



        void menu()

        {
            int opt;
            submenu();
            while (opt != 8)
            {

                cin >> opt;
                cin.ignore();


                switch(opt)
                {
                    case 1: //colocar nome novo no humaninho
                    {
                        system("clear");
                        AdicionarHumano(Mankind, humanos);
                        cout << endl;
                        submenu();
                        break;
                    }

                    case 2: //colocar nome novo pros orcs
                    {
                        system("clear");
                        AdicionarOrc(Horde, orcs);
                        cout << endl;
                        submenu();
                        break;
                    }

                    case 3: //mostrar todos os lutadores
                    {
                        system("clear");
                        ListarHumanos(humanos);
                        cout << endl;
                        submenu();
                        break;
                    }

                    case 4:
                    {
                        system("clear");
                        ListarOrcs(orcs);
                        cout << endl;
                        submenu();
                        break;
                    }

                    case 5:
                    {
                        system("clear");
                        RemoverHumano(Mankind, humanos);
                        cout << endl;
                        submenu();
                        break;
                    }

                    case 6:
                    {
                        system("clear");
                        RemoverOrcs(Horde, orcs);
                        cout << endl;
                        submenu();
                        break;
                    }


                    case 7:
                        system("clear");
                        Luta(humanos, orcs);
                        cout << endl;
                        submenu();
                        break;

                    case 8:
                        cout << "saindo... ";
                        break;
                    default:
                    break;

                }
            }

        }

        void submenu()
        {

            cout << "1.Adicione um novo lutador para a humanidade" << endl;
            cout << "2.Incorporar um novo guerreiro a orda" << endl;
            cout << "3.Mostrar todos os guerreiros da humanidade"<< endl;
            cout << "4.Revelar Horda"<<endl;
            cout << "5.Obliterar um guerreiro humano" << endl;
            cout << "6.Caçar um monstro"<<endl;
            cout << "7.Iniciar o Ragnarok" << endl;

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

             SalvarHumanos(Mankind, humanos);
            system("clear");
            cout << "         ESTÁ BRINCANDO DE DEUS ? 0_0 " << endl;
        }

        void AdicionarOrc(vector<string>& Horde, vector<Player>& orcs)
        {
            string nome, nomeArma, Escnome;

            float life, attack, defense, esquiva, danoArma, criticoArma, velocidade, Escblock, Escdefesa, Escvida;

            cout << "Nome do orc: ";
            getline(cin, nome);


            life = rand()%1;
            attack = rand()%1;
            defense = rand()%1;
            esquiva = rand()%1;

            cout <<  "De nome ao aço: ";
            getline(cin, nomeArma);
            danoArma = rand()%1;
            criticoArma = rand()%1;
            velocidade = rand()%1;

            cout << "De nome a tabua para-golpe:";
            getline(cin, Escnome);
            Escblock = rand()%1;
            Escdefesa = rand()%1;
            Escvida = rand()%1;

            Horde.push_back(nome);

            orcs.emplace_back
            (
                nome, life, attack, defense,
             nomeArma, danoArma, criticoArma,
             esquiva, velocidade,
             Escnome, Escblock, Escdefesa, Escvida);


            SalvarHumanos(Horde, orcs);
            system("clear");
            cout << "        USANDO MAGIA PROIBIDA ? ISSO TERA CONSEQUENCIAS 0_0  " << endl;
        }

        void CarregarHumanos(vector<string>& Mankind, vector<Player>& humanos)
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

        void CarregarOrcs(vector<string>& Horde, vector<Player>& orcs)
        {
            ifstream arquivo("orcs.txt");
            int indice;

            string nome, nomeArma, nomeEscudo;

            float life, attack, defense, esquiva;
            float danoArma, criticoArma, velocidade;
            float Escblock, Escdefesa, Escvida;

            while(arquivo >> indice >> nome >> life >> attack >> defense >> esquiva >> nomeArma >> danoArma >> criticoArma >> velocidade >> nomeEscudo >> Escblock >> Escdefesa >> Escvida)
            {
                Horde.push_back(nome);

                orcs.emplace_back(
                    nome, life, attack, defense,
                    nomeArma, danoArma, criticoArma,
                    esquiva, velocidade,
                    nomeEscudo, Escblock, Escdefesa, Escvida);
            }

            arquivo.close();
        }

        void SalvarHumanos(vector<string>& Mankind, vector<Player>& humanos)
        {
            ofstream alala("humanos.txt");

            for(size_t i = 0; i < humanos.size(); i++)
            {
                alala << i << " "<< humanos[i].lutador.Getname() << " " <<humanos[i].lutador.Getlife() << " " <<humanos[i].lutador.Getattack() << " " <<humanos[i].lutador.Getdefense() << " " << humanos[i].lutador.Getesquiva() << " " << humanos[i].arma.GetnomeArma() << " " << humanos[i].arma.GetdanoArma() << " " << humanos[i].arma.GetcriticoArma() << " " << humanos[i].arma.GetvelocidadeArma() << " " << humanos[i].escudo.GetEscnome() << " " << humanos[i].escudo.GetEscblock() << " " << humanos[i].escudo.GetEscdefesa() << " " << humanos[i].escudo.GetEscvida() << endl;
            }

            alala.close();
        }

        void SalvarOrcs(vector<string>& Horde, vector<Player>& orcs)
        {
            ofstream oinc("orcs.txt");

            for(size_t i = 0; i < orcs.size(); i++)
            {
            oinc << i << " "<< orcs[i].lutador.Getname() << " " << orcs[i].lutador.Getlife() << " " << orcs[i].lutador.Getattack() << " " << orcs[i].lutador.Getdefense() << " " << orcs[i].lutador.Getesquiva() << " " << orcs[i].arma.GetnomeArma() << " " << orcs[i].arma.GetdanoArma() << " " << orcs[i].arma.GetcriticoArma() << " " << orcs[i].arma.GetvelocidadeArma() << " " << orcs[i].escudo.GetEscnome() << " " << orcs[i].escudo.GetEscblock() << " " << orcs[i].escudo.GetEscdefesa() << " " << orcs[i].escudo.GetEscvida() << endl;

            }

            oinc.close();
        }

        void RemoverHumano(vector<string>& Mankind, vector<Player>& humanos)
        {
            int ind;

            for(size_t i = 0; i < humanos.size(); i++)
            {
                cout << i << " - "
                << humanos[i].lutador.Getname() << endl;
            }

            cout << "O humano de qual posicao sera obliterado? ";
            cin >> ind;

            if(ind >= 0 && ind < humanos.size())
            {
                Mankind.erase(Mankind.begin() + ind);
                humanos.erase(humanos.begin() + ind);

                SalvarHumanos(Mankind, humanos);

                cout << "Humano Abatido!" << endl << endl;
            }
            else
            {
                cout << "Indice invalido!" << endl;
            }
        }

        void RemoverOrcs(vector<string>& Horde, vector<Player>& orcs)
        {
            int ind;

            for(size_t i = 0; i < orcs.size(); i++)
            {
                cout << i << " - "
                << orcs[i].lutador.Getname() << endl;
            }

            cout << "Qual fera caçaremos hoje? ";
            cin >> ind;

            if(ind >= 0 && ind < orcs.size())
            {
                Horde.erase(Horde.begin() + ind);
                orcs.erase(orcs.begin() + ind);

                SalvarOrcs(Horde, orcs);

                cout << "MONSTRO CAIDO !" << endl << endl;
            }
            else
            {
                cout << "indice invalido !" << endl;
            }
        }

        void ListarHumanos(vector<Player>& humanos)
        {
        if (humanos.size() > 0 )
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
        else
            cout << "Estamos sem caçadores" << endl;

        }

        void ListarOrcs(vector<Player>& orcs)
        {
            if (orcs.size() > 0 )

            {

            for(size_t i = 0; i < orcs.size(); i++)
            {
                cout << endl << "Nome: " << orcs[i].lutador.Getname() << endl;

                cout << "/-------------------Status -------------------/" << endl;

                cout << "Vida: " << orcs[i].lutador.Getlife() << ", ";
                cout << "Ataque: " << orcs[i].lutador.Getattack() << ", ";
                cout << "Defesa: " << orcs[i].lutador.Getdefense() << endl;

                cout << "/-------------------Equipamento --------------/" << endl;

                cout << "Arma: " << orcs[i].arma.GetnomeArma() << ", ";
                cout << "Dano: " << orcs[i].arma.GetdanoArma() << ", ";
                cout << "Velocidade: " << orcs[i].arma.GetvelocidadeArma() << ", ";
                cout << "Critico: " << orcs[i].arma.GetcriticoArma() << endl;

                cout << "Escudo: " << orcs[i].escudo.GetEscnome() << ", ";
                cout << "Defesa: " << orcs[i].escudo.GetEscdefesa() << ", ";
                cout << "Block: " << orcs[i].escudo.GetEscblock() << endl;
            }
            }
            else
                cout << "A orda não possui guerreiros" << endl;


        }


