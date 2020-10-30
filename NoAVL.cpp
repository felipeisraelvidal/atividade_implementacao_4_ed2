//
//  NoAVL.cpp
//  ArvoreAVL
//
//  Created by Felipe Israel on 27/10/20.
//

#include "NoAVL.hpp"

NoAVL* NoAVL::getEsq() {
    return this->esq;
}

void NoAVL::setInfo(int val) {
    this->info = val;
}

NoAVL* NoAVL::getDir() {
    return this->dir;
}

void NoAVL::setEsq(NoAVL *p) {
    this->esq = p;
}

int NoAVL::getInfo() {
    return info;
}

void NoAVL::setDir(NoAVL *p) {
    this->dir = p;
}

void NoAVL::setFatorBalanceamento(int fb) {
    this->fatorBalanceamento = fb;
}

int NoAVL::getFatorBalanceamento() {
    return this->fatorBalanceamento;
}
