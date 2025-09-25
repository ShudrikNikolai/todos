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

# NOTE: temporarily set to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # -----------------------------------------------------------------------------
# # Run clang-tidy on normal build
# set(CMAKE_CXX_CLANG_TIDY clang-tidy)
# # Run run-clang-tidy python script as a custom command that uses
# # compile_commands.json and intentionally does not run during "ALL" build
# add_custom_target(lint-tidy)
# # add_custom_command(TARGET lint-tidy POST_BUILD COMMAND run-clang-tidy -header-filter='^.*(?:third_party).*')
# add_custom_command(TARGET lint-tidy POST_BUILD COMMAND
# 	run-clang-tidy -quiet controllers* util* test* > ../clang-tidy-out.txt &&
# 	cat ../clang-tidy-out.txt &&
# 	echo &&
# 	echo &&
# 	echo &&
# 	echo "-----------------------------------------------------------------------------" &&
# 	echo "See ./clang-tidy-out.txt for output" &&
# 	echo "-----------------------------------------------------------------------------" &&
# 	echo &&
# 	echo &&
# 	echo
# )
# # -----------------------------------------------------------------------------


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

# find_program(CLANG_FORMAT "clang-format")
# if(CLANG_FORMAT)
#     add_custom_target(format
#         COMMAND ${CLANG_FORMAT}
#         -style=file
#         -i
#         ${SOURCE_FILES}
#         COMMENT "Formatting source code..."
#     )
# endif()

# Link Drogon
target_link_libraries(${PROJECT_NAME} Drogon::Drogon)