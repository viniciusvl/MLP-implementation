#include "solution.h"
#include "data.h"
#include "construction.h"
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <cmath>

std::vector<int> initialSubTour(Solution &s);
std::vector<insertionInfo> calculateCost(Solution &s, std::vector<int> &CL);

Solution Construction()
{
    Data &data = Data::getInstance();

    Solution s;
    s.route = {1, 1};

    // inicia CL  
    std::vector<int> CL = initialSubTour(s);

    while (!CL.empty())
    {
        std::vector<insertionInfo> costsCandidates =  calculateCost(s, CL);
        std::sort(costsCandidates.begin(), costsCandidates.end(), 
                    [](insertionInfo &a, insertionInfo &b){
                        return a.cost < b.cost;
                    });

        // indice aleatorio
        double alpha = 0.5;
        int i = rand() % ((int) ceil(alpha * costsCandidates.size()));

        // insere o valor escolhido
        s.route.insert(s.route.end() - 1, costsCandidates[i].k);

        // remove o indice escolhido de CL
        auto itRemove = std::find(CL.begin(), CL.end(), costsCandidates[i].k);
        CL.erase(itRemove);
    }
    s.cost = s.calculateCost();

    return s;
}

// Constroi o subtour inicial
std::vector<int> initialSubTour(Solution &s)
{
    std::vector<int> CL;
    Data &data = Data::getInstance();
    
    // inicializa todos os candidatos
    for (int i = 2; i <= data.n; i++)
    {
        CL.push_back(i);
    }
    
    // quantidade de nós a adicionar em s 
    int  nodes = 3;    
    while (nodes--) 
    {
        // seleciona indice aleatorio 
        int index = rand() % CL.size(); 

        // insere na rota
        s.route.insert(s.route.end() - 1, CL[index]);

        // exclui de CL
        CL.erase(CL.begin() + index);
    }

    return CL;
}

// Calcula todos os custos de inserção
std::vector<insertionInfo> calculateCost(Solution &s, std::vector<int> &CL)
{
    Data &data = Data::getInstance();
    auto &t = data.matrizAdj;

    std::vector<insertionInfo> infoCosts(CL.size());

    int sizeRoute = s.route.size();

    // Calcula as possibilidades de inserção de CL no último elemento
    int l = 0;
    int lastRoute = sizeRoute - 2;
    for (auto &node: CL)
    {
        infoCosts[l].k = node;
        infoCosts[l].cost = t[node][lastRoute]; // calcula custo de 'node' adicionado
        l++;
    }
    
    return infoCosts;
}