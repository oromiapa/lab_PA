#ifndef DTINMXPROP_H
#define DTINMXPROP_H

//DataTypes internos empaquetados
#include "DtDireccion.h"
#include "DtPropietario.h"

#include "../ICollection/interfaces/ICollectible.h"


class DtInmXProp : public ICollectible {

private:
    int numid;
    DtDireccion direccion;
    DtPropietario propietariovinculado;

public:
//Constructor y Destructor
    DtInmXProp(int id, const DtDireccion &dir, const DtPropietario &prop);
    virtual ~DtInmXProp();

//Gets
    int getNumId() const ;
    DtDireccion getDireccion() const ;
    DtPropietario getPropietariovinculado() const ;

};


#endif