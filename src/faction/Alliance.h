#ifndef ALLIANCE_H
#define ALLIANCE_H

#include "Country.h"
#include "Faction.h"
/**
 * This class is the Composite of the Faction Composite Design Pattern Hierarchy. The alliance may store many countries
 * and alliances may join a greater alliance.
 */
class Alliance : public Faction {
    private:
        std::vector<Faction *> members;
    public:
        /**
         * Provides functionality to create an Alliance object.
         * 
         * @param name Alliance name
         */
        Alliance(std::string name);
        /**
         * Provides functionality to add a country to an alliance
         * @param country pointer to the country to be added
         */
        void addCountry(Country *country);
        /**
         * Provide functionality to remove a country from an alliance
         * 
         * @param country pointer to the country to be added
         */
        void removeCountry(Country *country);
        /**
         * Provides functionality to generate resources for each country in the alliance
         * 
         * @param theatreResource The amount of resources from theatres to divide among countries
         */
        void generateResources(int theatreResource) override;
        /**
         * Provides functionality to invest research into a research category
         * If the category that is invested in meets the goal of >= 500 points, the category is decreased by 500 points
         * and the alliance is given the appropriate advantage which is then provided to all the countries in the alliance.
         * 
         * @param researchPoints Total resources to research
         * @param category Category to invest
         */
        virtual void setResearch(int researchPoints, std::string category);
        /**
         * Provides functionality to get total research of a category
         * 
         * @param i The index of the research category
         * @return Total research of current category
         */
        virtual int getResearch(int i) override;
        /**
         * Provides functionality to reduce the research points by 500
         * 
         * @param index The index of the category for which to reduce the research points
         */
        virtual void resetResearch(int index) override;
        /**
         * Provides functionality to get members vector of an alliance
         * 
         * @return vector<Faction*> Vector of pointers to the faction in the alliance
         */
        std::vector<Faction*> getMembers();
        /**
         * Provides functionality to get the alliance the the current alliance is in if
         * it is in a greater alliance.
         * 
         * @return Alliance* Return if alliance is in a greater alliance
         * @return NULL Return if alliance is highest alliance and has no greater alliance
         */
        virtual Alliance *getAlliance() override;
        /**
         * Provides functionality to command each faction in the alliance to clear their casualties 
         * by calling clearCasualties()
         */
        virtual void clearCasualties() override;
        /**
         * Provides functionality to convert an alliance to JSON format. The object will have the alliance name
         * and an array of the countries that have joined the alliance.
         * (e.g. {"name": "Allies", "countries": ["America", "France"]})
         * 
         * @return json JSON object of an Alliance
         */
        json toJSON() ;
        /**
         * Provides functionality to destroy an Alliance object
         */
        virtual ~Alliance();
};

#endif  // ALLIANCE_H