#include "solution.h"
#include "data.h"
#include "construction.h"
#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <cmath>

std::vector<int> initialSubTour(Solution &s);
std::vector<insertionInfo> calculateCost(int r, std::vector<int> &CL);

Solution Construction()
{
    Data &data = Data::getInstance();

    Solution s;
    s.route = {1, 1};

    // inicia CL  
    std::vector<int> CL;
    for (int i = 2; i <= data.n; i++)
    {
        CL.push_back(i);
    }

    int r = 1;
    while (!CL.empty())
    {
        // calculando array de custos
        std::vector<insertionInfo> costsCandidates =  calculateCost(r, CL);

        // ordenando array 
        std::sort(costsCandidates.begin(), costsCandidates.end(), 
                    [](insertionInfo &a, insertionInfo &b){
                        return a.cost < b.cost;
                    });

        // indice aleatorio
        double alpha = 0.5;
        int i = rand() % ((int) ceil(alpha * costsCandidates.size()));

        // valor escolhido
        int r = costsCandidates[i].k;

        // insere o valor escolhido
        s.route.insert(s.route.end() - 1, r);

        // remove o indice escolhido de CL
        auto itRemove = std::find(CL.begin(), CL.end(), r);
        CL.erase(itRemove);
    }
    s.cost = s.calculateCost();

    return s;
}

// Calcula todos os custos de inserção
std::vector<insertionInfo> calculateCost(int r, std::vector<int> &CL)
{
    Data &data = Data::getInstance();
    auto &t = data.matrizAdj;
    std::vector<insertionInfo> infoCosts(CL.size());

    // Calcula as possibilidades de inserção de CL no último elemento
    int l = 0;
    for (auto &node: CL)
    {
        infoCosts[l].k = node;
        infoCosts[l].cost = t[r][node]; // calcula custo de 'node' adicionado
        l++;
    }
    
    return infoCosts;
}