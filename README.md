# Compile time string hashes

This repository contains C++ functions to generate hashes at compile time. There is also an algorithm to generate a perfect hash from a known list of integers. 
The perfect hash will be in a reduced range, e.g. 100 values might be represented from 0 to 150. This can be used to create a static lookup array instead of using a
hash map. In the end, it should result in a better performance, as a lookup is then just a offset into an array.

In the future, the Code will be converted to a C++20 module. C++20 will allow a nicer interface, since constexpr functions got expanded.
Also, once C++20 is here a version for a minimal perfect hash function for strings at compile time will be added.

# List of compile time algorithms

  - Insertion sort
  - Radix sort
  - Murmurhash 2
  - FNV1A
  - Hashed string view
  - Perfect hash generator

# Build

There are no external dependencies. Just call CMake to generate a build solution for your favorite build system. 
The library is a header only implementation and makes heavy use of templates and constant expressions.
This means you will need a compiler that supports C++17. 


# Tests

Tests can be enabled via HASHES_BUILD_TESTS and use the testing framework google test.
The sources of google test will be downloaded from github via FetchContent.

All functionality will be covered by tests. For bugfixes, first a test reproducing the issue
will be created, then the bug will be fixed.

# Benchmarks

Benchmarks use google benchmark. They can be enabled if HASHES_BUILD_BENCHMAKRS is set to ON during the call to CMake.
The sources of google benchmark will be downloaded from github via FetchContent.
Be aware that a benchmark may get optimized away, so take care to use arguments that are not knwon at compile time.

## Results

The radix sort is always faster than std::sort. But how fast depends on your array size and the number of bits
per pass (due to cache associativity of your machine). 
Here is a table with benchmarks sorting 64 usigned integers run on my machine:

| Elements | Radix sort(2) | Radix sort(4) | Radix sort(8) | std::sort |
|:--------:|:-------------:|:-------------:|:-------------:|:---------:|
| 512      |         8.7us |         8.1us |         6.3us | 14.8us    |
| 4096     |        69.7us |        75.8us |        56.5us | 152us     |
| 262'144  |         4.9ms |         7.1ms |           5ms | 14.3ms    |
| 16'777'216 |       332ms |         548ms |         517ms | 1.24s     |
| 1'073'741'824 |    21.7s |         42.0s |         45.5s | 99.2s     |


A "bad" perfect hash can be generated in O(N).
A perfect hash with a load of 50% can be generated in O(N3), but this is a work in progress.

# License
The software is licensed under the Mozilla Public License 2.0. See LICENSE.txt for the full text of the license.
 