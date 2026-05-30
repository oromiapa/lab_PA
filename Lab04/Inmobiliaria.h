#ifndef INMOBILIARIA_H
#define INMOBILIARIA_H

#include "Usuario.h"

using namespace std;


class Inmobiliaria : public Usuario {

private:
    DtDireccion direccionInmobiliaria;
    string telefono;
    string URL;

public:
    Inmobiliaria();
    Inmobiliaria(const string & nombre, const string & email, const DtDireccion & direccion, const DtFecha & fechaNacimiento, const DtDireccion & direccionInmobiliaria, const string & telefono, const string & URL);

    DtDireccion getDireccionInmobiliaria();
    string getTelefono();
    string getURL();
    string getNickname();
};


#endif