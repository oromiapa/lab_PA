#ifndef INMUEBLE_H
#define INMUEBLE_H

#include "Propietario.h"
#include "DataTypes/DtDireccion.h"
#include "DataTypes/DtFecha.h"
#include <string>
#include <memory>

class Inmueble {
private:
    DtDireccion direccion;
    float superficie;
    DtFecha anioConstruccion;
    int numeroID;

public:
    Inmueble();
    Inmueble(const DtDireccion& direccion, const float & superficie,
             const DtFecha& anioConstruccion, int numeroID);
    
    DtDireccion getDireccion();
    float getSuperficie();
    DtFecha getAnioConstruccion();
    int getNumeroID();
    
};

#endif
