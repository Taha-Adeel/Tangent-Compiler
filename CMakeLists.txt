cmake_minimum_required(VERSION 3.0.0)
project(Tangent VERSION 0.1.0)

find_package(FLEX REQUIRED)
if (FLEX_FOUND)
    add_custom_command(
        OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.c
        SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/lexer.l
        COMMAND ${FLEX_EXECUTABLE}
            --outfile=${CMAKE_CURRENT_SOURCE_DIR}/lexer.c
            ${CMAKE_CURRENT_SOURCE_DIR}/lexer.l
        COMMENT "Generating lex"
    )
endif(FLEX_FOUND)
find_package(BISON REQUIRED)

# flex_target(lexer ${SOURCE_PATH}/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lex.cpp)
# bison_target(bison ${SOURCE_PATH}/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
# ADD_FLEX_BISON_DEPENDENCY(lexer bison)
# include_directories(${CMAKE_CURRENT_BINARY_DIR})

include(CTest)
enable_testing()

add_executable(Tangent main.cpp)
add_executable(Tgt src/lexer.c)
# add_executable(Tgt main.cpp
# ${FLEX_lexer_OUTPUTS}
# ${BISON_parser_OUTPUTS})
# target_link_libraries(Tgt ${FLEX_LIBRARIES})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
