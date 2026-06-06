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


std::string Propietario::getTelefono() const {
    return this->telefono;
}

int Propietario::getCuentaBancaria() const {
    return this->cuentaBancaria;
}

void Propietario::setTelefono(const char* telefono) {
    this->telefono = telefono;
}

void Propietario::setCuentaBancaria(int cuentaBancaria) {
    this->cuentaBancaria = cuentaBancaria;
}


DtPropietario Propietario::getDatos() {
    DtPropietario dt(this->getNickname().c_str(), this->getNombre().c_str());
    return dt;
}


IDictionary* Propietario::obtenerInmueblesPropios() const {
    return this->inmuebles;
} 


void Propietario::vincularInmueble(Inmueble* i) {
    if (i == nullptr) return;

    // 1. Obtenemos el ID numérico que identifica al inmueble
    int id = i->getNumeroID(); 

    // 2. Instanciamos la clave usando el constructor que nos mostraste
    Integer* key = new Integer(id);

    // 3. Lo agregamos al OrderedDictionary interno del propietario
    // El diccionario toma posesión de 'key' (él la borrará en su destructor).
    this->inmuebles->add(key, i);

    //El propietario se asigna a sí mismo (this) como dueño del inmueble
    i->setDuenio(this);
}