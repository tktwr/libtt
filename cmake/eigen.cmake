#-------------------------------------------------
# eigen
#-------------------------------------------------

set(EIGEN $ENV{MY_OPT}/eigen)

include_directories(${EIGEN})

message(STATUS "EIGEN=${EIGEN}")
