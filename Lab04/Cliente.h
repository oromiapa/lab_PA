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
    Cliente(const string & nombre, const string & email, const DtDireccion & direccion, const DtFecha & fechaNacimiento, const string & apellido, const string & documento);

    string getApellido();
    string getDocumento();
    string getNickname();
    string getNombre();
    string getEmail();
    DtDireccion getDireccion();
    
};

#endif