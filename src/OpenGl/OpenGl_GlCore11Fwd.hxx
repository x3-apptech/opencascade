// Created on: 2014-03-17
// Created by: Kirill GAVRILOV
// Copyright (c) 2014 OPEN CASCADE SAS
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

#ifndef OpenGl_GlCore11Fwd_HeaderFile
#define OpenGl_GlCore11Fwd_HeaderFile

#include <OpenGl_GlFunctions.hxx>

//! OpenGL 1.1 core without deprecated Fixed Pipeline entry points.
//! Notice that all functions within this structure are actually exported by system GL library.
//! The main purpose for these hint - to control visibility of functions per GL version
//! (global functions should not be used directly to achieve this effect!).
struct OpenGl_GlCore11Fwd : protected OpenGl_GlFunctions
{

public: //! @name Miscellaneous

  inline void glClearColor (GLclampf theRed, GLclampf theGreen, GLclampf theBlue, GLclampf theAlpha)
  {
    ::glClearColor  (theRed, theGreen, theBlue, theAlpha);
    OpenGl_TRACE(glClearColor)
  }

  inline void glClear (GLbitfield theMask)
  {
    ::glClear (theMask);
    OpenGl_TRACE(glClear)
  }

  inline void glColorMask (GLboolean theRed, GLboolean theGreen, GLboolean theBlue, GLboolean theAlpha)
  {
    ::glColorMask (theRed, theGreen, theBlue, theAlpha);
    OpenGl_TRACE(glColorMask)
  }

  inline void glBlendFunc (GLenum sfactor, GLenum dfactor)
  {
    ::glBlendFunc(sfactor, dfactor);
    OpenGl_TRACE(glBlendFunc)
  }

  inline void glCullFace (GLenum theMode)
  {
    ::glCullFace (theMode);
    OpenGl_TRACE(glCullFace)
  }

  inline void glFrontFace (GLenum theMode)
  {
    ::glFrontFace (theMode);
    OpenGl_TRACE(glFrontFace)
  }

  inline void glLineWidth (GLfloat theWidth)
  {
    ::glLineWidth (theWidth);
    OpenGl_TRACE(glLineWidth)
  }

  inline void glPolygonOffset (GLfloat theFactor, GLfloat theUnits)
  {
    ::glPolygonOffset (theFactor, theUnits);
    OpenGl_TRACE(glPolygonOffset)
  }

  inline void glScissor (GLint theX, GLint theY, GLsizei theWidth, GLsizei theHeight)
  {
    ::glScissor (theX, theY, theWidth, theHeight);
    OpenGl_TRACE(glScissor)
  }

  inline void glEnable (GLenum theCap)
  {
    ::glEnable (theCap);
    OpenGl_TRACE(glEnable)
  }

  inline void glDisable (GLenum theCap)
  {
    ::glDisable (theCap);
    OpenGl_TRACE(glDisable)
  }

  inline GLboolean glIsEnabled (GLenum theCap)
  {
    return ::glIsEnabled (theCap);
  }

  inline void glGetBooleanv (GLenum theParamName, GLboolean* theValues)
  {
    ::glGetBooleanv (theParamName, theValues);
    OpenGl_TRACE(glGetBooleanv)
  }

  inline void glGetFloatv (GLenum theParamName, GLfloat* theValues)
  {
    ::glGetFloatv (theParamName, theValues);
    OpenGl_TRACE(glGetFloatv)
  }

  inline void glGetIntegerv (GLenum theParamName, GLint* theValues)
  {
    ::glGetIntegerv (theParamName, theValues);
    OpenGl_TRACE(glGetIntegerv)
  }

  inline GLenum glGetError()
  {
    return ::glGetError();
  }

  inline const GLubyte* glGetString (GLenum theName)
  {
    const GLubyte* aRes = ::glGetString (theName);
    OpenGl_TRACE(glGetString)
    return aRes;
  }

  inline void glFinish()
  {
    ::glFinish();
    OpenGl_TRACE(glFinish)
  }

  inline void glFlush()
  {
    ::glFlush();
    OpenGl_TRACE(glFlush)
  }

  inline void glHint (GLenum theTarget, GLenum theMode)
  {
    ::glHint (theTarget, theMode);
    OpenGl_TRACE(glHint)
  }

public: //! @name Depth Buffer

  inline void glClearDepth (GLclampd theDepth)
  {
  #if defined(GL_ES_VERSION_2_0)
    ::glClearDepthf ((GLfloat )theDepth);
  #else
    ::glClearDepth (theDepth);
  #endif
    OpenGl_TRACE(glClearDepth)
  }

  inline void glClearDepthf (GLfloat theDepth)
  {
  #if defined(GL_ES_VERSION_2_0)
    ::glClearDepthf (theDepth);
  #else
    ::glClearDepth ((GLclampd )theDepth);
  #endif
    OpenGl_TRACE(glClearDepthf)
  }

  inline void glDepthFunc (GLenum theFunc)
  {
    ::glDepthFunc (theFunc);
    OpenGl_TRACE(glDepthFunc)
  }

  inline void glDepthMask (GLboolean theFlag)
  {
    ::glDepthMask (theFlag);
    OpenGl_TRACE(glDepthMask)
  }

  inline void glDepthRange (GLclampd theNearValue,
                            GLclampd theFarValue)
  {
  #if defined(GL_ES_VERSION_2_0)
    ::glDepthRangef ((GLfloat )theNearValue, (GLfloat )theFarValue);
  #else
    ::glDepthRange (theNearValue, theFarValue);
  #endif
    OpenGl_TRACE(glDepthRange)
  }

  inline void glDepthRangef (GLfloat theNearValue,
                             GLfloat theFarValue)
  {
  #if defined(GL_ES_VERSION_2_0)
    ::glDepthRangef (theNearValue, theFarValue);
  #else
    ::glDepthRange ((GLclampd )theNearValue, (GLclampd )theFarValue);
  #endif
    OpenGl_TRACE(glDepthRangef)
  }

public: //! @name Transformation

  inline void glViewport (GLint theX, GLint theY, GLsizei theWidth, GLsizei theHeight)
  {
    ::glViewport (theX, theY, theWidth, theHeight);
    OpenGl_TRACE(glViewport)
  }

public: //! @name Vertex Arrays

  inline void glDrawArrays (GLenum theMode, GLint theFirst, GLsizei theCount)
  {
    ::glDrawArrays (theMode, theFirst, theCount);
    OpenGl_TRACE(glDrawArrays)
  }

  inline void glDrawElements (GLenum theMode, GLsizei theCount, GLenum theType, const GLvoid* theIndices)
  {
    ::glDrawElements (theMode, theCount, theType, theIndices);
    OpenGl_TRACE(glDrawElements)
  }

public: //! @name Raster functions

  inline void glPixelStorei (GLenum theParamName, GLint   theParam)
  {
    ::glPixelStorei (theParamName, theParam);
    OpenGl_TRACE(glPixelStorei)
  }

  inline void glReadPixels (GLint x, GLint y,
                            GLsizei width, GLsizei height,
                            GLenum format, GLenum type,
                            GLvoid* pixels)
  {
    ::glReadPixels (x, y, width, height, format, type, pixels);
    OpenGl_TRACE(glReadPixels)
  }

public: //! @name Stenciling

  inline void glStencilFunc (GLenum func, GLint ref, GLuint mask)
  {
    ::glStencilFunc (func, ref, mask);
    OpenGl_TRACE(glStencilFunc)
  }

  inline void glStencilMask (GLuint mask)
  {
    ::glStencilMask (mask);
    OpenGl_TRACE(glStencilMask)
  }

  inline void glStencilOp (GLenum fail, GLenum zfail, GLenum zpass)
  {
    ::glStencilOp (fail, zfail, zpass);
    OpenGl_TRACE(glStencilOp)
  }

  inline void glClearStencil (GLint s)
  {
    ::glClearStencil (s);
    OpenGl_TRACE(glClearStencil)
  }

public: //! @name Texture mapping

  inline void glTexParameterf (GLenum target, GLenum pname, GLfloat param)
  {
    ::glTexParameterf (target, pname, param);
    OpenGl_TRACE(glTexParameterf)
  }

  inline void glTexParameteri (GLenum target, GLenum pname, GLint param)
  {
    ::glTexParameteri (target, pname, param);
    OpenGl_TRACE(glTexParameteri)
  }

  inline void glTexParameterfv (GLenum target, GLenum pname, const GLfloat* params)
  {
    ::glTexParameterfv (target, pname, params);
    OpenGl_TRACE(glTexParameterfv)
  }

  inline void glTexParameteriv (GLenum target, GLenum pname, const GLint* params)
  {
    ::glTexParameteriv (target, pname, params);
    OpenGl_TRACE(glTexParameteriv)
  }

  inline void glGetTexParameterfv (GLenum target, GLenum pname, GLfloat* params)
  {
    ::glGetTexParameterfv (target, pname, params);
    OpenGl_TRACE(glGetTexParameterfv)
  }

  inline void glGetTexParameteriv (GLenum target, GLenum pname, GLint* params)
  {
    ::glGetTexParameteriv (target, pname, params);
    OpenGl_TRACE(glGetTexParameteriv)
  }

  inline void glTexImage2D (GLenum target, GLint level,
                            GLint internalFormat,
                            GLsizei width, GLsizei height,
                            GLint border, GLenum format, GLenum type,
                            const GLvoid* pixels)
  {
    ::glTexImage2D(target, level, internalFormat, width, height, border, format, type, pixels);
    OpenGl_TRACE(glTexImage2D)
  }

  inline void glGenTextures (GLsizei n, GLuint* textures)
  {
    ::glGenTextures(n, textures);
    OpenGl_TRACE(glGenTextures)
  }

  inline void glDeleteTextures (GLsizei n, const GLuint* textures)
  {
    ::glDeleteTextures(n, textures);
    OpenGl_TRACE(glDeleteTextures)
  }

  inline void glBindTexture (GLenum target, GLuint texture)
  {
    ::glBindTexture(target, texture);
    OpenGl_TRACE(glBindTexture)
  }

  inline GLboolean glIsTexture (GLuint texture)
  {
    const GLboolean aRes = ::glIsTexture (texture);
    OpenGl_TRACE(glIsTexture)
    return aRes;
  }

  inline void glTexSubImage2D (GLenum target, GLint level,
                               GLint xoffset, GLint yoffset,
                               GLsizei width, GLsizei height,
                               GLenum format, GLenum type,
                               const GLvoid* pixels)
  {
    ::glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
    OpenGl_TRACE(glTexSubImage2D)
  }

  inline void glCopyTexImage2D (GLenum target, GLint level,
                                GLenum internalformat,
                                GLint x, GLint y,
                                GLsizei width, GLsizei height,
                                GLint border)
  {
    ::glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
    OpenGl_TRACE(glCopyTexImage2D)
  }

  inline void glCopyTexSubImage2D (GLenum target, GLint level,
                                   GLint xoffset, GLint yoffset,
                                   GLint x, GLint y,
                                   GLsizei width, GLsizei height)
  {
    ::glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
    OpenGl_TRACE(glCopyTexSubImage2D)
  }

#if !defined(GL_ES_VERSION_2_0)
  inline void glTexImage1D (GLenum target, GLint level,
                            GLint internalFormat,
                            GLsizei width, GLint border,
                            GLenum format, GLenum type,
                            const GLvoid* pixels)
  {
    ::glTexImage1D(target, level, internalFormat, width, border, format, type, pixels);
    OpenGl_TRACE(glTexImage1D)
  }

  inline void glTexSubImage1D (GLenum target, GLint level,
                               GLint xoffset,
                               GLsizei width, GLenum format,
                               GLenum type, const GLvoid* pixels)
  {
    ::glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
    OpenGl_TRACE(glTexSubImage1D)
  }

  inline void glCopyTexImage1D (GLenum target, GLint level,
                                GLenum internalformat,
                                GLint x, GLint y,
                                GLsizei width, GLint border)
  {
    ::glCopyTexImage1D(target, level, internalformat, x, y, width, border);
    OpenGl_TRACE(glCopyTexImage1D)
  }

  inline void glCopyTexSubImage1D (GLenum target, GLint level,
                                   GLint xoffset, GLint x, GLint y,
                                   GLsizei width)
  {
    ::glCopyTexSubImage1D(target, level, xoffset, x, y, width);
    OpenGl_TRACE(glCopyTexSubImage1D)
  }

  inline void glGetTexImage (GLenum target, GLint level,
                             GLenum format, GLenum type,
                             GLvoid* pixels)
  {
    ::glGetTexImage (target, level, format, type, pixels);
    OpenGl_TRACE(glGetTexImage)
  }
#endif

#if !defined(GL_ES_VERSION_2_0)

  inline void glAlphaFunc (GLenum theFunc, GLclampf theRef)
  {
    ::glAlphaFunc (theFunc, theRef);
    OpenGl_TRACE(glAlphaFunc)
  }

  inline void glPointSize (GLfloat theSize)
  {
    ::glPointSize (theSize);
    OpenGl_TRACE(glPointSize)
  }

#endif

/*#if !defined(GL_ES_VERSION_2_0)

  inline void glTexEnvf (GLenum target, GLenum pname, GLfloat param)
  {
    ::glTexEnvf (target, pname, param);
  }

  inline void glTexEnvi (GLenum target, GLenum pname, GLint param)
  {
    ::glTexEnvi (target, pname, param);
  }

  inline void glTexEnvfv (GLenum target, GLenum pname, const GLfloat* params)
  {
    ::glTexEnvfv (target, pname, params);
  }

  inline void glTexEnviv (GLenum target, GLenum pname, const GLint* params)
  {
    ::glTexEnviv (target, pname, params);
  }

  inline void glGetTexEnvfv (GLenum target, GLenum pname, GLfloat* params)
  {
    ::glGetTexEnvfv (target, pname, params);
  }

  inline void glGetTexEnviv (GLenum target, GLenum pname, GLint* params)
  {
    ::glGetTexEnviv (target, pname, params);
  }

  inline void glGetTexLevelParameterfv (GLenum target, GLint level, GLenum pname, GLfloat* params)
  {
    ::glGetTexLevelParameterfv (target, level, pname, params);
  }

  inline void glGetTexLevelParameteriv (GLenum target, GLint level, GLenum pname, GLint* params)
  {
    ::glGetTexLevelParameteriv (target, level, pname, params);
  }

  inline void glClearIndex (GLfloat c)
  {
    ::glClearIndex(c);
  }

  inline void glIndexMask (GLuint theMask)
  {
    ::glIndexMask (theMask);
  }

  inline void glLogicOp (GLenum opcode)
  {
    ::glLogicOp(opcode);
  }

  inline void glPolygonMode (GLenum theFace, GLenum theMode)
  {
    ::glPolygonMode (theFace, theMode);
  }

  inline void glDrawBuffer (GLenum theMode)
  {
    ::glDrawBuffer (theMode);
  }

  inline void glReadBuffer (GLenum theMode)
  {
    ::glReadBuffer (theMode);
  }

  inline void glGetDoublev (GLenum theParamName, GLdouble* theValues)
  {
    ::glGetDoublev (theParamName, theValues);
  }

  inline GLint glRenderMode (GLenum theMode)
  {
    return ::glRenderMode (theMode);
  }

  inline void glArrayElement (GLint i)
  {
    ::glArrayElement (i);
  }

  inline void glPixelStoref (GLenum theParamName, GLfloat theParam)
  {
    ::glPixelStoref (theParamName, theParam);
  }

  inline void glPixelTransferf (GLenum theParamName, GLfloat theParam)
  {
    ::glPixelTransferf (theParamName, theParam);
  }

  inline void glPixelTransferi (GLenum theParamName, GLint   theParam)
  {
    ::glPixelTransferi (theParamName, theParam);
  }

  inline void glPixelMapfv  (GLenum map, GLsizei mapsize, const GLfloat*  values)
  {
    ::glPixelMapfv (map, mapsize, values);
  }

  inline void glPixelMapuiv (GLenum map, GLsizei mapsize, const GLuint*   values)
  {
    ::glPixelMapuiv (map, mapsize, values);
  }

  inline void glPixelMapusv (GLenum map, GLsizei mapsize, const GLushort* values)
  {
    ::glPixelMapusv (map, mapsize, values);
  }

  inline void glGetPixelMapfv  (GLenum map, GLfloat*  values)
  {
    ::glGetPixelMapfv (map, values);
  }

  inline void glGetPixelMapuiv (GLenum map, GLuint*   values)
  {
    ::glGetPixelMapuiv (map, values);
  }

  inline void glGetPixelMapusv (GLenum map, GLushort* values)
  {
    ::glGetPixelMapusv (map, values);
  }
#endif*/

};

#endif // _OpenGl_GlCore11Fwd_Header
