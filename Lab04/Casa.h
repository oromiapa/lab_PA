#ifndef CASA_H
#define CASA_H

#include "Inmueble.h"
#include "./DataTypes/TipoTecho.h"

class Casa : public Inmueble {
private:
    bool propiedadHorizontal;
    TipoTecho techo;

public:
    Casa();
    Casa(const DtDireccion& direccion, const float superficie, const DtFecha& anioConstruccion, int numeroID, bool propiedadHorizontal, TipoTecho techo);

    bool isPropiedadHorizontal() const;
    TipoTecho getTecho() const;    
};

#endif