#include <stdexcept>
#include "../src/client/client.h"
#include "../src/engine/WarEngine.h"
#include "gtest/gtest.h"

namespace {

    //============Testing Theatre============

    //Testing removeEntity in Theatre.cpp
    //Testing the remove of a faction that does not exist
    TEST(RemoveTheatreEntity, TestRemoveInvalidFaction){
        try{
            Theatre *t = WarEngine::instance()->TestTheatre();
            t->removeEntity("test", "seaZone", "0");
            FAIL();
        }
        catch (WarException &err){
            EXPECT_EQ(err.what(), std::string("Faction not found."));
        }
        catch (...){
            FAIL();
        }
    }

    //Testing the remove of an entity that does not exist
    TEST(RemoveTheatreEntity, TestRemoveInvalidEntity){
        try{
            Theatre *t = WarEngine::instance()->TestTheatre();
            t->removeEntity("Germany", "seaZone", "0");
            FAIL();
        }
        catch (WarException &err){
            EXPECT_EQ(err.what(), std::string("Entity not found."));
        }
        catch (...){
            FAIL();
        }
    }

    //Testing the remove of a valid entity
    TEST(RemoveTheatreEntity, TestRemoveValidEntity){
        Entity *entity = WarEngine::instance()->generateUnit("Germany", "LightLandUnit", "NA");
        Theatre *t = WarEngine::instance()->TestTheatre();
        t->addEntity("Germany", entity);
        EXPECT_EQ(t->removeEntity("Germany", "land", entity->getId())->getName(), entity->getName());
    }

    //Testing changeStrategy for null strategy
    TEST(ChangeFactionStrategy, TestChangeOfNULLStrategy){
        try{
            Theatre *t = WarEngine::instance()->TestTheatre();
            t->changeStrategy("Germany", NULL);
            FAIL();
        }
        catch(WarException &err){
            EXPECT_EQ(err.what(), std::string("NULL Strategy"));
        }
        catch(...){
            FAIL();
        }
    }

    //Testing changeStrategy for valid strategy
    TEST(ChangeFactionStrategy, TestChangeOfValidStrategy){
        try{
            AttackStrategy *s = new AttackStrategy("Test");
            Theatre *t = WarEngine::instance()->TestTheatre();
            t->changeStrategy("Germany", s);
            SUCCEED();
        }
        catch(...){
            FAIL();
        }
        
    }

    //Testing checkForFaction
    TEST(ChangeFactionStrategy, TestCheckForValidFaction){
        try{
            Theatre *t = WarEngine::instance()->TestTheatre();
            EXPECT_TRUE(t->checkForFaction("Germany"));
        }
        catch(...){
            FAIL();
        }
    }


    TEST(ChangeFactionStrategy, TestCheckForInValidFaction){
        try{
            Theatre *t = WarEngine::instance()->TestTheatre();
            EXPECT_FALSE(t->checkForFaction("Invalid"));
        }
        catch(...){
            FAIL();
        }
    }


    //============Testing Warengine============

    //Testing generateUnit 
    //Testing the create of type that does not exist
    TEST(GenerateUnit, TestCreationOfInvalidUnit){
        try{
            WarEngine::instance()->generateUnit("Germany", "Invalid", "NA");
            FAIL();
        }
        catch(WarException &err){
            EXPECT_EQ(err.what(), std::string("Could not generate Unit."));
        }
        catch(...){
            FAIL();
        }
    }
    //Testing the create of valid unit type
    TEST(GenerateUnit, TestCreationOfValidUnit){
        Entity *entity = WarEngine::instance()->generateUnit("Germany", "LightLandUnit", "NA");
        EXPECT_EQ(entity->getType(), "land");
    }

    //Testing that the simulation is loaded in correctly
    TEST(GetSimulation, TestGetEngineStats){
        json data = WarEngine::instance()->getEngineStats();
        if(data["stage"] != "Early Stage"){
            FAIL() << "stage";
        }
        if(data["duration"] != 5){
            FAIL() << "duration";
        }
        if(data["day"] != 1){
            FAIL() << "day";
        }
        if(data["numberOfCountries"] != 2){
            FAIL() << "numberOfCountries";
        }
        if(data["numberOfAlliances"] != 0){
            FAIL() << "numberOfAlliances";
        }
        SUCCEED();
    }

    //Testing getCountryStats
    TEST(GetSimulation, TestGetCountryStats){
        json data = WarEngine::instance()->getCountryStats();
        if(data["data"][0]["name"] != "America"){
            FAIL() << "Name of country 0";
        }
        if(data["data"][0]["resources"] != 40){
            FAIL() << "Resource count for America";
        }
        if(data["data"][0]["totalUnits"] != 5){
            FAIL() << "Unit count for country America";
        }
        if(data["data"][1]["name"] != "Germany"){
            FAIL() << "Name of country 1";
        }
        if(data["data"][1]["resources"] != 70){
            FAIL() << "Resource count for country Germany";
        }
        if(data["data"][1]["totalUnits"] != 5){
            FAIL() << "Unit count for country Germany";
        }
        SUCCEED();
    }

    //Testing getAllianceStats
    TEST(GetSimulation, TestGetAllianceStats){
        json data = WarEngine::instance()->getAllianceStats();
        if(data["data"].size() != 0){
            FAIL() << "Alliance bigger that 0";
        }
        SUCCEED();
    }

    //Testing getOverallUnits
    TEST(GetSimulation, TestGetOverAllUnits){
        json data = WarEngine::instance()->getOverallUnits();
        std::string AmericaArr[5] = {"A-10", "USS Nebraska (SSBN-739)", "Destroyer", "Destroyer", "HMMWV"};
        std::string GermanyArr[5] = {"Eurofighter Typhoon", "Baden-Württemberg class", "Baden-Württemberg class", "Baden-Württemberg class", "Leopard 2A7"};
        for(int i = 0; i < data["data"][0]["units"].size(); i++){
            if(data["data"][0]["units"][i]["name"] != AmericaArr[i]){
                FAIL() << "America " << i;
            }
        }
        for(int i = 0; i < data["data"][1]["units"].size(); i++){
            if(data["data"][1]["units"][i]["name"] != GermanyArr[i]){
                FAIL() << "Germany " << i;
            }
        }
    }

    //Testing getTheatreStats and check that simulations is correct on day 1
    TEST(GetSimulation, TestGetTheatreStats){
        json data = WarEngine::instance()->getTheatreStats();
        //Testing that the right theatre names is in the correct coordinate
        if(data["data"][0]["name"] != "Sicily"){
            FAIL() << "Sicily 0";
        }
        if(data["data"][1]["name"] != "Tunisia"){
            FAIL() << "Tunisia 1";
        }
        if(data["data"][2]["name"] != "Normandy"){
            FAIL() << "Normandy 2";
        }
        if(data["data"][3]["name"] != "Netherlands"){
            FAIL() << "Netherlands 3";
        }
        if(data["data"][4]["name"] != "Belgium"){
            FAIL() << "Belgium 4";
        }
        if(data["data"][5]["name"] != "Ruhr"){
            FAIL() << "Ruhr 5";
        }
        if(data["data"][6]["name"] != "Paris"){
            FAIL() << "Paris 6";
        }
        if(data["data"][7]["name"] != "Alsace-Lorraine"){
            FAIL() << "Alsace-Lorraine 7";
        }
        if(data["data"][8]["name"] != "Italy"){
            FAIL() << "Italy 8";
        }

        //Testing the power of each country in theatre
        //0-0
        if(data["data"][0]["data"][0]["landPower"] != 10){
            FAIL() << "America Power 0-0";
        }
        if(data["data"][0]["data"][1]["landPower"] != 20){
            FAIL() << "Germany Power 0-0";
        }
        //0-1
        if(data["data"][1]["data"][0]["seaPower"] != 10){
            FAIL() << "America Power 0-1";
        }
        if(data["data"][1]["data"][1]["seaPower"] != 5){
            FAIL() << "Germany Power 0-1";
        }
        //0-2
        if(data["data"][2]["data"][0]["seaPower"] != 10){
            FAIL() << "America Power 0-2";
        }
        if(data["data"][2]["data"][1]["seaPower"] != 5){
            FAIL() << "Germany Power 0-2";
        }
        //1-0
        if(data["data"][3]["data"].size() != 0){
            FAIL() << "Netherlands data 1-0";
        }
        //1-1
        if(data["data"][4]["data"][0]["airPower"] != 10){
            FAIL() << "America Power 1-1";
        }
        if(data["data"][4]["data"][1]["airPower"] != 10){
            FAIL() << "Germany Power 1-1";
        }
        //1-2
        if(data["data"][5]["data"].size() != 0){
            FAIL() << "Ruhr data 1-2";
        }
        //2-0
        if(data["data"][6]["data"].size() != 0){
            FAIL() << "Paris data 2-0";
        }
        //2-1
        if(data["data"][7]["data"].size() != 0){
            FAIL() << "Alsace data 2-1";
        }
        //2-2
        if(data["data"][8]["data"][0]["seaPower"] != 20){
            FAIL() << "America Power 2-2";
        }
        if(data["data"][8]["data"][1]["seaPower"] != 5){
            FAIL() << "Germany Power 2-2";
        }
        SUCCEED();
    }
    
    //Testing getStrategies
    TEST(GetSimulation, TestGetStrategies){
        json data = WarEngine::instance()->getStrategies();
        //America
        if(data["data"][0]["theatres"][0]["strategy"] != "Plan Strategy" ||
            data["data"][0]["theatres"][1]["strategy"] != "Attack Strategy" || 
            data["data"][0]["theatres"][2]["strategy"] != "Counter Strategy"){
                FAIL() << "America strategies";
        }
        //Germany
        if(data["data"][1]["theatres"][0]["strategy"] != "Attack Strategy" ||
            data["data"][1]["theatres"][1]["strategy"] != "Counter Strategy" ||
            data["data"][1]["theatres"][2]["strategy"] != "Plan Strategy"){
                FAIL() << "Germany Strategies";
        }
        SUCCEED();
    }

    //Testing getMobilization
    TEST(GetSimulation, TestGetMobilization){

        json data = WarEngine::instance()->getMobilization();

        if(data["data"][0]["mobilization"] != "Partial" || data["data"][1]["mobilization"] != "Partial"){
            FAIL() << "Get Mobilization";
        }


    }

    //Testing getResearch
    TEST(GetSimulation, TestGetResearch){
        json data = WarEngine::instance()->getResearch();

        if(data["data"][0]["industryCurrent"] != 50){
            FAIL() << "America research";
        }
        if(data["data"][1]["industryCurrent"] != 50){
            FAIL() << "Germany research";
        }
    }




    //Testing loadNextBattleDay
    //Testing loadNextBattleDay before battle day results 
    TEST(LoadNextBattleDay, TestLoadBeforeResult){
        try{
            WarEngine::instance()->loadNextBattleDay();
            FAIL();
        }
        catch(WarException &err){
            EXPECT_EQ(err.what(), std::string("Load battle day results before loading next battle day"));
        }
        catch(...){
            FAIL();
        }
    }

    TEST(LoadNextBattleDay, TestLoadAfterResult){
        try{
            WarEngine::instance()->loadBattleDayResults();
            WarEngine::instance()->loadNextBattleDay();
            SUCCEED();
        }
        catch(...){
            FAIL() << "NextBattleDay";
        }

    }
}
