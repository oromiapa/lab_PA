#ifndef CLIENTE_H
#define CLIENTE_H


#include "Usuario.h"


class Cliente : public Usuario {
    
private:
    std::string apellido;
    std::string documento;

public:
    Cliente();
    Cliente(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const std::string & apellido, const std::string & documento);

    std::string getApellido();
    std::string getDocumento();
    
    void setApellido(const std::string & apellido);
    void setDocumento(const std::string & documento);

    
    
};

#endif