#-------------------------------------------------
# nativefiledialog
#-------------------------------------------------

set(NFD ${OPT_DIR}/nativefiledialog/src)

include_directories(${NFD}/include)

set(NFD_SRCS
  ${NFD}/nfd_common.c
  ${NFD}/nfd_win.cpp
)

message(STATUS "NFD=${NFD}")
