#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include "Usuario.h"
#include "Inmueble.h"
#include "./ICollection/String.h"
#include "./ICollection/Integer.h"
#include "./ICollection/collections/List.h"
#include "./ICollection/collections/OrderedDictionary.h"
#include "./ICollection/interfaces/IIterator.h"
#include "./ICollection/interfaces/IDictionary.h"
#include "./ICollection/interfaces/IKey.h"
#include "./DataTypes/DtPropietario.h"
#include "./DataTypes/DtInmueble.h"

class Inmueble;

class Propietario : public Usuario {

private:
    std::string telefono;
    int cuentaBancaria;
    IDictionary* inmuebles;

public:
    Propietario(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* telefono, int cuentaBancaria);
    ~Propietario();

    
    std::string getTelefono() const;
    int getCuentaBancaria() const;

    void setTelefono(const char* telefono);
    void setCuentaBancaria(int cuentaBancaria);

    DtPropietario getDatos();
    ICollection* obtenerInmueblesPropios();

    void vincularInmueble(Inmueble* i);
    void removerInmueble(Inmueble* i);

};

#endif