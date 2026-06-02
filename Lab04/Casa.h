#ifndef CASA_H
#define CASA_H

#include "Inmueble.h"
#include "./DataTypes/TipoTecho.h"

class Casa : public Inmueble {
private:
    bool propiedadHorizontal;
    TipoTecho techo;

public:
    Casa(const DtDireccion& direccion, float superficie, const DtFecha& anioConstruccion, const int numid, bool propiedadHorizontal, TipoTecho techo);

    bool getPropiedadHorizontal() ;
    TipoTecho getTecho() ;

    void setPropiedadHorizontal(bool propiedadHorizontal);
    void setTecho(TipoTecho techo);

    bool isPropiedadHorizontal() ;




};

#endif