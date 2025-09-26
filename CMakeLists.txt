cmake_minimum_required(VERSION 3.5)
project(todo_backend)

# -----------------------------------------------------------------------------
# If you include the drogon source code locally in your project, use this method
# to add drogon (in the appropriate location), and uncomment
# find_package and the Drogon::Drogon links
# add_subdirectory(../third_party/drogon) 
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
# -----------------------------------------------------------------------------



# # Default to debug
# if(NOT CMAKE_BUILD_TYPE)
# 	set(CMAKE_BUILD_TYPE Debug)
# endif()

# NOTE: temporarily set to C++17
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

# Controllers
aux_source_directory(controllers CTL_SRC)
aux_source_directory(controllers/api/v1 CTL_SRC)
aux_source_directory(controllers/api/v2 CTL_SRC)


target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC})

# Link Drogon
target_link_libraries(${PROJECT_NAME} Drogon::Drogon)