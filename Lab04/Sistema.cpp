#include <iostream>


#include "Sistema.h"
#include "Usuario.h"
#include "Cliente.h"
#include "Propietario.h"
#include "Inmobiliaria.h"
#include "Inmueble.h"
#include "Casa.h"
#include "Apartamento.h"
#include "Administracion.h"
#include "Publicacion.h"

//DataTypes
#include "./DataTypes/DtPropietario.h"
#include "./DataTypes/DtInmobiliaria.h"
#include "./DataTypes/DtInmueble.h"
#include "./DataTypes/DtVisita.h"
#include "./DataTypes/DtInmXProp.h"
#include "./DataTypes/DtInmuebleAdministrado.h"
#include "./DataTypes/DataFiltro.h"
#include "./DataTypes/TipoInmueble.h"

//ICollection
#include "./ICollection/String.h"
#include "./ICollection/Integer.h"

//ICollection/interfaces
#include "./ICollection/interfaces/IIterator.h"

//ICollection/collections
#include "./ICollection/collections/OrderedDictionary.h"
#include "./ICollection/collections/List.h"


Sistema::Sistema() {
    this->usuarios       = new OrderedDictionary();
    this->clientes       = new OrderedDictionary();
    this->propietarios   = new OrderedDictionary();
    this->inmobiliarias  = new OrderedDictionary();
    this->inmuebles      = new OrderedDictionary();
    this->casas          = new OrderedDictionary();
    this->apartamentos   = new OrderedDictionary();
    this->inmobiliariaActual = nullptr;
    this->propietarioActual  = nullptr;
    this->inmuebleActual     = nullptr;
    this->contadorInmuebles  = 0;
}

Sistema::~Sistema() {

    std::cout << "  [DEBUG] Antes de destruir Sistema\n";
    std::cout.flush();

    IIterator* itI = this->inmuebles->getIterator();
    while (itI->hasCurrent()) {
        delete itI->getCurrent();
        itI->next();
    }
    delete itI;
 
    IIterator* itU = this->usuarios->getIterator();
    while (itU->hasCurrent()) {
        delete itU->getCurrent();
        itU->next();
    }
    delete itU;
 

    delete this->casas;
    delete this->apartamentos;
    delete this->clientes;
    delete this->propietarios;
    delete this->inmobiliarias;
    delete this->inmuebles;
    delete this->usuarios;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// CASO 1: ALTA DE USUARIOS
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


bool Sistema::existeUsuario(const char* nickname) {

    String* key = new String(nickname);
    bool existe = this->usuarios->member(key);
    delete key;
    return existe;

}


void Sistema::altaCliente(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* apellido, const char* documento) {

    if (this->existeUsuario(nickname))
        throw std::invalid_argument("El usuario ya existe");

    Cliente* cliente = new Cliente(nickname, nombre, email, contrasenia, apellido, documento);

    this->usuarios->add(new String(nickname), cliente);
    this->clientes->add(new String(nickname), cliente);

}


void Sistema::altaPropietario(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const char* telefono, int cuentaBancaria) {

    if (this->existeUsuario(nickname))
        throw std::invalid_argument("El usuario ya existe");

    Propietario* propietario = new Propietario(nickname, nombre, email, contrasenia, telefono, cuentaBancaria);

    this->usuarios->add(new String(nickname), propietario);
    this->propietarios->add(new String(nickname), propietario);

    this->propietarioActual = propietario;

}


int Sistema::autoincremental() {
    return ++this->contadorInmuebles;
}


void Sistema::crearCasa(const DtDireccion& direccion, const DtFecha& anioConstruccion, float superficie, bool propiedadHorizontal, TipoTecho tipoTecho) {

    int numid = this->autoincremental();
    Casa* casa = new Casa(direccion, superficie, anioConstruccion, numid, propiedadHorizontal, tipoTecho);

    this->inmuebles->add(new Integer(numid), casa);
    this->casas->add(new Integer(numid), casa);

    this->propietarioActual->vincularInmueble(casa);

}


void Sistema::crearApartamento(const DtDireccion& direccion, const DtFecha& anioConstruccion, float superficie, int numeroPiso, bool tieneAscensor, const float& gastosComunes) {

    int numid = this->autoincremental();
    Apartamento* apartamento = new Apartamento(direccion, superficie, anioConstruccion, numid, numeroPiso, tieneAscensor, gastosComunes);

    this->inmuebles->add(new Integer(numid), apartamento);
    this->apartamentos->add(new Integer(numid), apartamento);

    this->propietarioActual->vincularInmueble(apartamento);

}


void Sistema::altaInmobiliaria(const char* nickname, const char* nombre, const char* email, const char* contrasenia, const DtDireccion& direccionInmobiliaria, const char* telefono, const char* URL) {

    if (this->existeUsuario(nickname))
        throw std::invalid_argument("El usuario ya existe");

    Inmobiliaria* inmobiliaria = new Inmobiliaria(nickname, nombre, email, contrasenia, direccionInmobiliaria, telefono, URL);

    this->usuarios->add(new String(nickname), inmobiliaria);
    this->inmobiliarias->add(new String(nickname), inmobiliaria);

    this->inmobiliariaActual = inmobiliaria;

}


ICollection* Sistema::listarPropietarios() {

    ICollection* lista = new List();
    IIterator* it = this->propietarios->getIterator();

    while (it->hasCurrent()) {

        Propietario* p = static_cast<Propietario*>(it->getCurrent());
        DtPropietario datos = p->getDatosPropietario();
        lista->add(new DtPropietario(datos.getNickname(), datos.getNombre()));
        it->next();

    }

    delete it;
    return lista;

}


void Sistema::vincularPropietario(const char* nicknamePropietario) {

    String* key = new String(nicknamePropietario);
    ICollectible* item = this->propietarios->find(key);
    delete key;

    if (item == nullptr)
        throw std::invalid_argument("El propietario no existe.");

    if (this->inmobiliariaActual == nullptr)
        throw std::runtime_error("No hay una inmobiliaria activa en el sistema para vincular.");

    this->inmobiliariaActual->vincularPropietario(static_cast<Propietario*>(item));

}


void Sistema::finalizarAltaInmobiliaria() {
    this->inmobiliariaActual = nullptr;
}

void Sistema::finalizarAltaPropietario() {
    this->propietarioActual = nullptr;
}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// CASO 2: ALTA DE ADMINISTRACION
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


ICollection* Sistema::listarInmobiliarias() {

    ICollection* lista = new List();
    IIterator* it = this->inmobiliarias->getIterator();

    while (it->hasCurrent()) {

        Inmobiliaria* i = static_cast<Inmobiliaria*>(it->getCurrent());
        DtInmobiliaria datos = i->getDatos();
        lista->add(new DtInmobiliaria(datos.getNickname(), datos.getNombre()));
        it->next();

    }

    delete it;
    return lista;

}


ICollection* Sistema::seleccionarInmobiliaria(const char* nombreInmobiliaria) {

    if (nombreInmobiliaria == nullptr)
        throw std::invalid_argument("El nombre de la inmobiliaria no puede ser nulo.");

    String* key = new String(nombreInmobiliaria);
    ICollectible* item = this->inmobiliarias->find(key);
    delete key;

    if (item == nullptr)
        throw std::invalid_argument("La inmobiliaria seleccionada no existe.");

    Inmobiliaria* inm = static_cast<Inmobiliaria*>(item);
    this->inmobiliariaActual = inm;

    return inm->seleccionarInmobiliaria();

}


void Sistema::altaAdministracion(int numid) {

    if (this->inmobiliariaActual == nullptr)
        throw std::runtime_error("Error: No hay ninguna inmobiliaria seleccionada en memoria.");

    this->inmobiliariaActual->altaAdministracion(numid);
    this->inmobiliariaActual = nullptr;

}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// CASO 3: ALTA DE PUBLICACION
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


ICollection* Sistema::seleccionarInmobiliariaAdministrada(const char* nombreInmobiliaria) {

    ICollection* listaRetorno = new List();
    IIterator* it = this->inmuebles->getIterator();

    while (it->hasCurrent()) {

        Inmueble* inm = static_cast<Inmueble*>(it->getCurrent());

        if (inm->getAdministracion() != nullptr) {  

            DtInmuebleAdministrado* dt = new DtInmuebleAdministrado(
                inm->getNumeroID(),
                inm->getDireccion(),
                inm->getFechaAdministracion()
            );

            listaRetorno->add(dt);

        }
        it->next();
    }

    delete it;
    return listaRetorno;

}


void Sistema::altaPublicacion(const int numid, const char* text, float price, bool tipopub) {

    Integer* key = new Integer(numid);
    ICollectible* item = this->inmuebles->find(key);
    delete key;

    if (item == nullptr)
        throw std::invalid_argument("Error: No existe un inmueble con el ID especificado.");

    static_cast<Inmueble*>(item)->altaPublicacion(numid, text, price, tipopub);

}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// CASO ESPECIAL: ALTA DE VISITA
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||



void Sistema::altaVisita(const char* nicknameCliente, int idPublicacion, const DtFecha& fechaVisita , const char* contacto) {

    String* keyCli = new String(nicknameCliente);
    ICollectible* itemCli = this->clientes->find(keyCli);
    delete keyCli;
    Cliente* cli = static_cast<Cliente*>(itemCli);
    
    if (cli == nullptr) 
        throw std::invalid_argument("Cliente no encontrado");

    Publicacion* pub = nullptr;
    IIterator* itInm = this->inmuebles->getIterator();

    while (itInm->hasCurrent()) {
        
        Inmueble* inm = static_cast<Inmueble*>(itInm->getCurrent());
        
        if (inm != nullptr) {
            Administracion* adm = inm->getAdministracion();
            if (adm != nullptr) {
                pub = adm->getPublicacion(idPublicacion);
                if (pub != nullptr) 
                    break;
            }
        }
        itInm->next();

    }

    delete itInm;

    if (pub == nullptr) 
        throw std::invalid_argument("Publicación no encontrada");

    Visita* nueva = new Visita(fechaVisita, contacto);
    cli->agregarVisita(nueva);
    pub->agregarVisita(nueva);

}


ICollection* Sistema::listarVisitas(int idPublicacion) {

    IIterator* it = this->inmobiliarias->getIterator();

    while (it->hasCurrent()) {

        Inmobiliaria* inmo = static_cast<Inmobiliaria*>(it->getCurrent());
        Publicacion* pub = inmo->getPublicacion(idPublicacion);
        
        if (pub != nullptr) {
            delete it;
            return pub->listarVisitas(idPublicacion);
        }
        it->next();

    }
    delete it;
 
    throw std::invalid_argument("Publicacion no encontrada.");

}







//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// CASO 4: ELIMINAR INMUEBLE
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


ICollection* Sistema::listarinmueblesxpropietario() {

    ICollection* listaRetorno = new List();
    IIterator* it = this->inmuebles->getIterator();

    while (it->hasCurrent()) {

        Inmueble* inm = static_cast<Inmueble*>(it->getCurrent());
        Propietario* prop = inm->getDuenio();

        if (prop != nullptr) {
            DtPropietario dtProp(prop->getNickname().c_str(), prop->getNombre().c_str());
            listaRetorno->add(new DtInmXProp(inm->getNumeroID(), inm->getDireccion(), dtProp));
        }
        it->next();

    }

    delete it;
    return listaRetorno;

}


DtInmueble Sistema::seleccionarInmueble(int numid) {

    Integer* key = new Integer(numid);
    ICollectible* item = this->inmuebles->find(key);
    delete key;

    if (item == nullptr)
        throw std::invalid_argument("El inmueble seleccionado no existe.");

    Inmueble* i = static_cast<Inmueble*>(item);
    this->inmuebleActual = i;

    return DtInmueble(i->getNumeroID(), i->getDireccion(), i->getSuperficie(), i->getAnioConstruccion());

}


void Sistema::eliminarInmueble(int numid) {

    if (this->inmuebleActual == nullptr || this->inmuebleActual->getNumeroID() != numid)
        throw std::runtime_error("Error: Inmueble no seleccionado o ID inválido.");

    this->inmuebleActual->borrarAdministracion();
    this->inmuebleActual->removerPropietario(numid);

    Integer* key = new Integer(numid);
    this->inmuebles->remove(key);

    if (this->casas->member(key))
        this->casas->remove(key);

    else
        this->apartamentos->remove(key);
    
    delete key;

    delete this->inmuebleActual;
    this->inmuebleActual = nullptr;

}


//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
// CASO 5: CONSULTAR PUBLICACION
//|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


ICollection* Sistema::filtrarPublicaciones(bool tipopub, float preciomin, float preciomax, TipoInmueble tipo) {

    ICollection* resultado = new List();

    IIterator* it = this->inmobiliarias->getIterator();

    while (it->hasCurrent()) {

        Inmobiliaria* inmo = static_cast<Inmobiliaria*>(it->getCurrent());

        ICollection* filtroInmo = inmo->filtrarPublicaciones(tipopub, preciomin, preciomax, tipo);

        IIterator* itFiltro = filtroInmo->getIterator();

        while (itFiltro->hasCurrent()) {
            resultado->add(static_cast<DataFiltro*>(itFiltro->getCurrent()));
            itFiltro->next();
        }

        delete itFiltro;
        delete filtroInmo;

        it->next();

    }

    delete it;

    return resultado;

}


DtInmueble Sistema::seleccionarPublicacion(int id) {

    IIterator* it = this->inmobiliarias->getIterator();

    while (it->hasCurrent()) {

        Inmobiliaria* inmo = static_cast<Inmobiliaria*>(it->getCurrent());

        DtInmueble* resultado = inmo->seleccionarPublicacion(id);

        if (resultado != nullptr) {
            DtInmueble dt = *resultado;
            delete resultado;
            delete it;
            return dt;
        }

        it->next();

    }

    delete it;

    throw std::invalid_argument("No existe una publicacion con el ID ingresado.");

}