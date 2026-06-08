#include "DataFiltro.h"


DataFiltro::DataFiltro(const DtInmobiliaria &datainm, const DtPublicacion &datapub)
    : datosinm(datainm), datospub(datapub) {}


DataFiltro::~DataFiltro() {}

DtInmobiliaria DataFiltro::getDatosInmobiliaria() const {
    return this->datosinm;
}

DtPublicacion DataFiltro::getDatosPublicacion() const {
    return this->datospub;
}