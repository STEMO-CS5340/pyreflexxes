cmake_minimum_required(VERSION 3.1)
project(pyreflexxes)

find_package(pybind11 2.2 REQUIRED)

include_directories(
  ./ReflexxesTypeII/include
)

add_custom_target(ReflexxesTypeII
  ${CMAKE_MAKE_PROGRAM}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/ReflexxesTypeII
)

pybind11_add_module(rml_type_ii
  src/rmlerror.cpp
  src/pyreflexxes.cpp
  src/pyreflexxes_extra.cpp
)

target_compile_definitions(rml_type_ii PRIVATE "RML_TYPE_II")

if(UNIX)
  # target_link_libraries(rml_type_ii PRIVATE ${CMAKE_SOURCE_DIR}/ReflexxesTypeII/Linux/x64/release/lib/static/libReflexxesTypeII.a)
  target_link_libraries(rml_type_ii PRIVATE ${CMAKE_SOURCE_DIR}/ReflexxesTypeII/Linux/x64/release/lib/shared/libReflexxesTypeII.so)
  elseif(APPLE)
  target_link_libraries(rml_type_ii PRIVATE ${CMAKE_SOURCE_DIR}/ReflexxesTypeII/MacOS/x64/release/lib/libReflexxesTypeII.a)
elseif(WIN32)
  message(WARNING "Not Implemented in Cmake Yet!")
endif()
