cmake_minimum_required(VERSION 3.5)
project(todo_backend)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Drogon
find_package(Drogon REQUIRED)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Source files
set(SRC_FILES
    main.cc
)

# Create executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

aux_source_directory(controllers CTL_SRC)

target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC})

# Link Drogon
target_link_libraries(${PROJECT_NAME} Drogon::Drogon)