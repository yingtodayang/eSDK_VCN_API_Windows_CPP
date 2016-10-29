/*Copyright 2015 Huawei Technologies Co., Ltd. All rights reserved.
eSDK is licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
		http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.*/
#ifndef _OCX_BITMAP_SLIDER_H_
#define _OCX_BITMAP_SLIDER_H_

#if _MSC_VER > 1000
#endif // _MSC_VER > 1000

#include "memdc.h"

#ifdef _DEBUG
#undef THIS_FILE
#define  THIS_FILE  __FILE__
#endif

#define WM_BITMAPSLIDER_MOVING		(WM_USER + 9425)
#define WM_BITMAPSLIDER_MOVED		(WM_USER + 9426)
#define    COLOR_BLACK                  RGB(0,0,0)              //��ɫ
#define    COLOR_WHITE                  RGB(255,255,255)        //��ɫ

class CBitmapSlider : public CSliderCtrl
{
// Construction
public:
	CBitmapSlider();
	virtual ~CBitmapSlider();
	void GetRange(int &nMin, int &nMax) { nMin = m_nMin; nMax = m_nMax; };//lint !e1762
	int GetRangeMax() { return m_nMax; };//lint !e1762
	int GetRangeMin() { return m_nMin; };//lint !e1762
	int GetPos() {return m_nPos; };//lint !e1762

	void Enable(BOOL bEnable = TRUE);
	void DrawFocusRect(BOOL bDraw = TRUE, BOOL bRedraw = FALSE);

	void SetRange(int nMin, int nMax, BOOL bRedraw=FALSE);
	void SetRangeMin(int nMin, BOOL bRedraw = FALSE);
	void SetRangeMax( int nMax, BOOL bRedraw = FALSE );
	void SetPos(int nPos);
	int SetPageSize(int nSize);
	void SetVertical(BOOL bVertical=TRUE) { m_bVertical = bVertical; };
	HBITMAP StretchImage(UINT nBitmapID,int nWidth, int nHeight);
	void   SetToolTipText(LPCTSTR lpszToolTipText);
	void SetMargin(int nLeft, int nTop, int nRight, int nBottom);
	void SetMarginTop(int nMargin) { m_nMarginTop = nMargin; };
	void SetMarginLeft(int nMargin) { m_nMarginLeft = nMargin; };
	void SetMarginRight(int nMargin) { m_nMarginRight = nMargin; };
	void SetMarginBottom(int nMargin) { m_nMarginBottom = nMargin; };

	BOOL SetBitmapChannel(
		UINT nChannelID, UINT nActiveID=NULL, BOOL bTransparent=FALSE,
		COLORREF clrpTransColor=0xFF000000, int iTransPixelX=0, int iTransPixelY=0 );

	BOOL SetBitmapChannelEx(
		HBITMAP cBitmapChannel, HBITMAP cBitmapChannelActive, BOOL bTransparent=FALSE,
		COLORREF clrpTransColor=0xFF000000, int iTransPixelX=0, int iTransPixelY=0 );

	BOOL SetBitmapThumb(
		UINT nThumbID, UINT nActiveID=NULL, BOOL bTransparent=FALSE,
		COLORREF clrpTransColor=0xFF000000, int iTransPixelX=0, int iTransPixelY=0 );

	// Generated message map functions
protected:
	int Pixel2Pos(int nPixel);
	int Pos2Pixel(int nPos);

	void RestoreBackground(
		CDC *pDC, int nXDst, int nYDst, int nWidth, int nHeight, CBitmap *pBmSrc);

	void CopyBackground(
		CDC *pDC, int nXSrc, int nYSrc, int nWidth, int nHeight, CBitmap *pBmDst );

	void DrawBitmap(
		CDC* pDC, int xStart, int yStart, int wWidth, int wHeight,
		CDC* pTmpDC, int xSource, int ySource,
		CBitmap *bmMask = NULL, BOOL bTransparent = FALSE );


	void DrawTransparentBitmap(
		CDC* pDC, int xStart, int yStart, int wWidth, int wHeight,
		CDC* pTmpDC, int xSource, int ySource, CBitmap *bmMask );

	void PrepareMask(
		CBitmap* pBmpSource, CBitmap* pBmpMask,
		COLORREF clrpTransColor=0xFF000000, int iTransPixelX=0, int iTransPixelY=0 );

    void DrawThumb(CDC &dcMem, XCMemDC& dc);
    void DrawChannel(CDC &dcMem, XCMemDC& dc);

	//{{AFX_MSG(CBitmapSlider)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg UINT OnGetDlgCode();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
    CToolTipCtrl m_ToolTip;
    void RelayToolTipEvent(const CPoint &point );
protected:
	int m_nMax, m_nMin, m_nPos, m_nPage;

	CRect m_rectWindow;
	int m_nWidth, m_nHeight;
	int m_nThumbWidth, m_nThumbHeight;
	int m_nMarginLeft, m_nMarginRight, m_nMarginTop, m_nMarginBottom;
	int m_nThumbBgX, m_nThumbBgY;
	int m_nMouseOffset;

	BOOL m_bVertical;
	BOOL m_bChannelActive, m_bThumbActive;
	BOOL m_bTransparentChannel, m_bTransparentThumb, m_bThumb, m_bChannel;
	BOOL m_bLButtonDown, m_bFocus, m_bFocusRect, m_bDrawFocusRect;
	BOOL m_bEnable;

	CBitmap m_bmChannel, m_bmChannelMask, m_bmChannelActive, m_bmChannelActiveMask;
	CBitmap m_bmThumb, m_bmThumbMask, m_bmThumbActive, m_bmThumbActiveMask, m_bmThumbBg;

public:
    void AddToolTip(void);
    void RelayToolTipEventFromParent(CPoint &point);    
};

#endif	//_OCX_BITMAP_SLIDER_H_
