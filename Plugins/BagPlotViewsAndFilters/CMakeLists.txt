set(qrc_files)

if (PARAVIEW_USE_QT)
  list(APPEND qrc_files
    BagPlotViewsAndFilters.qrc)
endif ()

paraview_add_plugin(BagPlotViewsAndFilters
  REQUIRED_ON_CLIENT
  REQUIRED_ON_SERVER
  VERSION "1.0"
  SERVER_MANAGER_XML BagPlotViewsAndFilters.xml
  UI_RESOURCES ${qrc_files}
  MODULES BagPlotViewsAndFilters::BagPlotViewsAndFiltersBagPlot
  MODULE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/BagPlot/vtk.module")

if (BUILD_TESTING)
  add_subdirectory(Testing)
endif()
