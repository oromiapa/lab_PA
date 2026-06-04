#include <iostream>
#include <stdexcept>

// Se incluyen los DataTypes necesarios para los parámetros
#include "./DataTypes/DtDireccion.h"
#include "./DataTypes/DtFecha.h"
#include "./DataTypes/TipoTecho.h"
#include "./DataTypes/DtPropietario.h"

// Se incluyen las interfaces de las colecciones para poder iterar
#include "./ICollection/interfaces/ICollection.h"
#include "./ICollection/interfaces/IIterator.h"

// Se incluye la Factory para acceder al sistema de forma correcta
#include "Factory.h"
#include "ISistema.h"

int main() {
    std::cout << "========== INICIANDO PRUEBAS DEL SISTEMA ==========" << std::endl;

    // 1. Obtener la interfaz del sistema a través de la Fábrica (corregido)
    ISistema* sys = Factory::getInstancia()->getSistema();
    std::cout << "[OK] Sistema instanciado correctamente a traves de la Factory." << std::endl;

    // 2. Definir datos de prueba para los DataTypes
    DtDireccion dirCasa("Av. Siempreviva", 742, "Springfield");
    DtDireccion dirApto("18 de Julio", 1234, "Montevideo");
    DtDireccion dirInmo("Sarandi", 555, "San Jose");
    DtFecha fechaConstruccion(15, 5, 2010);

    // 3. Prueba de Alta de Clientes y validación de excepciones
    std::cout << "\n--- Probando Alta de Clientes ---" << std::endl;
    try {
        std::cout << "Intentando registrar a 'juan99'..." << std::endl;
        sys->altaCliente("juan99", "Juan Perez", "juan@mail.com", "pass123", "Perez", "1.234.567-8");
        std::cout << "[OK] Cliente 'juan99' registrado con exito." << std::endl;

        // Intentamos registrar al mismo usuario para forzar la excepcion std::invalid_argument
        std::cout << "Intentando registrar a 'juan99' de nuevo (debe fallar)..." << std::endl;
        sys->altaCliente("juan99", "Juan Distinto", "juan2@mail.com", "otra", "Gomez", "8.765.432-1");
    } 
    catch (const std::invalid_argument& e) {
        std::cout << "[CONTROLADO] Excepcion capturada con exito: " << e.what() << std::endl;
    } 
    catch (...) {
        std::cout << "[ERROR] Se produjo un error inesperado al dar de alta el cliente." << std::endl;
    }

    // 4. Prueba de Alta de Propietarios
    std::cout << "\n--- Probando Alta de Propietarios ---" << std::endl;
    try {
        std::cout << "Registrando al propietario 'maria_prop'..." << std::endl;
        sys->altaPropietario("maria_prop", "Maria Lopez", "maria@mail.com", "secret456", "099123456", 12345678);
        std::cout << "[OK] Propietario 'maria_prop' registrado." << std::endl;
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] No se pudo registrar al propietario: " << e.what() << std::endl;
    }

    // 5. Prueba de Alta de Inmobiliarias
    std::cout << "\n--- Probando Alta de Inmobiliarias ---" << std::endl;
    try {
        std::cout << "Registrando Inmobiliaria 'InmoCentral'..." << std::endl;
        sys->altaInmobiliaria("inmo_central", "Inmo Central", "contacto@inmo.com", "admin789", dirInmo, "29001234", "www.inmocentral.com");
        std::cout << "[OK] Inmobiliaria 'InmoCentral' registrada." << std::endl;
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] No se pudo registrar la inmobiliaria: " << e.what() << std::endl;
    }

    // 6. Prueba de Creación de Inmuebles (Casas y Apartamentos)
    std::cout << "\n--- Probando Creacion de Inmuebles ---" << std::endl;
    try {
        std::cout << "Creando una Casa..." << std::endl;
        // Cambia 'Tejas' por un enum valido de tu TipoTecho.h si es necesario
        sys->crearCasa(dirCasa, fechaConstruccion, 120.5f, false, TipoTecho::TECHO_A_DOS_AGUAS); 
        std::cout << "[OK] Casa creada exitosamente. Id Autoincremental actual: " << sys->autoincremental() << std::endl;

        std::cout << "Creando un Apartamento..." << std::endl;
        sys->crearApartamento(dirApto, fechaConstruccion, 65.0f, 4, true, 4500.0f);
        std::cout << "[OK] Apartamento creado exitosamente. Id Autoincremental actual: " << sys->autoincremental() << std::endl;
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] Fallo la creacion de inmuebles: " << e.what() << std::endl;
    }

    // 7. Prueba de Listar Propietarios (Recorrido e impresion real)
    std::cout << "\n--- Probando Listar Propietarios ---" << std::endl;
    try {
        ICollection* lista = sys->listarPropietarios();
        if (lista != nullptr) {
            std::cout << "[OK] Se obtuvo la lista de propietarios. Iterando elementos:" << std::endl;
            std::cout << "--------------------------------------------------" << std::endl;

            IIterator* it = lista->getIterator();
            int contador = 1;

            while (it->hasCurrent()) {
                // Hacemos el cast al DataType que tu funcion almacena de forma dinamica
                DtPropietario* dtProp = (DtPropietario*)it->getCurrent();

                std::cout << " Propietario #" << contador << std::endl;
                std::cout << "   - Nickname: " << dtProp->getNickname() << std::endl;
                std::cout << "   - Nombre:   " << dtProp->getNombre() << std::endl;
                std::cout << "--------------------------------------------------" << std::endl;

                contador++;
                it->next(); // Avanzar al siguiente
            }

            delete it; // Evitamos fugas de memoria del iterador del main

            if (contador == 1) {
                std::cout << " (La lista de propietarios esta vacia actualmente)" << std::endl;
            }

            // Opcional: Si necesitas liberar la memoria de la lista y sus dts,
            // deberias hacerlo aqui antes de terminar, pero para la prueba basica sirve.

        } else {
            std::cout << "[WARN] La lista devuelta es un puntero nulo." << std::endl;
        }
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] Error al listar propietarios: " << e.what() << std::endl;
    }

    std::cout << "\n========== FIN DE LAS PRUEBAS DEL SISTEMA ==========" << std::endl;
    return 0;
}