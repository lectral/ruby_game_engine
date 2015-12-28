    #=============================================================================
# Copyright 2012 Philipp Berger <admin at philippberger.de>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)
#
# Credits:
# 
# HUGE thanks to Michael Wild
# Additional thanks to:
# Mateusz Loskot
# Rolf Eike Beer



# default for WideString option
set(PANTHEIOS_WIDESTRING 0)
# default for Front- and BackEnd
set(PANTHEIOS_FRONTEND "simple")
set(PANTHEIOS_BACKEND "file")
set(PANTHEIOS_BACKEND_L OFF)
set(PANTHEIOS_BACKEND_R OFF)
set(PANTHEIOS_BACKEND_LIST)

# Use FIND_PACKAGE( Pantheios COMPONENTS ... ) to enable modules
if( Pantheios_FIND_COMPONENTS )
  list(FIND Pantheios_FIND_COMPONENTS "LRSplit" PANTHEIOS_use_lrsplit)
  list(FIND Pantheios_FIND_COMPONENTS "NFrontEnd" PANTHEIOS_use_nfe)
  list(FIND Pantheios_FIND_COMPONENTS "NBackEnd" PANTHEIOS_use_nbe)
  list(FIND Pantheios_FIND_COMPONENTS "WideString" PANTHEIOS_use_ws)
  
  list(REMOVE_ITEM Pantheios_FIND_COMPONENTS "LRSplit" "NFrontEnd" "NBackEnd" "WideString")
  
  if (NOT PANTHEIOS_use_ws EQUAL -1)
    # Use WideString
    set(PANTHEIOS_WIDESTRING 1)
  endif()
  
  if (NOT PANTHEIOS_use_lrsplit EQUAL -1)
    # Found LRSplit
    set(PANTHEIOS_BACKEND "lrsplit")
    if (NOT PANTHEIOS_use_nbe EQUAL -1)
      # Also found NBe
      message(FATAL_ERROR "Pantheios: Use either LRSplit or NBackEnd, not both.")
    endif()
    if (NOT PANTHEIOS_use_nfe EQUAL -1)
      # Also found NFe
      message(FATAL_ERROR "Pantheios: Use either LRSplit or NFrontEnd, not both.")
    endif()
    
    foreach( component ${Pantheios_FIND_COMPONENTS} )
      # LRSplit L BackEnds
      if (component STREQUAL "LACELogger")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to ACELogger")
        set(PANTHEIOS_BACKEND_L "ACE")
      elseif (component STREQUAL "LCOMErrorObject")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to COMErrorObject")
        set(PANTHEIOS_BACKEND_L "COMErrorObject")
      elseif (component STREQUAL "LFile")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to File")
        set(PANTHEIOS_BACKEND_L "file")
      elseif (component STREQUAL "LFileCallback")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to FileCallback")
        set(PANTHEIOS_BACKEND_L "file.WithCallback")
      elseif (component STREQUAL "LFPrintf")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to FPrintf")
        set(PANTHEIOS_BACKEND_L "fprintf")
      elseif (component STREQUAL "LFPrintfCallback")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to FPrintfCallback")
        set(PANTHEIOS_BACKEND_L "fprintf.WithCallback")
      elseif (component STREQUAL "LNull")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to Null")
        set(PANTHEIOS_BACKEND_L "null")
      elseif (component STREQUAL "LSpeech")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to Speech")
        set(PANTHEIOS_BACKEND_L "speech")
      elseif (component STREQUAL "LSyslog")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to Syslog")
        set(PANTHEIOS_BACKEND_L "syslog")
      elseif (component STREQUAL "LWindowsConsole")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to WindowsConsole")
        set(PANTHEIOS_BACKEND_L "WindowsConsole")
      elseif (component STREQUAL "LWindowsConsoleCallback")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to WindowsConsoleCallback")
        set(PANTHEIOS_BACKEND_L "WindowsConsole.WithCallback")
      elseif (component STREQUAL "LWindowsDebugger")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to WindowsDebugger")
        set(PANTHEIOS_BACKEND_L "WindowsDebugger")
      elseif (component STREQUAL "LWindowsDebuggerCallback")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to WindowsDebuggerCallback")
        set(PANTHEIOS_BACKEND_L "WindowsDebugger.WithCallback")
      elseif (component STREQUAL "LWindowsEventLog")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to WindowsEventLog")
        set(PANTHEIOS_BACKEND_L "EventLog")
      elseif (component STREQUAL "LWindowsMessageBox")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to WindowsMessageBox")
        set(PANTHEIOS_BACKEND_L "MessageBox")
      elseif (component STREQUAL "LWindowsSyslog")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to WindowsSyslog")
        set(PANTHEIOS_BACKEND_L "WindowsSyslog")
      elseif (component STREQUAL "LWindowsSyslogCallback")
        message(STATUS "Pantheios: Setting LRSplit BackEnd L to WindowsSyslogCallback")
        set(PANTHEIOS_BACKEND_L "WindowsSyslog.WithCallback") 
      # LRSplit R BackEnds
      elseif (component STREQUAL "RACELogger")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to ACELogger")
        set(PANTHEIOS_BACKEND_R "ACE")
      elseif (component STREQUAL "RCOMErrorObject")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to COMErrorObject")
        set(PANTHEIOS_BACKEND_R "COMErrorObject")
      elseif (component STREQUAL "RFile")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to File")
        set(PANTHEIOS_BACKEND_R "file")
      elseif (component STREQUAL "RFileCallback")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to FileCallback")
        set(PANTHEIOS_BACKEND_R "file.WithCallback")
      elseif (component STREQUAL "RFPrintf")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to FPrintf")
        set(PANTHEIOS_BACKEND_R "fprintf")
      elseif (component STREQUAL "RFPrintfCallback")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to FPrintfCallback")
        set(PANTHEIOS_BACKEND_R "fprintf.WithCallback")
      elseif (component STREQUAL "RNull")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to Null")
        set(PANTHEIOS_BACKEND_R "null")
      elseif (component STREQUAL "RSpeech")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to Speech")
        set(PANTHEIOS_BACKEND_R "speech")
      elseif (component STREQUAL "RSyslog")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to Syslog")
        set(PANTHEIOS_BACKEND_R "syslog")
      elseif (component STREQUAL "RWindowsConsole")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to WindowsConsole")
        set(PANTHEIOS_BACKEND_R "WindowsConsole")
      elseif (component STREQUAL "RWindowsConsoleCallback")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to WindowsConsoleCallback")
        set(PANTHEIOS_BACKEND_R "WindowsConsole.WithCallback")
      elseif (component STREQUAL "RWindowsDebugger")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to WindowsDebugger")
        set(PANTHEIOS_BACKEND_R "WindowsDebugger")
      elseif (component STREQUAL "RWindowsDebuggerCallback")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to WindowsDebuggerCallback")
        set(PANTHEIOS_BACKEND_R "WindowsDebugger.WithCallback")
      elseif (component STREQUAL "RWindowsEventLog")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to WindowsEventLog")
        set(PANTHEIOS_BACKEND_R "EventLog")
      elseif (component STREQUAL "RWindowsMessageBox")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to WindowsMessageBox")
        set(PANTHEIOS_BACKEND_R "MessageBox")
      elseif (component STREQUAL "RWindowsSyslog")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to WindowsSyslog")
        set(PANTHEIOS_BACKEND_R "WindowsSyslog")
      elseif (component STREQUAL "RWindowsSyslogCallback")
        message(STATUS "Pantheios: Setting LRSplit BackEnd R to WindowsSyslogCallback")
        set(PANTHEIOS_BACKEND_R "WindowsSyslog.WithCallback") 
      # FrontEnds
      elseif (component STREQUAL "NoFrontEnd")
        message(STATUS "Pantheios: Setting FrontEnd to NoFrontEnd")
        set(PANTHEIOS_FRONTEND "null")
      elseif (component STREQUAL "SimpleFrontEnd")
        message(STATUS "Pantheios: Setting FrontEnd to SimpleFrontEnd")
        set(PANTHEIOS_FRONTEND "simple")    

      else ()
        message(FATAL_ERROR "Unknown Component: ${component}")
      endif ()
    endforeach(component)
  elseif (NOT PANTHEIOS_use_nbe EQUAL -1)
    # Found NBackEnd
    if (PANTHEIOS_use_nfe EQUAL -1)
      message(FATAL_ERROR "Pantheios: Usage of NBackEnd requires the NFrontEnd.")
    endif()
    set(PANTHEIOS_BACKEND "N")
    set(PANTHEIOS_FRONTEND "N")
    
    foreach( component ${Pantheios_FIND_COMPONENTS} )
      # Std BackEnds
      if (component STREQUAL "ACELogger")
        message(STATUS "Pantheios: Adding BackEnd to ACELogger")
        list(APPEND PANTHEIOS_BACKEND_LIST "ACE")
      elseif (component STREQUAL "COMErrorObject")
        message(STATUS "Pantheios: Adding BackEnd to COMErrorObject")
        list(APPEND PANTHEIOS_BACKEND_LIST "COMErrorObject")
      elseif (component STREQUAL "File")
        message(STATUS "Pantheios: Adding BackEnd to File")
        list(APPEND PANTHEIOS_BACKEND_LIST "file")
      elseif (component STREQUAL "FileCallback")
        message(STATUS "Pantheios: Adding BackEnd to FileCallback")
        list(APPEND PANTHEIOS_BACKEND_LIST "file.WithCallback")
      elseif (component STREQUAL "FPrintf")
        message(STATUS "Pantheios: Adding BackEnd to FPrintf")
        list(APPEND PANTHEIOS_BACKEND_LIST "fprintf")
      elseif (component STREQUAL "FPrintfCallback")
        message(STATUS "Pantheios: Adding BackEnd to FPrintfCallback")
        list(APPEND PANTHEIOS_BACKEND_LIST "fprintf.WithCallback")
      elseif (component STREQUAL "Null")
        message(STATUS "Pantheios: Adding BackEnd to Null")
        list(APPEND PANTHEIOS_BACKEND_LIST "null")
      elseif (component STREQUAL "Speech")
        message(STATUS "Pantheios: Adding BackEnd to Speech")
        list(APPEND PANTHEIOS_BACKEND_LIST "speech")
      elseif (component STREQUAL "Syslog")
        message(STATUS "Pantheios: Adding BackEnd to Syslog")
        list(APPEND PANTHEIOS_BACKEND_LIST "syslog")
      elseif (component STREQUAL "WindowsConsole")
        message(STATUS "Pantheios: Adding BackEnd to WindowsConsole")
        list(APPEND PANTHEIOS_BACKEND_LIST "WindowsConsole")
      elseif (component STREQUAL "WindowsConsoleCallback")
        message(STATUS "Pantheios: Adding BackEnd to WindowsConsoleCallback")
        list(APPEND PANTHEIOS_BACKEND_LIST "WindowsConsole.WithCallback")
      elseif (component STREQUAL "WindowsDebugger")
        message(STATUS "Pantheios: Adding BackEnd to WindowsDebugger")
        list(APPEND PANTHEIOS_BACKEND_LIST "WindowsDebugger")
      elseif (component STREQUAL "WindowsDebuggerCallback")
        message(STATUS "Pantheios: Adding BackEnd to WindowsDebuggerCallback")
        list(APPEND PANTHEIOS_BACKEND_LIST "WindowsDebugger.WithCallback")
      elseif (component STREQUAL "WindowsEventLog")
        message(STATUS "Pantheios: Adding BackEnd to WindowsEventLog")
        list(APPEND PANTHEIOS_BACKEND_LIST "EventLog")
      elseif (component STREQUAL "WindowsMessageBox")
        message(STATUS "Pantheios: Adding BackEnd to WindowsMessageBox")
        list(APPEND PANTHEIOS_BACKEND_LIST "MessageBox")
      elseif (component STREQUAL "WindowsSyslog")
        message(STATUS "Pantheios: Adding BackEnd to WindowsSyslog")
        list(APPEND PANTHEIOS_BACKEND_LIST "WindowsSyslog")
      elseif (component STREQUAL "WindowsSyslogCallback")
        message(STATUS "Pantheios: Adding BackEnd to WindowsSyslogCallback")
        list(APPEND PANTHEIOS_BACKEND_LIST "WindowsSyslog.WithCallback")  
          
      else ()
        message(FATAL_ERROR "Unknown Component: ${component}")
      endif ()
    endforeach(component)
  else ()
    # Simple, one FE, one BE
    foreach( component ${Pantheios_FIND_COMPONENTS} )
      if (component STREQUAL "ACELogger")
        message(STATUS "Pantheios: Setting BackEnd to ACELogger")
        set(PANTHEIOS_BACKEND "ACE")
      elseif (component STREQUAL "COMErrorObject")
        message(STATUS "Pantheios: Setting BackEnd to COMErrorObject")
        set(PANTHEIOS_BACKEND "COMErrorObject")
      elseif (component STREQUAL "File")
        message(STATUS "Pantheios: Setting BackEnd to File")
        set(PANTHEIOS_BACKEND "file")
      elseif (component STREQUAL "FileCallback")
        message(STATUS "Pantheios: Setting BackEnd to FileCallback")
        set(PANTHEIOS_BACKEND "file.WithCallback")
      elseif (component STREQUAL "FPrintf")
        message(STATUS "Pantheios: Setting BackEnd to FPrintf")
        set(PANTHEIOS_BACKEND "fprintf")
      elseif (component STREQUAL "FPrintfCallback")
        message(STATUS "Pantheios: Setting BackEnd to FPrintfCallback")
        set(PANTHEIOS_BACKEND "fprintf.WithCallback")
      elseif (component STREQUAL "Null")
        message(STATUS "Pantheios: Setting BackEnd to Null")
        set(PANTHEIOS_BACKEND "null")
      elseif (component STREQUAL "Speech")
        message(STATUS "Pantheios: Setting BackEnd to Speech")
        set(PANTHEIOS_BACKEND "speech")
      elseif (component STREQUAL "Syslog")
        message(STATUS "Pantheios: Setting BackEnd to Syslog")
        set(PANTHEIOS_BACKEND "syslog")
      elseif (component STREQUAL "WindowsConsole")
        message(STATUS "Pantheios: Setting BackEnd to WindowsConsole")
        set(PANTHEIOS_BACKEND "WindowsConsole")
      elseif (component STREQUAL "WindowsConsoleCallback")
        message(STATUS "Pantheios: Setting BackEnd to WindowsConsoleCallback")
        set(PANTHEIOS_BACKEND "WindowsConsole.WithCallback")
      elseif (component STREQUAL "WindowsDebugger")
        message(STATUS "Pantheios: Setting BackEnd to WindowsDebugger")
        set(PANTHEIOS_BACKEND "WindowsDebugger")
      elseif (component STREQUAL "WindowsDebuggerCallback")
        message(STATUS "Pantheios: Setting BackEnd to WindowsDebuggerCallback")
        set(PANTHEIOS_BACKEND "WindowsDebugger.WithCallback")
      elseif (component STREQUAL "WindowsEventLog")
        message(STATUS "Pantheios: Setting BackEnd to WindowsEventLog")
        set(PANTHEIOS_BACKEND "EventLog")
      elseif (component STREQUAL "WindowsMessageBox")
        message(STATUS "Pantheios: Setting BackEnd to WindowsMessageBox")
        set(PANTHEIOS_BACKEND "MessageBox")
      elseif (component STREQUAL "WindowsSyslog")
        message(STATUS "Pantheios: Setting BackEnd to WindowsSyslog")
        set(PANTHEIOS_BACKEND "WindowsSyslog")
      elseif (component STREQUAL "WindowsSyslogCallback")
        message(STATUS "Pantheios: Setting BackEnd to WindowsSyslogCallback")
        set(PANTHEIOS_BACKEND "WindowsSyslog.WithCallback") 
      
        
      # FrontEnds
      elseif (component STREQUAL "NoFrontEnd")
        message(STATUS "Pantheios: Setting FrontEnd to NoFrontEnd")
        set(PANTHEIOS_FRONTEND "null")
      elseif (component STREQUAL "SimpleFrontEnd")
        message(STATUS "Pantheios: Setting FrontEnd to SimpleFrontEnd")
        set(PANTHEIOS_FRONTEND "simple")      
      else ()
        message(FATAL_ERROR "Unknown Component: ${component}")
      endif ()
    endforeach(component)
  endif ()
endif(Pantheios_FIND_COMPONENTS)

if (PANTHEIOS_USE_DYNAMIC_RUNTIME)
  set(PANTHEIOS_LIB_LINKTYPE "dll")
else ()
  set(PANTHEIOS_LIB_LINKTYPE "mt")
endif ()

if(PANTHEIOS_INCLUDE_DIR)
  if (NOT PANTHEIOS_ROOT)
    get_filename_component(PANTHEIOS_ROOT "${PANTHEIOS_INCLUDE_DIR}" PATH)
  endif()
  
  get_filename_component(PANTHEIOS_ROOT_HINT "${PANTHEIOS_INCLUDE_DIR}" PATH)
endif()

find_path(PANTHEIOS_INCLUDE_DIR pantheios/pantheios.h
    PATH_SUFFIXES include
  HINTS ${PANTHEIOS_ROOT} ${PANTHEIOS_ROOT_HINT}
  ENV PANTHEIOS_ROOT
)

# No idea what the stuff for ICC et. al. is, so I don't handle it here...
set(_P_COMP_TAG)
set(_P_OS_TAG)
set(_P_ARCH_TAG)
if(MSVC)
  if(MSVC60)
    set(_P_COMP_TAG vc6)
  elseif(MSVC70)
    set(_P_COMP_TAG vc7)
  elseif(MSVC71)
    set(_P_COMP_TAG vc71)
  elseif(MSVC80)
    set(_P_COMP_TAG vc8)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(_P_ARCH_TAG .x64)
    endif()
  elseif(MSVC90)
    set(_P_COMP_TAG vc9)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(_P_ARCH_TAG .x64)
    endif()
  elseif(MSVC10)
    set(_P_COMP_TAG vc10)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
      set(_P_ARCH_TAG .x64)
    endif()
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC)
  execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    string(REGEX MATCHALL "[0-9]+" GCC_VERSION_COMPONENTS ${GCC_VERSION})
    list(GET GCC_VERSION_COMPONENTS 0 GCC_MAJOR)
    list(GET GCC_VERSION_COMPONENTS 1 GCC_MINOR)
  if(GCC_MAJOR STREQUAL "3")
    # GCC Version 3
    if(GCC_MINOR STREQUAL "2")
      set(_P_COMP_TAG gcc32)
    elseif(GCC_MINOR STREQUAL "3")
      set(_P_COMP_TAG gcc33)
    elseif(GCC_MINOR STREQUAL "4")
      set(_P_COMP_TAG gcc34)
    else()
      message(FATAL_ERROR "Pantheios: Unknown GCC3 Version")
    endif()
  elseif(GCC_MAJOR STREQUAL "4")
    # GCC Version 4
    if(GCC_MINOR STREQUAL "0")
      set(_P_COMP_TAG gcc40)
    elseif(GCC_MINOR STREQUAL "1")
      set(_P_COMP_TAG gcc41)
    elseif(GCC_MINOR STREQUAL "2")
      set(_P_COMP_TAG gcc42)
    elseif(GCC_MINOR STREQUAL "3")
      set(_P_COMP_TAG gcc43)
    elseif(GCC_MINOR STREQUAL "4")
      set(_P_COMP_TAG gcc44)
      if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(_P_ARCH_TAG .file64bit)
      endif()
    elseif(GCC_MINOR STREQUAL "5")
      set(_P_COMP_TAG gcc45)
      if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(_P_ARCH_TAG .file64bit)
      endif()
    elseif(GCC_MINOR STREQUAL "6")
      set(_P_COMP_TAG gcc46)
      if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(_P_ARCH_TAG .file64bit)
      endif()
    else()
      message(FATAL_ERROR "Pantheios: Unknown GCC4 Version")
    endif()
  else()
    message(FATAL_ERROR "Pantheios: Unknown GCC Version")
  endif()
else()
  message(FATAL_ERROR "Pantheios: Your compiler/environment is currently unsupported.")
endif()

set(_P_LIB_TAG ${_P_COMP_TAG}${_P_OS_TAG}${_P_ARCH_TAG})

# Is this the right way?
set(PANTHEIOS_INCLUDE_DIRS ${PANTHEIOS_INCLUDE_DIR})

set(_P_REQUIRED_LIBVARS)
set(PANTHEIOS_LIBRARIES)

# core and util libraries
foreach(l core util)
  find_library(PANTHEIOS_${l}_${PANTHEIOS_LIB_LINKTYPE}_DEBUG_LIBRARY
    pantheios.1.${l}.${_P_LIB_TAG}.${PANTHEIOS_LIB_LINKTYPE}.debug
    PATH_SUFFIXES lib
    HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
    ENV PANTHEIOS_ROOT
  )

  find_library(PANTHEIOS_${l}_${PANTHEIOS_LIB_LINKTYPE}_LIBRARY
    pantheios.1.${l}.${_P_LIB_TAG}.${PANTHEIOS_LIB_LINKTYPE}
    PATH_SUFFIXES lib
    HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
    ENV PANTHEIOS_ROOT
  )

  list(APPEND _P_REQUIRED_LIBVARS
    PANTHEIOS_${l}_${PANTHEIOS_LIB_LINKTYPE}_DEBUG_LIBRARY
    PANTHEIOS_${l}_${PANTHEIOS_LIB_LINKTYPE}_LIBRARY
  )
  list(APPEND PANTHEIOS_LIBRARIES
    debug ${PANTHEIOS_${l}_${PANTHEIOS_LIB_LINKTYPE}_DEBUG_LIBRARY}
    optimized ${PANTHEIOS_${l}_${PANTHEIOS_LIB_LINKTYPE}_LIBRARY}
  )
endforeach()

# set PANTHEIOS_LIBRARY_DIRS
get_filename_component(PANTHEIOS_LIBRARY_DIRS ${PANTHEIOS_core_${PANTHEIOS_LIB_LINKTYPE}_LIBRARY} PATH)



# backend libraries (split, sole, local, remote and common)
set(_P_LT ${PANTHEIOS_LIB_LINKTYPE})
set(_P_BE ${PANTHEIOS_BACKEND})

if (_P_BE STREQUAL N)
  # N Backend, go through list
  message(STATUS "Pantheios: Dbg: Lib-n")
  find_library(PANTHEIOS_be_${_P_BE}_${_P_LT}_DEBUG_LIBRARY
    pantheios.1.be.${_P_BE}.${_P_LIB_TAG}.${_P_LT}.debug
    PATH_SUFFIXES lib
    HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
    ENV PANTHEIOS_ROOT
  )

  find_library(PANTHEIOS_be_${_P_BE}_${_P_LT}_LIBRARY
    pantheios.1.be.${_P_BE}.${_P_LIB_TAG}.${_P_LT}
    PATH_SUFFIXES lib
    HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
    ENV PANTHEIOS_ROOT
  )

  list(APPEND _P_REQUIRED_LIBVARS
    PANTHEIOS_be_${_P_BE}_${_P_LT}_DEBUG_LIBRARY
    PANTHEIOS_be_${_P_BE}_${_P_LT}_LIBRARY
  )
  list(APPEND PANTHEIOS_LIBRARIES
    debug ${PANTHEIOS_be_${_P_BE}_${_P_LT}_DEBUG_LIBRARY}
    optimized ${PANTHEIOS_be_${_P_BE}_${_P_LT}_LIBRARY}
  )
  
  foreach (blib PANTHEIOS_BACKEND_LIST)
    find_library(PANTHEIOS_bec_${blib}_${_P_LT}_DEBUG_LIBRARY
      pantheios.1.bec.${blib}.${_P_LIB_TAG}.${_P_LT}.debug
      PATH_SUFFIXES lib
      HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
      ENV PANTHEIOS_ROOT
    )

    find_library(PANTHEIOS_bec_${blib}_${_P_LT}_LIBRARY
      pantheios.1.bec.${blib}.${_P_LIB_TAG}.${_P_LT}
      PATH_SUFFIXES lib
      HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
      ENV PANTHEIOS_ROOT
    )

    list(APPEND _P_REQUIRED_LIBVARS
      PANTHEIOS_bec_${blib}_${_P_LT}_DEBUG_LIBRARY
      PANTHEIOS_bec_${blib}_${_P_LT}_LIBRARY
    )
    list(APPEND PANTHEIOS_LIBRARIES
      debug ${PANTHEIOS_bec_${blib}_${_P_LT}_DEBUG_LIBRARY}
      optimized ${PANTHEIOS_bec_${blib}_${_P_LT}_LIBRARY}
    )
  endforeach()
elseif (_P_BE STREQUAL lrsplit)
  # LRSplit
  message(STATUS "Pantheios: Dbg: Lib-lrsplit")
  find_library(PANTHEIOS_be_${_P_BE}_${_P_LT}_DEBUG_LIBRARY
    pantheios.1.be.${_P_BE}.${_P_LIB_TAG}.${_P_LT}.debug
    PATH_SUFFIXES lib
    HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
    ENV PANTHEIOS_ROOT
  )

  find_library(PANTHEIOS_be_${_P_BE}_${_P_LT}_LIBRARY
    pantheios.1.be.${_P_BE}.${_P_LIB_TAG}.${_P_LT}
    PATH_SUFFIXES lib
    HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
    ENV PANTHEIOS_ROOT
  )

  list(APPEND _P_REQUIRED_LIBVARS
    PANTHEIOS_be_${_P_BE}_${_P_LT}_DEBUG_LIBRARY
    PANTHEIOS_be_${_P_BE}_${_P_LT}_LIBRARY
  )
  list(APPEND PANTHEIOS_LIBRARIES
    debug ${PANTHEIOS_be_${_P_BE}_${_P_LT}_DEBUG_LIBRARY}
    optimized ${PANTHEIOS_be_${_P_BE}_${_P_LT}_LIBRARY}
  )
  
  # Left side
  foreach (t bec bel)
    find_library(PANTHEIOS_${t}_${PANTHEIOS_BACKEND_L}_${_P_LT}_DEBUG_LIBRARY
      pantheios.1.${t}.${PANTHEIOS_BACKEND_L}.${_P_LIB_TAG}.${_P_LT}.debug
      PATH_SUFFIXES lib
      HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
      ENV PANTHEIOS_ROOT
    )

    find_library(PANTHEIOS_${t}_${PANTHEIOS_BACKEND_L}_${_P_LT}_LIBRARY
      pantheios.1.${t}.${PANTHEIOS_BACKEND_L}.${_P_LIB_TAG}.${_P_LT}
      PATH_SUFFIXES lib
      HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
      ENV PANTHEIOS_ROOT
    )
    list(APPEND _P_REQUIRED_LIBVARS
      PANTHEIOS_${t}_${PANTHEIOS_BACKEND_L}_${_P_LT}_DEBUG_LIBRARY
      PANTHEIOS_${t}_${PANTHEIOS_BACKEND_L}_${_P_LT}_LIBRARY
    )
    list(APPEND PANTHEIOS_LIBRARIES
      debug ${PANTHEIOS_${t}_${PANTHEIOS_BACKEND_L}_${_P_LT}_DEBUG_LIBRARY}
      optimized ${PANTHEIOS_${t}_${PANTHEIOS_BACKEND_L}_${_P_LT}_LIBRARY}
    )
  endforeach()
  # Right side
  foreach (t bec ber)
    find_library(PANTHEIOS_${t}_${PANTHEIOS_BACKEND_R}_${_P_LT}_DEBUG_LIBRARY
      pantheios.1.${t}.${PANTHEIOS_BACKEND_R}.${_P_LIB_TAG}.${_P_LT}.debug
      PATH_SUFFIXES lib
      HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
      ENV PANTHEIOS_ROOT
    )

    find_library(PANTHEIOS_${t}_${PANTHEIOS_BACKEND_R}_${_P_LT}_LIBRARY
      pantheios.1.${t}.${PANTHEIOS_BACKEND_R}.${_P_LIB_TAG}.${_P_LT}
      PATH_SUFFIXES lib
      HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
      ENV PANTHEIOS_ROOT
    )
    list(APPEND _P_REQUIRED_LIBVARS
      PANTHEIOS_${t}_${PANTHEIOS_BACKEND_R}_${_P_LT}_DEBUG_LIBRARY
      PANTHEIOS_${t}_${PANTHEIOS_BACKEND_R}_${_P_LT}_LIBRARY
    )
    list(APPEND PANTHEIOS_LIBRARIES
      debug ${PANTHEIOS_${t}_${PANTHEIOS_BACKEND_R}_${_P_LT}_DEBUG_LIBRARY}
      optimized ${PANTHEIOS_${t}_${PANTHEIOS_BACKEND_R}_${_P_LT}_LIBRARY}
    )
  endforeach()
else ()
  # normal
  message(STATUS "Pantheios: Dbg: Lib-normal")
  foreach (t be bec)
    find_library(PANTHEIOS_${t}_${PANTHEIOS_BACKEND}_${_P_LT}_DEBUG_LIBRARY
      pantheios.1.${t}.${PANTHEIOS_BACKEND}.${_P_LIB_TAG}.${_P_LT}.debug
      PATH_SUFFIXES lib
      HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
      ENV PANTHEIOS_ROOT
    )

    find_library(PANTHEIOS_${t}_${PANTHEIOS_BACKEND}_${_P_LT}_LIBRARY
      pantheios.1.${t}.${PANTHEIOS_BACKEND}.${_P_LIB_TAG}.${_P_LT}
      PATH_SUFFIXES lib
      HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
      ENV PANTHEIOS_ROOT
    )
    list(APPEND _P_REQUIRED_LIBVARS
      PANTHEIOS_${t}_${PANTHEIOS_BACKEND}_${_P_LT}_DEBUG_LIBRARY
      PANTHEIOS_${t}_${PANTHEIOS_BACKEND}_${_P_LT}_LIBRARY
    )
    list(APPEND PANTHEIOS_LIBRARIES
      debug ${PANTHEIOS_${t}_${PANTHEIOS_BACKEND}_${_P_LT}_DEBUG_LIBRARY}
      optimized ${PANTHEIOS_${t}_${PANTHEIOS_BACKEND}_${_P_LT}_LIBRARY}
    )
  endforeach()
endif()

# frontent libraries
set(PANTHEIOS_fe_DEBUG_LIBRARY)
set(PANTHEIOS_fe_LIBRARY)
if(NOT PANTHEIOS_FRONTENT STREQUAL null)
  set(_P_FE ${PANTHEIOS_FRONTEND})
  find_library(PANTHEIOS_${_P_FE}_${_P_LT}_DEBUG_LIBRARY
    pantheios.1.fe.${_P_FE}.${_P_LIB_TAG}.${_P_LT}.debug
    PATH_SUFFIXES lib
    HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
    ENV PANTHEIOS_ROOT
  )
  find_library(PANTHEIOS_${_P_FE}_${_P_LT}_LIBRARY
    pantheios.1.fe.${_P_FE}.${_P_LIB_TAG}.${_P_LT}
    PATH_SUFFIXES lib
    HINTS ${PANTHEIOS_ROOT_HINT} ${PANTHEIOS_ROOT}
    ENV PANTHEIOS_ROOT
  )

  list(APPEND _P_REQUIRED_LIBVARS
    PANTHEIOS_${_P_FE}_${_P_LT}_DEBUG_LIBRARY
    PANTHEIOS_${_P_FE}_${_P_LT}_LIBRARY
  )
  list(APPEND PANTHEIOS_LIBRARIES
    debug ${PANTHEIOS_${_P_FE}_${_P_LT}_DEBUG_LIBRARY}
    optimized ${PANTHEIOS_${_P_FE}_${_P_LT}_LIBRARY}
  )
endif()

# copy to NAME_LIBS
set(PANTHEIOS_LIBS ${PANTHEIOS_LIBRARIES})  

# handle the QUIETLY and REQUIRED arguments and set Pantheios_FOUND to TRUE if 
# all listed variables are TRUE
include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Pantheios
  REQUIRED_VARS PANTHEIOS_INCLUDE_DIR ${_P_REQUIRED_LIBVARS}
)
                  

mark_as_advanced(PANTHEIOS_INCLUDE_DIR PANTHEIOS_LIBRARIES)