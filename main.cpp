//
//  main.cpp
//  ArvoreAVL
//
//  Created by Felipe Israel on 27/10/20.
//

#include <iostream>
#include "ArvoreAVL.hpp"
#include <chrono>

using namespace std;
using namespace chrono;

int myrandom (int i) {
    return rand() % i;
}

void start(bool ordenado, int *array, int n, int m) {
    
    if (!ordenado) {
        // desoordenar o array
        random_shuffle(array, array + n, myrandom);
        
        cout << "Iniciando os testes com um array aleatório..." << endl << endl;
    } else {
        cout << "Iniciando os testes com um array ordenado..." << endl << endl;
    }
    
    ArvoreAVL abb(false);
    ArvoreAVL avl(true);
    
    for (int i = 0; i < n; i++) {
        abb.insert(array[i]);
        avl.insert(array[i]);
    }
    
    // Gerar array de busca
    int* searchArray = (int*)malloc(m * sizeof(int));
    int number;
    for (int i = 0; i < m; i++) {
        number = rand() % (n - 0 + 1);
        searchArray[i] = number;
    }
    
    time_point<system_clock> inicioTimeABB, fimTimeABB;
    
    inicioTimeABB = system_clock::now();
    
    // Busca na abb
    for (int i = 0; i < m; i++) {
        abb.busca(searchArray[i]);
    }
    
    fimTimeABB = system_clock::now();
    long secondsTimeABB = duration_cast<milliseconds>(fimTimeABB - inicioTimeABB).count();
    
    cout << "Relatório Árvore Binária de Busca:" << endl;
    cout << "Comparação de chaves: " << abb.getComparacoes() << endl;
    cout << "Altura: " << abb.getAltura() << endl;
    cout << "Tempo de execução: " << secondsTimeABB << "ms" << endl;
    
    cout << endl;
    
    
    time_point<system_clock> inicioTimeAVL, fimTimeAVL;
    
    inicioTimeAVL = system_clock::now();
    
    // Busca na avl
    for (int i = 0; i < m; i++) {
        avl.busca(searchArray[i]);
    }
    
    fimTimeAVL = system_clock::now();
    long secondsTimeAVL = duration_cast<milliseconds>(fimTimeAVL - inicioTimeAVL).count();
    
    cout << "Relatório Árvore AVL:" << endl;
    cout << "Comparação de chaves: " << avl.getComparacoes() << endl;
    cout << "Altura: " << avl.getAltura() << endl;
    cout << "Tempo de execução: " << secondsTimeAVL << "ms" << endl;
    
//    abb.print();
//    avl.print();
    
    cout << endl;
}

int main(int argc, const char * argv[]) {
    
    srand((unsigned) time(NULL));
    
    int n = 1000;
    int* array = (int*)malloc(n * sizeof(int));
    
    // Popular array
    for (int i = 0; i < n; i++) {
        array[i] = i;
    }
    
    start(true, array, n, 1500); // executa com o array ordenado
    start(false, array, n, 1500); // executa com o array aleatório
    
    return 0;
}
