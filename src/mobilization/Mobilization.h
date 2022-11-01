#ifndef MOBILIZATION_h
#define MOBILIZATION_h

#include <iostream>


class Mobilization {
    protected:

    std::string state;

    public:

        Mobilization(std::string state);

        void checkWarState(std::string state);
        /**
        * Provides the industryModifier of this state as a percentage
        * @return float : The industryModifier for this state.
        */
        virtual float getIndustryModifier() = 0;

        /**
        * Provides the NationalMoraleTick of this state as a negative integer
        * @return int : The NationalMorale for this state.
        */
        virtual int getNationalMoraleTick() = 0;

        /**
        * Specifies what state the current state is
        * @return string : The current state
        */
        virtual std::string getState() = 0;

        virtual ~Mobilization();
};

#endif
