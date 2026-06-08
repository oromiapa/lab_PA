#include "Propietario.h"
#include "Inmueble.h"

// interfaces y collections
#include "./ICollection/interfaces/ICollection.h"
#include "./ICollection/interfaces/IIterator.h"
#include "./ICollection/collections/OrderedDictionary.h" 
#include "./ICollection/collections/List.h"

// Wrappers para claves
#include "./ICollection/String.h"
#include "./ICollection/Integer.h"

// DataTypes
#include "./DataTypes/DtInmueble.h"
#include "./DataTypes/DtInmXProp.h"



Propietario::Propietario(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* telefono, int cuentaBancaria) 
    : Usuario(nickname, nombre, email, contrasenia), telefono(telefono), cuentaBancaria(cuentaBancaria) {
        this->inmuebles = new OrderedDictionary();
}

Propietario::~Propietario() {
    delete this->inmuebles;
}

//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


std::string Propietario::getTelefono() const {
    return this->telefono;
}

int Propietario::getCuentaBancaria() const {
    return this->cuentaBancaria;
}



DtPropietario Propietario::getDatosPropietario() {
    DtPropietario dt(this->getNickname().c_str(), this->getNombre().c_str());
    return dt;
}


IDictionary* Propietario::obtenerInmueblesPropios() const {
    return this->inmuebles;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void Propietario::setTelefono(const char* telefono) {
    this->telefono = telefono;
}

void Propietario::setCuentaBancaria(int cuentaBancaria) {
    this->cuentaBancaria = cuentaBancaria;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void Propietario::vincularInmueble(Inmueble* i) {

    if (i == nullptr) return;

    int id = i->getNumeroID(); 

    Integer* key = new Integer(id);

    this->inmuebles->add(key, i);

    i->setDuenio(this);
}



//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


void Propietario::removerPropietario(int numid) {
    if (this->inmuebles != nullptr) {
        
        Integer* keyInm = new Integer(numid);
        
        this->inmuebles->remove(keyInm);
        
        delete keyInm;
    }
}

