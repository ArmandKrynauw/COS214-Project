#include <stdexcept>
#include "../src/client/client.h"
#include "../src/engine/WarEngine.h"
#include "gtest/gtest.h"

namespace {



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
    //Testing the create of valid type
    TEST(GenerateUnit, TestCreationOfValidUnit){
        Entity *entity = WarEngine::instance()->generateUnit("Germany", "LightLandUnit", "NA");
        EXPECT_EQ(entity->getType(), "land");
    }


    //Testing loadNextBattleDay
    //Testing loadNextBattleDay before battle day results 
    TEST(LoadNextBattleDay, TestLoadBeforeResult){
        try{
            Client::instance()->loadNextBattleDay();
            FAIL();
        }
        catch(WarException &err){
            EXPECT_EQ(err.what(), std::string("Load battle day results before loading next battle day"));
        }
        catch(...){
            FAIL();
        }
    }

    //Test loadNextBattleDay after battle day results
    //TEST(LoadNextBattleDay, TestLoadAfterResult){
    //    try{
    //        Client::instance()->loadDayResults();
    //        Client::instance()->loadNextBattleDay();
    //        SUCCEED();
    //    }
    //    catch(...){
    //        FAIL();
    //    }
    //}



}