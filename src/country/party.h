#ifndef PARTY_H
#define PARTY_H

#include <iostream>
#include <vector>

class Unit;
class Alliance;
class Theatre; //

class Party {
    protected:              //made protected to allow country to access variable
        std::string name;
		std::vector<Unit*> units;
        int resourceCount;
        
        std::vector<Theatre*> theatres; //
        
    public:
        Party(std::string name);
        std::string getName();
        void setName(std::string name);
        virtual int getResourceCount() = 0;
        virtual int setResourceCount(int resourceCount) = 0;
        virtual Alliance* getAlliance() = 0;

        
        //Turn
        virtual void makeDecision() = 0;   //
        virtual void chooseStrategy() = 0; //
    
};

#endif // PARTY_H