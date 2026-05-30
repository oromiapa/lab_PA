#include "Apartamento.h"

Apartamento::Apartamento() : Inmueble(), numeroPiso(0), TieneAscensor(false), gastosComunes(0.0f) {}

Apartamento::Apartamento(const DtDireccion& direccion, const std::string& superficie,
                         const DtFecha& anioConstruccion, int numeroID,
                         int numeroPiso, bool TieneAscensor, float gastosComunes)
    : Inmueble(direccion, superficie, anioConstruccion, numeroID),
      numeroPiso(numeroPiso), TieneAscensor(TieneAscensor), gastosComunes(gastosComunes) {}

int Apartamento::getNumeroPiso() const {
    return numeroPiso;
}

bool Apartamento::tieneAscensor() const {
    return TieneAscensor;
}

float Apartamento::getGastosComunes() const {
    return gastosComunes;
}
