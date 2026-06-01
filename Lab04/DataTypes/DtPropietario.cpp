#include "DtPropietario.h"

DtPropietario::DtPropietario() : nickname(""), nombre("") {}

DtPropietario::DtPropietario(const std::string& nickname,
                             const std::string& nombre,
                             const std::set<DtInmueble>& inmuebles)
    : nickname(nickname), nombre(nombre), inmuebles(inmuebles) {}

std::string DtPropietario::getNickname() const {
    return nickname;
}

std::string DtPropietario::getNombre() const {
    return nombre;
}

std::set<DtInmueble> DtPropietario::getInmuebles() const {
    return inmuebles;
}
