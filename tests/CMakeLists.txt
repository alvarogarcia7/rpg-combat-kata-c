cmake_minimum_required(VERSION 3.5)

# Unit tests

# enable CTest testing
enable_testing()

include(FetchContent)

FetchContent_Declare(
        cmocka
        GIT_REPOSITORY https://git.cryptomilk.org/projects/cmocka.git
        GIT_TAG        cmocka-1.1.5
        GIT_SHALLOW    1
)

set(WITH_STATIC_LIB ON CACHE BOOL "CMocka: Build with a static library" FORCE)
set(WITH_CMOCKERY_SUPPORT OFF CACHE BOOL "CMocka: Install a cmockery header" FORCE)
set(WITH_EXAMPLES OFF CACHE BOOL "CMocka: Build examples" FORCE)
set(UNIT_TESTING OFF CACHE BOOL "CMocka: Build with unit testing" FORCE)
set(PICKY_DEVELOPER OFF CACHE BOOL "CMocka: Build with picky developer flags" FORCE)

FetchContent_MakeAvailable(cmocka)

# Add a testing executable
add_executable(unit_tests
        test.c
        )
target_link_libraries(unit_tests
        PRIVATE
        prod_lib
        cmocka-static
        )

add_test(test_all
        unit_tests
        )

target_compile_features(unit_tests PRIVATE c_std_99)