#include "Inmueble.h"

// Constructor por defecto
Inmueble::Inmueble() : direccion(), superficie(""), anioConstruccion(), numeroID(0) {}

// Constructor con parámetros
Inmueble::Inmueble(const DtDireccion& direccion, const std::string& superficie,
                   const DtFecha& anioConstruccion, int numeroID)
    : direccion(direccion), superficie(superficie),
      anioConstruccion(anioConstruccion), numeroID(numeroID) {}

// Getters
DtDireccion Inmueble::getDireccion() const {
    return direccion;
}

std::string Inmueble::getSuperficie() const {
    return superficie;
}

DtFecha Inmueble::getAnioConstruccion() const {
    return anioConstruccion;
}

int Inmueble::getNumeroID() const {
    return numeroID;
}
