# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/taylor/Documents/Flurdbop/pa6-RelativiBit/build/googletest-src"
  "/Users/taylor/Documents/Flurdbop/pa6-RelativiBit/build/googletest-build"
  "/Users/taylor/Documents/Flurdbop/pa6-RelativiBit/build/googletest-download/googletest-prefix"
  "/Users/taylor/Documents/Flurdbop/pa6-RelativiBit/build/googletest-download/googletest-prefix/tmp"
  "/Users/taylor/Documents/Flurdbop/pa6-RelativiBit/build/googletest-download/googletest-prefix/src/googletest-stamp"
  "/Users/taylor/Documents/Flurdbop/pa6-RelativiBit/build/googletest-download/googletest-prefix/src"
  "/Users/taylor/Documents/Flurdbop/pa6-RelativiBit/build/googletest-download/googletest-prefix/src/googletest-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/taylor/Documents/Flurdbop/pa6-RelativiBit/build/googletest-download/googletest-prefix/src/googletest-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/taylor/Documents/Flurdbop/pa6-RelativiBit/build/googletest-download/googletest-prefix/src/googletest-stamp${cfgdir}") # cfgdir has leading slash
endif()
