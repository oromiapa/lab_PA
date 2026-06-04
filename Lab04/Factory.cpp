#include "Factory.h"
#include "Sistema.h" 

Factory* Factory::instancia = nullptr;

Factory::Factory() {
    this->sys = nullptr;
}

Factory* Factory::getInstancia() {
    if (instancia == nullptr)
        instancia = new Factory();
    return instancia;
}

ISistema* Factory::getSistema() {
    if (this->sys == nullptr) {
        this->sys = new Sistema(); 
    }
    return this->sys;
}