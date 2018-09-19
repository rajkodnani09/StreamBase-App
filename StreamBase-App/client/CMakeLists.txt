cmake_minimum_required ( VERSION 3.12 )

file ( GLOB SOURCES *.cpp *.hpp )

add_executable ( client ${SOURCES} )

set (Boost_USE_STATIC_LIBS ON) # enable dynamic linking
set (Boost_USE_MULTITHREAD ON)  # enable multithreading

find_package(Boost 1.68.0 REQUIRED COMPONENTS system thread iostreams serialization)
IF(Boost_FOUND)
  INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
  LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_IOSTREAMS_LIBRARY} ${Boost_SERIALIZATION_LIBRARY})

#include_directories ( ${Streamlabs_StreambaseApp}/directories_header )

target_link_libraries ( client ${USED_LIBS} )