#include <iostream>
#include <vector>

using namespace std;

class Lutadores
{
private:
    //atributos

    string m_name;
    float m_life, m_attack, m_defense, m_esquiva;

public:
    //  construtor

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
    void SetAttack(float novoValor)
    {
        m_attack = novoValor;
    }
    void SetDefense(float novoValor)
    {
        m_defense = novoValor;
    }
};

class Armas
{

private:

    //atributos

    string m_nome;
    float m_dano, m_velocidade, m_critico;

public:

    //construtor

    Armas(string nomeArma, float danoArma, float velocidadeArma, float criticoArma)
    {
        m_nome = nomeArma;
        m_dano = danoArma;
        m_velocidade = velocidadeArma;
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

    //atributos

    string m_Escnome;
    float m_Escdefesa, m_Escblock, m_Escvida;
public:

    //construtor

    Escudos(string Escnome, float Escblock,float Escdefesa, float Escvida)
    {
        m_Escnome = Escnome;
        m_Escblock = Escblock;
        m_Escdefesa = Escdefesa;
        m_Escvida = Escvida;
    }

    //getter e setters

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

    //atributos

    bool m_isHero;
public:

    //construtor

    Armas arma;
    Lutadores lutador;
    Escudos escudo;

    Player(string nome, float life, float attack, float defense,string nomeArma, float danoArma,
    float criticoArma,float esquiva, float velocidadeArma, string Escnome , float Escblock, float Escdefesa,
    float Escvida, bool isHero = false)
    : arma(nomeArma, danoArma, criticoArma, velocidadeArma),
    lutador(nome, life, attack, defense, esquiva),
    escudo(Escnome, Escblock, Escdefesa, Escvida),
    m_isHero(isHero)
    {}

    //metodo

    bool IsHero() {
        return m_isHero;
    }
    bool Attack(vector<Player>& alvos, int indice)
    {
        if (indice < 0 || indice >= alvos.size())
            return false;

        Player& opponent = alvos[indice];

        if (lutador.Getattack() + arma.GetdanoArma() <= rand() % 15)
        {
            cout << "o jogador se esquivou" << endl;
            return false;
        }

        float dano = arma.GetdanoArma() + lutador.Getattack();

        if (rand() % 10 == 1)
        {
            cout << "tu critou!" << endl;
            dano *= 2;
        }
        else
        {
            dano -= opponent.lutador.Getdefense();
        }

        opponent.lutador.SetLife(opponent.lutador.Getlife() - dano);

        if(m_isHero && dano > 0 && (rand() % 3 == 0))
        {
            float vamp = dano*0.30f;
            lutador.SetLife(lutador.Getlife() + vamp);
            cout << " Blood, ohhh Blood +" << vamp << " life!";

        }
        return true;
    }
};

