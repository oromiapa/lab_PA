#include "Factory.h"
#include "Sistema.h" // Solo aquí se conoce la clase concreta [10]

Factory* Factory::instancia = nullptr;

Factory::Factory() {}

Factory* Factory::getInstancia() {
    if (instancia == nullptr)
        instancia = new Factory();
    return instancia;
}

ISistema* Factory::getSistema() {

}