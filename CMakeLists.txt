cmake_minimum_required(VERSION 3.16)
project(SolarSystem VERSION 1.0 LANGUAGES CXX)

# Enable C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include vcpkg
if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/external/vcpkg/scripts/buildsystems/vcpkg.cmake CACHE STRING "")
endif ()

# Find required packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm CONFIG REQUIRED)

# Source files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/include/*.h)

# Executable target
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Define asset path
target_compile_definitions(${PROJECT_NAME} PRIVATE ASSET_PATH="${CMAKE_SOURCE_DIR}/assets")

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL GLUT::GLUT GLEW::GLEW glm::glm)

# Copy assets to the build directory
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

# Platform-specific settings
if (WIN32)
    # Windows-specific settings
    target_compile_definitions(${PROJECT_NAME} PRIVATE _WIN32)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
    set_target_properties(${PROJECT_NAME} PROPERTIES
            VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
            VS_GLOBAL_KEYWORD "Win32Proj"
    )
elseif (APPLE)
    # macOS-specific settings
    target_compile_definitions(${PROJECT_NAME} PRIVATE __APPLE__)
    target_compile_options(${PROJECT_NAME} PRIVATE -Wno-deprecated-declarations)
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++20")
    set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            XCODE_ATTRIBUTE_ENABLE_TESTABILITY "YES"
            XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "Apple Development"
    )
else ()
    # Linux and other Unix-like systems
    target_compile_definitions(${PROJECT_NAME} PRIVATE __LINUX__)
    if (CMAKE_GENERATOR STREQUAL "Unix Makefiles")
        set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    endif ()
endif ()

# Installation settings
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# Packaging settings
include(CPack)
set(CPACK_PACKAGE_NAME "SolarSystem")
set(CPACK_PACKAGE_VERSION "1.0")
set(CPACK_GENERATOR "ZIP;TGZ")
set(CPACK_SOURCE_GENERATOR "ZIP;TGZ")
set(CPACK_SOURCE_IGNORE_FILES "/build/;/external/;.git/;${CPACK_SOURCE_IGNORE_FILES}")