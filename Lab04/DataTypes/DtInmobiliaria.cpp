#include "DtInmobiliaria.h"

DtInmobiliaria::DtInmobiliaria(const char* nick, const char* nom) {
    this->nickname = nick;
    this->nombre = nom;
}

DtInmobiliaria::~DtInmobiliaria() {
}

std::string DtInmobiliaria::getNickname() const {
    return this->nickname;
}

std::string DtInmobiliaria::getNombre() const {
    return this->nombre;
}

