#include "Tipo.h"
#include <string>

std::string tipoToString(Tipo tipo) {
    switch (tipo) {
        case Tipo::CASA:
            return "Casa";
        case Tipo::APARTAMENTO:
            return "Apartamento";
        case Tipo::CASA_Y_APARTAMENTO:
            return "Casa y apartamento";
        default:
            return "Desconocido";
    }
}
