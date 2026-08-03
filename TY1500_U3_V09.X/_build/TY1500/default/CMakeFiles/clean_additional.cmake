# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "D:\\yiming\\00work\\TY1500_U3_V06.X\\out\\TY1500\\default.cmf"
  "D:\\yiming\\00work\\TY1500_U3_V06.X\\out\\TY1500\\default.hex"
  "D:\\yiming\\00work\\TY1500_U3_V06.X\\out\\TY1500\\default.hxl"
  "D:\\yiming\\00work\\TY1500_U3_V06.X\\out\\TY1500\\default.mum"
  "D:\\yiming\\00work\\TY1500_U3_V06.X\\out\\TY1500\\default.o"
  "D:\\yiming\\00work\\TY1500_U3_V06.X\\out\\TY1500\\default.sdb"
  "D:\\yiming\\00work\\TY1500_U3_V06.X\\out\\TY1500\\default.sym"
  )
endif()
