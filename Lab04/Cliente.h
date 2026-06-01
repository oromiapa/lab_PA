#ifndef CLIENTE_H
#define CLIENTE_H

#include "Usuario.h"

using namespace std;

class Cliente : public Usuario {
    
private:
    string apellido;
    string documento;

public:
    Cliente();
    Cliente(const string & nombre, const string & email, const string & nickname, const string & contrasenia, const string & apellido, const string & documento);
    string getApellido();
    string getDocumento();
    
};

#endif