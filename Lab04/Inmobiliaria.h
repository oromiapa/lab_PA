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
    Inmobiliaria(const string & nombre, const string & email, const DtDireccion & direccionInmobiliaria,
         const string & telefono, const string & URL, const string & nickname, const string & contrasenia);

    DtDireccion getDireccionInmobiliaria();
    string getTelefono();
    string getURL();
};


#endif