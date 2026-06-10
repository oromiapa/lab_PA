#include "DtCasa.h"


 DtCasa::DtCasa(int id, const DtDireccion& dir, float sup, const DtFecha& fecha, bool propiedadHorizontal, TipoTecho techo)
        : DtInmueble(id, dir, sup, fecha), propiedadHorizontal(propiedadHorizontal), techo(techo) {}


bool DtCasa::getPropiedadHorizontal() const {
    return this->propiedadHorizontal ;
}
    
TipoTecho DtCasa::getTecho() const {
    return this->techo ;
}



