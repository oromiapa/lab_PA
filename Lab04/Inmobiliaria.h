#ifndef INMOBILIARIA_H
#define INMOBILIARIA_H

#include "Usuario.h"
#include <string>
#include "./DataTypes/DtDireccion.h"


class Inmobiliaria : public Usuario {

private:
    DtDireccion direccionInmobiliaria;
    std::string telefono;
    std::string URL;

public:
    Inmobiliaria();
    Inmobiliaria(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const DtDireccion & direccionInmobiliaria, const std::string & telefono, const std::string & URL);

    DtDireccion getDireccionInmobiliaria() ;
    std::string getTelefono();
    std::string getURL();

    void setDireccionInmobiliaria(const DtDireccion & direccionInmobiliaria);
    void setTelefono(const std::string & telefono);
    void setURL(const std::string & URL);



};


#endif