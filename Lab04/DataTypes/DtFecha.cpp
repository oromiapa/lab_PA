#include "DtFecha.h"

DtFecha::DtFecha() : dia(0), mes(0), anio(0) {}

DtFecha::DtFecha(int dia, int mes, int anio) : dia(dia), mes(mes), anio(anio) {}

int DtFecha::getDia() {
    return this->dia;
}

int DtFecha::getMes() {
    return this->mes;
}

int DtFecha::getAnio() {
    return this->anio;
}