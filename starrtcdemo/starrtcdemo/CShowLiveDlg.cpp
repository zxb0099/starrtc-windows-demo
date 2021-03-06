// CShowLiveDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "starrtcdemo.h"
#include "CShowLiveDlg.h"
#include "afxdialogex.h"


// CShowLiveDlg 对话框

IMPLEMENT_DYNAMIC(CShowLiveDlg, CDialogEx)

CShowLiveDlg::CShowLiveDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SHOW_LIVE, pParent)
{
	m_pShowLiveControl = new CShowLiveControl();
	m_pPicControlCallback = NULL;
}

CShowLiveDlg::~CShowLiveDlg()
{
	if (m_pShowLiveControl != NULL)
	{
		m_pShowLiveControl->removeAllUpUser();
		delete m_pShowLiveControl;
		m_pShowLiveControl = NULL;
	}
}

void CShowLiveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_SHOW_LIVE_PIC1, m_Pic1);
	DDX_Control(pDX, IDC_STATIC_SHOW_LIVE_PIC2, m_Pic2);
	DDX_Control(pDX, IDC_STATIC_SHOW_LIVE_PIC3, m_Pic3);
	DDX_Control(pDX, IDC_STATIC_SHOW_LIVE_PIC4, m_Pic4);
	DDX_Control(pDX, IDC_STATIC_SHOW_LIVE_PIC5, m_Pic5);
	DDX_Control(pDX, IDC_STATIC_SHOW_LIVE_PIC6, m_Pic6);
	DDX_Control(pDX, IDC_STATIC_SHOW_LIVE_PIC7, m_Pic7);
}


BEGIN_MESSAGE_MAP(CShowLiveDlg, CDialogEx)
	ON_WM_MOVE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CShowLiveDlg 消息处理程序


BOOL CShowLiveDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	::GetClientRect(this->m_hWnd, rect);
	m_pShowLiveControl->setDrawRect(rect);

	DWORD dwStyle = ::GetWindowLong(m_Pic1.GetSafeHwnd(), GWL_STYLE);
	::SetWindowLong(m_Pic1.GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

	dwStyle = ::GetWindowLong(m_Pic2.GetSafeHwnd(), GWL_STYLE);
	::SetWindowLong(m_Pic2.GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

	dwStyle = ::GetWindowLong(m_Pic3.GetSafeHwnd(), GWL_STYLE);
	::SetWindowLong(m_Pic3.GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

	dwStyle = ::GetWindowLong(m_Pic4.GetSafeHwnd(), GWL_STYLE);
	::SetWindowLong(m_Pic4.GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

	dwStyle = ::GetWindowLong(m_Pic5.GetSafeHwnd(), GWL_STYLE);
	::SetWindowLong(m_Pic5.GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

	dwStyle = ::GetWindowLong(m_Pic6.GetSafeHwnd(), GWL_STYLE);
	::SetWindowLong(m_Pic6.GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

	dwStyle = ::GetWindowLong(m_Pic7.GetSafeHwnd(), GWL_STYLE);
	::SetWindowLong(m_Pic7.GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);


	m_pShowLiveControl->m_pPictureControlArr[0] = &m_Pic1;
	m_Pic1.setInfo(m_pPicControlCallback, m_pShowLiveControl);

	m_pShowLiveControl->m_pPictureControlArr[1] = &m_Pic2;
	m_Pic2.setInfo(m_pPicControlCallback, m_pShowLiveControl);

	m_pShowLiveControl->m_pPictureControlArr[2] = &m_Pic3;
	m_Pic3.setInfo(m_pPicControlCallback, m_pShowLiveControl);

	m_pShowLiveControl->m_pPictureControlArr[3] = &m_Pic4;
	m_Pic4.setInfo(m_pPicControlCallback, m_pShowLiveControl);

	m_pShowLiveControl->m_pPictureControlArr[4] = &m_Pic5;
	m_Pic5.setInfo(m_pPicControlCallback, m_pShowLiveControl);

	m_pShowLiveControl->m_pPictureControlArr[5] = &m_Pic6;
	m_Pic6.setInfo(m_pPicControlCallback, m_pShowLiveControl);

	m_pShowLiveControl->m_pPictureControlArr[6] = &m_Pic7;
	m_Pic7.setInfo(m_pPicControlCallback, m_pShowLiveControl);

	m_pShowLiveControl->resetPicControlPos();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CShowLiveDlg::addPictureControlListener(CPicControlCallback* pPicControlCallback)
{
	m_pPicControlCallback = pPicControlCallback;
}

void CShowLiveDlg::addShowLiveListener(IShowLiveCallback* pShowLiveCallback)
{
	m_pShowLiveCallback = pShowLiveCallback;
}


void CShowLiveDlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);
	CRect rect;
	::GetClientRect(this->m_hWnd, rect);
	m_pShowLiveControl->setDrawRect(rect);
	m_pShowLiveControl->setDrawRect(rect);
}


void CShowLiveDlg::OnClose()
{
	if (IDYES == AfxMessageBox("是否要关闭视频通话", MB_YESNO))
	{
		if (m_pShowLiveCallback != NULL)
		{
			m_pShowLiveCallback->stopLive();
		}
		CDialogEx::OnClose();
	}	
}
