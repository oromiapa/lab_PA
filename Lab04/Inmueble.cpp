#include "Inmueble.h"
#include <string>

Inmueble::Inmueble(const DtDireccion& direccion, float superficie, const DtFecha& anioConstruccion, const int numid) 
    : direccion(direccion), superficie(superficie), anioConstruccion(anioConstruccion), numeroID(numid) {}

Inmueble::~Inmueble() {}

DtDireccion Inmueble::getDireccion() {
    return this->direccion;
}

float Inmueble::getSuperficie() {
    return this->superficie;
}

DtFecha Inmueble::getAnioConstruccion() {
    return this->anioConstruccion;
}

int Inmueble::getNumeroID() {
    return this->numeroID;
}

void Inmueble::setDireccion(const DtDireccion& direccion) {
    this->direccion = direccion;
}

void Inmueble::setSuperficie(float superficie) {
    this->superficie = superficie;
}

void Inmueble::setAnioConstruccion(const DtFecha& anioConstruccion) {
    this->anioConstruccion = anioConstruccion;
}

void Inmueble::setNumeroID(int numeroID) {
    this->numeroID = numeroID;
}

