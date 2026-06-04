#include "Propietario.h"

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


ICollection* Propietario::obtenerInmueblesPropios() {
    ICollection* listaDts = new List();
    IIterator* it = this->inmuebles->getIterator();

    while (it->hasCurrent()) {
        // Obtenemos el Inmueble real del diccionario
        Inmueble* inm = dynamic_cast<Inmueble*>(it->getCurrent());
        
        if (inm != nullptr) {
            // Metemos el objeto Inmueble directo a la lista 
            // (o si prefieres transferir puros DataTypes, crearías un new DtInmueble aquí)
            listaDts->add(inm); 
        }
        it->next();
    }
    delete it;
    return listaDts; 
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
}