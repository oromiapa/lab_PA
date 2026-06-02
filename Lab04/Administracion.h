#ifndef ADMINISTRACION_H
#define ADMINISTRACION_H

#include "Inmobiliaria.h"
#include "Publicacion.h"

class Administracion {

private:
    DtFecha fechainicio;

public:
    Administracion();
    Administracion(const DtFecha& fechainicio);

    DtFecha getFechaInicio() ;

    void setFechaInicio(const DtFecha& fechainicio) ;

    

};

#endif