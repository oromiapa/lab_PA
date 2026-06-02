#ifndef CLIENTE_H
#define CLIENTE_H


#include "Usuario.h"


class Cliente : public Usuario {
    
private:
    std::string apellido;
    std::string documento;

public:
    Cliente(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* apellido, const char* documento);
    virtual ~Cliente();

    std::string getApellido() const;
    std::string getDocumento() const;
    
    void setApellido(const char* apellido);
    void setDocumento(const char* documento);

    
    
};

#endif