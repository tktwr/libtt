#-------------------------------------------------
# cmdline
#-------------------------------------------------

set(CMDLINE $ENV{MY_OPT}/cmdline)

include_directories(${CMDLINE})

message(STATUS "CMDLINE=${CMDLINE}")
