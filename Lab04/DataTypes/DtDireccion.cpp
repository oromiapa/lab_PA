#include "DtDireccion.h"

// Constructor por defecto
DtDireccion::DtDireccion() : calle(""), numero(0), ciudad("") {}

// Constructor con parámetros
DtDireccion::DtDireccion(const std::string& calle, int numero, const std::string& ciudad)
    : calle(calle), numero(numero), ciudad(ciudad) {}

// Getters
std::string DtDireccion::getCalle() {
    return calle;
}

int DtDireccion::getNumero() {
    return numero;
}

std::string DtDireccion::getCiudad() {
    return ciudad;
}
