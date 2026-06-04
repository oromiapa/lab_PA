#include "DtDireccion.h"

DtDireccion::DtDireccion() : calle(""), numero(0), ciudad("") {}

DtDireccion::DtDireccion(const std::string & calle, int numero, const std::string & ciudad) : calle(calle), numero(numero), ciudad(ciudad) {}

std::string DtDireccion::getCalle() const {
    return this->calle;
}
    
int DtDireccion::getNumero() const {
    return this->numero;
}

std::string DtDireccion::getCiudad() const {
    return this->ciudad;
}
