cmake_minimum_required (VERSION 3.10)
project (RRP2)



# Define the RRP2 interface library (header-only)
#add_library(RRP2 INTERFACE)

# Specify include directories so that your project can find all RRP2 headers
#target_include_directories(RRP2 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Glob all .lib files in the lib directory
#file(GLOB LIB_FILES "${CMAKE_CURRENT_SOURCE_DIR}/libin/*.lib")
#target_link_libraries(RRP2 INTERFACE ${LIB_FILES})




# Add the library target
file(GLOB CPP_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(RRP2 STATIC ${CPP_FILES})

# Specify include directories if needed
target_include_directories(RRP2 
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
)



# Specify output directories for static libraries
set_target_properties(RRP2 PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/libin"
    OUTPUT_NAME "RRP2" # Replace with your desired output name
)