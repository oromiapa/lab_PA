#ifndef PROPIETARIO_H
#define PROPIETARIO_H


#include "Usuario.h"
#include "./DataTypes/DtPropietario.h"
#include "./ICollection/interfaces/IDictionary.h"


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
    IDictionary* obtenerInmueblesPropios() const;

    void vincularInmueble(Inmueble* i);

};

#endif