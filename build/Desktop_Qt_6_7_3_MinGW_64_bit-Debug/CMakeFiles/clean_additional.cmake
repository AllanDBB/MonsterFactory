# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\MonsterFactoryGuiQt2_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\MonsterFactoryGuiQt2_autogen.dir\\ParseCache.txt"
  "MonsterFactoryGuiQt2_autogen"
  )
endif()
