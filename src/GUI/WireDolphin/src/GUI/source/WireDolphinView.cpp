
// WireDolphinView.cpp: CWireDolphinView 클래스의 구현
//

#include "../header/stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "../header/WireDolphin.h"
#endif

#include "../header/WireDolphinDoc.h"
#include "../header/WireDolphinView.h"
#include "../header/PacketInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWireDolphinView

IMPLEMENT_DYNCREATE(CWireDolphinView, CListView)

BEGIN_MESSAGE_MAP(CWireDolphinView, CListView)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CWireDolphinView::OnNMDblclk)
	ON_COMMAND(ID_STOP, &CWireDolphinView::OnStop)
	ON_COMMAND(ID_START, &CWireDolphinView::OnStart)
	ON_UPDATE_COMMAND_UI(ID_START, &CWireDolphinView::OnUpdateStart)
	ON_UPDATE_COMMAND_UI(ID_STOP, &CWireDolphinView::OnUpdateStop)
END_MESSAGE_MAP()

// CWireDolphinView 생성/소멸

CWireDolphinView::CWireDolphinView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CWireDolphinView::~CWireDolphinView()
{
}

BOOL CWireDolphinView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.style &= ~LVS_TYPEMASK;
	cs.style |= LVS_REPORT;

	return CListView::PreCreateWindow(cs);
}

void CWireDolphinView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();

	CListCtrl& list = GetListCtrl();

	pcap_if_t *alldevs;
	pcap_if_t *d;
	int iCnt = 0;
	char errbuf[PCAP_ERRBUF_SIZE];
	CRect winRect;
	startStat = FALSE;
	stopStat = FALSE;
	capChk = FALSE;

	GetClientRect(winRect);

	CFont font;
	font.CreatePointFont(120, _T("굴림"));
	list.SetFont(&font);
	list.SetExtendedStyle(list.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	list.InsertColumn(0, _T("NAME"), LVCFMT_LEFT, winRect.Width() * 0.4);
	list.InsertColumn(1, _T("DESCRIPTION"), LVCFMT_LEFT, winRect.Width() * 0.5);

	
	/* Retrieve the device list from the local machine */
	if (pcap_findalldevs_ex((char*)PCAP_SRC_IF_STRING, NULL /* auth is not needed */, &alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs_ex: %s\n", errbuf);
		exit(1);
	}
	
	/* Print the list */
	int i = 0;
	for (d = alldevs; d != NULL; d = d->next, i++)
	{
		list.InsertItem(i, CA2W(d->name));
		list.SetItem(i, 1, LVIF_TEXT, CA2W(d->description), 0, 0, 0, NULL);
	}



}

#ifdef _DEBUG
void CWireDolphinView::AssertValid() const
{
	CListView::AssertValid();
}

void CWireDolphinView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CWireDolphinDoc* CWireDolphinView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWireDolphinDoc)));
	return (CWireDolphinDoc*)m_pDocument;
}
#endif //_DEBUG


// CWireDolphinView 메시지 처리기

void CWireDolphinView::startCapture()
{
	// Pcaket Capture Start
	// selected = d->name
	// pcap_open_live
	// pcap_compile
	// pcap_setfilter
	// pcap_loop
	/*
	while (capChk)
	{

	}
	*/

}

void CWireDolphinView::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CListCtrl& list = GetListCtrl();
	CRect winRect;

	GetClientRect(winRect);

	if (selected.IsEmpty())
	{
		if (pNMItemActivate->iItem != -1)
		{
			selected = list.GetItemText(pNMItemActivate->iItem, 0);
			AfxGetMainWnd()->SetWindowTextW(selected);
		}

		list.DeleteColumn(0);
		list.DeleteColumn(0);
		list.DeleteAllItems();
		// Start Packet Capture
		
		list.InsertColumn(0, _T("Num"), LVCFMT_LEFT, winRect.Width() * 0.05);
		list.InsertColumn(1, _T("Time"), LVCFMT_LEFT, winRect.Width() * 0.05);
		list.InsertColumn(2, _T("Source"), LVCFMT_LEFT, winRect.Width() * 0.2);
		list.InsertColumn(3, _T("Destination"), LVCFMT_LEFT, winRect.Width() * 0.2);
		list.InsertColumn(4, _T("Protocol"), LVCFMT_LEFT, winRect.Width() * 0.1);
		list.InsertColumn(5, _T("Length"), LVCFMT_LEFT, winRect.Width() * 0.05);
		list.InsertColumn(6, _T("Info"), LVCFMT_LEFT, winRect.Width() * 0.4);

		stopStat = true;
		startCapture();

	}
	else
	{
	}

	*pResult = 0;
}

void CWireDolphinView::OnStop()
{
	startStat = TRUE;
	stopStat = FALSE;
	capChk = FALSE;
	PacketInfo dlg;
	dlg.DoModal();
}


void CWireDolphinView::OnStart()
{
	startStat = FALSE;
	stopStat = TRUE;
	capChk = TRUE;
	startCapture();
}


void CWireDolphinView::OnUpdateStart(CCmdUI *pCmdUI)
{
	if (startStat)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}


void CWireDolphinView::OnUpdateStop(CCmdUI *pCmdUI)
{
	if (stopStat)
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
}
