cmake_minimum_required(VERSION 3.2)
project(WarSimulator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) 

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/utilities/simulations.json DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/build/utilities)

add_custom_target(run ./main)
add_custom_target(dev ./main dev)

file(GLOB client_source ${CMAKE_CURRENT_SOURCE_DIR}/src/client/*.cpp)
file(GLOB client_header ${CMAKE_CURRENT_SOURCE_DIR}/src/client/*.h)
file(GLOB engine_source ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.cpp)
file(GLOB engine_header ${CMAKE_CURRENT_SOURCE_DIR}/src/engine/*.h)
file(GLOB_RECURSE entity_source ${CMAKE_CURRENT_SOURCE_DIR}/src/entity/*.cpp)
file(GLOB_RECURSE entity_header ${CMAKE_CURRENT_SOURCE_DIR}/src/entity/*.h)
file(GLOB escalation_source ${CMAKE_CURRENT_SOURCE_DIR}/src/escalation/*.cpp)
file(GLOB escalation_header ${CMAKE_CURRENT_SOURCE_DIR}/src/escalation/*.h)
file(GLOB faction_source ${CMAKE_CURRENT_SOURCE_DIR}/src/faction/*.cpp)
file(GLOB faction_header ${CMAKE_CURRENT_SOURCE_DIR}/src/faction/*.h)
file(GLOB mobilization_source ${CMAKE_CURRENT_SOURCE_DIR}/src/mobilization/*.cpp)
file(GLOB mobilization_header ${CMAKE_CURRENT_SOURCE_DIR}/src/mobilization/*.h)
file(GLOB theatre_source ${CMAKE_CURRENT_SOURCE_DIR}/src/theatre/*.cpp)
file(GLOB theatre_header ${CMAKE_CURRENT_SOURCE_DIR}/src/theatre/*.h)
file(GLOB utilities_source ${CMAKE_CURRENT_SOURCE_DIR}/src/utilities/*.cpp)
file(GLOB utilities_header ${CMAKE_CURRENT_SOURCE_DIR}/src/utilities/*.h)
file(GLOB command_source ${CMAKE_CURRENT_SOURCE_DIR}/src/war-commands/*.cpp)
file(GLOB command_header ${CMAKE_CURRENT_SOURCE_DIR}/src/war-commands/*.h)
file(GLOB strategy_source ${CMAKE_CURRENT_SOURCE_DIR}/src/war-strategy/*.cpp)
file(GLOB strategy_header ${CMAKE_CURRENT_SOURCE_DIR}/src/war-strategy/*.h)
file(GLOB zone_source ${CMAKE_CURRENT_SOURCE_DIR}/src/theatre/zone-factory/*.cpp)
file(GLOB zone_header ${CMAKE_CURRENT_SOURCE_DIR}/src/theatre/zone-factory/*.h)
 
add_executable(main 
    ${client_source} ${client_header}
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