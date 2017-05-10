cmake_minimum_required(VERSION 3.0)

#-----------#
# Configure
#-----------#

project(Crash2D VERSION 0.1.0 LANGUAGES CXX)
set(API_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
set(BUILD_VERSION "${PROJECT_VERSION}")

#-----------#
#    Env
#-----------#

include_directories(include/)

set(SOURCES "src/circle.cpp" "src/polygon.cpp" "src/segment.cpp" "src/transformation.cpp" "src/collision.cpp" "src/projection.cpp" "src/shape_impl.cpp" "src/vector2.cpp")
set(HEADERS "include/Crash2D.hpp" "include/collision.hpp" "include/projection.hpp" "include/shape.hpp" "include/transformation.hpp" "include/circle.hpp" "include/polygon.hpp" "include/segment.hpp" "include/shape_impl.hpp" "include/vector2.hpp")

configure_file("Crash2DConfig.cmake.in" "Crash2DConfig.cmake" @ONLY)
include(CMakePackageConfigHelpers)
write_basic_package_version_file("Crash2DConfigVersion.cmake" COMPATIBILITY SameMajorVersion)

#-----------#
#   Build
#-----------#

list(APPEND targets Crash2D)

add_library(Crash2D STATIC ${SOURCES})
set_target_properties(Crash2D PROPERTIES VERSION ${BUILD_VERSION})

set_property(TARGET Crash2D
             APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
             $<INSTALL_INTERFACE:include>)
             
#-----------#
#  Install
#-----------#

include(GNUInstallDirs)

install(TARGETS ${targets}
        EXPORT tmx_exports
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${HEADERS} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Crash2D)

install(EXPORT tmx_exports
        FILE "Crash2DExports.cmake"
        DESTINATION "lib/cmake/Crash2D")
install(FILES "${CMAKE_BINARY_DIR}/Crash2DConfig.cmake" "${CMAKE_BINARY_DIR}/Crash2DConfigVersion.cmake"
        DESTINATION "lib/cmake/Crash2D")
