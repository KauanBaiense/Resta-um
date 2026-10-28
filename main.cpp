#include "player.hpp"
#include "nomes.hpp"


int main()
{

    srand(time(0));


        //CRIANDO UM PLAYER

        vector<Player> jogador;
        for (size_t i=0; i<armas.size(); i++) //armas tem que ser maior q nomes ^^
        {

            float life=rand()%100;
            float attack=rand()%10;
            float defense=rand()%2;
            float dano=rand()%5;
            float critico;
            float esquiva;
            float velocidade;

            Player novoJogador(names[i], life, attack, defense,armas[i], dano,critico, esquiva,velocidade);
            jogador.push_back(novoJogador);

        }


    //IMPRIMIR TODOS OS LUTADORES E ARMAS
    for(size_t i=0; i<jogador.size(); i++)
    {
        cout << "Nome: " << jogador[i].lutador.Getname() << endl;
        cout << "Vida: " << jogador[i].lutador.Getlife() << endl;
        cout << "ataque: "<< jogador[i].lutador.Getattack() << endl;
        cout << "defesa: " <<jogador[i].lutador.Getdefense() << endl;
        cout << "Arma: " << jogador[i].arma.Getnome() << endl;
        cout << "dano: " << jogador[i].arma.Getdano() << endl;

        // if (jogador[i].arma.Getcritico() == 1)
        // {
        //     cout << jogador[i].arma.Getnome() << " possui critico";
        // }
        // else
        //     cout << jogador[i].arma.Getnome() << " não possui critico" << endl;
        // cout << "chance de critico: " << jogador[i].arma.Getcritico() << endl;
        //cout << "velocidade: " <<jogador[i].arma.Getvelocidade() << endl;

    }

    while(jogador.size() > 1)
            {



                size_t i=rand()%jogador.size();
                size_t j=rand()%jogador.size();

                if(i==j) continue;

                cout << "Lutador " << jogador[i].lutador.Getname() << " atacando " <<  jogador[j].lutador.Getname() << "....";
                bool status = jogador[i].Attack(jogador[j]);

                if(status == true)
                {

                    cout << "ataque bem sucedido" << endl;



                    if(jogador[j].lutador.Getlife()<=0)
                    {
                        cout << " Dead: " << jogador[j].lutador.Getname() << endl ;
                        jogador.erase(jogador.begin()+j);
                    }
                }
                else


                    cout << "vida restante: " <<jogador[j].lutador.Getlife() << endl;
            }

            //temos um vencedor
            cout << "WINNER: " << jogador[0].lutador.Getname() << endl;

            return 0;
        }

