########### AGGREGATED COMPONENTS AND DEPENDENCIES FOR THE MULTI CONFIG #####################
#############################################################################################

set(fontconfig_COMPONENT_NAMES "")
if(DEFINED fontconfig_FIND_DEPENDENCY_NAMES)
  list(APPEND fontconfig_FIND_DEPENDENCY_NAMES Freetype EXPAT)
  list(REMOVE_DUPLICATES fontconfig_FIND_DEPENDENCY_NAMES)
else()
  set(fontconfig_FIND_DEPENDENCY_NAMES Freetype EXPAT)
endif()
set(Freetype_FIND_MODE "MODULE")
set(EXPAT_FIND_MODE "MODULE")

########### VARIABLES #######################################################################
#############################################################################################
set(fontconfig_PACKAGE_FOLDER_DEBUG "/home/htrq/.conan2/p/b/fontce7dca713c2c76/p")
set(fontconfig_BUILD_MODULES_PATHS_DEBUG )


set(fontconfig_INCLUDE_DIRS_DEBUG )
set(fontconfig_RES_DIRS_DEBUG )
set(fontconfig_DEFINITIONS_DEBUG )
set(fontconfig_SHARED_LINK_FLAGS_DEBUG )
set(fontconfig_EXE_LINK_FLAGS_DEBUG )
set(fontconfig_OBJECTS_DEBUG )
set(fontconfig_COMPILE_DEFINITIONS_DEBUG )
set(fontconfig_COMPILE_OPTIONS_C_DEBUG )
set(fontconfig_COMPILE_OPTIONS_CXX_DEBUG )
set(fontconfig_LIB_DIRS_DEBUG "${fontconfig_PACKAGE_FOLDER_DEBUG}/lib")
set(fontconfig_BIN_DIRS_DEBUG )
set(fontconfig_LIBRARY_TYPE_DEBUG STATIC)
set(fontconfig_IS_HOST_WINDOWS_DEBUG 0)
set(fontconfig_LIBS_DEBUG fontconfig)
set(fontconfig_SYSTEM_LIBS_DEBUG m pthread)
set(fontconfig_FRAMEWORK_DIRS_DEBUG )
set(fontconfig_FRAMEWORKS_DEBUG )
set(fontconfig_BUILD_DIRS_DEBUG )
set(fontconfig_NO_SONAME_MODE_DEBUG FALSE)


# COMPOUND VARIABLES
set(fontconfig_COMPILE_OPTIONS_DEBUG
    "$<$<COMPILE_LANGUAGE:CXX>:${fontconfig_COMPILE_OPTIONS_CXX_DEBUG}>"
    "$<$<COMPILE_LANGUAGE:C>:${fontconfig_COMPILE_OPTIONS_C_DEBUG}>")
set(fontconfig_LINKER_FLAGS_DEBUG
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,SHARED_LIBRARY>:${fontconfig_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,MODULE_LIBRARY>:${fontconfig_SHARED_LINK_FLAGS_DEBUG}>"
    "$<$<STREQUAL:$<TARGET_PROPERTY:TYPE>,EXECUTABLE>:${fontconfig_EXE_LINK_FLAGS_DEBUG}>")


set(fontconfig_COMPONENTS_DEBUG )