#include "Visita.h"

Visita::Visita(const DtFecha& fechavisita, const char* contacto) 
    : fechavisita(fechavisita), contacto(contacto) {}

Visita::~Visita() {}

// Gets
DtFecha Visita::getFechaVisita() const {
    return this->fechavisita;
}

std::string Visita::getContacto() const {
    return this->contacto;
}

// Sets
void Visita::setFechaVisita(const DtFecha& fechavisita) {
    this->fechavisita = fechavisita;
}

void Visita::setContacto(const std::string& contacto) {
    this->contacto = contacto;
}