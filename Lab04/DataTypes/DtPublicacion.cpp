#include "DtPublicacion.h"

DtPublicacion::DtPublicacion() : codigoID(0), texto(""), nombre(""), tipo(Tipo::CASA) {}

DtPublicacion::DtPublicacion(int codigoID, const DtFecha& fechaPublicacion,
                             const std::string& texto, const std::string& nombre,
                             Tipo tipo)
    : codigoID(codigoID),
      fechaPublicacion(fechaPublicacion),
      texto(texto),
      nombre(nombre),
      tipo(tipo) {}

int DtPublicacion::getCodigoID() const {
    return codigoID;
}

DtFecha DtPublicacion::getFechaPublicacion() const {
    return fechaPublicacion;
}

std::string DtPublicacion::getTexto() const {
    return texto;
}

std::string DtPublicacion::getNombre() const {
    return nombre;
}

Tipo DtPublicacion::getTipo() const {
    return tipo;
}
