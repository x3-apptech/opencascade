// Created on: 2011-10-20
// Created by: Sergey ZERCHANINOV
// Copyright (c) 2011-2013 OPEN CASCADE SAS
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

#ifdef HAVE_CONFIG_H
  #include <config.h>
#endif

#include <OpenGl_GraphicDriver.hxx>
#include <OpenGl_Context.hxx>
#include <OpenGl_Flipper.hxx>
#include <OpenGl_GraduatedTrihedron.hxx>
#include <OpenGl_Group.hxx>
#include <OpenGl_CView.hxx>
#include <OpenGl_View.hxx>
#include <OpenGl_StencilTest.hxx>
#include <OpenGl_Text.hxx>
#include <OpenGl_Trihedron.hxx>
#include <OpenGl_Workspace.hxx>

#include <Standard_NotImplemented.hxx>

IMPLEMENT_STANDARD_HANDLE(OpenGl_GraphicDriver,Graphic3d_GraphicDriver)
IMPLEMENT_STANDARD_RTTIEXT(OpenGl_GraphicDriver,Graphic3d_GraphicDriver)

namespace
{
  static const Handle(OpenGl_Context) TheNullGlCtx;
};

// Pour eviter de "mangler" MetaGraphicDriverFactory, le nom de la
// fonction qui cree un Graphic3d_GraphicDriver.
// En effet, ce nom est recherche par la methode DlSymb de la
// classe OSD_SharedLibrary dans la methode SetGraphicDriver de la
// classe Graphic3d_GraphicDevice
extern "C" {
#if defined(_MSC_VER) // disable MS VC++ warning on C-style function returning C++ object
  #pragma warning(push)
  #pragma warning(disable:4190)
#endif
  Standard_EXPORT Handle(Graphic3d_GraphicDriver) MetaGraphicDriverFactory (const Standard_CString theShrName)
  {
    Handle(OpenGl_GraphicDriver) aDriver = new OpenGl_GraphicDriver (theShrName);
    return aDriver;
  }
#if defined(_MSC_VER)
  #pragma warning(pop)
#endif
}

// =======================================================================
// function : OpenGl_GraphicDriver
// purpose  :
// =======================================================================
OpenGl_GraphicDriver::OpenGl_GraphicDriver (const Handle(Aspect_DisplayConnection)& theDisplayConnection)
: Graphic3d_GraphicDriver ("TKOpenGl"),
  myCaps           (new OpenGl_Caps()),
  myMapOfView      (1, NCollection_BaseAllocator::CommonBaseAllocator()),
  myMapOfWS        (1, NCollection_BaseAllocator::CommonBaseAllocator()),
  myMapOfStructure (1, NCollection_BaseAllocator::CommonBaseAllocator()),
  myUserDrawCallback (NULL),
  myTempText (new OpenGl_Text())
{
  Begin (theDisplayConnection);
}

// =======================================================================
// function : OpenGl_GraphicDriver
// purpose  :
// =======================================================================
OpenGl_GraphicDriver::OpenGl_GraphicDriver (const Standard_CString theShrName)
: Graphic3d_GraphicDriver (theShrName),
  myCaps           (new OpenGl_Caps()),
  myMapOfView      (1, NCollection_BaseAllocator::CommonBaseAllocator()),
  myMapOfWS        (1, NCollection_BaseAllocator::CommonBaseAllocator()),
  myMapOfStructure (1, NCollection_BaseAllocator::CommonBaseAllocator()),
  myUserDrawCallback (NULL),
  myTempText (new OpenGl_Text())
{
  //
}

// =======================================================================
// function : UserDrawCallback
// purpose  :
// =======================================================================
OpenGl_GraphicDriver::OpenGl_UserDrawCallback_t& OpenGl_GraphicDriver::UserDrawCallback()
{
  return myUserDrawCallback;
}

// =======================================================================
// function : DefaultTextHeight
// purpose  :
// =======================================================================
Standard_ShortReal OpenGl_GraphicDriver::DefaultTextHeight() const
{
  return 16.;
}

// =======================================================================
// function : EnableVBO
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::EnableVBO (const Standard_Boolean theToTurnOn)
{
  myCaps->vboDisable = !theToTurnOn;
}

// =======================================================================
// function : GetSharedContext
// purpose  :
// =======================================================================
const Handle(OpenGl_Context)& OpenGl_GraphicDriver::GetSharedContext() const
{
  if (myMapOfWS.IsEmpty())
  {
    return TheNullGlCtx;
  }

  NCollection_DataMap<Standard_Integer, Handle(OpenGl_Workspace)>::Iterator anIter (myMapOfWS);
  return anIter.Value()->GetGlContext();
}

// =======================================================================
// function : MemoryInfo
// purpose  :
// =======================================================================
Standard_Boolean OpenGl_GraphicDriver::MemoryInfo (Standard_Size&           theFreeBytes,
                                                   TCollection_AsciiString& theInfo) const
{
  // this is extra work (for OpenGl_Context initialization)...
  OpenGl_Context aGlCtx;
  if (!aGlCtx.Init())
  {
    return Standard_False;
  }
  theFreeBytes = aGlCtx.AvailableMemory();
  theInfo      = aGlCtx.MemoryInfo();
  return !theInfo.IsEmpty();
}

// =======================================================================
// function : SetImmediateModeDrawToFront
// purpose  :
// =======================================================================
Standard_Boolean OpenGl_GraphicDriver::SetImmediateModeDrawToFront (const Graphic3d_CView& theCView,
                                                                    const Standard_Boolean theDrawToFrontBuffer)
{
  if (theCView.ViewId == -1)
  {
    return Standard_False;
  }

  const OpenGl_CView* aCView = (const OpenGl_CView* )theCView.ptrView;
  if (aCView != NULL)
  {
    return aCView->WS->SetImmediateModeDrawToFront (theDrawToFrontBuffer);
  }
  return Standard_False;
}

// =======================================================================
// function : GetOpenClDeviceInfo
// purpose  : Returns information about device used for computations
// =======================================================================
#ifndef HAVE_OPENCL

Standard_Boolean OpenGl_GraphicDriver::GetOpenClDeviceInfo (const Graphic3d_CView&,
  NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>&)
{
  return Standard_False;
}

#else

Standard_Boolean OpenGl_GraphicDriver::GetOpenClDeviceInfo (const Graphic3d_CView& theCView,
  NCollection_DataMap<TCollection_AsciiString, TCollection_AsciiString>& theInfo)
{

  if (theCView.ViewId == -1 || theCView.ptrView == NULL)
  {
    return Standard_False;
  }

  return reinterpret_cast<const OpenGl_CView*> (theCView.ptrView)->WS->GetOpenClDeviceInfo (theInfo);
}

#endif

// =======================================================================
// function : DisplayImmediateStructure
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::DisplayImmediateStructure (const Graphic3d_CView&      theCView,
                                                      const Graphic3d_CStructure& theCStructure)
{
  OpenGl_CView*     aCView     = (OpenGl_CView*     )theCView.ptrView;
  OpenGl_Structure* aStructure = (OpenGl_Structure* )&theCStructure;
  if (aCView == NULL)
  {
    return;
  }

  aCView->View->DisplayImmediateStructure (aStructure);
}

// =======================================================================
// function : EraseImmediateStructure
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::EraseImmediateStructure (const Graphic3d_CView&      theCView,
                                                    const Graphic3d_CStructure& theCStructure)
{
  OpenGl_CView*     aCView     = (OpenGl_CView*     )theCView.ptrView;
  OpenGl_Structure* aStructure = (OpenGl_Structure* )&theCStructure;
  if (aCView == NULL)
  {
    return;
  }

  aCView->View->EraseImmediateStructure (aStructure);
}


// =======================================================================
// function : Print
// purpose  :
// =======================================================================
Standard_Boolean OpenGl_GraphicDriver::Print (const Graphic3d_CView& theCView,
                                              const Aspect_CLayer2d& theCUnderLayer,
                                              const Aspect_CLayer2d& theCOverLayer,
                                              const Aspect_Handle    thePrintDC,
                                              const Standard_Boolean theToShowBackground,
                                              const Standard_CString theFilename,
                                              const Aspect_PrintAlgo thePrintAlgorithm,
                                              const Standard_Real    theScaleFactor) const
{
  const OpenGl_CView* aCView = (const OpenGl_CView* )theCView.ptrView;
  if (aCView == NULL
   || !myPrintContext.IsNull())
  {
    return Standard_False;
  }

  Standard_Boolean isPrinted = Standard_False;
  myPrintContext = new OpenGl_PrinterContext();
#ifdef _WIN32
  isPrinted = aCView->WS->Print (myPrintContext,
                                 theCView,
                                 theCUnderLayer,
                                 theCOverLayer,
                                 thePrintDC,
                                 theToShowBackground,
                                 theFilename,
                                 thePrintAlgorithm,
                                 theScaleFactor);
#else
  Standard_NotImplemented::Raise ("OpenGl_GraphicDriver::Print is implemented only on Windows");
#endif
  myPrintContext.Nullify();
  return isPrinted;
}

// =======================================================================
// function : ZBufferTriedronSetup
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::ZBufferTriedronSetup (const Quantity_NameOfColor theXColor,
                                                 const Quantity_NameOfColor theYColor,
                                                 const Quantity_NameOfColor theZColor,
                                                 const Standard_Real        theSizeRatio,
                                                 const Standard_Real        theAxisDiametr,
                                                 const Standard_Integer     theNbFacettes)
{
  OpenGl_Trihedron::Setup (theXColor, theYColor, theZColor, theSizeRatio, theAxisDiametr, theNbFacettes);
}

// =======================================================================
// function : TriedronDisplay
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::TriedronDisplay (const Graphic3d_CView&              theCView,
                                            const Aspect_TypeOfTriedronPosition thePosition,
                                            const Quantity_NameOfColor          theColor,
                                            const Standard_Real                 theScale,
                                            const Standard_Boolean              theAsWireframe)
{
  const OpenGl_CView* aCView = (const OpenGl_CView* )theCView.ptrView;
  if (aCView != NULL)
  {
    aCView->View->TriedronDisplay (aCView->WS->GetGlContext(), thePosition, theColor, theScale, theAsWireframe);
  }
}

// =======================================================================
// function : TriedronErase
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::TriedronErase (const Graphic3d_CView& theCView)
{
  const OpenGl_CView* aCView = (const OpenGl_CView* )theCView.ptrView;
  if (aCView != NULL)
  {
    aCView->View->TriedronErase (aCView->WS->GetGlContext());
  }
}

// =======================================================================
// function : TriedronEcho
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::TriedronEcho (const Graphic3d_CView& ,
                                         const Aspect_TypeOfTriedronEcho )
{
  // do nothing
}

// =======================================================================
// function : Environment
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::Environment (const Graphic3d_CView& theCView)
{
  const OpenGl_CView* aCView = (const OpenGl_CView* )theCView.ptrView;
  if (aCView == NULL)
  {
    return;
  }

  aCView->View->SetTextureEnv    (aCView->WS->GetGlContext(), theCView.Context.TextureEnv);
  aCView->View->SetSurfaceDetail ((Visual3d_TypeOfSurfaceDetail)theCView.Context.SurfaceDetail);
}

// =======================================================================
// function : BackgroundImage
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::BackgroundImage (const Standard_CString  theFileName,
                                            const Graphic3d_CView&  theCView,
                                            const Aspect_FillMethod theFillStyle)
{
  const OpenGl_CView* aCView = (const OpenGl_CView* )theCView.ptrView;
  if (aCView != NULL)
  {
    aCView->View->CreateBackgroundTexture (theFileName, theFillStyle);
  }
}

// =======================================================================
// function : SetBgImageStyle
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::SetBgImageStyle (const Graphic3d_CView&  theCView,
                                            const Aspect_FillMethod theFillStyle)
{
  const OpenGl_CView* aCView = (const OpenGl_CView* )theCView.ptrView;
  if (aCView != NULL)
  {
    aCView->View->SetBackgroundTextureStyle (theFillStyle);
  }
}

// =======================================================================
// function : SetBgGradientStyle
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::SetBgGradientStyle (const Graphic3d_CView&          theCView,
                                               const Aspect_GradientFillMethod theFillType)
{
  const OpenGl_CView* aCView = (const OpenGl_CView* )theCView.ptrView;
  if (aCView != NULL)
  {
    aCView->View->SetBackgroundGradientType (theFillType);
  }
}

// =======================================================================
// function : GraduatedTrihedronDisplay
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::GraduatedTrihedronDisplay (const Graphic3d_CView&               theCView,
                                                      const Graphic3d_CGraduatedTrihedron& theCubic)
{
  const OpenGl_CView* aCView = (const OpenGl_CView* )theCView.ptrView;
  if (aCView != NULL)
  {
    aCView->View->GraduatedTrihedronDisplay (aCView->WS->GetGlContext(), theCubic);
  }
}

// =======================================================================
// function : GraduatedTrihedronErase
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::GraduatedTrihedronErase (const Graphic3d_CView& theCView)
{
  const OpenGl_CView* aCView = (const OpenGl_CView* )theCView.ptrView;
  if (aCView != NULL)
  {
    aCView->View->GraduatedTrihedronErase (aCView->WS->GetGlContext());
  }
}

// =======================================================================
// function : GraduatedTrihedronMinMaxValues
// purpose  :
// =======================================================================
void OpenGl_GraphicDriver::GraduatedTrihedronMinMaxValues (const Standard_ShortReal theMinX,
                                                           const Standard_ShortReal theMinY,
                                                           const Standard_ShortReal theMinZ,
                                                           const Standard_ShortReal theMaxX,
                                                           const Standard_ShortReal theMaxY,
                                                           const Standard_ShortReal theMaxZ)
{
  OpenGl_GraduatedTrihedron::SetMinMax (theMinX, theMinY, theMinZ, theMaxX, theMaxY, theMaxZ);
}
