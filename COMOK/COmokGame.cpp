// COmokGame.cpp: 구현 파일
//

#include "pch.h"
#include "COMOK.h"
#include "afxdialogex.h"
#include "COmokGame.h"


// COmokGame 대화 상자

IMPLEMENT_DYNAMIC(COmokGame, CDialog)

COmokGame::COmokGame(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_strCol(_T(""))
	, m_bStart(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

COmokGame::~COmokGame()
{
}

void COmokGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_COL, m_strCol);
}


BEGIN_MESSAGE_MAP(COmokGame, CDialog)
	ON_BN_CLICKED(IDC_BUTT_START, &COmokGame::OnBnClickedButtStart)
	ON_BN_CLICKED(IDC_BUTT_RESTART, &COmokGame::OnBnClickedButtRestart)
	ON_BN_CLICKED(IDC_BUTT_EXIT, &COmokGame::OnBnClickedButtExit)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// COmokGame 메시지 처리기


void COmokGame::OnBnClickedButtStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_strCol = "검정색 돌";
	m_bStart = true;

	UpdateData(false);
	Invalidate(true);
}


void COmokGame::OnBnClickedButtRestart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bTrun = false;
	m_strCol = "검정색 돌";
	InitBoard();
	UpdateData(false);
	Invalidate(true);
}


void COmokGame::OnBnClickedButtExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK();
}

void COmokGame::DrawBoard()
{
	int x = 0, y = 0;
	CClientDC dc(this);

	CPen MyPen(PS_SOLID, 0, RGB(255, 255, 255));
	CPen* oldPen = dc.SelectObject(&MyPen);

	CBrush myBrush(RGB(255, 255, 255));
	CBrush* oldBrush = dc.SelectObject(&myBrush);

	dc.Rectangle(10, 10, 10 + 20 * 9, 10 + 20 * 9);

	dc.SelectObject(oldPen);
	dc.SelectObject(oldBrush);

	CPen MyPen2(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* oldPen2 = dc.SelectObject(&MyPen2);

	for (x = 0; x <= 9; x++) {//위에서 아래로 선그음(10개)
		dc.MoveTo(10 + 20 * x, 10);
		dc.LineTo(10 + 20 * x, 10 + 20 * 9);
	}
	for (y = 0; y <= 9; y++) {//왼쪽에서 오른쪽으로 선그음
		dc.MoveTo(10, 10+20*y);
		dc.LineTo(10 + 20 * 9, 10 + 20 * y);
	}
	dc.SelectObject(oldPen2);

}


void COmokGame::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.
	if (m_bStart == true) {
		DrawBoard();
		DrawDol();
	}
}

void COmokGame::InitBoard()
{
	for (int y = 0; y < 10; y++) {
		for (int x = 0; x < 10; x++) {
			m_nBoard[y][x] = 0;
		}
	}
}


BOOL COmokGame::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_bStart = false;
	InitBoard();
	m_bTrun = false;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void COmokGame::DrawDol()
{
	CClientDC dc(this);
	int x, y;
	for (y = 0; y < 10; y++) {
		for (x = 0; x < 10; x++) {
			if (m_nBoard[y][x] == 1) {//바둑알이 검정색이라면
				dc.SelectObject(GetStockObject(BLACK_BRUSH));
				dc.Ellipse(2 + 20 * x, 2 + 20 * y, 18 + 20 * x, 18 + 20 * y);
			}
			else if(m_nBoard[y][x]==2){//바둑알이 흰색이라면
				dc.SelectObject(GetStockObject(WHITE_BRUSH));
				dc.Ellipse(2 + 20 * x, 2 + 20 * y, 18 + 20 * x, 18 + 20 * y);
			}
		}
	}
}


void COmokGame::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bStart == true) {
		int ax = 0, ay = 0;
		ax = point.x / 20;//선과선사이가 20이라 20을 나눔
		ay = point.y / 20;
		//오목판 벗어났는지 판단
		if ((ax < 0) || (ax >= 10) || (ay < 0) || (ay >= 10)) {
			return;
		}
		//오목판에 알이 놓여져 있는지 판단
		if (m_nBoard[ay][ax] != 0) {
			return;
		}
		//검정돌 흰돌 차례대로 놓이게 하기
		if (m_bTrun == false) {
			m_nBoard[ay][ax] = 1;
			m_bTrun = true;
		}
		else if (m_bTrun == true) {
			m_nBoard[ay][ax] = 2;
			m_bTrun = false;
		}

		if (m_bTrun == false) {
			m_strCol = "검정색 돌";
		}
		else if (m_bTrun == true) {
			m_strCol = "흰색 돌";
		}
		UpdateData(false);//화면 갱신
		Gameover();
		DrawDol();//알을 다시 그림
	}
	CDialog::OnLButtonDown(nFlags, point);
}

BOOL COmokGame::Gameover(void)
{
	if (m_bTrun) {
		//가로체크
		for (int x = 0; x < 11; x++) {
			for (int y = 0; y < 15; y++) {
				if (m_nBoard[x][y] == 1) {
					if ((m_nBoard[x + 1][y] == 1) && (m_nBoard[x + 2][y] == 1) && (m_nBoard[x + 3][y] == 1) && (m_nBoard[x + 4][y] == 1)) {
						MessageBox(_T("검은돌 승리"));
						return true;
					}
				}
			}
		}
		//세로체크
		for (int x = 0; x < 15; x++) {
			for (int y = 0; y < 11; y++) {
				if (m_nBoard[x][y] == 1) {
					if ((m_nBoard[x][y + 1] == 1) && (m_nBoard[x][y + 2] == 1) && (m_nBoard[x][y + 3] == 1) && (m_nBoard[x][y + 4] == 1)) {
						MessageBox(_T("검은돌 승리"));
						return true;
					}
				}
			}
		}
		//대각선 체크
		for (int x = 0; x < 11; x++) {
			for (int y = 0; y < 11; y++) {
				if (m_nBoard[x][y] == 1) {
					if ((m_nBoard[x + 1][y + 1] == 1) && (m_nBoard[x + 2][y + 2] == 1) && (m_nBoard[x + 3][y + 3] == 1) && (m_nBoard[x + 4][y + 4] == 1)) {
						MessageBox(_T("검은돌 승리"));
						return true;
					}
				}
			}
		}

		for (int x = 0; x < 11; x++) {
			for (int y = 0; y < 11; y++) {
				if (m_nBoard[x][y] == 1) {
					if ((m_nBoard[x - 1][y + 1] == 1) && (m_nBoard[x - 2][y + 2] == 1) && (m_nBoard[x - 3][y + 3] == 1) && (m_nBoard[x - 4][y + 4] == 1)) {
						MessageBox(_T("검은돌 승리"));
						return true;
					}
				}
			}
		}
		
	}
	else {//가로체크
		for (int x = 0; x < 11; x++) {
			for (int y = 0; y < 15; y++) {
				if (m_nBoard[x][y] == 2) {
					if ((m_nBoard[x + 1][y] == 2) && (m_nBoard[x + 2][y] == 2) && (m_nBoard[x + 3][y] == 2) && (m_nBoard[x + 4][y] == 2)) {
						MessageBox(_T("흰돌 승리"));
						return true;
					}
				}
			}
		}
		//세로체크
		for (int x = 0; x < 15; x++) {
			for (int y = 0; y < 11; y++) {
				if (m_nBoard[x][y] == 2) {
					if ((m_nBoard[x][y + 1] == 2) && (m_nBoard[x][y + 2] == 2) && (m_nBoard[x][y + 3] == 2) && (m_nBoard[x][y + 4] == 2)) {
						MessageBox(_T("흰돌 승리"));
						return true;
					}
				}
			}
		}
		//대각선 체크
		for (int x = 0; x < 11; x++) {
			for (int y = 0; y < 11; y++) {
				if (m_nBoard[x][y] == 2) {
					if ((m_nBoard[x + 1][y + 1] == 2) && (m_nBoard[x + 2][y + 2] == 2) && (m_nBoard[x + 3][y + 3] == 2) && (m_nBoard[x + 4][y + 4] == 2)) {
						MessageBox(_T("흰돌 승리"));
						return true;
					}
				}
			}
		}

		for (int x = 0; x < 11; x++) {
			for (int y = 0; y < 11; y++) {
				if (m_nBoard[x][y] == 2) {
					if ((m_nBoard[x - 1][y + 1] == 2) && (m_nBoard[x - 2][y + 2] == 2) && (m_nBoard[x - 3][y + 3] == 2) && (m_nBoard[x - 4][y + 4] == 2)) {
						MessageBox(_T("흰돌 승리"));
						return true;
					}
				}
			}
		}
		
	}

	return 0;
}
