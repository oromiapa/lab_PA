#include "Propietario.h"

Propietario::Propietario() : Usuario("", "", "", ""), telefono(""), cuentaBancaria(0) {
    this->inmuebles = new OrderedDictionary();
}

Propietario::~Propietario() {
    delete this->inmuebles;
}

Propietario::Propietario(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const std::string & telefono, int cuentaBancaria) : Usuario(nickname, nombre, email, contrasenia), telefono(telefono), cuentaBancaria(cuentaBancaria) {
    this->inmuebles = new OrderedDictionary();
}

std::string Propietario::getTelefono() const {
    return this->telefono;
}

int Propietario::getCuentaBancaria() const {
    return this->cuentaBancaria;
}

void Propietario::setTelefono(const std::string & telefono) {
    this->telefono = telefono;
}

void Propietario::setCuentaBancaria(int cuentaBancaria) {
    this->cuentaBancaria = cuentaBancaria;
}

