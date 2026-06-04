#ifndef TIPOTECHO_H
#define TIPOTECHO_H

enum class TipoTecho {
    TECHO_PLANO,
    TECHO_A_DOS_AGUAS,
    TECHO_LIVIANO    
};

inline std::string tipoTechoToString(TipoTecho techo) {
    switch(techo) {
        case TipoTecho::TECHO_PLANO:       return "Plano";
        case TipoTecho::TECHO_A_DOS_AGUAS: return "A dos aguas";
        case TipoTecho::TECHO_LIVIANO:    return "Liviano";
        default:                           return "Desconocido";
    }
}

#endif