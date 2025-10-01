cmake_minimum_required(VERSION 3.5)
project(todo_backend)

# -----------------------------------------------------------------------------
# If you include the drogon source code locally in your project, use this method
# to add drogon (in the appropriate location), and uncomment
# find_package and the Drogon::Drogon links
# add_subdirectory(../third_party/drogon) 
# target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
# -----------------------------------------------------------------------------

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)
if (NOT "${CMAKE_CXX_STANDARD}" STREQUAL "")
    # Do nothing
elseif (HAS_ANY AND HAS_STRING_VIEW AND HAS_COROUTINE)
    set(CMAKE_CXX_STANDARD 20)
elseif (HAS_ANY AND HAS_STRING_VIEW)
    set(CMAKE_CXX_STANDARD 17)
else ()
    set(CMAKE_CXX_STANDARD 14)
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find Drogon
find_package(Drogon REQUIRED)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Source files
set(SRC_FILES
    main.cc
)

##########
# https://github.com/Thalhammer/jwt-cpp
# project config.cmake installs onto wrong dir
# had to be linked locally
add_subdirectory(external/jwt-cpp)
##########

##########
# https://github.com/trusch/libbcrypt
# project doesn't have config.cmake file
# linking locally is easier
add_subdirectory(external/libbcrypt)
##########

# Сначала собираем все исходные файлы
# Controllers
aux_source_directory(controllers CTL_SRC)
aux_source_directory(controllers/views CTL_SRC)
aux_source_directory(controllers/api/v1 CTL_SRC)
aux_source_directory(controllers/api/v2 CTL_SRC)

# Dto
aux_source_directory(dtos DTO_SRC)

# Helpers
aux_source_directory(helpers HELPER_SRC)

# Utils
aux_source_directory(utils UTIL_SRC)

# Validators
aux_source_directory(validators VALIDATOR_SRC)

# Plugins
aux_source_directory(plugins PLUGIN_SRC)

# Models
aux_source_directory(models MODEL_SRC)

# Filters
aux_source_directory(filters FILTER_SRC)

# Добавляем все исходные файлы в SRC_FILES
list(APPEND SRC_FILES
    ${CTL_SRC}
    ${DTO_SRC}
    ${HELPER_SRC}
    ${UTIL_SRC}
    ${VALIDATOR_SRC}
    ${FILTER_SRC}
    ${PLUGIN_SRC}
    ${MODEL_SRC}
)

# Create executable - ПОСЛЕ СБОРА ВСЕХ ИСХОДНЫХ ФАЙЛОВ
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Настройка views
drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
                    ${CMAKE_CURRENT_BINARY_DIR})
# use the following line to create views with namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE)
# use the following line to create views with namespace CHANGE_ME prefixed
# and path namespaces.
# drogon_create_views(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/views
#                     ${CMAKE_CURRENT_BINARY_DIR} TRUE CHANGE_ME)

target_sources(${PROJECT_NAME}
               PRIVATE
               ${SRC_DIR}
               ${CTL_SRC}
               ${FILTER_SRC}
               ${PLUGIN_SRC}
               ${MODEL_SRC}
               ${VALIDATOR_SRC}
               ${UTIL_SRC}
               ${HELPER_SRC}
               ${DTO_SRC})

# Директории include
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
                                   ${CMAKE_CURRENT_SOURCE_DIR}/models
                                   ${CMAKE_CURRENT_SOURCE_DIR}/controllers
                                   ${CMAKE_CURRENT_SOURCE_DIR}/dtos
                                   ${CMAKE_CURRENT_SOURCE_DIR}/helpers
                                   ${CMAKE_CURRENT_SOURCE_DIR}/utils
                                   ${CMAKE_CURRENT_SOURCE_DIR}/validators
                                   ${CMAKE_CURRENT_SOURCE_DIR}/plugins
                                   ${CMAKE_CURRENT_SOURCE_DIR}/filters)

# Link libraries - ТЕПЕРЬ ПОСЛЕ add_executable
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon jwt-cpp bcrypt)

# TODO: clean cmake