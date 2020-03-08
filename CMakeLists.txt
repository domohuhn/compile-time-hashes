# Copyright (C) 2020 by domohuhn
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

cmake_minimum_required(VERSION 3.14)

project(hashes)

option(HASHES_BUILD_TESTS "Build the tests for the hashes module" ON)
option(HASHES_BUILD_BENCHMAKRS "Build the benchmarks for the hashes module" ON)

include(FetchContent)

add_library(hashes
	${CMAKE_CURRENT_SOURCE_DIR}/include/hashes/config.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/hashes/fast_perfect_compressed_hash.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/hashes/perfect_compressed_hash.hpp
)

target_include_directories(hashes PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_compile_features(hashes
	PUBLIC cxx_std_17
)
set_target_properties(hashes PROPERTIES LINKER_LANGUAGE CXX)
add_library(domohuhn::hashes ALIAS hashes)

#
# Tests
#

if(HASHES_BUILD_TESTS)

	FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG release-1.10.0
	)

	FetchContent_GetProperties(googletest)
	if(NOT ${googletest_POPULATED})
		message(STATUS "Populating googletest...")
		FetchContent_Populate(googletest)
	endif()
  	add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

	if(TARGET gtest AND TARGET gtest_main)
		add_executable(test_hashes 
			tests/test_compressed_hash.cpp
			tests/test_fast_compressed_hash.cpp
			tests/test_fnv1a.cpp
			tests/test_murmur2.cpp
			tests/test_hashed_strings.cpp
			tests/test_main.cpp
		)

		target_link_libraries(test_hashes PRIVATE gtest gtest_main domohuhn::hashes)
		include(GoogleTest)
		gtest_discover_tests(test_hashes)
	endif()
endif()


#
# Benchmarks
#


if(HASHES_BUILD_BENCHMAKRS)
	FetchContent_Declare(
	googlebenchmark
	GIT_REPOSITORY https://github.com/google/benchmark.git
	GIT_TAG v1.5.0
	)

	FetchContent_GetProperties(googlebenchmark)
	if(NOT ${googlebenchmark_POPULATED})
		message(STATUS "Populating googlebenchmark...")
		FetchContent_Populate(googlebenchmark)
	endif()
  	add_subdirectory(${googlebenchmark_SOURCE_DIR} ${googlebenchmark_BINARY_DIR})

	if(TARGET benchmark)
		add_executable(bench_hashes 
			benchmark/bench_compressed_hash.cpp
			benchmark/bench_perfect_hash_generation.cpp
			benchmark/bench_hashes.cpp
			benchmark/bench_main.cpp
		)
		target_link_libraries(bench_hashes PRIVATE benchmark domohuhn::hashes)
	endif()

endif()


#
# Install
#

