#include <iostream>

using namespace std;

class Lutadores
{
private:

    string m_name;
    float m_life, m_attack, m_defense, m_esquiva;

public:

    Lutadores(string name, float life, float attack, float defense, float esquiva)
    {
        m_name = name;
        m_life=life;
        m_attack=attack;
        m_defense=defense;
        m_esquiva=esquiva;
    }

    //getters e setters
    string Getname()
    {
        return m_name;
    }
    float Getlife()
    {
        return m_life;
    }
    float Getattack()
    {
        return m_attack;
    }
    float Getdefense()
    {
        return m_defense;
    }
    float Getesquiva()
    {
        return m_esquiva;
    }
    float Setlife()
    {
        return m_life;
    }


    void SetLife(float novoValor)
            {

                 m_life = novoValor;
             }

};


 class Armas
 {
 private:
     string m_nome;
     float m_dano, m_velocidade, m_critico;

 public:
     Armas(string nomeArma, float danoArma, float criticoArma, float velocidade)
     {
         m_nome = nomeArma;
         m_dano = danoArma;
         m_velocidade = velocidade;
         m_critico = criticoArma;
    }

    //getters e setters
     string GetnomeArma()
    {
        return m_nome;
    }
    float GetdanoArma()
    {
        return m_dano;
    }
     float GetvelocidadeArma()
    {
        return m_velocidade;
    }
    float GetcriticoArma()
    {
        return m_critico;
    }

 };

 class Escudos
 {
 private:
     string m_Escnome;
     float m_Escdefesa, m_Escblock, m_Escvida;
 public:
     Escudos(string Escnome, float Escblock,float Escdefesa, float Escvida)
     {
         m_Escnome = Escnome;
         m_Escblock = Escblock;
         m_Escdefesa = Escdefesa;
         m_Escvida = Escvida;
    }


     string GetEscnome()
     {
         return m_Escnome;
     }


     float GetEscblock()
     {
         return m_Escblock;
     }
    float GetEscvida()
{
    return m_Escvida;
}

     float GetEscdefesa()
     {
         return m_Escdefesa;
     }

};


 class Player
 {

 private:

 public:
     Armas arma;
     Lutadores lutador;
     Escudos escudo;

     Player(string nome, float life, float attack, float defense,string nomeArma, float danoArma, float criticoArma,float esquiva, float velocidadeArma, string Escnome , float Escblock, float Escdefesa, float Escvida)
     : arma(nomeArma, danoArma, criticoArma, velocidadeArma),
       lutador(nome, life, attack, defense, esquiva),
       escudo(Escnome, Escblock, Escdefesa, Escvida)
     {}




      bool Attack(Player &opponent)
     {
         //PREMISSA 1: CONSEGUIR Passar pela esquiva :)

         float esquiva = opponent.lutador.Getesquiva();
         esquiva=rand()%15;

         if((lutador.Getattack() + arma.GetdanoArma()) > esquiva)
         {
             //PREMISSA 2: Rolar um crit :)

             float novoValorLife;
             float critico = arma.GetcriticoArma();
             critico=rand()%10;
             float AcertoCritico =1;



             if(critico == AcertoCritico)
             {
                 cout <<"tu critou!" << endl;
                 novoValorLife = opponent.lutador.Getlife() - (2*(arma.GetdanoArma() + lutador.Getattack())); //se o crit hitar o dano vira x2
                 opponent.lutador.SetLife(novoValorLife);
                 return true;
             }
             else
             {
             novoValorLife = opponent.lutador.Getlife() - ((arma.GetdanoArma() + lutador.Getattack())-opponent.lutador.Getdefense());
             opponent.lutador.SetLife(novoValorLife);
             return true;
             }
         }
         else
             cout << "o jogador se esquivou " << endl;

             return false;

     }

 };






