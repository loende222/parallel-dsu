get_filename_component(LIB_INCLUDE_PATH ".." ABSOLUTE)
get_filename_component(LIB_PATH "." ABSOLUTE)


# Find all headers and sources
file(GLOB_RECURSE LIB_CXX_SOURCES ${LIB_PATH}/*.cpp)
file(GLOB_RECURSE LIB_HEADERS ${LIB_PATH}/*.h)
# Create library
add_library(parallel-dsu-lib STATIC ${LIB_CXX_SOURCES} ${LIB_HEADERS})
# Set include path for library
target_include_directories(parallel-dsu-lib PUBLIC ${LIB_INCLUDE_PATH})
