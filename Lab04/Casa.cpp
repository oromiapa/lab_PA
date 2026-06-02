#include "Casa.h"

Casa::Casa(const DtDireccion& direccion, float superficie, const DtFecha& anioConstruccion, const int numid, bool propiedadHorizontal, TipoTecho techo) 
    : Inmueble(direccion, superficie, anioConstruccion, numid), propiedadHorizontal(propiedadHorizontal), techo(techo) {}


bool Casa::getPropiedadHorizontal() {
    return this->propiedadHorizontal;
}

TipoTecho Casa::getTecho() {
    return this->techo;
}

void Casa::setPropiedadHorizontal(bool propiedadHorizontal) {
    this->propiedadHorizontal = propiedadHorizontal;
}

void Casa::setTecho(TipoTecho techo) {
    this->techo = techo;
}

bool Casa::isPropiedadHorizontal() {
    return this->propiedadHorizontal;
}

