cmake_minimum_required(VERSION 2.6)
project(UnitTest)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../src/utilities/data.json DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/utilities)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../src/utilities/simulations.json DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/utilities)
add_custom_target(run ./runTests)

#file(GLOB client_source ${CMAKE_CURRENT_SOURCE_DIR}/../src/client/*.cpp.o)
#file(GLOB client_header ${CMAKE_CURRENT_SOURCE_DIR}/client/*.h)
file(GLOB engine_source ${CMAKE_CURRENT_SOURCE_DIR}/../src/engine/*.cpp)
file(GLOB engine_header ${CMAKE_CURRENT_SOURCE_DIR}/../src/engine/*.h)
file(GLOB_RECURSE entity_source ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/*.cpp)
file(GLOB_RECURSE entity_header ${CMAKE_CURRENT_SOURCE_DIR}/../src/entity/*.h)
file(GLOB escalation_source ${CMAKE_CURRENT_SOURCE_DIR}/../src/escalation/*.cpp)
file(GLOB escalation_header ${CMAKE_CURRENT_SOURCE_DIR}/../src/escalation/*.h)
file(GLOB faction_source ${CMAKE_CURRENT_SOURCE_DIR}/../src/faction/*.cpp)
file(GLOB faction_header ${CMAKE_CURRENT_SOURCE_DIR}/../src/faction/*.h)
file(GLOB mobilization_source ${CMAKE_CURRENT_SOURCE_DIR}/../src/mobilization/*.cpp)
file(GLOB mobilization_header ${CMAKE_CURRENT_SOURCE_DIR}/../src/mobilization/*.h)
file(GLOB theatre_source ${CMAKE_CURRENT_SOURCE_DIR}/../src/theatre/*.cpp)
file(GLOB theatre_header ${CMAKE_CURRENT_SOURCE_DIR}/../src/theatre/*.h)
file(GLOB utilities_source ${CMAKE_CURRENT_SOURCE_DIR}/../src/utilities/*.cpp)
file(GLOB utilities_header ${CMAKE_CURRENT_SOURCE_DIR}/../src/utilities/*.h)
file(GLOB command_source ${CMAKE_CURRENT_SOURCE_DIR}/../src/war-commands/*.cpp)
file(GLOB command_header ${CMAKE_CURRENT_SOURCE_DIR}/../src/war-commands/*.h)
file(GLOB strategy_source ${CMAKE_CURRENT_SOURCE_DIR}/../src/war-strategy/*.cpp)
file(GLOB strategy_header ${CMAKE_CURRENT_SOURCE_DIR}/../src/war-strategy/*.h)
file(GLOB zone_source ${CMAKE_CURRENT_SOURCE_DIR}/../src/theatre/zone-factory/*.cpp)
file(GLOB zone_header ${CMAKE_CURRENT_SOURCE_DIR}/../src/theatre/zone-factory/*.h)

#configure_file(utilities ${CMAKE_CURRENT_BINARY_DIR}/../src/utilities/simulations.json COPYONLY)
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests 
    #Test files
    main.cpp 
    UnitTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/client/Client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/client/WarSocket.cpp
    #${client_source} ${client_header}
    ${engine_source} ${engine_header}
    ${entity_source} ${entity_header} 
    ${escalation_source} ${escalation_header}
    ${faction_source} ${faction_header}
    ${mobilization_source} ${mobilization_header}
    ${theatre_source} ${theatre_header}
    ${utilities_source} ${utilities_header}
    ${command_source} ${command_header}
    ${strategy_source} ${strategy_header}
    ${zone_source} ${zone_header}
)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
#target_link_libraries(
#    runTests 
#    
#    #client
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/client/CMakeFiles/client.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/client/CMakeFiles/mongoose.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/client/CMakeFiles/WarSocket.cpp.o
#    
#    #engine
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/engine/CMakeFiles/WarEngine.cpp.o
#    
#    #entity
#        #factory
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/factory/AirUnitFactory.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/factory/LandUnitFactory.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/factory/SeaUnitFactory.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/factory/UnitFactory.cpp.o
#        #product
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/AirUnit.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/AirUnitHeavy.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/AirUnitLight.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/AirUnitMedium.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/ArmedForce.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/Engineers.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/Entity.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/FieldHospital.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/LandUnit.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/LandUnitHeavy.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/LandUnitLight.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/LandUnitMedium.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/SeaUnit.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/SeaUnitHeavy.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/SeaUnitLight.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/SeaUnitMedium.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/SupportCompany.cpp.o
#        ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/entity/product/Unit.cpp.o
#        
#    #escalation
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/escalation/EarlyStage.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/escalation/Escalation.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/escalation/LateStage.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/escalation/MiddleStage.cpp.o
#
#    #faction
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/faction/Alliance.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/faction/Faction.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/faction/Country.cpp.o
#
#    #mobilization
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/mobilization/Mobilization.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/mobilization/PartialMobilization.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/mobilization/TotalMobilization.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/mobilization/WarEconomy.cpp.o
#    
#    #theatre
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/theatre/AirZone.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/theatre/LandZone.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/theatre/SeaZone.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/theatre/Theatre.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/theatre/Zone.cpp.o
#
#    #utilities
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/utilities/uuid.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/utilities/WarException.cpp.o
#
#    #war-commands
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-commands/LoadBattle.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-commands/LoadNextDay.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-commands/RetrieveSimulations.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-commands/SelectSimulation.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-commands/LoadPreviousDay.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-commands/LoadDay.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-commands/WarCommand.cpp.o
#
#
#    #war-strategy
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-strategy/AttackStrategy.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-strategy/CounterStrategy.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-strategy/PlanStrategy.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/war-strategy/WarStrategy.cpp.o
#
#    #zone-factory
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/zone-factory/AirZoneFactory.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/zone-factory/LandZoneFactory.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/zone-factory/SeaZoneFactory.cpp.o
#    ${CMAKE_CURRENT_SOURCE_DIR}/../src/build/zone-factory/ZoneFactory.cpp.o
#    
#)
