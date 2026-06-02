#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include <iostream>
#include "Usuario.h"
#include "./ICollection/collections/OrderedDictionary.h"
#include "./Icollection/interfaces/IDictionary.h"
#include "./Icollection/interfaces/IKey.h"
#include "./Icollection/String.h"


class Inmueble;

class Propietario : public Usuario {

private:
    std::string telefono;
    int cuentaBancaria;
    IDictionary* inmuebles;

public:
    Propietario();
    ~Propietario();
    Propietario(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const std::string & telefono, int cuentaBancaria);

    std::string getTelefono();
    int getCuentaBancaria();

    void setTelefono(const std::string & telefono);
    void setCuentaBancaria(int cuentaBancaria);

    void vincularInmueble(Inmueble* i);
    

};

#endif