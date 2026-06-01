#ifndef DTINMOBILIARIA_H
#define DTINMOBILIARIA_H

#include <string>

class DtInmobiliaria {
private:
    std::string nickname;
    std::string nombre;

public:
    // Constructores
    DtInmobiliaria();
    DtInmobiliaria(const std::string& nickname, const std::string& nombre);

    // Getters según UML
    std::string getNickname() const;
    std::string getNombre() const;
};

#endif
