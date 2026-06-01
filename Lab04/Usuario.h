#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"

using namespace std;

class Usuario {
private:
    string nombre;
    string email;
    DtDireccion direccion;
    DtFecha fechaNacimiento;

public:
    Usuario();
    Usuario(const string & nombre, const string & email, const string & nickname, const string & contrasenia);

    string getNombre();
    string getEmail();
    string getNickname();
    string getContrasenia();
};

#endif