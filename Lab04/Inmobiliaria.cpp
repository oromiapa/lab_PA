#include "Inmobiliaria.h"


Inmobiliaria::Inmobiliaria() : Usuario("", "", "", ""), telefono(""), URL(""), direccionInmobiliaria(DtDireccion("", 0, "")) {
    this->inmuebles = new OrderedDictionary();
}

Inmobiliaria::Inmobiliaria(const std::string & nickname, const std::string & nombre, const std::string & email, const std::string & contrasenia, const DtDireccion & direccionInmobiliaria, const std::string & telefono, const std::string & URL) : Usuario(nickname, nombre, email, contrasenia), telefono(telefono), URL(URL), direccionInmobiliaria(direccionInmobiliaria) {
    this->inmuebles = new OrderedDictionary();
}

Inmobiliaria::~Inmobiliaria() {
    delete this->inmuebles;
}

DtDireccion Inmobiliaria::getDireccionInmobiliaria() const {
    return this->direccionInmobiliaria;
}

std::string Inmobiliaria::getTelefono() const {
    return this->telefono;
}

std::string Inmobiliaria::getURL() const {
    return this->URL;
}

void Inmobiliaria::setDireccionInmobiliaria(const DtDireccion & direccionInmobiliaria) {
    this->direccionInmobiliaria = direccionInmobiliaria;
}

void Inmobiliaria::setTelefono(const std::string & telefono) {
    this->telefono = telefono;
}

void Inmobiliaria::setURL(const std::string & URL) {
    this->URL = URL;
}

