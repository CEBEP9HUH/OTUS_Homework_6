cmake_minimum_required(VERSION 3.2)

# set var
set(INCLUDE ${CMAKE_BINARY_DIR}/../include)
set(SOURCE ${CMAKE_BINARY_DIR}/../src)
set(TESTS ${CMAKE_BINARY_DIR}/../tests)
set(PROJ_NAME infinite_matrix)
set(TESTS_NAME infinite_matrix_test)

# set version
if($ENV{TRAVIS_BUILD_NUMBER})
    project(${PROJ_NAME} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(${PROJ_NAME} VERSION 0.0.42)
endif()

configure_file(description.json.in description.json)

# packaging
#   GTest
find_package(GTest REQUIRED)
include_directories(
    ${INCLUDE}
    ${GTEST_INCLUDE_DIRS}
)  

# executables
add_executable(${PROJ_NAME} ${SOURCE}/main.cpp ${INCLUDE}/InfiniteMatrix2D.hpp)
add_executable(${TESTS_NAME} ${TESTS}/MatrixTest.cpp)

set_target_properties(
    ${PROJ_NAME} ${TESTS_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(
    ${TESTS_NAME} PRIVATE
    ${GTEST_LIBRARIES}
    pthread
)

# compillers
if(MSVC)
    target_compile_options(${PROJ_NAME} PRIVATE
        /W4
    )
    target_compile_options(${TESTS_NAME} PRIVATE
        /W4
    )
else()
    target_compile_options(${PROJ_NAME} PRIVATE
        -Wall -Wextra -Werror -pedantic
    )
    target_compile_options(${TESTS_NAME} PRIVATE
        -Wall -Wextra -Werror -pedantic
    )
endif()

# packaging
install(TARGETS ${PROJ_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

# testing
enable_testing()
add_test(${TESTS_NAME} ${TESTS_NAME})