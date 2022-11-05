cmake_minimum_required(VERSION 2.6)
project(UnitTest)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
#configure_file(utilities ${CMAKE_CURRENT_BINARY_DIR}/../src/utilities/simulations.json COPYONLY)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests 
    #Test files
    main.cpp 
    UnitTest.cpp

    #${CMAKE_CURRENT_SOURCE_DIR}/../src//client/client.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src//client/mongoose.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src//client/WarSocket.cpp

    ##engine
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/engine/WarEngine.cpp

    ##entity
    #    #factory
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/factory/AirUnitFactory.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/factory/LandUnitFactory.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/factory/SeaUnitFactory.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/factory/UnitFactory.cpp
    #    #product
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/AirUnit.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/AirUnitHeavy.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/AirUnitLight.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/AirUnitMedium.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/ArmedForce.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/Engineers.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/Entity.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/FieldHospital.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/LandUnit.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/LandUnitHeavy.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/LandUnitLight.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/LandUnitMedium.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/SeaUnit.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/SeaUnitHeavy.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/SeaUnitLight.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/SeaUnitMedium.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/SupportCompany.cpp
    #    ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/product/Unit.cpp

    ##escalation
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/escalation/EarlyStage.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/escalation/Escalation.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/escalation/LateStage.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/escalation/MiddleStage.cpp

    ##faction
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/faction/Alliance.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/faction/Faction.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/faction/Country.cpp

    ##mobilization
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/mobilization/Mobilization.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/mobilization/PartialMobilization.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/mobilization/TotalMobilization.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/mobilization/WarEconomy.cpp

    ##theatre
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/theatre/AirZone.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/theatre/LandZone.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/theatre/SeaZone.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/theatre/Theatre.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/theatre/Zone.cpp

    ##utilities
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/utilities/uuid.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/utilities/WarException.cpp

    ##war-strategy
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/war-strategy/AttackStrategy.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/war-strategy/CounterStrategy.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/war-strategy/PlanStrategy.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/war-strategy/WarStrategy.cpp

    ##zone-factory
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/zone-factory/AirZoneFactory.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/zone-factory/LandZoneFactory.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/zone-factory/SeaZoneFactory.cpp
    #${CMAKE_CURRENT_SOURCE_DIR}/../src/zone-factory/ZoneFactory.cpp


    
)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
target_link_libraries(
    runTests 
    
    #client
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/client/client.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/client/mongoose.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/client/WarSocket.cpp.o
    
    #engine
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/engine/WarEngine.cpp.o
    
    #entity
        #factory
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/factory/AirUnitFactory.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/factory/LandUnitFactory.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/factory/SeaUnitFactory.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/factory/UnitFactory.cpp.o
        #product
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/AirUnit.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/AirUnitHeavy.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/AirUnitLight.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/AirUnitMedium.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/ArmedForce.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/Engineers.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/Entity.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/FieldHospital.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/LandUnit.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/LandUnitHeavy.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/LandUnitLight.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/LandUnitMedium.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/SeaUnit.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/SeaUnitHeavy.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/SeaUnitLight.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/SeaUnitMedium.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/SupportCompany.cpp.o
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/Unit.cpp.o
        
    #escalation
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/escalation/EarlyStage.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/escalation/Escalation.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/escalation/LateStage.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/escalation/MiddleStage.cpp.o

    #faction
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/faction/Alliance.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/faction/Faction.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/faction/Country.cpp.o

    #mobilization
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/mobilization/Mobilization.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/mobilization/PartialMobilization.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/mobilization/TotalMobilization.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/mobilization/WarEconomy.cpp.o
    
    #theatre
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/theatre/AirZone.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/theatre/LandZone.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/theatre/SeaZone.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/theatre/Theatre.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/theatre/Zone.cpp.o

    #utilities
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/utilities/uuid.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/utilities/WarException.cpp.o

    #war-commands
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-commands/LoadBattle.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-commands/LoadNextDay.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-commands/RetrieveSimulations.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-commands/SelectSimulation.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-commands/WarCommand.cpp.o


    #war-strategy
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-strategy/AttackStrategy.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-strategy/CounterStrategy.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-strategy/PlanStrategy.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-strategy/WarStrategy.cpp.o

    #zone-factory
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/zone-factory/AirZoneFactory.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/zone-factory/LandZoneFactory.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/zone-factory/SeaZoneFactory.cpp.o
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/zone-factory/ZoneFactory.cpp.o
    
)
