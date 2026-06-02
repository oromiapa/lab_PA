#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>

class Usuario {

private:
    std::string nickname;
    std::string nombre;
    std::string email;
    std::string contrasenia;


public:
    Usuario(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia);
    virtual ~Usuario();

    std::string getNickname();
    std::string getNombre();
    std::string getEmail();
    std::string getContrasenia();

    void setNickname(const std::string & nickname);
    void setNombre(const std::string & nombre);
    void setEmail(const std::string & email);
    void setContrasenia(const std::string & contrasenia);
    

};

#endif