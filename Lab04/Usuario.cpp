#include "Usuario.h"

Usuario::Usuario(const char* nickname, const char* nombre, const char* email, const char* contrasenia) 
    : nickname(nickname), nombre(nombre), email(email), contrasenia(contrasenia) {}

Usuario::~Usuario() {}

std::string Usuario::getNickname() const {
    return this -> nickname;
}

std::string Usuario::getNombre() const {
    return this -> nombre;
}

std::string Usuario::getEmail() const {
    return this -> email;
}

std::string Usuario::getContrasenia() const {
    return this -> contrasenia;
}

void Usuario::setNickname(const char* nickname) {
    this->nickname = nickname;
}

void Usuario::setNombre(const char* nombre) {
    this->nombre = nombre;
}

void Usuario::setEmail(const char* email) {
    this->email = email;
}

void Usuario::setContrasenia(const char* contrasenia) {
    this->contrasenia = contrasenia;
}

