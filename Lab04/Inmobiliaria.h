#ifndef INMOBILIARIA_H
#define INMOBILIARIA_H

//Clases
#include "Usuario.h"

//DataTypes
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"
#include "./DataTypes/DtInmobiliaria.h"

//ICollection/interfaces
#include "./ICollection/interfaces/IDictionary.h"
#include "./ICollection/interfaces/ICollection.h"

class Inmueble;
class Propietario;
class Administracion;

class Inmobiliaria : public Usuario {

private:
    std::string telefono;
    std::string URL;
    DtDireccion direccionInmobiliaria;
    IDictionary* inmuebles;
    IDictionary* propietariosAsociados;
    ICollection* administraciones;

public:
//Constructor y Destructor
    Inmobiliaria(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const DtDireccion & direccionInmobiliaria, const char* telefono, const char* URL);
    virtual ~Inmobiliaria();

//Gets
    DtDireccion getDireccionInmobiliaria() const ;
    std::string getTelefono() const;
    std::string getURL() const;

//Sets
    void setDireccionInmobiliaria(const DtDireccion & direccionInmobiliaria);
    void setTelefono(const char* telefono);
    void setURL(const char* URL);

//1er Caso
    void vincularPropietario(Propietario* p);
    void vincularInmueble(Inmueble* i);

//2do Caso
    IDictionary* getInmuebles() const;
    DtInmobiliaria getDatos();
    DtFecha obtenerFecha();
    ICollection* seleccionarInmobiliaria();
    void altaAdministracion(int numid) ;

//3er Caso
    ICollection* seleccionarInmobiliariaAdministrada();

//4to Caso
    void desvincularInmueble(int numid , Administracion* admi) ;

//5to
    ICollection* filtrarPublicaciones(bool tipopub , float preciomin , float preciomax , TipoInmueble tipo) ;



};


#endif