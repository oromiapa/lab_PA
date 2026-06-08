#include "DtPublicacion.h"


DtPublicacion::DtPublicacion(const int idpub, const DtFecha &fecha, const char* text, const TipoInmueble &types)
    : id(idpub), fechapub(fecha), texto(text), tipo(types) {}


DtPublicacion::~DtPublicacion() {}



int DtPublicacion::getID() const {
    return this->id;
}

DtFecha DtPublicacion::getFechaPublicacion() const {
    return this->fechapub;
}

std::string DtPublicacion::getTexto() const {
    return this->texto;
}

TipoInmueble DtPublicacion::getTipo() const {
    return this->tipo;
}

