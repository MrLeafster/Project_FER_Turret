set(srcs "main.c")

set(requires "bluepad32")

# See: https://gitlab.com/ricardoquesada/bluepad32/-/issues/9
if(DEFINED ENV{BLUEPAD32_ARDUINO})
    list(APPEND srcs)
    list(APPEND requires "bluepad32_arduino" "arduino")
endif()

idf_component_register(SRCS "gamepad_logic.cpp" "sketch.cpp" "${srcs}"
                    INCLUDE_DIRS "include"
                    REQUIRES "${requires}")
