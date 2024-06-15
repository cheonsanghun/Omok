#pragma once
#include "afxdialogex.h"


// COmokGame 대화 상자

class COmokGame : public CDialog
{
	DECLARE_DYNAMIC(COmokGame)

public:
	COmokGame(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~COmokGame();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	HICON m_hIcon;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strCol;
	afx_msg void OnBnClickedButtStart();
	afx_msg void OnBnClickedButtRestart();
	afx_msg void OnBnClickedButtExit();
public:
	void DrawBoard();//오목판 그리기
	BOOL m_bStart;//시작시 판이 먼저 그려지지 않게 하기
	afx_msg void OnPaint();
	int m_nBoard[10][10];
	void InitBoard();
	virtual BOOL OnInitDialog();
	void DrawDol();
	BOOL m_bTrun;//어떤색 알이 놓이게 할 순서인지
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL Gameover(void);
};
