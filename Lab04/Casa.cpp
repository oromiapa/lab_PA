#include "Casa.h"

Casa::Casa(const DtDireccion& direccion, const std::string& superficie,
           const DtFecha& anioConstruccion, int numeroID,
           bool propiedadHorizontal, TipoTecho techo)
    : Inmueble(direccion, superficie, anioConstruccion, numeroID),
      propiedadHorizontal(propiedadHorizontal), techo(techo) {}


bool Casa::isPropiedadHorizontal() const {
    return propiedadHorizontal;
}

TipoTecho Casa::getTecho() const {
    return techo;
}
