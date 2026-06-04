#include "DtPropietario.h"

DtPropietario::DtPropietario(std::string nick, std::string nom) {
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

