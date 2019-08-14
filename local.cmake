
set(OPT_DIR Z:/opt)

if(ANDROID)
    set(OpenCV_DIR Z:/opt/opencv-4.1.0-android/sdk/native/jni)
elseif(MSVC)
    set(OpenCV_DIR Z:/opt/opencv-4.1.0/build)
endif()
