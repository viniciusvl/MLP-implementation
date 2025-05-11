#include "data.h"
#include "solution.h"
#include "construction.h"
#include <time.h>
#include <iostream>

int main(){
    char *argv[2]; // cria array de ponteiros para strings

    argv[0] = (char *) "TSP";
    argv[1] = (char *) "instancias/burma14.tsp"; 
    srand(time(NULL));

    Data &data = Data::getInstance();
    data.read(2, argv); // lê e salva as instâncias

    Solution s = Construction();
    s.print();
    
}