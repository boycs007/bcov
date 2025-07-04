cmake_minimum_required(VERSION 3.10)
project(bcov LANGUAGES C CXX)

add_library(bcov STATIC bcov.cpp)
target_include_directories(bcov PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

install(FILES bcov.h DESTINATION include)

install(TARGETS bcov
    EXPORT bcovTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(EXPORT bcovTargets
    FILE bcovTargets.cmake
    NAMESPACE bcov::
    DESTINATION lib/cmake/bcov
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/bcovConfigVersion.cmake"
    VERSION 1.0.0
    COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/bcovConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/bcovConfig.cmake"
    INSTALL_DESTINATION lib/cmake/bcov
)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/bcovConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/bcovConfigVersion.cmake"
    DESTINATION lib/cmake/bcov
)