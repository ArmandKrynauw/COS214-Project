#include <stdexcept>
#include "../src/client/client.h"
#include "../src/engine/WarEngine.h"
#include "gtest/gtest.h"

namespace {

    //Testing Theatre.cpp    

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
            PlanStrategy *s = new PlanStrategy("Test");
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


    //Testing Warengine

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
            FAIL();
        }
        if(data["duration"] != 5){
            FAIL();
        }
        if(data["day"] != 1){
            FAIL();
        }
        if(data["numberOfCountries"] != 2){
            FAIL();
        }
        if(data["numberOfAlliances"] != 0){
            FAIL();
        }
        SUCCEED();
    }

    //Testing getCountryStats
    TEST(GetSimulation, TestGetCountryStats){
        json data = WarEngine::instance()->getCountryStats();
        if(data["data"][0]["name"] != "Germany"){
            FAIL();
        }
        if(data["data"][0]["resources"] != 40){
            FAIL();
        }
        if(data["data"][0]["totalUnits"] != 3){
            FAIL();
        }
        if(data["data"][1]["name"] != "America"){
            FAIL();
        }
        if(data["data"][1]["resources"] != 70){
            FAIL();
        }
        if(data["data"][1]["totalUnits"] != 4){
            FAIL();
        }
        SUCCEED();
    }

    //Testing getAllianceStats
    TEST(GetSimulation, TestGetAllianceStats){
        json data = WarEngine::instance()->getAllianceStats();
        if(data["data"] != "null"){
            FAIL();
        }
        SUCCEED();
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
}
