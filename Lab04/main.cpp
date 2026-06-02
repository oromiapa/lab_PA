#include <iostream>
#include <string>
#include "Factory.h"
#include "ISistema.h"
#include "./ICollection/Interfaces/ICollection.h"
#include "./ICollection/Interfaces/IIterator.h"
#include "./DataTypes/DtPropietario.h"

int main() {
    // 1. Obtener la interfaz del sistema a través de la Fábrica
    Factory* Factory = Factory::getInstancia();
    ISistema* iSys = Factory->getSistema();

    try {
        // 2. Probar Alta de Propietario
        std::cout << "Registrando a Juan..." << std::endl;
        iSys->altaPropietario("juan99", "Juan Perez", "juan@mail.com", "pass123", "099123456", 12345);

        // 3. Probar Listar Propietarios
        std::cout << "Listado de Propietarios:" << std::endl;
        ICollection* lista = iSys->listarPropietarios();
        IIterator* it = lista->getIterator();
        
        while (it->hasCurrent()) {
            // Downcasting del ICollectible al DataType
            DtPropietario* dt = dynamic_cast<DtPropietario*>(it->getCurrent());
            if (dt) {
                std::cout << "- Nickname: " << dt->getNickname() << ", Nombre: " << dt->getNombre() << std::endl;
            }
            it->next();
        }

        // 4. Limpieza de memoria de la capa de presentación
        delete it;
        // IMPORTANTE: Al ser DataTypes devueltos en una colección nueva, 
        // la presentación debe borrar los elementos y la lista.
        // (Debes implementar una función auxiliar o borrar manual)
        delete lista; 

    } catch (std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // 5. Al finalizar, la destrucción de 'Factory' debería gatillar el destructor de 'Sistema'
    delete Factory; 

    return 0;
}