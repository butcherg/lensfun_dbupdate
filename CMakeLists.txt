cmake_minimum_required (VERSION 2.8.11)
project (LENSFUN_DBUPDATE)
include(FindPkgConfig)

add_definitions(-DCURL_STATICLIB)

macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()

#find_package(CURL REQUIRED)
#find_package(LibArchive REQUIRED)

pkg_check_modules(CURL REQUIRED libcurl)
pkg_check_modules(LibArchive REQUIRED libarchive)

add_library (lensfun_dbupdate lensfun_dbupdate.cpp)
target_include_directories (lensfun_dbupdate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(lensfun_dbupdate ${LibArchive_LIBRARIES} ${CURL_LIBRARIES})
include_directories(${CURL_INCLUDE_DIR} ${LibArchive_INCLUDE_DIR})


add_executable (dbupdate dbupdate.cpp lensfun_dbupdate.cpp)
target_link_libraries (dbupdate LINK_PUBLIC lensfun_dbupdate ${LibArchive_LIBRARIES} ${LibArchive_LDFLAGS} ${CURL_LIBRARIES} ${CURL_LDFLAGS})
include_directories(${CURL_INCLUDE_DIR} ${LibArchive_INCLUDE_DIR})

#print_all_variables()
message(STATUS "${LibArchive_LDFLAGS} ${CURL_LDFLAGS}")
