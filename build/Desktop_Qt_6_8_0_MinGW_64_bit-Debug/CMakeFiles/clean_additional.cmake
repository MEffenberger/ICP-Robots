# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\ICP_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ICP_autogen.dir\\ParseCache.txt"
  "ICP_autogen"
  )
endif()
