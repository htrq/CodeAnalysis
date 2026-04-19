# Avoid multiple calls to find_package to append duplicated properties to the targets
include_guard()########### VARIABLES #######################################################################
#############################################################################################
set(fontconfig_FRAMEWORKS_FOUND_DEBUG "") # Will be filled later
conan_find_apple_frameworks(fontconfig_FRAMEWORKS_FOUND_DEBUG "${fontconfig_FRAMEWORKS_DEBUG}" "${fontconfig_FRAMEWORK_DIRS_DEBUG}")

set(fontconfig_LIBRARIES_TARGETS "") # Will be filled later


######## Create an interface target to contain all the dependencies (frameworks, system and conan deps)
if(NOT TARGET fontconfig_DEPS_TARGET)
    add_library(fontconfig_DEPS_TARGET INTERFACE IMPORTED)
endif()

set_property(TARGET fontconfig_DEPS_TARGET
             APPEND PROPERTY INTERFACE_LINK_LIBRARIES
             $<$<CONFIG:Debug>:${fontconfig_FRAMEWORKS_FOUND_DEBUG}>
             $<$<CONFIG:Debug>:${fontconfig_SYSTEM_LIBS_DEBUG}>
             $<$<CONFIG:Debug>:Freetype::Freetype;EXPAT::EXPAT>)

####### Find the libraries declared in cpp_info.libs, create an IMPORTED target for each one and link the
####### fontconfig_DEPS_TARGET to all of them
conan_package_library_targets("${fontconfig_LIBS_DEBUG}"    # libraries
                              "${fontconfig_LIB_DIRS_DEBUG}" # package_libdir
                              "${fontconfig_BIN_DIRS_DEBUG}" # package_bindir
                              "${fontconfig_LIBRARY_TYPE_DEBUG}"
                              "${fontconfig_IS_HOST_WINDOWS_DEBUG}"
                              fontconfig_DEPS_TARGET
                              fontconfig_LIBRARIES_TARGETS  # out_libraries_targets
                              "_DEBUG"
                              "fontconfig"    # package_name
                              "${fontconfig_NO_SONAME_MODE_DEBUG}")  # soname

# FIXME: What is the result of this for multi-config? All configs adding themselves to path?
set(CMAKE_MODULE_PATH ${fontconfig_BUILD_DIRS_DEBUG} ${CMAKE_MODULE_PATH})

########## GLOBAL TARGET PROPERTIES Debug ########################################
    set_property(TARGET Fontconfig::Fontconfig
                 APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                 $<$<CONFIG:Debug>:${fontconfig_OBJECTS_DEBUG}>
                 $<$<CONFIG:Debug>:${fontconfig_LIBRARIES_TARGETS}>
                 )

    if("${fontconfig_LIBS_DEBUG}" STREQUAL "")
        # If the package is not declaring any "cpp_info.libs" the package deps, system libs,
        # frameworks etc are not linked to the imported targets and we need to do it to the
        # global target
        set_property(TARGET Fontconfig::Fontconfig
                     APPEND PROPERTY INTERFACE_LINK_LIBRARIES
                     fontconfig_DEPS_TARGET)
    endif()

    set_property(TARGET Fontconfig::Fontconfig
                 APPEND PROPERTY INTERFACE_LINK_OPTIONS
                 $<$<CONFIG:Debug>:${fontconfig_LINKER_FLAGS_DEBUG}>)
    set_property(TARGET Fontconfig::Fontconfig
                 APPEND PROPERTY INTERFACE_INCLUDE_DIRECTORIES
                 $<$<CONFIG:Debug>:${fontconfig_INCLUDE_DIRS_DEBUG}>)
    # Necessary to find LINK shared libraries in Linux
    set_property(TARGET Fontconfig::Fontconfig
                 APPEND PROPERTY INTERFACE_LINK_DIRECTORIES
                 $<$<CONFIG:Debug>:${fontconfig_LIB_DIRS_DEBUG}>)
    set_property(TARGET Fontconfig::Fontconfig
                 APPEND PROPERTY INTERFACE_COMPILE_DEFINITIONS
                 $<$<CONFIG:Debug>:${fontconfig_COMPILE_DEFINITIONS_DEBUG}>)
    set_property(TARGET Fontconfig::Fontconfig
                 APPEND PROPERTY INTERFACE_COMPILE_OPTIONS
                 $<$<CONFIG:Debug>:${fontconfig_COMPILE_OPTIONS_DEBUG}>)

########## For the modules (FindXXX)
set(fontconfig_LIBRARIES_DEBUG Fontconfig::Fontconfig)
