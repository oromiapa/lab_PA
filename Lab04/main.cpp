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

    // 2. Definir datos de prueba globales
    DtDireccion dirCasa("Av. Siempreviva", 742, "Springfield");
    DtDireccion dirApto("18 de Julio", 1234, "Montevideo");
    DtDireccion dirInmo("Sarandi", 555, "San Jose");
    DtFecha fechaConstruccion(15, 5, 2010);

    // 3. CASO DE USO: Alta de Propietario con sus Inmuebles asociados
    std::cout << "\n--- [Caso de Uso] Alta de Propietario e Inmuebles ---" << std::endl;
    try {
        std::cout << "Registrando al propietario 'maria_prop'..." << std::endl;
        sys->altaPropietario("maria_prop", "Maria Lopez", "maria@mail.com", "secret456", "099123456", 12345678);
        std::cout << "[OK] Propietario 'maria_prop' registrado en el sistema." << std::endl;

        // Simulando el bucle loop: "Mientras el propietario decida agregar inmuebles"
        std::cout << "  -> Creando y vinculando Casa a 'maria_prop'..." << std::endl;
        sys->crearCasa(dirCasa, fechaConstruccion, 120.5f, false, TipoTecho::TECHO_A_DOS_AGUAS); 

        std::cout << "  -> Creando y vinculando Apartamento a 'maria_prop'..." << std::endl;
        sys->crearApartamento(dirApto, fechaConstruccion, 65.0f, 4, true, 4500.0f);

        // Cerramos la sección de alta del propietario para liberar el puntero intermedio
        sys->finalizarAltaPropietario();
        std::cout << "[OK] Registro de inmuebles finalizado. Memoria intermedia liberada." << std::endl;
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] Fallo el alta del propietario o sus inmuebles: " << e.what() << std::endl;
    }

    // 4. CASO DE USO: Alta Inmobiliaria y Vinculación Automatizada
    std::cout << "\n--- [Caso de Uso] Alta Inmobiliaria y Vinculacion de Propietarios ---" << std::endl;
    try {
        std::cout << "Registrando Inmobiliaria 'InmoCentral'..." << std::endl;
        sys->altaInmobiliaria("inmo_central", "Inmo Central", "contacto@inmo.com", "admin789", dirInmo, "29001234", "www.inmocentral.com");
        std::cout << "[OK] Inmobiliaria 'InmoCentral' dada de alta." << std::endl;

        // Simulando el bucle del diagrama: El administrador selecciona un propietario de la lista
        std::cout << "\n[Bucle UI] Vinculando propietario 'maria_prop' a la nueva inmobiliaria..." << std::endl;
        std::cout << "(Internamente la Inmobiliaria tomara los inmuebles de 'maria_prop' usando getNumeroID())" << std::endl;
        
        sys->vincularPropietario("maria_prop");
        std::cout << "[OK] Vinculacion exitosa. Los inmuebles pasaron a la coleccion de la Inmobiliaria." << std::endl;

        // Prueba de control de errores
        std::cout << "\n[Bucle UI] Intentando vincular un propietario inexistente 'pepe_fantasma'..." << std::endl;
        try {
            sys->vincularPropietario("pepe_fantasma");
        } catch (const std::invalid_argument& e) {
            std::cout << "[CONTROLADO] Excepcion correcta capturada: " << e.what() << std::endl;
        }

        // Finalización del caso de uso de la inmobiliaria
        sys->finalizarAltaInmobiliaria();
        std::cout << "[OK] Caso de uso de Alta Inmobiliaria cerrado de forma segura." << std::endl;
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] Ocurrio un problema con la inmobiliaria: " << e.what() << std::endl;
    }

    // 5. Prueba de control de Clientes independientes
    std::cout << "\n--- Probando Alta de Clientes de forma independiente ---" << std::endl;
    try {
        sys->altaCliente("juan99", "Juan Perez", "juan@mail.com", "pass123", "Perez", "1.234.567-8");
        std::cout << "[OK] Cliente 'juan99' registrado con exito." << std::endl;
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] Fallo el alta de cliente: " << e.what() << std::endl;
    }

    // 6. Verificación: Listar Propietarios Globales del Sistema
    std::cout << "\n--- Verificacion Final: Listar Propietarios ---" << std::endl;
    try {
        ICollection* lista = sys->listarPropietarios();
        if (lista != nullptr) {
            std::cout << "[OK] Lista obtenida. Imprimiendo registros:" << std::endl;
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
                delete dtProp; // Limpieza del DataType dinámico devuelto
                it->next(); 
            }

            delete it;    // Limpieza del iterador
            delete lista; // Limpieza de la lista contenedora

            if (contador == 1) {
                std::cout << " (No hay propietarios registrados)" << std::endl;
            }
        }
    } 
    catch (const std::exception& e) {
        std::cout << "[ERROR] Fallo el listado final: " << e.what() << std::endl;
    }

    std::cout << "\n========== FIN DE LAS PRUEBAS DEL SISTEMA ==========" << std::endl;
    return 0;
}