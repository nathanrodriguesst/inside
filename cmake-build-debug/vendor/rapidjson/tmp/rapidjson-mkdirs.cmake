# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson"
  "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-build"
  "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson"
  "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/tmp"
  "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-stamp"
  "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src"
  "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/myazuk/Development/inside/cmake-build-debug/vendor/rapidjson/src/rapidjson-stamp${cfgdir}") # cfgdir has leading slash
endif()
