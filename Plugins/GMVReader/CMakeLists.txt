paraview_add_plugin(GMVReader
  REQUIRED_ON_CLIENT
  REQUIRED_ON_SERVER
  VERSION "1.0"
  MODULES GMVReader::vtkGMVReader
  MODULE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Reader/vtk.module")

# TODO: What to do with pqGMVReaderPanel? This is needed if it is to be used.
target_link_libraries(GMVReader
  PRIVATE
    ParaView::RemotingServerManager)
target_compile_definitions(GMVReader PRIVATE QT_NO_KEYWORDS)

if (BUILD_TESTING)
  add_subdirectory(Testing)
endif ()
