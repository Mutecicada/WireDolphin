#pragma once


// PacketInfo 대화 상자

class PacketInfo : public CDialogEx
{
	DECLARE_DYNAMIC(PacketInfo)

public:
	PacketInfo(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~PacketInfo();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PACKET_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
