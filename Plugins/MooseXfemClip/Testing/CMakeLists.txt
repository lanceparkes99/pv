ExternalData_Expand_Arguments("ParaViewData" _
  "DATA{Data/,REGEX:init_solution_propagation_out\\.e.*}")

set (TestMooseXfemClip_FORCE_SERIAL TRUE)  # since this uses popup-menu

paraview_add_client_tests(
  LOAD_PLUGINS "MooseXfemClip;LegacyExodusReader"
  BASELINE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Data/Baseline"
  TEST_DATA_TARGET ParaViewData
  TEST_SCRIPTS TestMooseXfemClip.xml
)
