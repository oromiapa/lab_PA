#ifndef INMOBILIARIA_H
#define INMOBILIARIA_H

#include "Usuario.h"
#include "Inmueble.h"
#include "Propietario.h"
#include "./ICollection/collections/OrderedDictionary.h"
#include "./ICollection/interfaces/IDictionary.h"
#include "./ICollection/interfaces/IKey.h"
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtInmobiliaria.h"

class Propietario;

class Inmobiliaria : public Usuario {

private:
    std::string telefono;
    std::string URL;
    DtDireccion direccionInmobiliaria;
    IDictionary* inmuebles;
    IDictionary* propietariosAsociados;

public:
    Inmobiliaria(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const DtDireccion & direccionInmobiliaria, const char* telefono, const char* URL);
    virtual ~Inmobiliaria();

    DtDireccion getDireccionInmobiliaria() const ;
    std::string getTelefono() const;
    std::string getURL() const;

    void setDireccionInmobiliaria(const DtDireccion & direccionInmobiliaria);
    void setTelefono(const char* telefono);
    void setURL(const char* URL);

    void vincularPropietario(Propietario* p);
    void vincularInmueble(Inmueble* i);
    DtInmobiliaria getDatos();



};


#endif