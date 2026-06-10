#include "Apartamento.h"

Apartamento::Apartamento(const DtDireccion& direccion, const float superficie, const DtFecha& anioConstruccion, const int numid, int numeroPiso, bool tieneAscensor, float gastosComunes) 
    : Inmueble(direccion, superficie, anioConstruccion, numid), numeroPiso(numeroPiso), tieneAscensor(tieneAscensor), gastosComunes(gastosComunes) {}

Apartamento::~Apartamento() {}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


int Apartamento::getNumeroPiso() {
    return this->numeroPiso;
}

float Apartamento::getGastosComunes() {
    return this->gastosComunes;
}

bool Apartamento::hayAscensor() {
    return this->tieneAscensor;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void Apartamento::setNumeroPiso(int numeroPiso) {
    this->numeroPiso = numeroPiso;
}

void Apartamento::setGastosComunes(float gastosComunes) {
    this->gastosComunes = gastosComunes;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


bool Apartamento::cumpleTipo(TipoInmueble tipo) {
    return tipo == TipoInmueble::APARTAMENTO || tipo == TipoInmueble::AMBOS;
}