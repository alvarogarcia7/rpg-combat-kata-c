cmake_minimum_required(VERSION 3.5)

# Set the project name
project(project)

# Add an library for the example classes
add_library(prod_lib
        prod.c
        )


add_executable(prod
        main.c
        )
target_link_libraries(prod
        prod_lib
        )


add_subdirectory(tests)
