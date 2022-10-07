#ifndef COUNTRY_H
#define COUNTRY_H
#include "party.h"

class Country : public Party{

    public:
        Country(std::string name);
        virtual int getResourceCount() override;
        virtual int setResourceCount(int resourceCount) override;
        virtual Alliance* getAlliance() override;
        
        virtual void makeDecision() override;   //
        virtual void chooseStrategy() override; //

};

#endif // COUNTRY_H