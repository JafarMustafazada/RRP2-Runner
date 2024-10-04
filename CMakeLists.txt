cmake_minimum_required (VERSION 3.10)
project (RRP2Runner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the toolchain for Emscripten
if(EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_HTML=1")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s FILESYSTEM=0")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s MODULARIZE=1")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s ASSERTIONS")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORT_NAME=\"MyModule\"")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s NO_EXIT_RUNTIME=1")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --no-entry")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s MINIMAL_RUNTIME=1")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_FUNCTIONS=\"['_loadgame', '_getconfig', '_savegame', '_getgeneral', '_getpmax', '_getplayer', '_creategame', '_gameio']\"")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s EXPORTED_RUNTIME_METHODS=\"['cwrap', 'ccall']\"")
    #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --external-wasm")
    set(CMAKE_EXECUTABLE_SUFFIX ".js") # This will generate an HTML output by default
endif()
  
 

### external cmake #######################################################################
add_subdirectory ("src/RRP2")



# Specify include directories
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(RRP2Runner ${MY_SOURCES})


### external library ######################################################################
target_link_libraries(RRP2Runner PRIVATE RRP2)



# Specify output directories (optional)
set_target_properties(RRP2Runner PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    OUTPUT_NAME "RRP2Runner"
)