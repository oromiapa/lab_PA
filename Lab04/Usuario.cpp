#include "Usuario.h"

Usuario::Usuario(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia) : nickname(nickname), nombre(nombre), email(email), contrasenia(contrasenia) {}

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

void Usuario::setNickname(const std::string & nickname) {
    this->nickname = nickname;
}

void Usuario::setNombre(const std::string & nombre) {
    this->nombre = nombre;
}

void Usuario::setEmail(const std::string & email) {
    this->email = email;
}

void Usuario::setContrasenia(const std::string & contrasenia) {
    this->contrasenia = contrasenia;
}

