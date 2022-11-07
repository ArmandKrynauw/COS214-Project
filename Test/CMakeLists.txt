cmake_minimum_required(VERSION 2.6)
project(UnitTest)
 
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

#get data files
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../src/utilities/simulations.json DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/utilities)
#add_custom_target(run ./runTests)

#get source files from src dir
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

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests 
    #Test files
    main.cpp 
    UnitTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/client/Client.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/client/WarSocket.cpp
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