# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-stamp/rapidjson-gitclone-lastrun.txt" AND EXISTS "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-stamp/rapidjson-gitinfo.txt" AND
  "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-stamp/rapidjson-gitclone-lastrun.txt" IS_NEWER_THAN "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-stamp/rapidjson-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-stamp/rapidjson-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: '/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "/usr/bin/git"
            clone --no-checkout --config "advice.detachedHead=false" "https://github.com/Tencent/rapidjson.git" "rapidjson"
    WORKING_DIRECTORY "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/Tencent/rapidjson.git'")
endif()

execute_process(
  COMMAND "/usr/bin/git"
          checkout "f54b0e47a08782a6131cc3d60f94d038fa6e0a51" --
  WORKING_DIRECTORY "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'f54b0e47a08782a6131cc3d60f94d038fa6e0a51'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "/usr/bin/git" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: '/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-stamp/rapidjson-gitinfo.txt" "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-stamp/rapidjson-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: '/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-stamp/rapidjson-gitclone-lastrun.txt'")
endif()
