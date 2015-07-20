// Created on: 2015-06-10
// Created by: Kirill Gavrilov
// Copyright (c) 2015 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#ifndef _D3DHost_GraphicDriver_HeaderFile
#define _D3DHost_GraphicDriver_HeaderFile

#include <OpenGl_GraphicDriver.hxx>

class Visual3d_View;
struct IDirect3DSurface9;

//! This class defines D3D host for an OpenGl graphic driver
class D3DHost_GraphicDriver : public OpenGl_GraphicDriver
{
public:

  //! Constructor.
  Standard_EXPORT D3DHost_GraphicDriver();

  //! Destructor.
  Standard_EXPORT virtual ~D3DHost_GraphicDriver();

  //! Create new view.
  Standard_EXPORT virtual Standard_Boolean View (Graphic3d_CView& theCView);

  //! Return D3D surface for specified view.
  Standard_EXPORT IDirect3DSurface9* D3dColorSurface (const Handle(Visual3d_View)& theCView) const;

public:

  DEFINE_STANDARD_RTTI(D3DHost_GraphicDriver, OpenGl_GraphicDriver)

};

DEFINE_STANDARD_HANDLE(D3DHost_GraphicDriver, OpenGl_GraphicDriver)

#endif // _D3DHost_GraphicDriver_HeaderFile
