# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(syst)

target_sources(app PRIVATE src/main.c)

if(CONFIG_CPP)
  # When building for C++, force C++ compilation
  set_source_files_properties(src/main.c PROPERTIES LANGUAGE CXX)
endif()
