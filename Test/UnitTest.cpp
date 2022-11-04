#include <stdexcept>
#include "../src/client/client.h"
#include "../src/engine/WarEngine.h"
#include "gtest/gtest.h"

namespace {

    TEST(AddTheatreEntity, TestRemoveNonexistentFaction){
        try{
            Theatre *t = WarEngine::instance()->getTheatre();
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

    TEST(AddTheatreEntity, TestRemoveNonexistentEntity){
        try{
            Theatre *t = WarEngine::instance()->getTheatre();
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

}