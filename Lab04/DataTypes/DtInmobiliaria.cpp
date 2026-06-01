#include "DtInmobiliaria.h"

DtInmobiliaria::DtInmobiliaria() : nickname(""), nombre("") {}

DtInmobiliaria::DtInmobiliaria(const std::string& nickname, const std::string& nombre)
    : nickname(nickname), nombre(nombre) {}

std::string DtInmobiliaria::getNickname() const {
    return nickname;
}

std::string DtInmobiliaria::getNombre() const {
    return nombre;
}
