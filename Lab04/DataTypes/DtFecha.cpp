#include "DtFecha.h"

// Constructor por defecto
DtFecha::DtFecha() : dia(1), mes(1), anio(1900) {}

// Constructor con parámetros
DtFecha::DtFecha(int dia, int mes, int anio)
    : dia(dia), mes(mes), anio(anio) {
    // Validación básica
    if (dia < 1 || dia > 31 || mes < 1 || mes > 12 || anio < 1) {
        throw std::invalid_argument("Fecha inválida");
    }
}

// Getters
int DtFecha::getDia() {
    return dia;
}

int DtFecha::getMes() {
    return mes;
}

int DtFecha::getAnio() {
    return anio;
}
