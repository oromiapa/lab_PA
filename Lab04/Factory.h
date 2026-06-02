#ifndef FACTORY_H
#define FACTORY_H

#include "ISistema.h"

class Factory {
private:
    static Factory* instancia; // Atributo para el Singleton [4]
    Factory();                 // Constructor privado [4]
public:
    static Factory* getInstancia(); // Método para obtener la fábrica única [4]
    ISistema* getSistema();         // Método de fábrica (ya no es static) [9]
};

#endif