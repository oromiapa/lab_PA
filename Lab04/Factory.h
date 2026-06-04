#ifndef FACTORY_H
#define FACTORY_H

#include "ISistema.h"

class Factory {
private:
    static Factory* instancia; 
    ISistema* sys;
    Factory();                 
public:
    static Factory* getInstancia(); 
    ISistema* getSistema();         
};

#endif