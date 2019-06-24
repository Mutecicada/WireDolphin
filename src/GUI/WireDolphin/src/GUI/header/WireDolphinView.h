
// WireDolphinView.h: CWireDolphinView 클래스의 인터페이스
//

#pragma once


class CWireDolphinView : public CListView
{
protected: // serialization에서만 만들어집니다.
	CWireDolphinView() noexcept;
	DECLARE_DYNCREATE(CWireDolphinView)

// 특성입니다.
public:
	CWireDolphinDoc* GetDocument() const;
	CString selected = NULL;
	BOOL startStat;
	BOOL stopStat;
	BOOL capChk;

// 작업입니다.
public:
	void startCapture();

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CWireDolphinView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStop();
	afx_msg void OnStart();
	afx_msg void OnUpdateStart(CCmdUI *pCmdUI);
	afx_msg void OnUpdateStop(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // WireDolphinView.cpp의 디버그 버전
inline CWireDolphinDoc* CWireDolphinView::GetDocument() const
   { return reinterpret_cast<CWireDolphinDoc*>(m_pDocument); }
#endif

