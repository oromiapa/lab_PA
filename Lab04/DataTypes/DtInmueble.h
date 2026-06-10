#ifndef DTINMUEBLE_H
#define DTINMUEBLE_H

#include <string>
#include <stdexcept>

//DataTypes
#include "DtDireccion.h"
#include "DtFecha.h"

#include "../ICollection/interfaces/ICollectible.h"


class DtInmueble : public ICollectible {

private:
    int numid;
    DtDireccion direccion;
    float superficie;
    DtFecha anioConstruccion;

public:
    DtInmueble(int id, const DtDireccion &dir, float sup, const DtFecha &fecha);
    virtual ~DtInmueble();

    int getNumId() const ;
    DtDireccion getDireccion() const ;
    float getSuperficie() const ;
    DtFecha getAnioConstruccion() const ;
    

};

#endif
