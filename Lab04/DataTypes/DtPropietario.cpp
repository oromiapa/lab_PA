#include "DtPropietario.h"

DtPropietario::DtPropietario(const char* nick, const char* nom) {
    this->nickname = nick;
    this->nombre = nom;
}

DtPropietario::~DtPropietario() {
}

std::string DtPropietario::getNickname() const {
    return this->nickname;
}

std::string DtPropietario::getNombre() const {
    return this->nombre;
}

