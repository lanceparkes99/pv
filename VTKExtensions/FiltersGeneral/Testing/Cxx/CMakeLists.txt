vtk_add_test_cxx(vtkPVVTKExtensionsFiltersGeneralCxxTests tests
  NO_VALID NO_OUTPUT
  TestHyperTreeGridGradient.cxx
  TestPolyhedralToSimpleCellsFilter.cxx)
vtk_test_cxx_executable(vtkPVVTKExtensionsFiltersGeneralCxxTests tests
  vtkErrorObserver.cxx )
