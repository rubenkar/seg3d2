#
#  For more information, please see: http://software.sci.utah.edu
# 
#  The MIT License
# 
#  Copyright (c) 2009 Scientific Computing and Imaging Institute,
#  University of Utah.
# 
#  
#  Permission is hereby granted, free of charge, to any person obtaining a
#  copy of this software and associated documentation files (the "Software"),
#  to deal in the Software without restriction, including without limitation
#  the rights to use, copy, modify, merge, publish, distribute, sublicense,
#  and/or sell copies of the Software, and to permit persons to whom the
#  Software is furnished to do so, subject to the following conditions:
# 
#  The above copyright notice and this permission notice shall be included
#  in all copies or substantial portions of the Software. 
# 
#  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
#  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
#  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
#  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
#  DEALINGS IN THE SOFTWARE.
#

###########################################
# PROJECT: Seg3D
###########################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(Seg3D)

###########################################
# Verify build directory
###########################################

IF ( ${CMAKE_BINARY_DIR} MATCHES ${CMAKE_SOURCE_DIR} )
	MESSAGE( FATAL_ERROR "Please delete the CMakeCache.txt from the src directory and build Seg3D in the bin directory. Run 'rm CMakeCache.txt; cd ../bin; cmake ../src' from the binary directory." )
ENDIF ( ${CMAKE_BINARY_DIR} MATCHES ${CMAKE_SOURCE_DIR} )

###########################################
# Set default CMAKE_BUILD_TYPE
# if empty for Unix Makefile builds
###########################################

IF (CMAKE_GENERATOR MATCHES "Unix Makefiles" AND NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
ENDIF (CMAKE_GENERATOR MATCHES "Unix Makefiles" AND NOT CMAKE_BUILD_TYPE)

###########################################
# WHERE TO COMPILE EXECUTABLES
###########################################

SET(SEG3D_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR} CACHE PATH "" FORCE) # Needed by ITK

###########################################
# COMPILE OPTIONS
###########################################

SET(SEG3D_BUILD_INTERFACE 1 CACHE BOOL "Build the interface to Seg3D")
IF (WIN32)
	SET(SEG3D_SHOW_CONSOLE FALSE CACHE BOOL "Show console for debugging")
ENDIF (WIN32)

###########################################
# SEG3D VERSION NUMBERS
###########################################

SET(SEG3D_MAJOR_VERSION 2 CACHE INTERNAL "Major version number" FORCE)
SET(SEG3D_MINOR_VERSION 1 CACHE INTERNAL "Minor version number" FORCE)
SET(SEG3D_PATCH_VERSION 5 CACHE INTERNAL "Patch version number" FORCE)

###########################################
# APPLICATION Information
###########################################

SET(APPLICATION_NAME "Seg3D2" CACHE INTERNAL "Name of the application" FORCE)
SET(APPLICATION_EXTENSION ".s3d" CACHE INTERNAL "Name of the extension" FORCE)
SET(APPLICATION_URL "www.seg3d.org" CACHE INTERNAL "URL where more information can be found" FORCE)
SET(APPLICATION_VENDOR "SCI" CACHE INTERNAL "Who generated the applicatio" FORCE)
SET(APPLICATION_CONTACT "seg3d-users@sci.utah.edu" CACHE INTERNAL "Contact information" FORCE)
SET(APPLICATION_WINDOWS_ICON "${CMAKE_SOURCE_DIR}/Resources/Icons\\\\Seg3D.ico" CACHE INTERNAL "Windows icon" FORCE)
SET(APPLICATION_WINDOWS_RC "${CMAKE_SOURCE_DIR}/Resources/Icons\\\\Seg3D.rc" CACHE INTERNAL "Windows icon" FORCE)
SET(APPLICATION_OSX_ICON_FULL_PATH "${CMAKE_SOURCE_DIR}/Resources/Icons/Seg3D.icns" CACHE INTERNAL "OSX icon" FORCE)
SET(APPLICATION_OSX_ICON "Seg3D.icns" CACHE INTERNAL "OSX icon" FORCE)


###########################################
# PACKAGING Information
###########################################

SET(PACKAGING_README "${CMAKE_CURRENT_SOURCE_DIR}/CMake/ReadMe.txt" CACHE INTERNAL "Where to find the readme file." FORCE )
SET(PACKAGING_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/CMake/License.txt" CACHE INTERNAL "Where to find the license file." FORCE )
SET(PACKAGING_RELEASENOTES "${CMAKE_CURRENT_SOURCE_DIR}/ReleaseNotes.txt" CACHE INTERNAL "Where to find the releasenotes file." FORCE )
SET(PACKAGING_WELCOME "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Welcome.txt" CACHE INTERNAL "Where to find the welcome file." FORCE )
SET(PACKAGING_ICON "${CMAKE_SOURCE_DIR}/Resources/Icons\\\\package_icon.bmp" CACHE INTERNAL "Packing icon." FORCE )


###########################################
# DO STANDARD TESTS
###########################################

INCLUDE(CMakeBackwardCompatibilityC)
INCLUDE(CMakeBackwardCompatibilityCXX)
INCLUDE(CheckCSourceCompiles)

###########################################
# DETERMINE ARCHITECTURE
# In order for the code to depend on the
# architecture settings
###########################################

IF (CMAKE_SIZEOF_VOID_P MATCHES 8)
  SET(SEG3D_BITS "64bit")
  SET(MSVC90_BUILD "amd64")
  ADD_DEFINITIONS(-DSCI_64BITS)
ELSE (CMAKE_SIZEOF_VOID_P MATCHES 8)
  SET(SEG3D_BITS "32bit")
  SET(MSVC90_BUILD "x86")
  ADD_DEFINITIONS(-DSCI_32BITS)
  IF (WIN32)
	ADD_DEFINITIONS(-DBOOST_BIND_ENABLE_STDCALL)
  ENDIF (WIN32)
ENDIF (CMAKE_SIZEOF_VOID_P MATCHES 8)

###########################################
# SETUP DEFINTIONS FOR EXTERNAL PACKAGES
# To force a static build these flags
# need to be set project wide.
###########################################

ADD_DEFINITIONS(-DGLEW_STATIC)
ADD_DEFINITIONS(-DTEEM_STATIC)
ADD_DEFINITIONS(-DLIBXML_STATIC)
ADD_DEFINITIONS(-DTINYXML_STATIC)
ADD_DEFINITIONS(-DBOOST_ALL_NO_LIB)
ADD_DEFINITIONS(-DQT_NO_KEYWORDS)
ADD_DEFINITIONS(-DTIXML_USE_STL)
  
SET(ITK_BUILD_SHARED_LIBS "STATIC")
SET(ITK_USE_REVIEW TRUE CACHE BOOLEAN "Seg3D requires the ITK Review directory for proper filter operations." FORCE)
SET(ITK_USE_REVIEW_STATISTICS TRUE CACHE BOOLEAN "Seg3D requires the ITK Review directory for proper filter operations." FORCE)

###########################################
# Flags for Microsoft Compiler
###########################################

IF (WIN32 AND MSVC)
  ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501 -DNTDDI_VERSION=0x05010000)
  ADD_DEFINITIONS(-DPSAPI_VERSION=1)
  # Disable Visual C++ Secure Warnings
  ADD_DEFINITIONS(-D_SCL_SECURE_NO_WARNINGS)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
  ADD_DEFINITIONS(-D_BIND_TO_CURRENT_VCLIBS_VERSION=1)
  ADD_DEFINITIONS(-D_BIND_TO_CURRENT_CRT_VERSION=1)
  # Enable Intrinsic Functions
  SET(CMAKE_CXX_FLAGS "/Oi ${CMAKE_CXX_FLAGS}")
  # Build with multiple processes -- speeds up compilation on multi-processor machines.
  SET(CMAKE_CXX_FLAGS "/MP ${CMAKE_CXX_FLAGS}") 
ENDIF (WIN32 AND MSVC)


###########################################
# RPATH settings for Linux
###########################################

IF(UNIX)
  MESSAGE(STATUS "Configuring RPATH settings")
  SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
  SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
  SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
  SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
ENDIF(UNIX)

###########################################
# Find QT
# We need QT - We use a modified version of
# the FindQt4.cmake file that can be set
# to search for different versions of QT
# just point QT_DIR to the right directory
# to skip the use of the default installed
# QT distribution. 
###########################################

IF(SEG3D_BUILD_INTERFACE)

SET(QT_MIN_VERSION "4.6.0")
#SET(QT_DIR "" CACHE PATH "Path to QT")
INCLUDE(FindQt4)

IF (QT_FOUND)
  MESSAGE(STATUS "QTVERSION=${QTVERSION}")
  IF(APPLE AND ${QTVERSION} VERSION_EQUAL 4.8 AND ${QTVERSION} VERSION_LESS 4.8.5)
    MESSAGE(WARNING "Qt 4.8 versions earlier than 4.8.3 contain a bug that disables menu items under some circumstances. Upgrade to a more recent version.")
  ENDIF()

  SET(QT_USE_QTOPENGL 1)
  INCLUDE(${QT_USE_FILE})
ELSE (QT_FOUND)
  MESSAGE(FATAL_ERROR "QT ${QT_MIN_VERSION} or later is required for building Seg3D")
ENDIF (QT_FOUND)

ENDIF(SEG3D_BUILD_INTERFACE)

###########################################
# Configure python
OPTION(BUILD_WITH_PYTHON "Build with python support." ON)
IF(BUILD_WITH_PYTHON)
  ADD_DEFINITIONS(-DBUILD_WITH_PYTHON 
				  -DPy_NO_ENABLE_SHARED 
				  -DBOOST_PYTHON_STATIC_MODULE
				  -DBOOST_PYTHON_STATIC_LIB)
ENDIF(BUILD_WITH_PYTHON)

###########################################
# External packages other than Qt
# Include the External packages, these are
# the packages that are shipped with 
# Seg3D to lower the number of dependencies.
# QT is currently not included as the code
# is a huge repository and to allow it to
# be build against different licensed 
# versions of Qt.
###########################################

ADD_SUBDIRECTORY(Externals)

###########################################
# SETUP FOR DEBUG BUILDS
# enable any extra compile warnings and 
# set any debug-specific variables
# NOTE: This needs to be here as ITK does
#  *NOT* compile with the DEBUG flag set.
#  It looks like ITK's vnl library is missing
#  includes that would allow it to compile
#  with this flag. Hence we only enable it
#  for our code.
###########################################

IF(CMAKE_BUILD_TYPE MATCHES "Debug")
  SET(SEG3D_DEBUG_VERSION "\"(Debug)\"")
ELSE(CMAKE_BUILD_TYPE MATCHES "Debug")
  SET(SEG3D_DEBUG_VERSION "\"\"")
ENDIF(CMAKE_BUILD_TYPE MATCHES "Debug")

###########################################
# Check for "XInitThreads" on X-window
# systems.
###########################################

IF(NOT WIN32 AND NOT APPLE)
  SET(CMAKE_REQUIRED_LIBRARIES ${CMAKE_REQUIRED_LIBRARIES} X11)

  CHECK_C_SOURCE_COMPILES(
	"
	#include <X11/Xlib.h>

	int main()
	{
		XInitThreads();
		return 1;
	}
	"
	X11_THREADSAFE
  )
  IF(${X11_THREADSAFE})
	MESSAGE(STATUS "XInitThreads found")
	OPTION(MULTITHREADED_RENDERING "Enable multi-threaded rendering." OFF)
	IF(MULTITHREADED_RENDERING)
	  ADD_DEFINITIONS(-DX11_THREADSAFE)
	ENDIF(MULTITHREADED_RENDERING)
  ENDIF(${X11_THREADSAFE})
ENDIF(NOT WIN32 AND NOT APPLE)

###########################################
# Build ApplicationConfiguration.h
# this file contains information such as
# version numbers and architecture
# on which code can depend.
###########################################

CONFIGURE_FILE (${CMAKE_CURRENT_SOURCE_DIR}/Configuration/ApplicationConfiguration.h.in 
                ${CMAKE_CURRENT_BINARY_DIR}/ApplicationConfiguration.h 
                @ONLY )

CONFIGURE_FILE (${CMAKE_CURRENT_SOURCE_DIR}/Configuration/InterfaceConfiguration.h.in 
                ${CMAKE_CURRENT_BINARY_DIR}/InterfaceConfiguration.h 
                @ONLY )

INCLUDE_DIRECTORIES(BEFORE ${CMAKE_CURRENT_BINARY_DIR})

###########################################
# Set the include paths
###########################################

INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR})
INCLUDE_DIRECTORIES(${SCI_BOOST_INCLUDE})
INCLUDE_DIRECTORIES(${SCI_ZLIB_INCLUDE})
INCLUDE_DIRECTORIES(${SCI_LIBPNG_INCLUDE})
INCLUDE_DIRECTORIES(${SCI_TEEM_INCLUDE})
INCLUDE_DIRECTORIES(${SCI_GLEW_INCLUDE})
INCLUDE_DIRECTORIES(${SCI_GDCM_INCLUDE})
INCLUDE_DIRECTORIES(${SCI_FREETYPE_INCLUDE})
INCLUDE_DIRECTORIES(${SCI_ITK_INCLUDE})
INCLUDE_DIRECTORIES(${SCI_TINYXML_INCLUDE})
INCLUDE_DIRECTORIES(${SCI_MATLABIO_INCLUDE})
INCLUDE_DIRECTORIES(${SCI_HDF5_INCLUDE})
INCLUDE_DIRECTORIES(${SCI_SQLITE_INCLUDE})
INCLUDE_DIRECTORIES(${SCI_MRC2000IO_INCLUDE})

IF(BUILD_WITH_PYTHON)
  INCLUDE_DIRECTORIES(${SCI_PYTHON_INCLUDE})
  ADD_DEFINITIONS(-DPy_NO_ENABLE_SHARED)
  INCLUDE(CMake/GenerateActionPythonWrapper.cmake)
ENDIF(BUILD_WITH_PYTHON)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

###########################################
# Generate a variable for registering all
# the plugins
###########################################

INCLUDE(CMake/Core.cmake)
INCLUDE(CMake/RegisterClass.cmake)

###########################################

SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Modules")

###########################################
# Application layers:
#  Core - Core functionality
#  Application - All pieces need for the
#          application specific to Seg3D
#  Interface - Seg3D interface
#  Main - Main function of the application
#
# Auxillary layers:
#  QtUtils - binding QtWidgets and abstract
#            class around Qt implementations
#  Resources - Icons, images, etc.
###########################################

MESSAGE(STATUS "Configuring Seg3D Core")
ADD_SUBDIRECTORY(Core)

MESSAGE(STATUS "Configuring Seg3D Application")
ADD_SUBDIRECTORY(Application)

MESSAGE(STATUS "Configuring Seg3D Interface")
IF(SEG3D_BUILD_INTERFACE)
  ADD_SUBDIRECTORY(QtUtils)
  ADD_SUBDIRECTORY(Interface)
ENDIF(SEG3D_BUILD_INTERFACE)

###########################################
# Plugins:
# Plugin libraries need be generated before
# we build the registration objects as they
# may contain as well pieces that need to
# be registered in the main object 
# factories.
###########################################

SET(IGNORE_RESOURCES FALSE CACHE INTERNAL "Ignore default resources library." FORCE)

MESSAGE(STATUS "Configuring Seg3D Plugins")
FILE(GLOB PLUGIN_DIRS "Plugins/*" )

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/Plugins")

FOREACH(DIR ${PLUGIN_DIRS})
  IF(NOT ${DIR} MATCHES "Plugins/.svn")
	IF(IS_DIRECTORY ${DIR}) 
      ADD_SUBDIRECTORY(${DIR})
	ENDIF(IS_DIRECTORY ${DIR}) 
  ENDIF(NOT ${DIR} MATCHES "Plugins/.svn")
ENDFOREACH(DIR ${PLUGIN_DIRS})

###########################################
# Rsources:
# images + icons
###########################################


IF(NOT IGNORE_RESOURCES)
MESSAGE(STATUS "Configuring Seg3D Resources")
IF(SEG3D_BUILD_INTERFACE)
  ADD_SUBDIRECTORY(Resources)
ENDIF(SEG3D_BUILD_INTERFACE)
ENDIF(NOT IGNORE_RESOURCES)


###########################################
# Main:
# Main needs to be included after custom 
# plugins
###########################################


IF(SEG3D_BUILD_INTERFACE)
  MESSAGE(STATUS "Configuring Seg3D main")
  ADD_SUBDIRECTORY(Main)
ENDIF(SEG3D_BUILD_INTERFACE)


###########################################
# Build the plugin generator files
# This code will automatically register all
# the components with the proper object
# factories
###########################################

MESSAGE(STATUS "Configuring Seg3D registered functions")
GENERATE_REGISTRATION_FILES()

###########################################
# Generate the python functions registration file
###########################################

IF(BUILD_WITH_PYTHON)
  MESSAGE(STATUS "Configuring action python wrapper functions")
  GENERATE_ACTION_PYTHON_WRAPPER_REGISTRATION_FILE()
ENDIF(BUILD_WITH_PYTHON)

###########################################
# Bootstrap
# Add code for packaging shaders and other
# objects into the executable
###########################################

ADD_SUBDIRECTORY(Bootstrap)

###########################################
# Configure LaTeX and Doxygen documentation
###########################################

FIND_PACKAGE(LATEX)

OPTION(BUILD_DOCUMENTATION "Build documentation" OFF)
MARK_AS_ADVANCED(BUILD_DOCUMENTATION)

IF(PDFLATEX_COMPILER)
  IF(BUILD_DOCUMENTATION)
    ADD_SUBDIRECTORY(Documentation)
  ENDIF(BUILD_DOCUMENTATION)
ENDIF(PDFLATEX_COMPILER)

IF(BUILD_DOCUMENTATION)
  OPTION(BUILD_DOXYGEN_DOCUMENTATION "Generate doxygen-based documentation." OFF)
  MARK_AS_ADVANCED(BUILD_DOXYGEN_DOCUMENTATION)

  IF(BUILD_DOXYGEN_DOCUMENTATION)
    FIND_PACKAGE(Doxygen)

    IF(DOXYGEN_FOUND)
      ADD_SUBDIRECTORY(Documentation/Doxygen)
    ELSE()
      SET(BUILD_DOXYGEN_DOCUMENTATION OFF CACHE BOOL "Generate doxygen-based documentation." FORCE)
    ENDIF()

  ENDIF(BUILD_DOXYGEN_DOCUMENTATION)
ENDIF(BUILD_DOCUMENTATION)

###########################################
# Packaging:
# This part sets up the packager using
# CPack.
###########################################

MESSAGE(STATUS "Configuring Seg3D packaging")

INCLUDE(InstallRequiredSystemLibraries)

SET(CPACK_PACKAGE_NAME "${APPLICATION_NAME}")

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${APPLICATION_NAME}")
SET(CPACK_PACKAGE_VENDOR "${APPLICATION_VENDOR}")
      
SET(CPACK_PACKAGE_DESCRIPTION_FILE ${PACKAGING_README} )
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${APPLICATION_NAME} ${SEG3D_MAJOR_VERSION}.${SEG3D_MINOR_VERSION}.${SEG3D_PATCH_VERSION} is a segmentation program")

SET(CPACK_RESOURCE_FILE_LICENSE ${PACKAGING_LICENSE})
SET(CPACK_RESOURCE_FILE_README ${PACKAGING_RELEASENOTES})
SET(CPACK_RESOURCE_FILE_WELCOME ${PACKAGING_WELCOME})

SET(CPACK_PACKAGE_VERSION_MAJOR "${SEG3D_MAJOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_MINOR "${SEG3D_MINOR_VERSION}")
SET(CPACK_PACKAGE_VERSION_PATCH "${SEG3D_PATCH_VERSION}")

SET(CPACK_PACKAGE_INSTALL_DIRECTORY 
    "${APPLICATION_NAME} ${SEG3D_MAJOR_VERSION}.${SEG3D_MINOR_VERSION}")
    
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSIS that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backslashes.
  SET(CPACK_PACKAGE_ICON "${PACKAGING_ICON}")
  
  IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET(CPACK_INSTALL_PREFIX "/" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
    SET(CMAKE_INSTALL_PREFIX "/" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
  ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  
  IF(CMAKE_SIZEOF_VOID_P MATCHES 8)
    SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
  ELSE(CMAKE_SIZEOF_VOID_P MATCHES 8)
    SET(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
  ENDIF(CMAKE_SIZEOF_VOID_P MATCHES 8)	
  
  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\${APPLICATION_NAME}")
  SET(CPACK_NSIS_MUI_ICON "${APPLICATION_WINDOWS_ICON}")
  SET(CPACK_NSIS_DISPLAY_NAME "${APPLICATION_NAME} ${SEG3D_MAJOR_VERSION}.${SEG3D_MINOR_VERSION}")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\${APPLICATION_URL}")
  SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\${APPLICATION_URL}")
  SET(CPACK_NSIS_CONTACT ${APPLICATION_CONTACT} )
  SET(CPACK_NSIS_MODIFY_PATH ON)
  SET(CPACK_PACKAGE_EXECUTABLES "${APPLICATION_NAME}" "${APPLICATION_NAME}")
  SET(CPACK_NSIS_EXTRA_INSTALL_COMMANDS "
	WriteRegStr HKCR '.nrrd' '' '${APPLICATION_NAME}-nrrd'
	WriteRegStr HKCR '${APPLICATION_NAME}-nrrd' '' '${APPLICATION_NAME} NRRD File'
	WriteRegStr HKCR '${APPLICATION_NAME}-nrrd\\\\shell' '' 'open'
	WriteRegStr HKCR '${APPLICATION_NAME}-nrrd\\\\DefaultIcon' '' '$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe,0'
	WriteRegStr HKCR '${APPLICATION_NAME}-nrrd\\\\shell\\\\open\\\\command' '' '$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe \\\"%1\\\"'
	WriteRegStr HKCR '${APPLICATION_NAME}-nrrd\\\\shell\\\\edit' '' 'Open NRRD Data File'
	WriteRegStr HKCR '${APPLICATION_NAME}-nrrd\\\\shell\\\\edit\\\\command' '' '$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe \\\"%1\\\"'
	#System::Call 'Shell32::SHChangeNotify( i 0x800000, i 0, i 0, i 0)'
	WriteRegStr HKCR '.nhdr' '' '${APPLICATION_NAME}-nhdr'
	WriteRegStr HKCR '${APPLICATION_NAME}-nhdr' '' '${APPLICATION_NAME} NHDR File'
	WriteRegStr HKCR '${APPLICATION_NAME}-nhdr\\\\shell' '' 'open'
	WriteRegStr HKCR '${APPLICATION_NAME}-nhdr\\\\DefaultIcon' '' '$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe,0'
	WriteRegStr HKCR '${APPLICATION_NAME}-nhdr\\\\shell\\\\open\\\\command' '' '$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe \\\"%1\\\"'
	WriteRegStr HKCR '${APPLICATION_NAME}-nhdr\\\\shell\\\\edit' '' 'Open NHDR Data File'
	WriteRegStr HKCR '${APPLICATION_NAME}-nhdr\\\\shell\\\\edit\\\\command' '' '$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe \\\"%1\\\"'
	#System::Call 'Shell32::SHChangeNotify( i 0x800000, i 0, i 0, i 0)'
	WriteRegStr HKCR '${APPLICATION_EXTENSION}' '' '${APPLICATION_NAME}'
	WriteRegStr HKCR '${APPLICATION_NAME}' '' '${APPLICATION_NAME} Project File'
	WriteRegStr HKCR '${APPLICATION_NAME}\\\\shell' '' 'open'
	WriteRegStr HKCR '${APPLICATION_NAME}\\\\DefaultIcon' '' '$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe,0'
	WriteRegStr HKCR '${APPLICATION_NAME}\\\\shell\\\\open\\\\command' '' '$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe \\\"%1\\\"'
	WriteRegStr HKCR '${APPLICATION_NAME}\\\\shell\\\\edit' '' 'Open ${APPLICATION_NAME} Project File'
	WriteRegStr HKCR '${APPLICATION_NAME}\\\\shell\\\\edit\\\\command' '' '$INSTDIR\\\\bin\\\\${APPLICATION_NAME}.exe \\\"%1\\\"'
	System::Call 'Shell32::SHChangeNotify( i 0x800000, i 0, i 0, i 0)'
  ")
  SET(CPACK_NSIS_EXTRA_UNINSTALL_COMMANDS "
	DeleteRegKey HKCR '.nrrd'
	DeleteRegKey HKCR '.nhdr'
	DeleteRegKey HKCR '${APPLICATION_EXTENSION}'
	DeleteRegKey HKCR '${APPLICATION_NAME}'
  ")
ELSE(WIN32 AND NOT UNIX)
  IF(APPLE)
    SET(CPACK_PACKAGE_DEFAULT_LOCATION "/Applications/")
    SET(CPACK_TOPLEVEL_TAG "")
    IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
      SET(CPACK_INSTALL_PREFIX "/" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
      SET(CMAKE_INSTALL_PREFIX "/" CACHE PATH "Install path prefix, prepended onto install directories." FORCE)
    ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    SET(CPACK_PACKAGING_INSTALL_PREFIX "/")
    SET(CPACK_STRIP_FILES TRUE)
    SET(CPACK_SOURCE_STRIP_FILES TRUE)
    SET(CPACK_PACKAGE_EXECUTABLES "${APPLICATION_NAME}.app" "${APPLICATION_NAME}")
  ELSE(APPLE)
    SET(CPACK_STRIP_FILES TRUE)
    SET(CPACK_SOURCE_STRIP_FILES TRUE)
    SET(CPACK_PACKAGE_EXECUTABLES "${APPLICATION_NAME}" "${APPLICATION_NAME}")
  ENDIF(APPLE)
ENDIF(WIN32 AND NOT UNIX)

INCLUDE(CPack)
