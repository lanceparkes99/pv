/*=========================================================================

Program:   Visualization Toolkit
Module:    vtkZSpaceSDKManager.cxx

Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
All rights reserved.
See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkZSpaceSDKManager.h"

#include "vtkMatrix4x4.h"
#include "vtkObjectFactory.h"
#include "vtkRenderWindow.h"
#include "vtkSmartPointer.h"
#include "vtkTransform.h"
#include "vtkZSpaceSDKVersion.h"

#ifdef ZSPACE_USE_COMPAT_SDK
#include "vtkZSpaceCoreCompatibilitySDKManager.h"
#else
#include "vtkZSpaceCoreSDKManager.h"
#endif

//------------------------------------------------------------------------------
vtkZSpaceSDKManager::vtkZSpaceSDKManager() = default;

//----------------------------------------------------------------------------
vtkZSpaceSDKManager::~vtkZSpaceSDKManager() = default;

//----------------------------------------------------------------------------
vtkZSpaceSDKManager* vtkZSpaceSDKManager::GetInstance()
{
  static vtkSmartPointer<vtkZSpaceSDKManager> instance = nullptr;
  if (instance.GetPointer() == nullptr)
  {
#ifdef ZSPACE_USE_COMPAT_SDK
    instance = vtkSmartPointer<vtkZSpaceCoreCompatibilitySDKManager>::New();
#else
    instance = vtkSmartPointer<vtkZSpaceCoreSDKManager>::New();
#endif
  }

  return instance;
}

//----------------------------------------------------------------------------
void vtkZSpaceSDKManager::SetRenderWindow(vtkRenderWindow* renderWindow)
{
  this->RenderWindow = renderWindow;
};

//------------------------------------------------------------------------------
void vtkZSpaceSDKManager::Update()
{
  this->UpdateViewport();
  this->UpdateViewAndProjectionMatrix();
  this->UpdateTrackers();
  this->UpdateButtonState();
}

//------------------------------------------------------------------------------
void vtkZSpaceSDKManager::SetClippingRange(const float nearPlane, const float farPlane)
{
  this->NearPlane = nearPlane;
  this->FarPlane = farPlane;
}

//------------------------------------------------------------------------------
vtkMatrix4x4* vtkZSpaceSDKManager::GetStereoViewMatrix(bool leftEye)
{
  return leftEye ? this->LeftEyeViewMatrix : this->RightEyeViewMatrix;
}

//------------------------------------------------------------------------------
vtkMatrix4x4* vtkZSpaceSDKManager::GetStereoProjectionMatrix(bool leftEye)
{
  return leftEye ? this->LeftEyeProjectionMatrix : this->RightEyeProjectionMatrix;
}

//------------------------------------------------------------------------------
void vtkZSpaceSDKManager::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);

  os << indent << "WindowX: " << this->WindowX << "\n";
  os << indent << "WindowY: " << this->WindowY << "\n";
  os << indent << "WindowWidth: " << this->WindowWidth << "\n";
  os << indent << "WindowHeight: " << this->WindowHeight << "\n";
  os << indent << "NbDisplays: " << this->Displays.size() << "\n";
  for (auto const& display : this->Displays)
  {
    os << indent << "\t" << display << "\n";
  }
  os << indent << "StylusTargets: " << this->StylusTargets << "\n";
  os << indent << "HeadTargets: " << this->HeadTargets << "\n";
  os << indent << "SecondaryTargets: " << this->SecondaryTargets << "\n";
  os << indent << "InterPupillaryDistance: " << this->InterPupillaryDistance << "\n";
  os << indent << "ViewerScale: " << this->ViewerScale << "\n";
  os << indent << "NearPlane: " << this->NearPlane << "\n";
  os << indent << "FarPlane: " << this->FarPlane << "\n";
  os << indent << "LeftButtonState: " << this->LeftButtonState << "\n";
  os << indent << "MiddleButtonState: " << this->MiddleButtonState << "\n";
  os << indent << "RightButtonState: " << this->RightButtonState << "\n";
}
