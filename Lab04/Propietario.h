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
    Propietario(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* telefono, int cuentaBancaria);
    ~Propietario();

    
    std::string getTelefono() const;
    int getCuentaBancaria() const;

    void setTelefono(const char* telefono);
    void setCuentaBancaria(int cuentaBancaria);

    void vincularInmueble(Inmueble* i);
    DtPropietario getDatos();
    void removerInmueble(Inmueble* i);

};

#endif