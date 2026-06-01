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
    Propietario(const string & nombre, const string & email, const string & nickname, const string & contrasenia, const int cuentaBancaria, const string & telefono);

    int getCuentaBancaria();
    string getTelefono();
    
};

#endif