#include "DtInmueble.h"

DtInmueble::DtInmueble() : codigoID(0), superficie(0.0f) {}

DtInmueble::DtInmueble(int codigoID, const DtDireccion& direccion,
                       float superficie, const DtFecha& anioConstruccion,
                       const DtPropietario& propietario)
    : codigoID(codigoID),
      direccion(direccion),
      superficie(superficie),
      anioConstruccion(anioConstruccion),
      propietario(propietario) {}

int DtInmueble::getCodigoID() const {
    return codigoID;
}

DtDireccion DtInmueble::getDireccion() const {
    return direccion;
}

float DtInmueble::getSuperficie() const {
    return superficie;
}

DtFecha DtInmueble::getAnioConstruccion() const {
    return anioConstruccion;
}

DtPropietario DtInmueble::getPropietario() const {
    return propietario;
}
