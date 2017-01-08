if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	add_definitions(-DLINUX_BUILD -D_GNU_SOURCE)
	set(DEFAULT_PREFIX /usr)
	set(CPP_LIBRARY_DIR "lib")

	if (CMAKE_SIZEOF_VOID_P EQUAL 8)
		message(STATUS "64 bits compiler detected")
		set(APP_BUILD_PLATFORM 64)
		set(APP_BUILD_PLATFORM_NAME "x86_64")
	else (CMAKE_SIZEOF_VOID_P EQUAL 8)
		message(STATUS "32 bits compiler detected")
		set(APP_BUILD_PLATFORM 32)
		set(APP_BUILD_PLATFORM_NAME "i686")
	endif (CMAKE_SIZEOF_VOID_P EQUAL 8)

	if(EXISTS "/etc/redhat-release")
			add_definitions(-D__RH_DISTRO__)
			if (CMAKE_SIZEOF_VOID_P EQUAL 8)
				set(CPP_LIBRARY_DIR "lib64")
			endif (CMAKE_SIZEOF_VOID_P EQUAL 8)
	endif(EXISTS "/etc/redhat-release")

	if(EXISTS "/etc/debian_version")
			add_definitions(-D__DEBIAN_DISTRO__)
	endif(EXISTS "/etc/debian_version")

	if(EXISTS "/etc/ubuntu-release")
			add_definitions(-D__UBUNTU_DISTRO__)
	endif(EXISTS "/etc/ubuntu-release")
else (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	message(STATUS "Compiling for " ${CMAKE_SYSTEM_NAME} "")
	set(CPP_LIBRARY_DIR "lib")

	if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
		set(CMAKE_MACOSX_RPATH TRUE)
		set(DEFAULT_PREFIX /usr/local)

		add_definitions(-D__OSX__)
		include_directories(/usr/local/include)
		link_directories(/usr/local/lib)
	endif (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
endif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/target/lib)
set (CTEST_BINARY_DIRECTORY ${CMAKE_BINARY_DIR}/target/tests/bin)

find_path(JSON_INCLUDE_DIR json.h
          PATH_SUFFIXES json json-c)

find_library(JSON_LIB NAMES json json-c)
link_libraries(${JSON_LIB})

message(STATUS "JSON headers found at ${JSON_INCLUDE_DIR}")
message(STATUS "JSON library found at ${JSON_LIB}")

find_path(GRU_INCLUDE_DIR common/gru_base.h
          PATH_SUFFIXES gru-0)
find_library(GRU_LIB NAMES gru-0)

message(STATUS "GRU headers found at ${GRU_INCLUDE_DIR}")
message(STATUS "GRU library found at ${GRU_LIB}")

find_path(CURL_INCLUDE_DIR curl/curl.h)
find_library(CURL_LIB NAMES curl)

message(STATUS "CURL headers found at ${CURL_INCLUDE_DIR}")
message(STATUS "CURL library found at ${CURL_LIB}")
