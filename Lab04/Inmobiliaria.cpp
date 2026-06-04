#include "Inmobiliaria.h"


Inmobiliaria::Inmobiliaria(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const DtDireccion & direccionInmobiliaria, const char* telefono, const char* URL) 
    : Usuario(nickname, nombre, email, contrasenia), telefono(telefono), URL(URL), direccionInmobiliaria(direccionInmobiliaria) {
        this->inmuebles = new OrderedDictionary();
        this->propietariosAsociados = new OrderedDictionary();
}

Inmobiliaria::~Inmobiliaria() {
    delete this->inmuebles;
    delete this->propietariosAsociados;
}

DtDireccion Inmobiliaria::getDireccionInmobiliaria() const {
    return this->direccionInmobiliaria;
}

std::string Inmobiliaria::getTelefono() const {
    return this->telefono;
}

std::string Inmobiliaria::getURL() const {
    return this->URL;
}

void Inmobiliaria::setDireccionInmobiliaria(const DtDireccion & direccionInmobiliaria) {
    this->direccionInmobiliaria = direccionInmobiliaria;
}

void Inmobiliaria::setTelefono(const char* telefono) {
    this->telefono = telefono;
}

void Inmobiliaria::setURL(const char* URL) {
    this->URL = URL;
}


void Inmobiliaria::vincularPropietario(Propietario* p) {
    if (p == nullptr) return;

    // 1. Le pedimos al propietario la lista de sus inmuebles reales
    ICollection* listaInmuebles = p->obtenerInmueblesPropios();
    
    // 2. Iteramos esa lista para agregarlos a la Inmobiliaria
    IIterator* it = listaInmuebles->getIterator();
    while (it->hasCurrent()) {
        Inmueble* inm = dynamic_cast<Inmueble*>(it->getCurrent());
        if (inm != nullptr) {
            // Llamamos a la función miembro de Inmobiliaria que ya tienes definida
            this->vincularInmueble(inm); 
        }
        it->next();
    }
    
    // 3. Limpieza de memoria temporal
    delete it;
    delete listaInmuebles; // Borramos la lista contenedora (los inmuebles no se borran)
}

void Inmobiliaria::vincularInmueble(Inmueble* i) {
    if (i == nullptr) return;

    int id = i->getNumeroID(); 
    Integer* key = new Integer(id);

    this->inmuebles->add(key, i); 
}