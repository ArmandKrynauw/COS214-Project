#include "FieldHospital.h"

FieldHospital::FieldHospital(Entity* entity) : SupportCompany(entity){

}
    int  FieldHospital::getDamage(){
        return SupportCompany::getDamage();
    }
    int FieldHospital::getHP(){
        return SupportCompany::getHP()*1.25;
    }

    FieldHospital::~FieldHospital(){
        
    }