#include "TipoTecho.h"
#include <string>

std::string tipoTechoToString(TipoTecho tipo) {
    switch (tipo) {
        case TipoTecho::TECHO_PLANO:
            return "Techo plano";
        case TipoTecho::TECHO_A_DOS_AGUAS:
            return "Techo a dos aguas";
        case TipoTecho::TECHO_LIVIANO:
            return "Techo liviano";
        default:
            return "Desconocido";
    }
}
