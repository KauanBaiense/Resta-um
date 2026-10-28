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
     Armas(string nome, float dano, float critico, float velocidade)
     {
         m_nome = nome;
         m_dano = dano;
         m_velocidade = velocidade;
         m_critico = critico;
    }

    //getters e setters
     string Getnome()
    {
        return m_nome;
    }
    float Getdano()
    {
        return m_dano;
    }
     float Getvelocidade()
    {
        return m_velocidade;
    }
    float Getcritico()
    {
        return m_critico;
    }

 };
 class Player
 {

 private:



 public:
     Armas arma;
     Lutadores lutador;

     Player(string nome, float life, float attack, float defense,string nomeArma, float dano, float critico, float velocidade, float esquiva)
     : arma(nomeArma, dano, critico, velocidade),
       lutador(nome, life, attack, defense, esquiva)
     {
    }




      bool Attack(Player &opponent)
     {
         //PREMISSA 1: CONSEGUIR Passar pela esquiva :)

         float esquiva = opponent.lutador.Getesquiva();
         esquiva=rand()%15;

         if((lutador.Getattack() + arma.Getdano()) > esquiva)
         {
             //PREMISSA 2: Rolar um crit :)

             float novoValorLife;
             float critico = arma.Getcritico();
             critico=rand()%10;
             float AcertoCritico =1;



             if(critico == AcertoCritico)
             {
                 cout <<"tu critou!" << endl;
                 novoValorLife = opponent.lutador.Getlife() - (2*(arma.Getdano() + lutador.Getattack())); //se o crit hitar o dano vira x2
                 opponent.lutador.SetLife(novoValorLife);
                 return true;
             }
             else
             {
             novoValorLife = opponent.lutador.Getlife() - ((arma.Getdano() + lutador.Getattack())-opponent.lutador.Getdefense());
             opponent.lutador.SetLife(novoValorLife);
             return true;
             }
         }
         else
             cout << "o jogador se esquivou " << endl;

             return false;

     }

 };







