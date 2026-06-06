#ifndef ADMINISTRACION_H
#define ADMINISTRACION_H

#include <string>
#include <stdexcept>

//DataTypes
#include "./DataTypes/DtFecha.h"

//ICollection/interfaces
#include "./ICollection/interfaces/ICollectible.h"
#include "./ICollection/interfaces/ICollection.h"

class Inmueble;

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