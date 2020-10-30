//
//  ArvoreAVL.hpp
//  ArvoreAVL
//
//  Created by Felipe Israel on 27/10/20.
//

#ifndef ArvoreAVL_hpp
#define ArvoreAVL_hpp

#include <stdio.h>
#include "NoAVL.hpp"

class ArvoreAVL {
    
private:
    NoAVL* raiz;
    int h;
    bool balancear;
    
    int comparacoes;
    int tempoExecucao;
    
    bool auxBusca(NoAVL *p, int ch);
    NoAVL* auxInsert(NoAVL *p, int val);
    void auxPrint(NoAVL* p, int space);
    
    NoAVL* auxRemove(NoAVL *p, int x);
    NoAVL* removeFolha(NoAVL *p);
    NoAVL* remove1Filho(NoAVL *p);
    NoAVL* menorSubArvDireita(NoAVL *p);
    
    int auxAltura(NoAVL *p);
    
    void recalcularFatorBalanceamento(NoAVL *p);
    
public:
    ArvoreAVL(bool balancearArvore);
    ~ArvoreAVL();
    
    NoAVL* getRaiz();
    bool isEmpty();
    bool busca(int val);
    void insert(int val);
    void remove(int val);
    
    NoAVL* rotSimplesEsq(NoAVL *p);
    NoAVL* rotSimplesDir(NoAVL *p);
    NoAVL* rotDuplaEsq(NoAVL *p);
    NoAVL* rotDuplaDir(NoAVL *p);
    
    int getAltura();
    
    void print();
    
    int getComparacoes();
    int getTempoExecucao();
    
};

#endif /* ArvoreAVL_hpp */
