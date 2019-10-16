#include <iostream>
#include <random>
#include <chrono>
#include <cmath>

using std::cout; using rdist = std::uniform_real_distribution<>; 
using idist = std::uniform_int_distribution<>; using std::mt19937;
using std::random_device;

struct instancia
{
    int estado[40];

    int &operator [] (int i) {return estado[i];}

    int n_rainhas_atacando() 
    {
        int ataques = 0;

        for (int i = 0; i < 40; i++)
        {
            int j = 1;
            while (i + j < 40 && estado[i+j] != (estado[i]))
            {
                j++;
            }

            if (i+j < 40) ataques++;
        }

        for (int i = 0; i < 40; i++)
        {
            int j = 1;
            while (i + j < 40 && estado[i+j] != (estado[i]+j))
            {
                j++;
            }

            if (i+j < 40) ataques++;
        }

        return ataques;
    }
};

instancia viz_aleatorio(instancia &a)
{
    instancia novo = a;
    random_device rd;
    mt19937 gerador (rd());
    idist distr(0,39);

    novo[distr(gerador)] = distr(gerador);
    return novo;
}

instancia instancia_aleatoria()
{
    instancia nova;
    random_device rd;
    mt19937 gerador (rd());
    idist distr(0,39);

    for (int i = 0; i < 40; i++)
    {
        nova[i] = distr(gerador);
    }

    return nova;
}

instancia simmulated_annealing(instancia &estado_inicial, float c, int iteracoes)
{
    instancia atual = estado_inicial;
    random_device rd;
    mt19937 gerador(rd());
    rdist distr(0.0, 1.0);

    for (int i = 0; i < iteracoes; i++)
    {
        float t = c/sqrt(i);
        instancia viz = viz_aleatorio(atual);

        if (viz.n_rainhas_atacando() < atual.n_rainhas_atacando()) 
        {
            atual = viz;
        }
        else 
        {
            double prob = exp((atual.n_rainhas_atacando()-viz.n_rainhas_atacando())/t);
            double randf = distr(gerador);

            if (randf < prob) 
            {
                atual = viz;
            }
        }
    } 

    return atual;
}

int main() {
    instancia novo = instancia_aleatoria();


    

    for (int i = 0; i<40; i++)
    {
        cout<<novo[i]<<'\n';
    }
}