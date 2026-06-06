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
class Publicacion;

class Administracion : public ICollectible {

private:
    DtFecha fechainicio;
    Inmueble* inmuebleAdministrado;
    ICollection* publicaciones;

public:
//Constructor y Destructor
    Administracion();
    Administracion(const DtFecha& fechainicio , Inmueble* inmueble);
    virtual ~Administracion();

//Gets
    DtFecha getFechaInicio() const;
    Inmueble* getInmueble() const;

//Sets
    void setFechaInicio(const DtFecha& fechainicio) ;
    void setInmueble(Inmueble* inmueble);

//3er Caso
    void altaPublicacion(const int numid , const char* text , float price , bool tipopub) ;

    

};

#endif