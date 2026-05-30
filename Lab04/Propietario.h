#ifndef PROPIETARIO_H
#define PROPIETARIO_H

#include "Usuario.h"

using namespace std;

class Propietario : public Usuario {

private:
    string telefono;
    int cuentaBancaria;

public:
    Propietario();
    Propietario(const string & nombre, const string & email, const DtDireccion & direccion, const DtFecha & fechaNacimiento, const string & telefono, int cuentaBancaria);

    string getTelefono();
    int getCuentaBancaria();
    string getNickname();
    string getNombre();
    string getEmail();
    DtDireccion getDireccion();
    DtFecha getFechaNacimiento();
    
};

#endif