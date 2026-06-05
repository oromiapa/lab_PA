#ifndef DTINMXPROP_H
#define DTINMXPROP_H

#include "DtDireccion.h"
#include "DtPropietario.h"
#include "../ICollection/interfaces/ICollectible.h" 


class DtInmXProp : public ICollectible {

private:
    int numid;
    DtDireccion direccion;
    DtPropietario propietariovinculado;

public:

    DtInmXProp(int id, const DtDireccion &dir, const DtPropietario &prop);
    virtual ~DtInmXProp();

    int getNumId() const ;
    DtDireccion getDireccion() const ;
    DtPropietario getPropietariovinculado() const ;

};


#endif