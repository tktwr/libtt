#-------------------------------------------------
# OpenCV
#-------------------------------------------------

if(NOT DEFINED OpenCV_DIR)
    if(ANDROID)
        set(OpenCV_DIR ${OPT_DIR}/opencv-4.1.0-android/sdk/native/jni)
    elseif(MSVC)
        set(OpenCV_DIR ${OPT_DIR}/opencv-4.1.0/build)
    endif()
endif()

message(STATUS "OpenCV_DIR=${OpenCV_DIR}")

if(MSVC)
  file(GLOB OpenCV_DLLS ${OpenCV_DIR}/x64/vc15/bin/*.dll)
endif()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "OpenCV_VERSION=${OpenCV_VERSION}")
message(STATUS "OpenCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS=${OpenCV_LIBS}")
message(STATUS "OpenCV_SHARED=${OpenCV_SHARED}")
message(STATUS "OpenCV_STATIC=${OpenCV_STATIC}")
message(STATUS "OpenCV_CUDA=${OpenCV_CUDA}")
message(STATUS "OpenCV_DLLS=${OpenCV_DLLS}")
