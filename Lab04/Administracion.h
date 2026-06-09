#ifndef ADMINISTRACION_H
#define ADMINISTRACION_H

#include <string>
#include <stdexcept>

//DataTypes
#include "./DataTypes/DtFecha.h"
#include "./DataTypes/TipoInmueble.h"
#include "./DataTypes/DtPublicacion.h"
#include "./DataTypes/DtInmueble.h"

//ICollection/interfaces
#include "./ICollection/interfaces/ICollectible.h"
#include "./ICollection/interfaces/ICollection.h"

class Inmueble;
class Publicacion;
class Inmobiliaria;

class Administracion : public ICollectible {

private:
    DtFecha fechainicio;
    Inmueble* inmuebleAdministrado;
    ICollection* publicaciones;
    Inmobiliaria* InmobiliariaAsociada;

public:
//Constructor y Destructor
    Administracion();
    Administracion(const DtFecha& fechainicio , Inmueble* inmueble);
    virtual ~Administracion();

//Gets
    DtFecha getFechaInicio() const;
    Inmueble* getInmueble() const;
    Inmobiliaria* getInmobiliaria() const;
    DtFecha obtenerFecha() const;

//Sets
    void setFechaInicio(const DtFecha& fechainicio) ;
    void setInmueble(Inmueble* inmueble);

//3er Caso
    void altaPublicacion(const int numid , const char* text , float price , bool tipopub) ;

//4to Caso
    void borrarPublicacion() ;
    void desvincularInmueble(int numid) ;

//5to Caso
    ICollection* filtrarPublicaciones(bool tipopub , float preciomin , float preciomax , TipoInmueble tipo) ;
    DtInmueble* seleccionarPublicacion(int id);

//Caso especial
    Publicacion* getPublicacion(int id);
    
};

#endif