#ifndef INMOBILIARIA_H
#define INMOBILIARIA_H

#include "Usuario.h"
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

public:
    Inmobiliaria();
    Inmobiliaria(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const DtDireccion & direccionInmobiliaria, const std::string & telefono, const std::string & URL);
    virtual ~Inmobiliaria();

    DtDireccion getDireccionInmobiliaria() const ;
    std::string getTelefono() const;
    std::string getURL() const;

    void setDireccionInmobiliaria(const DtDireccion & direccionInmobiliaria);
    void setTelefono(const std::string & telefono);
    void setURL(const std::string & URL);

    void vincularPropietario(Propietario* p);
    void vincularInmueble(Inmueble* i);
    DtInmobiliaria getDatos();



};


#endif