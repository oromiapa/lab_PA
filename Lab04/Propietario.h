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
//Constructor y Destructor
    Propietario(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* telefono, int cuentaBancaria);
    ~Propietario();

//Gets
    std::string getTelefono() const;
    int getCuentaBancaria() const;
    DtPropietario getDatosPropietario();
    IDictionary* obtenerInmueblesPropios() const;

//Sets
    void setTelefono(const char* telefono);
    void setCuentaBancaria(int cuentaBancaria);

//1er Caso
    void vincularInmueble(Inmueble* i);

//4to Caso
    void removerPropietario(int numid) ;

};

#endif