#include "DtApartamento.h"


DtApartamento::DtApartamento(int id, const DtDireccion& dir, float sup, const DtFecha& fecha, int numeroPiso, bool tieneAscensor, float gastosComunes)
        : DtInmueble(id, dir, sup, fecha), numeroPiso(numeroPiso), tieneAscensor(tieneAscensor), gastosComunes(gastosComunes) {}


int DtApartamento::getNumeroPiso() const {
    return this->numeroPiso ;
}


bool DtApartamento::hayAscensor() const {
    return this->tieneAscensor;
}

float DtApartamento::getGastosComunes() const {
    return this->gastosComunes;
}

