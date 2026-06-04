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

    // 1. Obtener la interfaz del sistema a través de la Fábrica
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
        
        std::cout << "Registrando un segundo propietario 'jose_prop' para pruebas de bucle..." << std::endl;
        sys->altaPropietario("jose_prop", "Jose Rodriguez", "jose@mail.com", "jose789", "099765432", 87654321);
        std::cout << "[OK] Propietario 'jose_prop' registrado." << std::endl;
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] No se pudo registrar al propietario: " << e.what() << std::endl;
    }

    // 5. Prueba de Alta de Inmobiliarias y Vinculación de Propietarios (Caso de Uso Integrado)
    std::cout << "\n--- Probando Caso de Uso: Alta Inmobiliaria y Vinculacion ---" << std::endl;
    try {
        std::cout << "Registrando Inmobiliaria 'InmoCentral' (Comienza el recuerdo en Sistema)..." << std::endl;
        sys->altaInmobiliaria("inmo_central", "Inmo Central", "contacto@inmo.com", "admin789", dirInmo, "29001234", "www.inmocentral.com");
        std::cout << "[OK] Inmobiliaria 'InmoCentral' registrada globalmente." << std::endl;

        // Simulando el bucle del diagrama de secuencia: "Mientras se desee agregar propietarios"
        std::cout << "\n[Bucle UI] Vinculando propietario 'maria_prop' a la inmobiliaria actual..." << std::endl;
        sys->vincularPropietario("maria_prop");
        std::cout << "[OK] 'maria_prop' vinculada exitosamente." << std::endl;

        std::cout << "[Bucle UI] Vinculando propietario 'jose_prop' a la inmobiliaria actual..." << std::endl;
        sys->vincularPropietario("jose_prop");
        std::cout << "[OK] 'jose_prop' vinculado exitosamente." << std::endl;

        // Intentamos un error de precondición (propietario inexistente)
        std::cout << "[Bucle UI] Intentando vincular un usuario inexistente 'fantasma' (debe fallar)..." << std::endl;
        try {
            sys->vincularPropietario("fantasma");
        } catch (const std::invalid_argument& e) {
            std::cout << "[CONTROLADO] Excepcion capturada con exito: " << e.what() << std::endl;
        }

        // Finalización del caso de uso según el diagrama de secuencia
        std::cout << "\nFinalizando Caso de Uso (Liberando memoria del sistema)..." << std::endl;
        sys->finalizarAltaInmobiliaria();
        std::cout << "[OK] Memoria intermedia del sistema limpia." << std::endl;

    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] Error critico en el proceso de la inmobiliaria: " << e.what() << std::endl;
    }

    // 6. Prueba de Creación de Inmuebles (Casas y Apartamentos)
    std::cout << "\n--- Probando Creacion de Inmuebles ---" << std::endl;
    try {
        std::cout << "Creando una Casa..." << std::endl;
        sys->crearCasa(dirCasa, fechaConstruccion, 120.5f, false, TipoTecho::TECHO_A_DOS_AGUAS); 
        std::cout << "[OK] Casa creada exitosamente." << std::endl;

        std::cout << "Creando un Apartamento..." << std::endl;
        sys->crearApartamento(dirApto, fechaConstruccion, 65.0f, 4, true, 4500.0f);
        std::cout << "[OK] Apartamento creado exitosamente." << std::endl;
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] Fallo la creacion de inmuebles: " << e.what() << std::endl;
    }

    // 7. Prueba de Listar Propietarios
    std::cout << "\n--- Probando Listar Propietarios ---" << std::endl;
    try {
        ICollection* lista = sys->listarPropietarios();
        if (lista != nullptr) {
            std::cout << "[OK] Se obtuvo la lista de propietarios globales. Iterando elementos:" << std::endl;
            std::cout << "--------------------------------------------------" << std::endl;

            IIterator* it = lista->getIterator();
            int contador = 1;

            while (it->hasCurrent()) {
                DtPropietario* dtProp = (DtPropietario*)it->getCurrent();

                std::cout << " Propietario #" << contador << std::endl;
                std::cout << "   - Nickname: " << dtProp->getNickname() << std::endl;
                std::cout << "   - Nombre:   " << dtProp->getNombre() << std::endl;
                std::cout << "--------------------------------------------------" << std::endl;

                contador++;
                
                // NOTA: Recuerda que los DtPropietario agregados dinámicamente en tu función
                // de listado deben borrarse para no perder memoria.
                delete dtProp; 
                it->next(); 
            }

            delete it;    // Liberamos el iterador de la lista
            delete lista; // Liberamos el contenedor de la lista de Data Types

            if (contador == 1) {
                std::cout << " (La lista de propietarios esta vacia actualmente)" << std::endl;
            }
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