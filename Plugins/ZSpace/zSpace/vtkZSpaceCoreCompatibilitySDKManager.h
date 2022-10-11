/*=========================================================================

Program:   Visualization Toolkit

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
All rights reserved.
See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkZSpaceCoreCompatibilitySDKManager
 * @brief   zSpace Core Compatibility SDK manager class.
 *
 * Class handling the interactions between the zSpace plugin
 * and the zSpace Core Compatibility SDK.
 *
 * @see vtkZSpaceSDKManager
 */

#ifndef vtkZSpaceCoreCompatibilitySDKManager_h
#define vtkZSpaceCoreCompatibilitySDKManager_h

#include "vtkZSpaceSDKManager.h"
#include "vtkZSpaceViewModule.h" // for export macro

#include <Windows.h>                 // for HMODULE
#include <vector>                    // for std::vector
#include <zSpaceCoreCompatibility.h> // zspace header

/**
 * Structure holding the loaded zSpace Core Compatibility
 * API entry point function pointers
 */
struct zSpaceCoreCompatEntryPoints
{
  // Use the zSpace Core Compatibilty API function name reflection macro to
  // auto-generate function pointer members for all zSpace Core Compatibility
  // API entry point functions.

#define ZC_COMPAT_SAMPLE_LOCAL_ENTRY_POINT_MEMBER(undecoratedFuncName)                             \
  ZCCompat##undecoratedFuncName##FuncPtrType zccompat##undecoratedFuncName;                        \
  /**/

  ZC_COMPAT_REFLECTION_LIST_UNDECORATED_FUNC_NAMES(ZC_COMPAT_SAMPLE_LOCAL_ENTRY_POINT_MEMBER)

#undef ZC_COMPAT_SAMPLE_LOCAL_ENTRY_POINT_MEMBER
};

class vtkRenderWindow;
class vtkMatrix4x4;

class VTKZSPACEVIEW_EXPORT vtkZSpaceCoreCompatibilitySDKManager : public vtkZSpaceSDKManager
{
public:
  static vtkZSpaceCoreCompatibilitySDKManager* New();
  vtkTypeMacro(vtkZSpaceCoreCompatibilitySDKManager, vtkObject);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * Initialize the zSpace SDK and check for zSpace devices :
   * the display, the stylus and the head trackers.
   */
  void InitializeZSpace() override;

  /**
   * Update the zSpace viewport position and size based
   * on the position and size of the application window.
   */
  void UpdateViewport() override;

  /**
   * Update the position of the stylus and head trakers.
   */
  void UpdateTrackers() override;

  /**
   * Update the zSpace view and projection matrix for each eye.
   */
  void UpdateViewAndProjectionMatrix() override;

  /**
   * Update the stylus buttons state.
   */
  void UpdateButtonState() override;

  /**
   * Let zSpace compute the viewer scale, camera position and camera view up from the
   * input bounds.
   */
  void CalculateFrustumFit(const double bounds[6], double position[3], double viewUp[3]) override;

  ///@{
  /**
   * Notify the zSpace SDK for the begining/end of a frame.
   */
  void BeginFrame() override;
  void EndFrame() override;
  ///@}

  ///@{
  /**
   * Set the render windwow the manager makes viewport computations
   * from. Overriden to pass the related Windows window handle to
   * the SDK.
   */
  void SetRenderWindow(vtkRenderWindow*) override;
  ///@}

protected:
  vtkZSpaceCoreCompatibilitySDKManager();
  ~vtkZSpaceCoreCompatibilitySDKManager() override;

  ZCCompatContext ZSpaceContext = nullptr;
  ZCCompatDisplay DisplayHandle = nullptr;
  ZCCompatViewport ViewportHandle = nullptr;
  ZCCompatFrustum FrustumHandle = nullptr;
  ZCCompatTarget StylusHandle = nullptr;

  // Store the API functions entry points.
  zSpaceCoreCompatEntryPoints EntryPts;

  // Handle to the zSpace Core Compatibility API dynamic library (.dll).
  HMODULE zSpaceCoreCompatDllModuleHandle;

  // Handle to the current window
  HWND WidondowHandle;

  /**
   * Load the "zSpaceCoreCompatibility64.dll" shared library then load the
   * zSpace Core Compatibility API entry point functions (at runtime)
   */
  bool loadZspaceCoreCompatibilityEntryPoints(const char* zSpaceCoreCompatDllFilePath,
    HMODULE& zSpaceCoreCompatDllModuleHandle, zSpaceCoreCompatEntryPoints& entryPoints);

  /**
   * zSpace stores matrix in column-major format (as OpenGL). The matrix
   * needs to be transposed to be used by VTK.
   */
  void ConvertAndTransposeZSpaceMatrixToVTKMatrix(ZSMatrix4 zSpaceMatrix, vtkMatrix4x4* vtkMatrix);

  /**
   * zSpace stores matrix in column-major format (as OpenGL). The matrix
   * needs to be transposed to be used by VTK.
   */
  void ConvertZSpaceMatrixToVTKMatrix(ZSMatrix4 zSpaceMatrix, vtkMatrix4x4* vtkMatrix);

private:
  vtkZSpaceCoreCompatibilitySDKManager(const vtkZSpaceCoreCompatibilitySDKManager&) = delete;
  void operator=(const vtkZSpaceCoreCompatibilitySDKManager&) = delete;
};

#endif
