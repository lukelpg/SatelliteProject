#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "perturb::perturb" for configuration ""
set_property(TARGET perturb::perturb APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(perturb::perturb PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libperturb.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS perturb::perturb )
list(APPEND _IMPORT_CHECK_FILES_FOR_perturb::perturb "${_IMPORT_PREFIX}/lib/libperturb.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
