#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include "./ICollection/Interfaces/ICollectible.h"

class Usuario : public ICollectible {

private:
    std::string nickname;
    std::string nombre;
    std::string email;
    std::string contrasenia;


public:
    Usuario(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia);
    virtual ~Usuario();

    std::string getNickname() const;
    std::string getNombre() const;
    std::string getEmail() const;
    std::string getContrasenia() const;

    void setNickname( const std::string & nickname );
    void setNombre( const std::string & nombre );
    void setEmail( const std::string & email );
    void setContrasenia( const std::string & contrasenia );

    

};

#endif