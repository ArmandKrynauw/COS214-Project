#ifndef ALLIANCE_H
#define ALLIANCE_H

#include "party.h"
#include "country.h"

class Alliance : public Party {
    private:
        std::vector<Party*> members;

    public:
		Alliance(std::string name);
        void addCountry(Country* country);
        void removeCountry(Country* country);
        virtual int getResourceCount() override;
        virtual int setResourceCount(int resourceCount) override;
        virtual Alliance* getAlliance() override;

        virtual void makeDecision() override;   //For each member in alliance call makeDecision()
        virtual void chooseStrategy() override; //For each member in alliance call chooseStrategy()

};

#endif // ALLIANCE_H