#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <stdexcept>

#include "./ICollection/interfaces/ICollectible.h"

class Usuario : public ICollectible {

private:
    std::string nickname;
    std::string nombre;
    std::string email;
    std::string contrasenia;


public:
//Constructor y destructor
    Usuario(const char* nickname, const char* nombre, const char* email, const char* contrasenia);
    virtual ~Usuario();

//Gets
    std::string getNickname() const;
    std::string getNombre() const;
    std::string getEmail() const;
    std::string getContrasenia() const;

//Sets
    void setNickname( const char* nickname );
    void setNombre( const char* nombre );
    void setEmail( const char* email );
    void setContrasenia( const char* contrasenia );

    

};

#endif