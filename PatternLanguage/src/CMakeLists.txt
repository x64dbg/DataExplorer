add_library(PatternLanguage SHARED
    PatternLanguage.cpp
)
set_target_properties(PatternLanguage PROPERTIES
    OUTPUT_NAME "PatternLanguage"
    PREFIX ""
)
target_link_libraries(PatternLanguage PRIVATE
    ${NLOHMANN_JSON_LIBRARIES}
    libpl
    libpl-gen
    ${FMT_LIBRARIES}
)

#[[
# Link to x64dbg
set(PLUGINSDK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/pluginsdk)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    target_link_libraries(PatternLanguage PRIVATE ${PLUGINSDK_DIR}/x64bridge.lib)
else()
    target_link_libraries(PatternLanguage PRIVATE ${PLUGINSDK_DIR}/x32bridge.lib)
endif()
target_include_directories(PatternLanguage PRIVATE ${PLUGINSDK_DIR})
]]

add_executable(runner runner.cpp)
target_link_libraries(runner PRIVATE
    PatternLanguage
)