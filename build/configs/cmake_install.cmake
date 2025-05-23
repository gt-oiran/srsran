# Install script for directory: /home/bezerra/Workspace/srsran/configs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
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

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/srsran" TYPE FILE FILES
    "/home/bezerra/Workspace/srsran/configs/amf.yml"
    "/home/bezerra/Workspace/srsran/configs/cell_cfg_max_128_ues.yml"
    "/home/bezerra/Workspace/srsran/configs/cell_cfg_max_256_ues.yml"
    "/home/bezerra/Workspace/srsran/configs/cell_cfg_max_32_ues.yml"
    "/home/bezerra/Workspace/srsran/configs/cell_cfg_max_512_ues.yml"
    "/home/bezerra/Workspace/srsran/configs/cell_cfg_max_64_ues.yml"
    "/home/bezerra/Workspace/srsran/configs/cu.yml"
    "/home/bezerra/Workspace/srsran/configs/du_rf_b200_tdd_n78_20mhz.yml"
    "/home/bezerra/Workspace/srsran/configs/geo_ntn.yml"
    "/home/bezerra/Workspace/srsran/configs/gnb_custom_cell_properties.yml"
    "/home/bezerra/Workspace/srsran/configs/gnb_rf_b200_tdd_n78_20mhz.yml"
    "/home/bezerra/Workspace/srsran/configs/gnb_rf_b210_fdd_srsUE.yml"
    "/home/bezerra/Workspace/srsran/configs/gnb_rf_n310_fdd_n3_20mhz.yml"
    "/home/bezerra/Workspace/srsran/configs/gnb_ru_picocom_scb_tdd_n78_20mhz.yml"
    "/home/bezerra/Workspace/srsran/configs/gnb_ru_ran550_tdd_n78_100mhz_4x2.yml"
    "/home/bezerra/Workspace/srsran/configs/gnb_ru_ran550_tdd_n78_20mhz.yml"
    "/home/bezerra/Workspace/srsran/configs/gnb_ru_rpqn4800e_tdd_n78_20mhz_2x2.yml"
    "/home/bezerra/Workspace/srsran/configs/low_latency.yml"
    "/home/bezerra/Workspace/srsran/configs/mimo_usrp.yml"
    "/home/bezerra/Workspace/srsran/configs/mobility.yml"
    "/home/bezerra/Workspace/srsran/configs/qam256.yml"
    "/home/bezerra/Workspace/srsran/configs/qos.yml"
    "/home/bezerra/Workspace/srsran/configs/slicing.yml"
    "/home/bezerra/Workspace/srsran/configs/srb.yml"
    "/home/bezerra/Workspace/srsran/configs/testmode.yml"
    )
endif()

