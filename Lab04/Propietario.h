#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include "Usuario.h"
#include "./ICollection/String.h"
#include "./ICollection/collections/OrderedDictionary.h"
#include "./ICollection/interfaces/IDictionary.h"
#include "./ICollection/interfaces/IKey.h"
#include "./DataTypes/DtPropietario.h"


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

    
    std::string getTelefono() const;
    int getCuentaBancaria() const;

    void setTelefono(const std::string & telefono);
    void setCuentaBancaria(int cuentaBancaria);

    void vincularInmueble(Inmueble* i);
    DtPropietario getDatos();
    void removerInmueble(Inmueble* i);

};

#endif