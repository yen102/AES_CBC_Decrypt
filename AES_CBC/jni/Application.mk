APP_PLATFORM := android-17

#we want to use exceptions
APP_CPPFLAGS += -fexceptions

APP_CPPFLAGS += -frtti -std=c++11

#we want to use stl
APP_STL := stlport_static
APP_STL := gnustl_static
APP_STL := c++_static
APP_OPTIM := release
APP_ALLOW_MISSING_DEPS := true

# APP_ABI := all
APP_ABI := x86
