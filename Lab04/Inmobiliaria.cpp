#include "Inmobiliaria.h"


Inmobiliaria::Inmobiliaria(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const DtDireccion & direccionInmobiliaria, const char* telefono, const char* URL) 
    : Usuario(nickname, nombre, email, contrasenia), telefono(telefono), URL(URL), direccionInmobiliaria(direccionInmobiliaria) {
        this->inmuebles = new OrderedDictionary();
        this->propietariosAsociados = new OrderedDictionary();
}

Inmobiliaria::~Inmobiliaria() {
    delete this->inmuebles;
    delete this->propietariosAsociados;
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

void Inmobiliaria::setTelefono(const char* telefono) {
    this->telefono = telefono;
}

void Inmobiliaria::setURL(const char* URL) {
    this->URL = URL;
}


void Inmobiliaria::vincularPropietario(Propietario* p) {
    if (p == nullptr) return;

    std::string nick = p->getNickname();
    String* key = new String(nick.c_str());

    this->propietariosAsociados->add(key, p);
}
