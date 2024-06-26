
// WordChainGameDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "WordChainGame.h"
#include "WordChainGameDlg.h"
#include "afxdialogex.h"
#pragma comment(lib, "winmm");
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWordChainGameDlg 대화 상자



CWordChainGameDlg::CWordChainGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_WORDCHAINGAME_DIALOG, pParent)
	, m_strAddress(_T("127.0.0.1"))	//IP 초기값
	, m_nPort(21000)		//Port 초기값
	, m_strID(_T(""))
	, m_strPASSWORD(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_cnt = 0;
	m_totaltimecount = 0;
}

void CWordChainGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strAddress);
	DDX_Text(pDX, IDC_EDIT2, m_nPort);
	DDX_Control(pDX, IDC_EDIT3, m_ctrlEdit);
	DDX_Text(pDX, IDC_EDIT4, m_strID);
	DDX_Text(pDX, IDC_EDIT5, m_strPASSWORD);
	DDX_Control(pDX, IDC_EDIT6, m_ctrlLeaderBoard);
	DDX_Control(pDX, IDC_EDIT8, m_MyWord);
	DDX_Control(pDX, IDC_EDIT9, m_OtherWord);
	DDX_Control(pDX, IDC_EDIT7, m_ctrlArchive);

}

BEGIN_MESSAGE_MAP(CWordChainGameDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CWordChainGameDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CWordChainGameDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CWordChainGameDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CWordChainGameDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &CWordChainGameDlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON5, &CWordChainGameDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CWordChainGameDlg 메시지 처리기

BOOL CWordChainGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CWordChainGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CWordChainGameDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CWordChainGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWordChainGameDlg::OnBnClickedButton1()
{
	m_pClientSocket = new CClientSocket;
	m_pClientSocket->Create();
	CString str; str.Format(_T("[나] 서버(%s:%d)와 연결!\r\n"), m_strAddress, m_nPort);
	m_ctrlEdit.ReplaceSel(str);
	this->UpdateData(TRUE);	// 컨트롤에 입력된 내용을 멤버변수에 넣는다.
	bool success = m_pClientSocket->Connect(m_strAddress, m_nPort);
	if (!success) m_ctrlEdit.ReplaceSel(_T("[error] 서버 연결 실패!\r\n"));
}



BOOL CWordChainGameDlg::DestroyWindow()
{
	m_pClientSocket->ShutDown();
	m_pClientSocket->Close();
	delete m_pClientSocket;
	return CDialogEx::DestroyWindow();
}


void CWordChainGameDlg::OnBnClickedButton2()
{
	//회원가입 버튼
	this->UpdateData(TRUE);
	CString msg;	//보낼 쿼리
	msg.Append(_T("0 "));
	msg.Append(m_strID);
	msg.Append(_T(" "));
	msg.Append(m_strPASSWORD);
	msg.Append(_T("\r\n"));
	m_pClientSocket->Send(msg, msg.GetLength());

	this->UpdateData(FALSE);
}


void CWordChainGameDlg::OnBnClickedButton3()
{
	//로그인 버튼
	this->UpdateData(TRUE);
	CString msg;	//보낼 쿼리
	msg.Append(_T("1 "));
	msg.Append(m_strID);
	msg.Append(_T(" "));
	msg.Append(m_strPASSWORD);
	msg.Append(_T("\r\n"));
	m_pClientSocket->Send(msg, msg.GetLength());

	this->UpdateData(FALSE);
}


void CWordChainGameDlg::OnBnClickedButton4()
{
	//준비 버튼
	CString strButton4;
	CString msg;
	GetDlgItemText(IDC_BUTTON4, strButton4);
	if (!strButton4.Compare(_T("준비"))) {
		msg.Append(_T("2 ready \r\n"));
		m_pClientSocket->Send(msg, msg.GetLength());
		SetDlgItemText(IDC_BUTTON4, _T("준비해제"));
	}
	else {
		msg.Append(_T("2 notready \r\n"));
		m_pClientSocket->Send(msg, msg.GetLength());
		SetDlgItemText(IDC_BUTTON4, _T("준비"));
	}
}


void CWordChainGameDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString msg;
	CString word;
	this->UpdateData(TRUE);
	GetDlgItemText(IDC_EDIT8, word);
	msg.Format(_T("6 %s \r\n"), word);
	m_pClientSocket->Send(msg, msg.GetLength());
	SetDlgItemText(IDC_EDIT8, _T(""));
	GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
	this->UpdateData(FALSE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	//CDialogEx::OnOK();
}


void CWordChainGameDlg::OnTimer(UINT_PTR nIDEvent)
{

	CString msg;
	if (nIDEvent == 1) {	//내턴

		CString s_time;
		s_time.Format(_T("%d"), m_cnt);
		SetDlgItemText(IDC_STATIC20, s_time);
		SetDlgItemText(IDC_STATIC19, _T(""));

		m_cnt--;
		this->UpdateData(FALSE);
		if (m_cnt < 0) {	//timeout
			GetDlgItem(IDC_EDIT8)->EnableWindow(FALSE);
			SetDlgItemText(IDC_EDIT8, _T(""));
			msg.Format(_T("5 0 \r\n"));
			m_pClientSocket->Send(msg, msg.GetLength());
			KillTimer(1);
		}
		else {	//time left

		}

	}
	else if(nIDEvent == 2) {	//상대턴

		CString s_time;
		s_time.Format(_T("%d"), m_cnt);
		SetDlgItemText(IDC_STATIC19, s_time);
		SetDlgItemText(IDC_STATIC20, _T(""));
		m_cnt--;
		this->UpdateData(FALSE);
		if (m_cnt < 0) {	//timeout
			//상대가 타임 아웃 되더라도 메시지는 보내지 않음
			SetDlgItemText(IDC_EDIT9, _T(""));
			KillTimer(2);
		}
		else {	//time left

		}
	}
	else {	//전체시간 타이머
		msg.Format(_T("남은시간: %d초"), m_totaltimecount);
		SetDlgItemText(IDC_STATIC23, msg);
		m_totaltimecount--;
		this->UpdateData(FALSE);
		if (m_totaltimecount < 0) {

			KillTimer(3);
		}
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CWordChainGameDlg::OnBnClickedButton5()
{
	//효과음 재생하기
	PlaySound("C:\\Users\\이가은\\source\\repos\\끝말잇기\\WordChainGame\\clock.wav", 
		AfxGetInstanceHandle(), SND_ASYNC | SND_LOOP);
}
