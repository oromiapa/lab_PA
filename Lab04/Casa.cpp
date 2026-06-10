#include "Casa.h"

Casa::Casa(const DtDireccion& direccion, float superficie, const DtFecha& anioConstruccion, const int numid, bool propiedadHorizontal, TipoTecho techo) 
    : Inmueble(direccion, superficie, anioConstruccion, numid), propiedadHorizontal(propiedadHorizontal), techo(techo) {}

Casa::~Casa() {}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


bool Casa::getPropiedadHorizontal() {
    return this->propiedadHorizontal;
}

TipoTecho Casa::getTecho() {
    return this->techo;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void Casa::setPropiedadHorizontal(bool propiedadHorizontal) {
    this->propiedadHorizontal = propiedadHorizontal;
}

void Casa::setTecho(TipoTecho techo) {
    this->techo = techo;
}

bool Casa::isPropiedadHorizontal() {
    return this->propiedadHorizontal;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


bool Casa::cumpleTipo(TipoInmueble tipo) {
    return tipo == TipoInmueble::CASA || tipo == TipoInmueble::AMBOS;
}