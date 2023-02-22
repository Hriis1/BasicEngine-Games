# Install script for directory: D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/cegui")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/build/lib/CEGUICoreWindowRendererSet_d.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/build/lib/CEGUICoreWindowRendererSet.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/build/lib/CEGUICoreWindowRendererSet.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/build/lib/CEGUICoreWindowRendererSet.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/build/bin/CEGUICoreWindowRendererSet_d.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/build/bin/CEGUICoreWindowRendererSet.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/build/bin/CEGUICoreWindowRendererSet.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/build/bin/CEGUICoreWindowRendererSet.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/cegui-0/CEGUI/WindowRendererSets/Core" TYPE FILE FILES
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Button.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Default.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Editbox.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/FrameWindow.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ItemEntry.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ItemListbox.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ListHeader.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ListHeaderSegment.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Listbox.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/MenuItem.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Menubar.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Module.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/MultiColumnList.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/MultiLineEditbox.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/PopupMenu.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ProgressBar.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ScrollablePane.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Scrollbar.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Slider.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Static.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/StaticImage.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/StaticText.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/TabButton.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/TabControl.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Titlebar.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/ToggleButton.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Tooltip.h"
    "D:/programing/C++ SDL OpenGL - MakingGamesWithBen/1.SDL_OpenGL/deps/cegui-0.8.7/cegui/src/WindowRendererSets/Core/../../../include/CEGUI/WindowRendererSets/Core/Tree.h"
    )
endif()

