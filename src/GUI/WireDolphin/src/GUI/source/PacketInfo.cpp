// PacketInfo.cpp: 구현 파일
//

#include "../header/stdafx.h"
#include "../header/WireDolphin.h"
#include "../header/PacketInfo.h"
#include "afxdialogex.h"


// PacketInfo 대화 상자

IMPLEMENT_DYNAMIC(PacketInfo, CDialogEx)

PacketInfo::PacketInfo(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PACKET_INFO, pParent)
{

}

PacketInfo::~PacketInfo()
{
}

void PacketInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(PacketInfo, CDialogEx)
END_MESSAGE_MAP()


// PacketInfo 메시지 처리기
