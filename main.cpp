#include "player.hpp"
#include <fstream>
#include "nomes.hpp"
#include <cstdlib>
#include <ctime>
//Allef e Kauan

void menu();
void submenu();

void GerarOrcs(vector<string>& Horde, vector<Player>& orcs);
void GerarHumanos(vector<string>& Mankind, vector<Player>& humanos);
//-- novo
void GerarElfos(vector<string>& Folk, vector<Player>&elfos);
void GerarDemonios(vector<string>& Cult, vector<Player>&demonios);
void GerarDraconatos(vector<string>&Clan, vector<Player>&draconatos);



void CarregarHumanos(vector<string>& Mankind, vector<Player>& humanos);
void CarregarOrcs(vector<string>& Horde, vector<Player>& orcs);
void CarregarElfos(vector<string>& Folk, vector<Player>&elfos);
void CarregarDemonios(vector<string>& Cult, vector<Player>&demonios);
void CarregarDraconatos(vector<string>&Clan, vector<Player>&draconatos);


void SalvarHumanos(vector<string>& Mankind, vector<Player>& humanos);
void SalvarOrcs(vector<string>& Horde, vector<Player>& orcs);
void SalvarElfos(vector<string>& Folk, vector<Player>&elfos);
void SalvarDemonios(vector<string>& Cult, vector<Player>&demonios);
void SalvarDraconatos(vector<string>&Clan, vector<Player>&draconatos);


void RemoverHumano(vector<string>& Mankind, vector<Player>& humanos);
void RemoverOrcs(vector<string>& Horde, vector<Player>& orcs);
void RemoverElfos(vector<string>& Folk, vector<Player>&elfos);
void RemoverDemonios(vector<string>& Cult, vector<Player>&demonios);
void RemoverDraconatos(vector<string>&Clan, vector<Player>&draconatos);





void AdicionarHumano(vector<string>& Mankind, vector<Player>& humanos);
void AdicionarOrc(vector<string>& Horde, vector<Player>& orcs);
void AdicionarElfos(vector<string>& Folk, vector<Player>&elfos);
void AdicionarDemonios(vector<string>& Cult, vector<Player>&demonios);
void AdicionarDraconatos(vector<string>&Clan, vector<Player>&draconatos);



void Luta(vector<Player>& grupo1, vector<Player>& grupo2);
void EscolherLuta();



void ListarHumanos(vector<Player>& humanos);
void ListarOrcs(vector<Player>& orcs);
void ListarElfos(vector<Player>&elfos);
void ListarDemonios(vector<Player>&demonios);
void ListarDraconatos(vector<Player>&draconatos);



vector<string> Mankind;
vector<Player> humanos;
vector<string> Horde;
vector<Player> orcs;
vector<string> Folk;
vector<Player> elfos;
vector<string> Cult;
vector<Player> demonios;
vector<string> Clan;
vector<Player> draconatos;



int main()
{

    CarregarHumanos(Mankind, humanos);
    CarregarOrcs(Horde, orcs);
    CarregarElfos(Folk, elfos);
    CarregarDemonios(Cult, demonios);
    CarregarDraconatos(Clan, draconatos);

    srand(time(0));

    menu();
            return 0;
}


void Luta(vector<Player>& grupo1, vector<Player>& grupo2)
{
    while (!grupo1.empty() && !grupo2.empty())
    {
        size_t i = rand() % grupo1.size();
        size_t j = rand() % grupo2.size();

        Player& jogador1 = grupo1[i];
        Player& jogador2 = grupo2[j];

        auto jogador1Ataca = [&]()
        {
            cout << "Lutador " << jogador1.lutador.Getname() << " atacando...\n";

            //critical-hit starts here
            int chanceCritico = rand() % 100;
            
            if (jogador1.IsHero() && chanceCritico > 20 && grupo2.size() > 1) 
            {
                cout << "I am the storm that is approaching!!!(CRITOOOUU EM GRUPO)" << endl;
                vector<size_t> indicesAfetados;
                
                size_t numAlvos = min(grupo2.size(), (size_t)(rand() % 2 + 2)); 
                
                for (size_t i = 0; i < numAlvos; i++) {
                    indicesAfetados.push_back(rand() % grupo2.size());
                }

                for (size_t danoGrupo : indicesAfetados) {
                    cout << "Acertando alvo secundário " << grupo2[danoGrupo].lutador.Getname() << "... ";
                    jogador1.Attack(grupo2, danoGrupo);
                }

                for (int i = grupo2.size() - 1; i >= 0; i--) {
                    if (grupo2[i].lutador.Getlife() <= 0) {
                        cout << "Lutador abatido no ataque em área: " << grupo2[i].lutador.Getname() << endl;
                        grupo2.erase(grupo2.begin() + i);
                    }
                }
                
                if(grupo2.empty()) return; 
            }
            else 
            {
                
                cout << "atacando " << jogador2.lutador.Getname() << "....";
                bool status = jogador1.Attack(grupo2, j);

                if (status)
                {
                    cout << "ataque bem-sucedido" << endl;

                    if (grupo2[j].lutador.Getlife() <= 0)
                    {
                        cout << "Lutador abatido: " << grupo2[j].lutador.Getname() << endl;
                        grupo2.erase(grupo2.begin() + j);
                        return;
                    }

                    cout << "vida restante: " << grupo2[j].lutador.Getlife() << endl;
                }
            }
        };

        auto jogador2Ataca = [&]()
        {
            cout << "Lutador " << jogador2.lutador.Getname()
            << " atacando " << jogador1.lutador.Getname() << "....";

            int chanceCritico = rand() %100;

            if (jogador2.IsHero() && chanceCritico > 20 && grupo1.size() > 1)
            {
                cout << "I am the storm that is approaching!!!(CRITOOOUU EM GRUPO)" << endl;
                vector<size_t> indicesAfetados;

                size_t numAlvos = min(grupo1.size(), (size_t)(rand()%2 + 2));

                for(size_t i=0; i < numAlvos; i++){
                    indicesAfetados.push_back(rand() % grupo1.size());

                }
                for(size_t danoGrupo : indicesAfetados){
                    cout << "Acertando alvo secundário " << grupo1[danoGrupo].lutador.Getname() << "... ";
                    jogador2.Attack(grupo1, danoGrupo);
                }
                for(int i = grupo1.size() - 1; i >= 0; i--){
                    if (grupo1[i].lutador.Getlife() <= 0) {
                        cout << "Lutador abatido no ataque em área: " << grupo1[i].lutador.Getname() << endl;
                        grupo1.erase(grupo1.begin() + i);
                    }
                }
                if(grupo1.empty()) return;

            }
            else 
            {
                cout << "atacando " << jogador1.lutador.Getname() << "....";
                bool status = jogador2.Attack(grupo1, i);

            
                if (status)
                {
                    cout << "ataque bem-sucedido" << endl;

                    if (jogador1.lutador.Getlife() <= 0)
                    {
                        cout << "Lutador abatido: "
                        << jogador1.lutador.Getname() << endl;

                        grupo1.erase(grupo1.begin() + i);
                        return;
                    }

                    cout << "vida restante: "
                    << jogador1.lutador.Getlife() << endl;
                }
            }
        };

        if (jogador1.arma.GetvelocidadeArma() >=
            jogador2.arma.GetvelocidadeArma())
        {
            jogador1Ataca();

            if (!grupo2.empty() && !grupo1.empty())
                jogador2Ataca();
        }
        else
        {
            jogador2Ataca();

            if (!grupo1.empty() && !grupo2.empty())
                jogador1Ataca();
        }
    }

    if (grupo1.empty())
    {
        cout << "O vencedor foi: " << endl;
        cout << grupo2[0].lutador.Getname() << endl;
    }
    else
    {
        cout << "O vencedor foi: " <<  endl;
        cout << grupo1[0].lutador.Getname() << endl;
    }
}

void EscolherLuta()
{
    int escolha1, escolha2;

    vector<Player>* equipe1 = nullptr; //lembrar desses ponteiros
    vector<Player>* equipe2 = nullptr;

    cout << "Escolha sua batalha" << endl;

    cout << "1 - Humanos" << endl;
    cout << "2 - Orcs" << endl;
    cout << "3 - Elfos" << endl;
    cout << "4 - Demonios" << endl;
    cout << "5 - Draconatos" << endl;

    cout << "Escolha o primeiro grupo: ";
    cin >> escolha1;

    cout << "Escolha o segundo grupo: ";
    cin >> escolha2;

    if (escolha1 < 1 || escolha1 > 5 ||
        escolha2 < 1 || escolha2 > 5 ||
        escolha1 == escolha2)
    {
        cout << "Escolha invalida!\n";
        return;
    }

    switch (escolha1)
    {
        case 1: equipe1 = &humanos;
        break;
        case 2: equipe1 = &orcs;
        break;
        case 3: equipe1 = &elfos;
        break;
        case 4: equipe1 = &demonios;
        break;
        case 5: equipe1 = &draconatos;
        break;
    }

    switch (escolha2)
    {
        case 1: equipe2 = &humanos;
        break;
        case 2: equipe2 = &orcs;
        break;
        case 3: equipe2 = &elfos;
        break;
        case 4: equipe2 = &demonios;
        break;
        case 5: equipe2 = &draconatos;
        break;
    }

    if (equipe1->empty() || equipe2->empty())
    {
        cout << "Algum dos grupos não tem ninguem, adicione guerreiros ou chame o Day of the Dead!" << endl;
        return;
    }

    Luta(*equipe1, *equipe2);
}



        void menu()

        {
            int opt = 0;
            submenu();
            while (opt != 6)
            {

                cin >> opt;
                cin.ignore();


                switch(opt)
                {
                    case 1:
                    {
                        int option = 0;
                        system("clear");
                        cout << "1. Criar um humano" << endl;
                        cout << "2. Adicionar um orc" << endl;
                        cout << "3. Achar um elfo" << endl;
                        cout << "4. Invocar um demonio" << endl;
                        cout << "5. Chocar um draconato" << endl;
                        cout << "6. voltar ao menu" << endl;
                        cin >> option;
                        cin.ignore();

                        switch(option)
                        {
                            case 1:
                                system("clear");
                                AdicionarHumano(Mankind, humanos);
                                break;
                            case 2:
                                system("clear");
                                AdicionarOrc(Horde, orcs);
                                break;
                            case 3:
                                system("clear");
                                AdicionarElfos(Folk, elfos);
                                break;
                            case 4:
                                system("clear");
                                AdicionarDemonios(Cult, demonios);
                                break;
                            case 5:
                                system("clear");
                                AdicionarDraconatos(Clan, draconatos);
                                break;
                            case 6:
                                system("clear");
                                break;
                            default:
                            break;
                        }
                        cout << endl;
                        submenu();
                        break;
                    }

                    case 2: //colocar nome novo pros orcs
                    {

                        int opt = 0;
                        system("clear");
                        cout << "1. Listar humanos" << endl;
                        cout << "2. Listar orcs" << endl;
                        cout << "3. Listar elfos" << endl;
                        cout << "4. Listas demonios" << endl;
                        cout << "5. Listar draconatos" << endl;
                        cout << "6. voltar ao menu" << endl;
                        cin >> opt;
                        cin.ignore();

                        switch(opt)
                        {
                            case 1:
                                ListarHumanos(humanos);
                                break;
                            case 2:
                                ListarOrcs(orcs);
                                break;
                            case 3:
                                ListarElfos(elfos);
                                break;
                            case 4:
                                ListarDemonios(demonios);
                                break;
                            case 5:
                                ListarDraconatos(draconatos);
                                break;
                            case 6:
                                break;
                            default:
                                break;
                        }

                        submenu();
                        break;
                    }

                    case 3: //mostrar todos os lutadores
                    {

                        int option;
                        system("clear");
                        cout << "1. Remover um humano." << endl;
                        cout << "2. Remover um orc" << endl;
                        cout << "3. Remover um elfo" << endl;
                        cout << "4. Remover um demonio" << endl;
                        cout << "5. Remover um draconato" << endl;
                        cout << "6. voltar ao menu" << endl;
                        cin >> option;
                        cin.ignore();

                        switch(option)
                        {
                            case 1:
                                system("clear");
                                RemoverHumano(Mankind, humanos);
                                break;
                            case 2:
                                system("clear");
                                RemoverOrcs(Horde, orcs);
                                break;
                            case 3:
                                system("clear");
                                RemoverElfos(Folk, elfos);
                                break;
                            case 4:
                                system("clear");
                                RemoverDemonios(Cult, demonios);
                                break;
                            case 5:
                                system("clear");
                                RemoverDraconatos(Clan, draconatos);
                                break;
                            case 6:
                                system("clear");
                                break;
                            default:
                                break;
                        }

                        submenu();
                        break;
                    }

                    case 4:
                    {
                        system("clear");
                        EscolherLuta();
                        cout << endl;
                        submenu();
                        break;
                    }


                    case 5:
                    {
                     system("clear");
                     cout << "Fantasmas de Valhala ";
                     GerarOrcs(Horde, orcs);
                     GerarHumanos(Mankind, humanos);
                     GerarElfos(Folk, elfos);
                     GerarDemonios(Cult, demonios);
                     GerarDraconatos(Clan, draconatos);
                     cout << endl;
                     submenu();
                     break;

                    }
                    case 6:
                    {
                        cout << "saindo... ";
                        break;
                    }

                    default:
                        break;
                }
            }

        }

        void submenu()
        {

            cout << "1.Adicionar um guerreiro" << endl;
            cout << "2.Mostar listas"<< endl;
            cout << "3. Obliterar um escolhido" << endl;
            cout << "4.Iniciar o Ragnarok" << endl;
            cout << "5.Day of the Dead" << endl;
            cout << "6.Sair" << endl;
        }

        void AdicionarHumano(vector<string>& Mankind, vector<Player>& humanos)
        {
            string nome, nomeArma, Escnome;

            float life, attack, defense, esquiva, danoArma, criticoArma, velocidade, Escblock, Escdefesa, Escvida;

            cout << "Nome do humano: ";
            getline(cin, nome);


            life = rand()%51 + 50;
            attack = rand()%11 + 10;
            defense = rand()%16;
            esquiva = rand()%29;

            cout <<  "Qual sera o nome da arma ? ";
            getline(cin, nomeArma);
            danoArma = rand()%25;
            criticoArma = rand()%25;
            velocidade = rand()%25;

            cout << "Qual sera o nome do escudo ?";
            getline(cin, Escnome);
            Escblock = rand()%25;
            Escdefesa = rand()%25;
            Escvida = rand()%25;

            bool isHero;
            cout << "Transformar em heroi? (1 - Sim, 0 - Nao): ";
            cin >> isHero;
            cin.ignore();

            Mankind.push_back(nome);

            humanos.emplace_back
            (
                nome, life, attack, defense,
                nomeArma, danoArma, criticoArma,
                esquiva, velocidade,
                Escnome, Escblock, Escdefesa, Escvida, isHero);

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


            life = rand()%51 + 50;
            attack = rand()%11 + 10;
            defense = rand()%16;
            esquiva = rand()%29;

            cout <<  "De nome ao aço: ";
            getline(cin, nomeArma);
            danoArma = rand()%25;
            criticoArma = rand()%25;
            velocidade = rand()%25;

            cout << "De nome a tabua para-golpe:";
            getline(cin, Escnome);
            Escblock = rand()%25;
            Escdefesa = rand()%25;
            Escvida = rand()%25;

            bool isHero;
            cout << "Transformar em heroi? (1 - Sim, 0 - Nao): ";
            cin >> isHero;
            cin.ignore();

            Horde.push_back(nome);

            orcs.emplace_back
            (
                nome, life, attack, defense,
             nomeArma, danoArma, criticoArma,
             esquiva, velocidade,
             Escnome, Escblock, Escdefesa, Escvida, isHero);


            SalvarOrcs(Horde, orcs);
            system("clear");
            cout << "        USANDO MAGIA PROIBIDA ? ISSO TERA CONSEQUENCIAS 0_0  " << endl;
        }

        void AdicionarElfos(vector<string>& Folk, vector<Player>& elfos)
        {
            string nome, nomeArma, Escnome;

            float life, attack, defense, esquiva, danoArma, criticoArma, velocidade, Escblock, Escdefesa, Escvida;

            cout << "Nome do elfo: ";
            getline(cin, nome);


            life = rand()%51 + 50;
            attack = rand()%11 + 10;
            defense = rand()%16;
            esquiva = rand()%29;

            cout <<  "Nomeando armamento: ";
            getline(cin, nomeArma);
            danoArma = rand()%25;
            criticoArma = rand()%25;
            velocidade = rand()%25;

            cout << "Nomeando Proteção:";
            getline(cin, Escnome);
            Escblock = rand()%25;
            Escdefesa = rand()%25;
            Escvida = rand()%25;

            bool isHero;
            cout << "Transformar em heroi? (1 - Sim, 0 - Nao): ";
            cin >> isHero;
            cin.ignore();

            Folk.push_back(nome);

            elfos.emplace_back
            (
                nome, life, attack, defense,
             nomeArma, danoArma, criticoArma,
             esquiva, velocidade,
             Escnome, Escblock, Escdefesa, Escvida, isHero);


            SalvarElfos(Folk, elfos);
            system("clear");
            cout << "        Um novo elfo nasceu!!, mas pera... ele...  " << endl;
        }

        void AdicionarDemonios(vector<string>& Cult, vector<Player>& demonios)
        {
            string nome, nomeArma, Escnome;

            float life, attack, defense, esquiva, danoArma, criticoArma, velocidade, Escblock, Escdefesa, Escvida;

            cout << "Nome do satanas: ";
            getline(cin, nome);


            life = rand()%51 + 50;
            attack = rand()%11 + 10;
            defense = rand()%16;
            esquiva = rand()%29;

            cout <<  "De nome a arma do capeta: ";
            getline(cin, nomeArma);
            danoArma = rand()%25;
            criticoArma = rand()%25;
            velocidade = rand()%25;

            cout << "De nome ao escudo do diabo:";
            getline(cin, Escnome);
            Escblock = rand()%25;
            Escdefesa = rand()%25;
            Escvida = rand()%25;

            bool isHero;
            cout << "Transformar em heroi? (1 - Sim, 0 - Nao): ";
            cin >> isHero;
            cin.ignore();

            Cult.push_back(nome);

            demonios.emplace_back
            (
                nome, life, attack, defense,
             nomeArma, danoArma, criticoArma,
             esquiva, velocidade,
             Escnome, Escblock, Escdefesa, Escvida, isHero);


            SalvarDemonios(Cult, demonios);
            system("clear");
            cout << "        VOCÊ INVOCOU ISSO ????? AQUI ???? NÃO PODE SER " << endl;
        }

        void AdicionarDraconatos(vector<string>& Clan, vector<Player>& draconatos)
        {
            string nome, nomeArma, Escnome;

            float life, attack, defense, esquiva, danoArma, criticoArma, velocidade, Escblock, Escdefesa, Escvida;

            cout << "Nome do dagrão: ";
            getline(cin, nome);


            life = rand()%51 + 50;
            attack = rand()%11 + 10;
            defense = rand()%16;
            esquiva = rand()%29;

            cout <<  "De nome a garra: ";
            getline(cin, nomeArma);
            danoArma = rand()%25;
            criticoArma = rand()%25;
            velocidade = rand()%25;

            cout << "De nome as escamas:";
            getline(cin, Escnome);
            Escblock = rand()%25;
            Escdefesa = rand()%25;
            Escvida = rand()%25;

            bool isHero;
            cout << "Transformar em heroi? (1 - Sim, 0 - Nao): ";
            cin >> isHero;
            cin.ignore();

            Clan.push_back(nome);

            draconatos.emplace_back
            (
                nome, life, attack, defense,
             nomeArma, danoArma, criticoArma,
             esquiva, velocidade,
             Escnome, Escblock, Escdefesa, Escvida, isHero);


            SalvarDraconatos(Clan, draconatos);
            system("clear");
            cout << "        Um dragão novo foi trazido ao mundo!  " << endl;
        }



        void CarregarHumanos(vector<string>& Mankind, vector<Player>& humanos)
        {
            ifstream arquivo("humanos.txt");
            int indice;

            string nome, nomeArma, nomeEscudo;

            float life, attack, defense, esquiva;
            float danoArma, criticoArma, velocidade;
            float Escblock, Escdefesa, Escvida;
            bool isHero;

            while(arquivo >> indice >> nome >> life >> attack >> defense >> esquiva >> nomeArma >> danoArma >> criticoArma >> velocidade >> nomeEscudo >> Escblock >> Escdefesa >> Escvida >> isHero)
            {
                Mankind.push_back(nome);

                humanos.emplace_back(
                    nome, life, attack, defense,
                    nomeArma, danoArma, criticoArma,
                    esquiva, velocidade,
                    nomeEscudo, Escblock, Escdefesa, Escvida, isHero);
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
            bool isHero;

            while(arquivo >> indice >> nome >> life >> attack >> defense >> esquiva >> nomeArma >> danoArma >> criticoArma >> velocidade >> nomeEscudo >> Escblock >> Escdefesa >> Escvida >> isHero)
            {
                Horde.push_back(nome);

                orcs.emplace_back(
                    nome, life, attack, defense,
                    nomeArma, danoArma, criticoArma,
                    esquiva, velocidade,
                    nomeEscudo, Escblock, Escdefesa, Escvida, isHero);
            }

            arquivo.close();
        }

        void CarregarElfos(vector<string>& Folk, vector<Player>& elfos)
        {
            ifstream arquivo("elfos.txt");
            int indice;

            string nome, nomeArma, nomeEscudo;

            float life, attack, defense, esquiva;
            float danoArma, criticoArma, velocidade;
            float Escblock, Escdefesa, Escvida;
            bool isHero;

            while(arquivo >> indice >> nome >> life >> attack >> defense >> esquiva >> nomeArma >> danoArma >> criticoArma >> velocidade >> nomeEscudo >> Escblock >> Escdefesa >> Escvida >> isHero)
            {
                Folk.push_back(nome);

                elfos.emplace_back(
                    nome, life, attack, defense,
                    nomeArma, danoArma, criticoArma,
                    esquiva, velocidade,
                    nomeEscudo, Escblock, Escdefesa, Escvida, isHero);
            }

            arquivo.close();
        }

        void CarregarDemonios(vector<string>& Cult, vector<Player>& demonios)
        {
            ifstream arquivo("Demonios.txt");
            int indice;

            string nome, nomeArma, nomeEscudo;

            float life, attack, defense, esquiva;
            float danoArma, criticoArma, velocidade;
            float Escblock, Escdefesa, Escvida;
            bool isHero;

            while(arquivo >> indice >> nome >> life >> attack >> defense >> esquiva >> nomeArma >> danoArma >> criticoArma >> velocidade >> nomeEscudo >> Escblock >> Escdefesa >> Escvida >> isHero)
            {
                Cult.push_back(nome);

                demonios.emplace_back(
                    nome, life, attack, defense,
                    nomeArma, danoArma, criticoArma,
                    esquiva, velocidade,
                    nomeEscudo, Escblock, Escdefesa, Escvida, isHero);
            }

            arquivo.close();
        }

        void CarregarDraconatos(vector<string>& Clan, vector<Player>& draconatos)
        {
            ifstream arquivo("draconatos.txt");
            int indice;

            string nome, nomeArma, nomeEscudo;

            float life, attack, defense, esquiva;
            float danoArma, criticoArma, velocidade;
            float Escblock, Escdefesa, Escvida;
            bool isHero;

            while(arquivo >> indice >> nome >> life >> attack >> defense >> esquiva >> nomeArma >> danoArma >> criticoArma >> velocidade >> nomeEscudo >> Escblock >> Escdefesa >> Escvida >> isHero)
            {
                Clan.push_back(nome);

                draconatos.emplace_back(
                    nome, life, attack, defense,
                    nomeArma, danoArma, criticoArma,
                    esquiva, velocidade,
                    nomeEscudo, Escblock, Escdefesa, Escvida, isHero);
            }

            arquivo.close();
        }




        void SalvarHumanos(vector<string>& Mankind, vector<Player>& humanos)
        {
            ofstream alala("humanos.txt");

            for(size_t i = 0; i < humanos.size(); i++)
            {
                alala << i << " "<< humanos[i].lutador.Getname() << " " <<humanos[i].lutador.Getlife() << " " <<humanos[i].lutador.Getattack() << " " <<humanos[i].lutador.Getdefense() << " " << humanos[i].lutador.Getesquiva() << " " << humanos[i].arma.GetnomeArma() << " " << humanos[i].arma.GetdanoArma() << " " << humanos[i].arma.GetcriticoArma() << " " << humanos[i].arma.GetvelocidadeArma() << " " << humanos[i].escudo.GetEscnome() << " " << humanos[i].escudo.GetEscblock() << " " << humanos[i].escudo.GetEscdefesa() << " " << humanos[i].escudo.GetEscvida() << " " << humanos[i].IsHero() << endl;
            }

            alala.close();
        }

        void SalvarOrcs(vector<string>& Horde, vector<Player>& orcs)
        {
            ofstream oinc("orcs.txt");

            for(size_t i = 0; i < orcs.size(); i++)
            {
            oinc << i << " "<< orcs[i].lutador.Getname() << " " << orcs[i].lutador.Getlife() << " " << orcs[i].lutador.Getattack() << " " << orcs[i].lutador.Getdefense() << " " << orcs[i].lutador.Getesquiva() << " " << orcs[i].arma.GetnomeArma() << " " << orcs[i].arma.GetdanoArma() << " " << orcs[i].arma.GetcriticoArma() << " " << orcs[i].arma.GetvelocidadeArma() << " " << orcs[i].escudo.GetEscnome() << " " << orcs[i].escudo.GetEscblock() << " " << orcs[i].escudo.GetEscdefesa() << " " << orcs[i].escudo.GetEscvida() << " " << orcs[i].IsHero() << endl;

            }

            oinc.close();
        }

        void SalvarElfos(vector<string>& Folk, vector<Player>& elfos)
        {
            ofstream fadas("elfos.txt");

            for(size_t i = 0; i < elfos.size(); i++)
            {
                fadas << i << " "<< elfos[i].lutador.Getname() << " " << elfos[i].lutador.Getlife() << " " << elfos[i].lutador.Getattack() << " " << elfos[i].lutador.Getdefense() << " " << elfos[i].lutador.Getesquiva() << " " << elfos[i].arma.GetnomeArma() << " " << elfos[i].arma.GetdanoArma() << " " << elfos[i].arma.GetcriticoArma() << " " << elfos[i].arma.GetvelocidadeArma() << " " << elfos[i].escudo.GetEscnome() << " " << elfos[i].escudo.GetEscblock() << " " << elfos[i].escudo.GetEscdefesa() << " " << elfos[i].escudo.GetEscvida() << " " << elfos[i].IsHero() << endl;

            }

            fadas.close();
        }

        void SalvarDemonios(vector<string>& Cult, vector<Player>& demonios)
        {
            ofstream inferno("Demonios.txt");

            for(size_t i = 0; i < demonios.size(); i++)
            {
                inferno << i << " "<< demonios[i].lutador.Getname() << " " << demonios[i].lutador.Getlife() << " " << demonios[i].lutador.Getattack() << " " << demonios[i].lutador.Getdefense() << " " << demonios[i].lutador.Getesquiva() << " " << demonios[i].arma.GetnomeArma() << " " << demonios[i].arma.GetdanoArma() << " " << demonios[i].arma.GetcriticoArma() << " " << demonios[i].arma.GetvelocidadeArma() << " " << demonios[i].escudo.GetEscnome() << " " << demonios[i].escudo.GetEscblock() << " " << demonios[i].escudo.GetEscdefesa() << " " << demonios[i].escudo.GetEscvida() << " " << demonios[i].IsHero() << endl;

            }

            inferno.close();
        }

        void SalvarDraconatos(vector<string>& Clan, vector<Player>& draconatos)
        {
            ofstream raaaw("draconatos.txt");

            for(size_t i = 0; i < draconatos.size(); i++)
            {
                raaaw << i << " "<< draconatos[i].lutador.Getname() << " " << draconatos[i].lutador.Getlife() << " " << draconatos[i].lutador.Getattack() << " " << draconatos[i].lutador.Getdefense() << " " << draconatos[i].lutador.Getesquiva() << " " << draconatos[i].arma.GetnomeArma() << " " << draconatos[i].arma.GetdanoArma() << " " << draconatos[i].arma.GetcriticoArma() << " " << draconatos[i].arma.GetvelocidadeArma() << " " << draconatos[i].escudo.GetEscnome() << " " << draconatos[i].escudo.GetEscblock() << " " << draconatos[i].escudo.GetEscdefesa() << " " << draconatos[i].escudo.GetEscvida() << " " << draconatos[i].IsHero() << endl;

            }

            raaaw.close();
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

            cout << "Qual orc a ser abatido? ";
            cin >> ind;

            if(ind >= 0 && ind < orcs.size())
            {
                Horde.erase(Horde.begin() + ind);
                orcs.erase(orcs.begin() + ind);

                SalvarOrcs(Horde, orcs);

                cout << "um orc foi,  só faltam... muitos." << endl << endl;
            }
            else
            {
                cout << "indice invalido !" << endl;
            }
        }

        void RemoverElfos(vector<string>& Folk, vector<Player>& elfos)
        {
            int ind;

            for(size_t i = 0; i < elfos.size(); i++)
            {
                cout << i << " - "
                << elfos[i].lutador.Getname() << endl;
            }

            cout << "Deidade a ser abatida ";
            cin >> ind;

            if(ind >= 0 && ind < elfos.size())
            {
                Folk.erase(Folk.begin() + ind);
                elfos.erase(elfos.begin() + ind);

                SalvarElfos(Folk, elfos);

                cout << " Caçar elfos não é proibido ? " << endl << endl;
            }
            else
            {
                cout << "indice invalido !" << endl;
            }
        }

        void RemoverDemonios(vector<string>& Cult, vector<Player>& demonios)
        {
            int ind;

            for(size_t i = 0; i < demonios.size(); i++)
            {
                cout << i << " - "
                << demonios[i].lutador.Getname() << endl;
            }

            cout << "Quem vamos exorcizar hoje? ";
            cin >> ind;

            if(ind >= 0 && ind < demonios.size())
            {
                Cult.erase(Cult.begin() + ind);
                demonios.erase(demonios.begin() + ind);

                SalvarDemonios(Cult, demonios);

                cout << endl <<"  ELE VOLTOU PRO LUGAR DE ONDE NUNCA DEVIA TER SAIDO! " << endl << endl;
            }
            else
            {
                cout << "indice invalido !" << endl;
            }
        }

        void RemoverDraconatos(vector<string>& Clan, vector<Player>& draconatos)
        {
            int ind;

            for(size_t i = 0; i < draconatos.size(); i++)
            {
                cout << i << " - "
                << draconatos[i].lutador.Getname() << endl;
            }

            cout << "Qual fera caçaremos hoje? ";
            cin >> ind;

            if(ind >= 0 && ind < draconatos.size())
            {
                Clan.erase(Clan.begin() + ind);
                draconatos.erase(draconatos.begin() + ind);

                SalvarDraconatos(Horde, orcs);

                cout << endl << "        MONSTRO CAIDO !" << endl << endl;
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
                cout << endl << "Nome: " << humanos[i].lutador.Getname() << (humanos[i].IsHero() ? " (H)" : "") << endl;

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
        {
            system ("clear");
            cout << "Estamos sem caçadores" << endl << endl;


        }
        }

        void ListarOrcs(vector<Player>& orcs)
        {
            if (orcs.size() > 0 )

            {

            for(size_t i = 0; i < orcs.size(); i++)
            {
                cout << endl << "Nome: " << orcs[i].lutador.Getname() << (orcs[i].IsHero() ? " (H)" : "") << endl;

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
                system ("clear");
                cout << "A Horda não possui guerreiros" << endl << endl;


        }

        void ListarElfos(vector<Player>& elfos)
        {
            if (elfos.size() > 0 )

            {

                for(size_t i = 0; i < elfos.size(); i++)
                {
                    cout << endl << "Nome: " << elfos[i].lutador.Getname() << (elfos[i].IsHero() ? " (H)" : "") << endl;

                    cout << "/-------------------Status -------------------/" << endl;

                    cout << "Vida: " << elfos[i].lutador.Getlife() << ", ";
                    cout << "Ataque: " << elfos[i].lutador.Getattack() << ", ";
                    cout << "Defesa: " << elfos[i].lutador.Getdefense() << endl;

                    cout << "/-------------------Equipamento --------------/" << endl;

                    cout << "Arma: " << elfos[i].arma.GetnomeArma() << ", ";
                    cout << "Dano: " << elfos[i].arma.GetdanoArma() << ", ";
                    cout << "Velocidade: " << elfos[i].arma.GetvelocidadeArma() << ", ";
                    cout << "Critico: " << elfos[i].arma.GetcriticoArma() << endl;

                    cout << "Escudo: " << elfos[i].escudo.GetEscnome() << ", ";
                    cout << "Defesa: " << elfos[i].escudo.GetEscdefesa() << ", ";
                    cout << "Block: " << elfos[i].escudo.GetEscblock() << endl;
                }
            }
            else
                system ("clear");
                cout << "A Conclave não possui membros" << endl << endl;


        }

        void ListarDemonios(vector<Player>& demonios)
        {
            if (demonios.size() > 0 )

            {

                for(size_t i = 0; i < demonios.size(); i++)
                {
                    cout << endl << "Nome: " << demonios[i].lutador.Getname() << (demonios[i].IsHero() ? " (H)" : "") << endl;

                    cout << "/-------------------Status -------------------/" << endl;

                    cout << "Vida: " << demonios[i].lutador.Getlife() << ", ";
                    cout << "Ataque: " << demonios[i].lutador.Getattack() << ", ";
                    cout << "Defesa: " << demonios[i].lutador.Getdefense() << endl;

                    cout << "/-------------------Equipamento --------------/" << endl;

                    cout << "Arma: " << demonios[i].arma.GetnomeArma() << ", ";
                    cout << "Dano: " << demonios[i].arma.GetdanoArma() << ", ";
                    cout << "Velocidade: " << demonios[i].arma.GetvelocidadeArma() << ", ";
                    cout << "Critico: " << demonios[i].arma.GetcriticoArma() << endl;

                    cout << "Escudo: " << demonios[i].escudo.GetEscnome() << ", ";
                    cout << "Defesa: " << demonios[i].escudo.GetEscdefesa() << ", ";
                    cout << "Block: " << demonios[i].escudo.GetEscblock() << endl;
                }
            }
            else
                system ("clear");
                cout << "Nenhum membro da legião foi invocado " << endl << endl;


        }


        void ListarDraconatos(vector<Player>& draconatos)
        {
            if (draconatos.size() > 0 )

            {

                for(size_t i = 0; i < draconatos.size(); i++)
                {
                    cout << endl << "Nome: " << draconatos[i].lutador.Getname() << (draconatos[i].IsHero() ? " (H)" : "") << endl;

                    cout << "/-------------------Status -------------------/" << endl;

                    cout << "Vida: " << draconatos[i].lutador.Getlife() << ", ";
                    cout << "Ataque: " << draconatos[i].lutador.Getattack() << ", ";
                    cout << "Defesa: " << draconatos[i].lutador.Getdefense() << endl;

                    cout << "/-------------------Equipamento --------------/" << endl;

                    cout << "Arma: " << draconatos[i].arma.GetnomeArma() << ", ";
                    cout << "Dano: " << draconatos[i].arma.GetdanoArma() << ", ";
                    cout << "Velocidade: " << draconatos[i].arma.GetvelocidadeArma() << ", ";
                    cout << "Critico: " << draconatos[i].arma.GetcriticoArma() << endl;

                    cout << "Escudo: " << draconatos[i].escudo.GetEscnome() << ", ";
                    cout << "Defesa: " << draconatos[i].escudo.GetEscdefesa() << ", ";
                    cout << "Block: " << draconatos[i].escudo.GetEscblock() << endl;
                }
            }
            else
                system ("clear");
                cout << "Nenhum ovo de draconato foi chocado" << endl << endl;


        }






        void GerarHumanos(vector<string>& Mankind, vector<Player>& humanos)
        {
            for (int i = 0; i < names.size(); i++)
            {
                string nome = names[i];

                float life = rand() %51 + 50;
                float attack = rand() %11 + 10;
                float defense = rand() %16;
                float esquiva = rand() %29;

                string nomeArma = "Espada";
                float danoArma = rand() %25;
                float criticoArma = rand() %25;
                float velocidade = rand() %25;

                string Escnome = "Escudo";
                float Escblock = rand() %25;
                float Escdefesa = rand() %25;
                float Escvida = rand() %25;

                Mankind.push_back(nome);

                humanos.emplace_back(
                    nome, life, attack, defense,
                    nomeArma, danoArma, criticoArma,
                    esquiva, velocidade,
                    Escnome, Escblock, Escdefesa, Escvida, (rand() % 10 == 0)
                );
            }
        }


        void GerarOrcs(vector<string>& Horde, vector<Player>& orcs)
        {
            for (int i = 0; i < nomesorc.size(); i++)
            {
                string nome = nomesorc[i];

                float life = rand() %51 + 50;
                float attack = rand() %11 + 10;
                float defense = rand() %16;
                float esquiva = rand() %29;

                string nomeArma = "Espada";
                float danoArma = rand() %25;
                float criticoArma = rand() %25;
                float velocidade = rand() %25;

                string Escnome = "Escudo";
                float Escblock = rand() %25;
                float Escdefesa = rand() %25;
                float Escvida = rand() %25;

                Horde.push_back(nome);

                orcs.emplace_back(
                    nome, life, attack, defense,
                    nomeArma, danoArma, criticoArma,
                    esquiva, velocidade,
                    Escnome, Escblock, Escdefesa, Escvida, (rand() % 10 == 0)
                );
            }
        }

        void GerarElfos(vector<string>& Folk, vector<Player>& elfos)
        {
            for (int i = 0; i < nomeselfos.size(); i++)
            {
                string nome = nomeselfos[i];

                float life = rand() %51 + 50;
                float attack = rand() %11 + 10;
                float defense = rand() %16;
                float esquiva = rand() %29;

                string nomeArma = "Espada";
                float danoArma = rand() %25;
                float criticoArma = rand() %25;
                float velocidade = rand() %25;

                string Escnome = "Escudo";
                float Escblock = rand() %25;
                float Escdefesa = rand() %25;
                float Escvida = rand() %25;

                Folk.push_back(nome);

                elfos.emplace_back(
                    nome, life, attack, defense,
                    nomeArma, danoArma, criticoArma,
                    esquiva, velocidade,
                    Escnome, Escblock, Escdefesa, Escvida, (rand() % 10 == 0)
                );
            }
        }


        void GerarDemonios(vector<string>& Cult, vector<Player>& demonios)
        {
            for (int i = 0; i < nomesdemonios.size(); i++)
            {
                string nome = nomesdemonios[i];

                float life = rand() %51 + 50;
                float attack = rand() %11 + 10;
                float defense = rand() %16;
                float esquiva = rand() %29;

                string nomeArma = "Espada";
                float danoArma = rand() %25;
                float criticoArma = rand() %25;
                float velocidade = rand() %25;

                string Escnome = "Escudo";
                float Escblock = rand() %25;
                float Escdefesa = rand() %25;
                float Escvida = rand() %25;

                Cult.push_back(nome);

                demonios.emplace_back(
                    nome, life, attack, defense,
                    nomeArma, danoArma, criticoArma,
                    esquiva, velocidade,
                    Escnome, Escblock, Escdefesa, Escvida, (rand() % 10 == 0)
                );
            }
        }

        void GerarDraconatos(vector<string>& Folk, vector<Player>& draconatos)
        {
            for (int i = 0; i < nomesdraconatos.size(); i++)
            {
                string nome = nomesdraconatos[i];

                float life = rand() %51 + 50;
                float attack = rand() %11 + 10;
                float defense = rand() %16;
                float esquiva = rand() %29;
    
                string nomeArma = "Espada";
                float danoArma = rand() %25;
                float criticoArma = rand() %25;
                float velocidade = rand() %25;

                string Escnome = "Escudo";
                float Escblock = rand() %25;
                float Escdefesa = rand() %25;
                float Escvida = rand() %25;

                Clan.push_back(nome);

                draconatos.emplace_back(
                    nome, life, attack, defense,
                    nomeArma, danoArma, criticoArma,
                    esquiva, velocidade,
                    Escnome, Escblock, Escdefesa, Escvida, (rand() % 10 == 0)
                );
            }
        }





