#ifndef DTINMUEBLE_H
#define DTINMUEBLE_H

#include <string>
#include "DtDireccion.h"
#include "DtFecha.h"
#include "DtPropietario.h"

class DtInmueble {
private:
    int codigoID;
    DtDireccion direccion;
    float superficie;
    DtFecha anioConstruccion;
    DtPropietario propietario;

public:
    // Constructores
    DtInmueble();
    DtInmueble(int codigoID, const DtDireccion& direccion,
               float superficie, const DtFecha& anioConstruccion,
               const DtPropietario& propietario);

    // Getters según UML
    int getCodigoID() const;
    DtDireccion getDireccion() const;
    float getSuperficie() const;
    DtFecha getAnioConstruccion() const;
    DtPropietario getPropietario() const;
};

#endif
