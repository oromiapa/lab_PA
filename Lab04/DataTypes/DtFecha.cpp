#include "DtFecha.h"

DtFecha::DtFecha() {
    this->dia = 0;
    this->mes = 0;
    this->anio = 0;
}

DtFecha::DtFecha(int dia, int mes, int anio) {
    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
}

int DtFecha::getDia() {
    return this->dia;
}

int DtFecha::getMes() {
    return this->mes;
}

int DtFecha::getAnio() {
    return this->anio;
}

