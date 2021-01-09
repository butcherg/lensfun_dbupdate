cmake_minimum_required (VERSION 2.8.11)
project (LENSFUN_DBUPDATE)

find_package(CURL REQUIRED)
find_package(LibArchive REQUIRED)

add_library (lensfun_dbupdate lensfun_dbupdate.cpp)
target_include_directories (lensfun_dbupdate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lensfun_dbupdate ${CURL_LIBRARIES} ${LibArchive_LIBRARIES})
include_directories(${CURL_INCLUDE_DIR} ${LIBARCHIVE_INCLUDE_DIR})


add_executable (dbupdate dbupdate.cpp)
target_link_libraries (dbupdate LINK_PUBLIC lensfun_dbupdate)
#include_directories(${LENSFUN_INCLUDE_DIR})
