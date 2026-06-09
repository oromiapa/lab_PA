#include "Cliente.h"


Cliente::Cliente(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* apellido, const char* documento) 
    : Usuario(nickname, nombre, email, contrasenia), apellido(apellido), documento(documento) {}

Cliente::~Cliente() {
    if (this->visitas != nullptr)
        delete this->visitas;
}
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


std::string Cliente::getApellido() const {
    return this->apellido;
}

std::string Cliente::getDocumento() const {
    return this->documento;
}

//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void Cliente::setApellido(const char* apellido) {
    this->apellido = apellido;
}

void Cliente::setDocumento(const char* documento) {
    this->documento = documento;
}



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void Cliente::agregarVisita(Visita* v) {
    if (this->visitas == nullptr) {
        this->visitas = new List();
    }
    this->visitas->add(v);
}

ICollection* Cliente::getVisitas() const {
    return this->visitas;
}
