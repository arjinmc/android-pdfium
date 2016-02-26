// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef CORE_INCLUDE_FPDFTEXT_FPDF_TEXT_H_
#define CORE_INCLUDE_FPDFTEXT_FPDF_TEXT_H_

#include "core/include/fpdfapi/fpdf_parser.h"

class CPDF_Page;
class CPDF_TextObject;
class IPDF_LinkExtract;
class IPDF_ReflowedPage;
class IPDF_TextPage;
class IPDF_TextPageFind;

#define CHAR_ERROR -1
#define CHAR_NORMAL 0
#define CHAR_GENERATED 1
#define CHAR_UNUNICODE 2

struct FPDF_CHAR_INFO {
  FX_WCHAR m_Unicode;
  FX_WCHAR m_Charcode;
  int32_t m_Flag;
  FX_FLOAT m_FontSize;
  FX_FLOAT m_OriginX;
  FX_FLOAT m_OriginY;
  CFX_FloatRect m_CharBox;
  CPDF_TextObject* m_pTextObj;
  CFX_Matrix m_Matrix;
};

using CFX_RectArray = CFX_ArrayTemplate<CFX_FloatRect>;

#define FPDFTEXT_LRTB 0
#define FPDFTEXT_RLTB 1
#define FPDFTEXT_TBRL 2
#define FPDFTEXT_LEFT -1
#define FPDFTEXT_RIGHT 1
#define FPDFTEXT_UP -2
#define FPDFTEXT_DOWN 2

class IPDF_TextPage {
 public:
  static IPDF_TextPage* CreateTextPage(const CPDF_Page* pPage, int flags = 0);
  static IPDF_TextPage* CreateReflowTextPage(IPDF_ReflowedPage* pRefPage);
  virtual ~IPDF_TextPage() {}

  virtual void ParseTextPage() = 0;
  virtual bool IsParsed() const = 0;
  virtual int CharIndexFromTextIndex(int TextIndex) const = 0;
  virtual int TextIndexFromCharIndex(int CharIndex) const = 0;
  virtual int CountChars() const = 0;
  virtual void GetCharInfo(int index, FPDF_CHAR_INFO* info) const = 0;
  virtual void GetRectArray(int start,
                            int nCount,
                            CFX_RectArray& rectArray) const = 0;
  virtual int GetIndexAtPos(CFX_FloatPoint point,
                            FX_FLOAT xTolerance,
                            FX_FLOAT yTolerance) const = 0;
  virtual int GetIndexAtPos(FX_FLOAT x,
                            FX_FLOAT y,
                            FX_FLOAT xTolerance,
                            FX_FLOAT yTolerance) const = 0;
  virtual CFX_WideString GetTextByRect(const CFX_FloatRect& rect) const = 0;
  virtual void GetRectsArrayByRect(const CFX_FloatRect& rect,
                                   CFX_RectArray& resRectArray) const = 0;
  virtual int CountRects(int start, int nCount) = 0;
  virtual void GetRect(int rectIndex,
                       FX_FLOAT& left,
                       FX_FLOAT& top,
                       FX_FLOAT& right,
                       FX_FLOAT& bottom) const = 0;
  virtual FX_BOOL GetBaselineRotate(int rectIndex, int& Rotate) = 0;
  virtual FX_BOOL GetBaselineRotate(const CFX_FloatRect& rect, int& Rotate) = 0;
  virtual int CountBoundedSegments(FX_FLOAT left,
                                   FX_FLOAT top,
                                   FX_FLOAT right,
                                   FX_FLOAT bottom,
                                   FX_BOOL bContains = FALSE) = 0;
  virtual void GetBoundedSegment(int index, int& start, int& count) const = 0;
  virtual int GetWordBreak(int index, int direction) const = 0;
  virtual CFX_WideString GetPageText(int start = 0, int nCount = -1) const = 0;
};

#define FPDFTEXT_MATCHCASE 0x00000001
#define FPDFTEXT_MATCHWHOLEWORD 0x00000002
#define FPDFTEXT_CONSECUTIVE 0x00000004

class IPDF_TextPageFind {
 public:
  static IPDF_TextPageFind* CreatePageFind(const IPDF_TextPage* pTextPage);
  virtual ~IPDF_TextPageFind() {}

  virtual FX_BOOL FindFirst(const CFX_WideString& findwhat,
                            int flags,
                            int startPos = 0) = 0;
  virtual FX_BOOL FindNext() = 0;
  virtual FX_BOOL FindPrev() = 0;
  virtual void GetRectArray(CFX_RectArray& rects) const = 0;
  virtual int GetCurOrder() const = 0;
  virtual int GetMatchedCount() const = 0;
};

class IPDF_LinkExtract {
 public:
  static IPDF_LinkExtract* CreateLinkExtract();
  virtual ~IPDF_LinkExtract() {}

  virtual FX_BOOL ExtractLinks(const IPDF_TextPage* pTextPage) = 0;
  virtual int CountLinks() const = 0;
  virtual CFX_WideString GetURL(int index) const = 0;
  virtual void GetBoundedSegment(int index, int& start, int& count) const = 0;
  virtual void GetRects(int index, CFX_RectArray& rects) const = 0;
};

#endif  // CORE_INCLUDE_FPDFTEXT_FPDF_TEXT_H_
