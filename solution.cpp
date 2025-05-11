#include "solution.h"
#include "data.h"

#include <vector>
#include <iostream>

// Calcula custo da rota 
double Solution::calculateCost()
{
    Data &data = Data::getInstance();
    auto &t = data.matrizAdj;

    double custo = 0, verticeAtual = 0;

    for (int i = 1; i <= data.n; i++) // itera até último elemento
    {
        verticeAtual += t[route[i-1]][route[i]]; // calcula custo do vertice atual
        custo += verticeAtual; // guarda a soma do custo de todos os vérticees 
    }

    return custo;
}

// Printa a rota
void Solution::print()
{
    Data &data = Data::getInstance(); 

    for (int i = 0; i < data.n; i++) // itera até o penúltimo elemento
    {
        std::cout << route[i] << " - ";
    }
    std::cout << route[data.n] << '\n';

    std::cout << "Custo: " << calculateCost() << '\n';
}

