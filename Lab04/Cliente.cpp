#include "Cliente.h"


Cliente::Cliente() : Usuario("", "", "", ""), apellido(""), documento("") {}

Cliente::Cliente(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const std::string & apellido, const std::string & documento) : Usuario(nickname, nombre, email, contrasenia), apellido(apellido), documento(documento) {}

Cliente::~Cliente() {}

std::string Cliente::getApellido() const {
    return this->apellido;
}

std::string Cliente::getDocumento() const {
    return this->documento;
}

void Cliente::setApellido(const std::string & apellido) {
    this->apellido = apellido;
}

void Cliente::setDocumento(const std::string & documento) {
    this->documento = documento;
}

