# Options
option(BUILD_GL "Whether to build OpenGL module" OFF)
option(BUILD_EGL "Whether to build EGL module" OFF)
option(BUILD_VULKAN "Whether to build Vulkan module" ON)
option(BUILD_EDITOR "Whether to build the Zeungine editor" ON)
option(BUILD_DEPENDENCIES "Whether to build ALL the dependencies" ON)
option(ZG_INSTALL "Whether to install Zeungine" ON)
option(ZG_PACKAGE "Whether to package Zeungine" OFF)
if(ZG_INSTALL)
    if(LINUX OR MACOS)
        set(ZG_UNX_INSTALL_PREFIX /usr/local)
        set(ZG_SRC_INSTALL_PREFIX ${ZG_UNX_INSTALL_PREFIX}/src/zg)
        set(ZG_LIB_INSTALL_PREFIX ${ZG_UNX_INSTALL_PREFIX}/lib/zg/${CMAKE_BUILD_TYPE})
        set(ZG_INC_INSTALL_PREFIX ${ZG_UNX_INSTALL_PREFIX}/include/zg)
        set(ZG_ASS_INSTALL_PREFIX ${ZG_SRC_INSTALL_PREFIX}/assets)
    elseif(WINDOWS)
        set(ZG_WIN_INSTALL_PREFIX "C:/Program Files/Zeungine")
        set(ZG_SRC_INSTALL_PREFIX ${ZG_WIN_INSTALL_PREFIX})
        set(ZG_LIB_INSTALL_PREFIX ${ZG_WIN_INSTALL_PREFIX}/${CMAKE_BUILD_TYPE})
        set(ZG_INC_INSTALL_PREFIX ${ZG_WIN_INSTALL_PREFIX}/include)
        set(LG_INC_INSTALL_PREFIX "/??/lunasvg") # todo fix quest|ion|
        set(ZG_ASS_INSTALL_PREFIX ${ZG_WIN_INSTALL_PREFIX}/assets)
    endif()
    add_definitions(-DZG_SRC_INSTALL_PREFIX="${ZG_SRC_INSTALL_PREFIX}")
    add_definitions(-DZG_LIB_INSTALL_PREFIX="${ZG_LIB_INSTALL_PREFIX}")
    add_definitions(-DZG_INC_INSTALL_PREFIX="${ZG_INC_INSTALL_PREFIX}")
    add_definitions(-DZG_ASS_INSTALL_PREFIX="${ZG_ASS_INSTALL_PREFIX}")
endif()