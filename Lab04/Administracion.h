#ifndef ADMINISTRACION_H
#define ADMINISTRACION_H

#include "Inmobiliaria.h"
#include "Publicacion.h"
#include "Inmueble.h"
#include "./DataTypes/DtFecha.h"
#include "./ICollection/interfaces/ICollectible.h"


class Administracion : public ICollectible {

private:
    DtFecha fechainicio;
    Inmueble* inmuebleAdministrado;

public:
    Administracion();
    Administracion(const DtFecha& fechainicio , Inmueble* inmueble);
    virtual ~Administracion();

    DtFecha getFechaInicio() const;
    Inmueble* getInmueble() const;

    void setFechaInicio(const DtFecha& fechainicio) ;
    void setInmueble(Inmueble* inmueble);
    

};

#endif