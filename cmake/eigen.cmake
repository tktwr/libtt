#-------------------------------------------------
# eigen
#-------------------------------------------------

set(EIGEN $ENV{MY_OPT_WIN}/eigen)

include_directories(${EIGEN})

message(STATUS "EIGEN=${EIGEN}")
