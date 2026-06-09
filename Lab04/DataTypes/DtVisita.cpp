#include "DtVisita.h"


DtVisita::DtVisita(const DtFecha & fecha, int idPublicacion, const std::string & nicknameCliente) {
    this->fecha = fecha;
    this->idPublicacion = idPublicacion;
    this->nicknameCliente = nicknameCliente;
}

DtVisita::~DtVisita() {
}

DtFecha DtVisita::getFecha() const {
    return this->fecha;
}

int DtVisita::getIdPublicacion() const {
    return this->idPublicacion;
}

std::string DtVisita::getNicknameCliente() const {
    return this->nicknameCliente;
}