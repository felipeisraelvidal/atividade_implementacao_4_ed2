//
//  ArvoreAVL.cpp
//  ArvoreAVL
//
//  Created by Felipe Israel on 27/10/20.
//

#include <iostream>
#include "ArvoreAVL.hpp"

using namespace std;

#define COUNT 10

ArvoreAVL::ArvoreAVL(bool balancearArvore) {
    this->raiz = NULL;
    this->h = 0;
    this->balancear = balancearArvore;
    this->comparacoes = 0;
    this->tempoExecucao = 0;
}

ArvoreAVL::~ArvoreAVL() {
    
}

NoAVL* ArvoreAVL::getRaiz() {
    return this->raiz;
}

bool ArvoreAVL::isEmpty() {
    return this->raiz == NULL;
}

bool ArvoreAVL::auxBusca(NoAVL *p, int ch) {
    if (p == NULL) {
        return false; // ávore vazia;
    } else if (p->getInfo() == ch) {
        comparacoes++;
        return true; // chave encontrada
    } else if (auxBusca(p->getEsq(), ch)) {
        return true;
    } else {
        return auxBusca(p->getDir(), ch);
    }
}

bool ArvoreAVL::busca(int val) {
    return auxBusca(raiz, val);
}

int ArvoreAVL::auxAltura(NoAVL *p) {
    int he, hd;
    if (p == NULL) {
        return -1;
    } else {
        he = auxAltura(p->getEsq());
        hd = auxAltura(p->getDir());
        return 1 + (he > hd ? he : hd);
    }
}

NoAVL* ArvoreAVL::auxInsert(NoAVL *p, int val) {
    if (p == NULL) {
        p = new NoAVL();
        p->setInfo(val);
        p->setEsq(NULL);
        p->setDir(NULL);
    } else if (val < p->getInfo()) {
        NoAVL *q = auxInsert(p->getEsq(), val);
        p->setEsq(q);
        comparacoes++;
    } else {
        NoAVL *q = auxInsert(p->getDir(), val);
        p->setDir(q);
        comparacoes++;
    }
    
    if (balancear) {
        recalcularFatorBalanceamento(p);
        
        if (p->getFatorBalanceamento() == -2 || p->getFatorBalanceamento() == +2) {
            // Precisa rebalancear
            int he = auxAltura(p->getEsq());
            int hd = auxAltura(p->getDir());
            
            NoAVL *q;
            if (he > hd) {
                q = p->getEsq();
            } else {
                q = p->getDir();
            }
            
            if (p->getFatorBalanceamento() == 2 && (q->getFatorBalanceamento() == 1 || q->getFatorBalanceamento() == 0)) {
                // Rotação simples à esquerda
                p = rotSimplesEsq(p);
            } else if (p->getFatorBalanceamento() == -2 && (q->getFatorBalanceamento() == -1 || q->getFatorBalanceamento() == 0)) {
                // Rotação simples à direita
                p = rotSimplesDir(p);
            } else if (p->getFatorBalanceamento() == 2 && q->getFatorBalanceamento() == -1) {
                // Rotação dupla à esquerda
                p = rotDuplaEsq(p);
            } else if (p->getFatorBalanceamento() == -2 && q->getFatorBalanceamento() == 1) {
                // Rotação dupla à direita
                p = rotDuplaDir(p);
            }
        }
    }
    
    return p;
}

void ArvoreAVL::recalcularFatorBalanceamento(NoAVL *p) {
    int he = auxAltura(p->getEsq());
    int hd = auxAltura(p->getDir());
    p->setFatorBalanceamento(hd - he);
}

void ArvoreAVL::insert(int val) {
    raiz = auxInsert(raiz, val);
}

void ArvoreAVL::auxPrint(NoAVL *p, int space) {
    if (p == NULL) {
        return;
    }
    
    space += COUNT;
    
    auxPrint(p->getDir(), space);
    
    cout << endl;
    for (int i = COUNT; i < space; i++) {
        cout << " ";
    }
    cout << p->getInfo() << "(" << p->getFatorBalanceamento() << ")" << endl;
    
    auxPrint(p->getEsq(), space);
}

void ArvoreAVL::print() {
    auxPrint(raiz, 0);
}

NoAVL* ArvoreAVL::removeFolha(NoAVL *p) {
    delete p;
    return NULL;
}

NoAVL* ArvoreAVL::remove1Filho(NoAVL *p) {
    NoAVL *aux;
    if (p->getEsq() == NULL) {
        aux = p->getDir();
    } else {
        aux = p->getEsq();
    }
    delete p;
    return aux;
}

NoAVL* ArvoreAVL::menorSubArvDireita(NoAVL *p) {
    NoAVL *aux = p->getDir();
    while (aux->getEsq() != NULL) {
        aux = aux->getEsq();
    }
    return aux;
}

NoAVL* ArvoreAVL::auxRemove(NoAVL *p, int x) {
    if (p == NULL) {
        return NULL;
    } else if (x < p->getInfo()) {
        comparacoes++;
        p->setEsq(auxRemove(p->getEsq(), x));
    } else if (x > p->getInfo()) {
        comparacoes++;
        p->setDir(auxRemove(p->getDir(), x));
    } else {
        if ((p->getEsq() == NULL) && (p->getDir() == NULL)) {
            p = removeFolha(p);
        } else if ((p->getEsq() == NULL) || (p->getDir() == NULL)) {
            p = remove1Filho(p);
        } else {
            NoAVL *aux = menorSubArvDireita(p);
            
            int auxInt = aux->getInfo();
            p->setInfo(auxInt);
            aux->setInfo(x);
            
            p->setDir(auxRemove(p->getDir(), x));
        }
    }
    
    if (balancear && p != NULL) {
        recalcularFatorBalanceamento(p);
        
        if (p->getFatorBalanceamento() == -2 || p->getFatorBalanceamento() == +2) {
            // Precisa rebalancear
            int he = auxAltura(p->getEsq());
            int hd = auxAltura(p->getDir());
            
            NoAVL *q;
            if (he > hd) {
                q = p->getEsq();
            } else {
                q = p->getDir();
            }
            
            if (p->getFatorBalanceamento() == 2 && (q->getFatorBalanceamento() == 1 || q->getFatorBalanceamento() == 0)) {
                // Rotação simples à esquerda
                cout << "Rotação simples à esquerda" << endl;
                p = rotSimplesEsq(p);
            } else if (p->getFatorBalanceamento() == -2 && (q->getFatorBalanceamento() == -1 || q->getFatorBalanceamento() == 0)) {
                // Rotação simples à direita
                cout << "Rotação simples à direita" << endl;
                p = rotSimplesDir(p);
            } else if (p->getFatorBalanceamento() == 2 && q->getFatorBalanceamento() == -1) {
                // Rotação dupla à esquerda
                cout << "Rotação dupla à esquerda" << endl;
                p = rotDuplaEsq(p);
            } else if (p->getFatorBalanceamento() == -2 && q->getFatorBalanceamento() == 1) {
                // Rotação dupla à direita
                cout << "Rotação dupla à direita" << endl;
                p = rotDuplaDir(p);
            }
        }
    }
    
    return p;
}

NoAVL* ArvoreAVL::rotSimplesEsq(NoAVL* p) {
    NoAVL *q = p->getDir();
    p->setDir(q->getEsq());
    q->setEsq(p);
    recalcularFatorBalanceamento(p);
    recalcularFatorBalanceamento(q);
    return q;
}

NoAVL* ArvoreAVL::rotSimplesDir(NoAVL *p) {
    NoAVL *q = p->getEsq();
    p->setEsq(q->getDir());
    q->setDir(p);
    recalcularFatorBalanceamento(p);
    recalcularFatorBalanceamento(q);
    return q;
}

NoAVL* ArvoreAVL::rotDuplaEsq(NoAVL *p) {
    NoAVL *q = p->getDir();
    NoAVL *r = q->getEsq();
    p->setDir(r->getEsq());
    q->setEsq(r->getDir());
    r->setEsq(p);
    r->setDir(q);
    
    recalcularFatorBalanceamento(p);
    recalcularFatorBalanceamento(q);
    recalcularFatorBalanceamento(r);
    
    return r;
}

NoAVL* ArvoreAVL::rotDuplaDir(NoAVL *p) {
    NoAVL *q = p->getEsq();
    NoAVL *r = q->getDir();
    p->setEsq(r->getDir());
    q->setDir(r->getEsq());
    r->setEsq(p);
    r->setDir(q);
    
    recalcularFatorBalanceamento(p);
    recalcularFatorBalanceamento(q);
    recalcularFatorBalanceamento(r);
    
    return r;
}

void ArvoreAVL::remove(int val) {
    raiz = auxRemove(raiz, val);
}

int ArvoreAVL::getAltura() {
    return auxAltura(raiz);
}

int ArvoreAVL::getComparacoes() {
    return this->comparacoes;
}

int ArvoreAVL::getTempoExecucao() {
    return this->tempoExecucao;
}
