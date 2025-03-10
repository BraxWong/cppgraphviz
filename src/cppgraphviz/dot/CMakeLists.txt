#include(AICxxProject)

add_library(dot_ObjLib OBJECT)

target_sources(dot_ObjLib
  PRIVATE
    Attribute.cpp
    Attribute.hpp
    AttributeList.cpp
    AttributeList.hpp
    DotID.cpp
    DotID.hpp
    Edge.cpp
    Edge.hpp
    Graph.cpp
    Graph.hpp
    Port.cpp
    Port.hpp
    TableNode.cpp
    TableNode.hpp
    GraphItem.hpp
    Node.hpp
)

# Required include search-paths.
get_target_property(CWDS_INTERFACE_INCLUDE_DIRECTORIES AICxx::cwds INTERFACE_INCLUDE_DIRECTORIES)
target_include_directories(dot_ObjLib
  PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}"
    "${CWDS_INTERFACE_INCLUDE_DIRECTORIES}" # For sys.h and debug.h.
)

# Make sure we compile with debug support.
target_link_libraries(dot_ObjLib PRIVATE ${AICXX_OBJECTS_LIST})

# Create an ALIAS target.
add_library(CppGraphviz::dot ALIAS dot_ObjLib)
