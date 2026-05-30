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
    std::string superficie;
    DtFecha anioConstruccion;
    int numeroID;

public:
    Inmueble();
    Inmueble(const DtDireccion& direccion, const std::string& superficie,
             const DtFecha& anioConstruccion, int numeroID);

    DtDireccion getDireccion() const;
    std::string getSuperficie() const;
    DtFecha getAnioConstruccion() const;
    int getNumeroID() const;
};

#endif
