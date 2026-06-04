#include "Factory.h"
#include "Sistema.h" 

Factory* Factory::instancia = nullptr;

// Modificamos el constructor para inicializar el puntero del sistema
Factory::Factory() {
    this->sys = nullptr;
}

Factory* Factory::getInstancia() {
    if (instancia == nullptr)
        instancia = new Factory();
    return instancia;
}

// Implementamos la lógica de creación del sistema
ISistema* Factory::getSistema() {
    if (this->sys == nullptr) {
        this->sys = new Sistema(); // Aquí se crea el objeto real por única vez
    }
    return this->sys;
}