#include "Sistema.h"
#include "Usuario.h"
#include "Cliente.h"
#include "Propietario.h"
#include "Inmobiliaria.h"
#include "Inmueble.h"
#include "Casa.h"
#include "Apartamento.h"
#include "./DataTypes/DtPropietario.h"
#include "./ICollection/String.h"
#include "./ICollection/Integer.h"
#include "./ICollection/collections/List.h"
#include "./DataTypes/TipoTecho.h"


//Constructor y destructor

Sistema::Sistema() {
    this->usuarios = new OrderedDictionary();
    this->inmuebles = new OrderedDictionary();
    this->inmobiliarias = new OrderedDictionary();
    this->inmobiliariaActual = nullptr;
    this->contadorInmuebles = 0;
}

Sistema::~Sistema() {
    IIterator* itU = this->usuarios->getIterator();
    while (itU->hasCurrent()) {
        delete itU->getCurrent();
        itU->next();
    }
    delete itU;
    delete this->usuarios; 

    IIterator* itI = this->inmuebles->getIterator();
    while (itI->hasCurrent()) {
        delete itI->getCurrent();
        itI->next();
    }
    delete itI;
    delete this->inmuebles;

    delete this->inmobiliarias; 
}





// Métodos

bool Sistema::existeUsuario(const char* nickname) {
    String* key = new String(nickname);
    bool existe = this->usuarios->member(key);
    delete key;
    return existe;
}


void Sistema::altaCliente(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* apellido, const char* documento) {
    if (this->existeUsuario(nickname)) {
        throw std::invalid_argument("El usuario ya existe");
    }
    Cliente* cliente = new Cliente(nickname, nombre, email, contrasenia, apellido, documento);
    String* key = new String(nickname);
    this->usuarios->add(key, cliente);
}


void Sistema::altaPropietario(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* telefono, int cuentaBancaria) {
    if (this->existeUsuario(nickname)) {
        throw std::invalid_argument("El usuario ya existe");
    }
    Propietario* propietario = new Propietario(nickname, nombre, email, contrasenia, telefono, cuentaBancaria);
    String* key = new String(nickname);
    this->usuarios->add(key, propietario);
}


int Sistema::autoincremental() {
    return ++this->contadorInmuebles;
}


void Sistema::crearCasa(const DtDireccion & direccion, const DtFecha & añoConstruccion, float superficie, bool propiedadHorizontal, TipoTecho tipoTecho) {
    int numid = this->autoincremental();
    Integer* key = new Integer(numid);
    Casa* casa = new Casa(direccion, superficie, añoConstruccion, numid, propiedadHorizontal, tipoTecho);
    this->inmuebles->add(key, casa);
}


void Sistema::crearApartamento(const DtDireccion & direccion, const DtFecha & añoConstruccion, float superficie, int numeroPiso, bool TieneAscensor, const float & gastosComunes) {
    int numid = this->autoincremental();
    Integer* key = new Integer(numid);
    Apartamento* apartamento = new Apartamento(direccion, superficie, añoConstruccion, numid, numeroPiso, TieneAscensor, gastosComunes);
    this->inmuebles->add(key, apartamento);
}


void Sistema::altaInmobiliaria(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const DtDireccion & direccionInmobiliaria, const char* telefono, const char* URL) {
    if (this->existeUsuario(nickname)) {
        throw std::invalid_argument("El usuario ya existe");
    }
    
    Inmobiliaria* inmobiliaria = new Inmobiliaria(nickname, nombre, email, contrasenia, direccionInmobiliaria, telefono, URL);
    String* key = new String(nickname);
    
    this->usuarios->add(key, inmobiliaria);
    
    this->inmobiliariaActual = inmobiliaria; 
}


ICollection* Sistema::listarPropietarios() {
    ICollection* propietarios = new List();
    IIterator* it = this->usuarios->getIterator();
    while (it->hasCurrent()) {
        ICollectible* item = it->getCurrent();
        Propietario* p = dynamic_cast<Propietario*>(item);
        if (p != nullptr) {
            DtPropietario datos = p->getDatos();
            DtPropietario* dtParaLista = new DtPropietario(datos.getNickname(), datos.getNombre());
            propietarios->add(dtParaLista);
        }
        it->next();
    }
    delete it;
    return propietarios;
}


void Sistema::vincularPropietario(const char* nicknamePropietario) {
    // ---- PASO 1 del diagrama: p : find(nickname) ----
    String* keyBuscar = new String(nicknamePropietario);
    ICollectible* item = this->usuarios->find(keyBuscar);
    delete keyBuscar; // Borramos la clave temporal de búsqueda

    if (item == nullptr) {
        throw std::invalid_argument("El propietario no existe.");
    }
    
    Propietario* p = dynamic_cast<Propietario*>(item);
    if (p == nullptr) {
        throw std::invalid_argument("El usuario encontrado no es un propietario.");
    }

    // ---- PASO 2 del diagrama: vincularPropietario(p) ----
    // El sistema le envía el mensaje a la inmobiliaria recordada
    if (this->inmobiliariaActual != nullptr) {
        this->inmobiliariaActual->vincularPropietario(p); 
    } else {
        throw std::runtime_error("No hay una inmobiliaria activa en el sistema.");
    }
}


void Sistema::finalizarAltaInmobiliaria() {
    this->inmobiliariaActual = nullptr; // Ya no recordamos la inmobiliaria, el caso de uso terminó.
}

