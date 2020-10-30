//
//  NoAVL.hpp
//  ArvoreAVL
//
//  Created by Felipe Israel on 27/10/20.
//

#ifndef NoAVL_hpp
#define NoAVL_hpp

#include <stdio.h>

class NoAVL {
    
private:
    NoAVL* pai;
    NoAVL* esq;
    NoAVL* dir;
    int info;
    int fatorBalanceamento;
    
public:
    int getInfo();
    void setInfo(int val);
    
    NoAVL* getEsq();
    void setEsq(NoAVL *p);
    
    NoAVL* getDir();
    void setDir(NoAVL *p);
    
    void setFatorBalanceamento(int fb);
    int getFatorBalanceamento();
    
};

#endif /* NoAVL_hpp */
