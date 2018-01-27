
// GetGlyphOutline_VS2010Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GetGlyphOutline_VS2010.h"
#include "GetGlyphOutline_VS2010Dlg.h"
#include "afxdialogex.h"
#include "GB18030_UNICODE.h"
#include "WizFontsEnumerator.h"
#include "WizFontNamesComboBox.h"
#include "WizFontScriptsComboBox.h"
#include "WizFontSizesComboBox.h"
#include "WizFontExampleStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define Function_Type 1

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGetGlyphOutline_VS2010Dlg 对话框




CGetGlyphOutline_VS2010Dlg::CGetGlyphOutline_VS2010Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGetGlyphOutline_VS2010Dlg::IDD, pParent)
	, m_dstBinaryFileName(_T(""))
	, m_dstFileName(_T(""))
	, m_RowPixel(48)
	, m_ColPixel(48)
	, m_OpenFileName(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetGlyphOutline_VS2010Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_RowPixel);
	DDX_Text(pDX, IDC_EDIT2, m_ColPixel);
	DDV_MinMaxUInt(pDX, m_RowPixel, 0, 200);
	DDV_MinMaxUInt(pDX, m_ColPixel, 0, 200);
	DDX_Text(pDX, IDC_EDIT3, m_OpenFileName);

	DDX_Control(pDX, IDC_ITALIC_CHECK, m_Italic);
	DDX_Control(pDX, IDC_BOLD_CHECK, m_bold);
	DDX_Control(pDX, IDC_UNDERLINE_CHECK, m_Underline);
	DDX_Control(pDX, IDC_SCRIPT, m_ScriptCombo);
	DDX_Control(pDX, IDC_FONTSIZE, m_SizeCombo);
	DDX_Control(pDX, IDC_FONTNAMES, m_FontNamesCombo);
	DDX_Control(pDX, IDC_SAMPLEBOX, m_SampleBox);
}

BEGIN_MESSAGE_MAP(CGetGlyphOutline_VS2010Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON5, &CGetGlyphOutline_VS2010Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CGetGlyphOutline_VS2010Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CGetGlyphOutline_VS2010Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CGetGlyphOutline_VS2010Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CGetGlyphOutline_VS2010Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON7, &CGetGlyphOutline_VS2010Dlg::OnBnClickedButton7)
	ON_CBN_SELCHANGE(IDC_FONTNAMES, &CGetGlyphOutline_VS2010Dlg::OnCbnSelchangeFontnames)
	ON_CBN_SELCHANGE(IDC_FONTSIZE, &CGetGlyphOutline_VS2010Dlg::OnCbnSelchangeFontsize)
	ON_CBN_SELCHANGE(IDC_SCRIPT, &CGetGlyphOutline_VS2010Dlg::OnCbnSelchangeScript)
	ON_BN_CLICKED(IDC_ITALIC_CHECK, &CGetGlyphOutline_VS2010Dlg::OnBnClickedItalicCheck)
	ON_BN_CLICKED(IDC_BOLD_CHECK, &CGetGlyphOutline_VS2010Dlg::OnBnClickedBoldCheck)
	ON_BN_CLICKED(IDC_UNDERLINE_CHECK, &CGetGlyphOutline_VS2010Dlg::OnBnClickedUnderlineCheck)
	ON_CBN_EDITUPDATE(IDC_FONTSIZE, &CGetGlyphOutline_VS2010Dlg::OnCbnEditupdateFontsize)
	ON_EN_CHANGE(IDC_EDIT1, &CGetGlyphOutline_VS2010Dlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDOK, &CGetGlyphOutline_VS2010Dlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT2, &CGetGlyphOutline_VS2010Dlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CGetGlyphOutline_VS2010Dlg 消息处理程序

BOOL CGetGlyphOutline_VS2010Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_Fonts.Enumerate(this);
	m_FontNamesCombo.Initialize(m_Fonts);
	Update4NewFontName();
	FontChanged();
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGetGlyphOutline_VS2010Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGetGlyphOutline_VS2010Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGetGlyphOutline_VS2010Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGetGlyphOutline_VS2010Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CFontDialog fdlg;
	fdlg.DoModal();
	fdlg.GetCurrentFont(&m_logFont);
}


CString CGetGlyphOutline_VS2010Dlg::SelFileName(void)
{
#if 0
	TCHAR lpstrFile[MAX_PATH];
	OPENFILENAME file = { 0 };
	file.lStructSize = sizeof(file);
	file.lpstrTitle = TEXT("Please select a file");
	file.lpstrFile = lpstrFile;
	file.nMaxFile = MAX_PATH;
	file.lpstrFilter = _T("txt(*.txt)\0*.txt\0\0");
	file.hwndOwner = GetSafeHwnd();
	if (::GetOpenFileName(&file)) {

	}
	return (CString)lpstrFile;
#endif
	OPENFILENAME ofn;      // 公共对话框结构。
	TCHAR szFile[MAX_PATH]; // 保存获取文件名称的缓冲区。          

	// 初始化选择文件对话框。
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = m_hWnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = _T('\0');
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = _T("txt(*.txt)\0*.txt\0\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = _T("Please select a file");
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn)) {
		//OutputDebugString(szFile);
		//OutputDebugString(_T("\r\n"));
	}
	return (CString)szFile;
}


CString CGetGlyphOutline_VS2010Dlg::AppPath(void)
{
	CString strModulePath;

	DWORD dwResult = ::GetModuleFileName(NULL, strModulePath.GetBuffer(MAX_PATH), MAX_PATH);
	ASSERT(dwResult);

	strModulePath.ReleaseBuffer();
	strModulePath = strModulePath.Left(strModulePath.ReverseFind(_T('\\')) + 1);

	return strModulePath;
}
#define CODE_PAGE_GB18030 54936
#define CODE_PAGE_utf32B 12000
#define CODE_PAGE_utf32BE 12001
void CharToTchar_CP(UINT CP_VALUE, const char * _char, int charlen, TCHAR * tchar)
{
	int iLength;
	iLength = MultiByteToWideChar(CP_VALUE, 0, _char, charlen, NULL, 0);
	MultiByteToWideChar(CP_VALUE, 0, _char, charlen, (LPWSTR)tchar, iLength);
}
void CGetGlyphOutline_VS2010Dlg::CharToTchar(const char * _char, int charlen, TCHAR * tchar)
{
	int iLength;
	iLength = MultiByteToWideChar(CODE_PAGE_GB18030, 0, _char, charlen, NULL, 0);
	MultiByteToWideChar(CODE_PAGE_GB18030, 0, _char, charlen, (LPWSTR)tchar, iLength);
}
void CGetGlyphOutline_VS2010Dlg::TCharToChar(const TCHAR * tchar, char * _char)
{
	int iLength;
	//获取字节长度   
	iLength = WideCharToMultiByte(CODE_PAGE_GB18030, 0, (LPCWSTR)tchar, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CODE_PAGE_GB18030, 0, (LPCWSTR)tchar, -1, _char, iLength, NULL, NULL);
}

UINT Gb18030ToUnicode(__in const UINT m_gb18030)
{
	UINT s = 0;
	UINT m_unicode = 0;
	int Gb18030cnt;
	//双字节
	if (m_gb18030 < 0x10000)
	{
		Gb18030cnt = sizeof(INT_GB18030_2b) / sizeof(UINT);
		for (s = 0; s < Gb18030cnt; s++)
		{
			if (m_gb18030 == INT_GB18030_2b[s])
			{
				m_unicode = INT_UNICODE_2b[s];
				return m_unicode;
			}
		}
	}
	else if ((m_gb18030 >= 0X81308130) && (m_gb18030 <= 0X8431A439))///0X81308130-0X8431A439
	{
		Gb18030cnt = sizeof(INT_GB18030_4b) / sizeof(UINT);
		for (s = 0; s < Gb18030cnt; s++)
		{
			if (m_gb18030 == INT_GB18030_4b[s])
			{
				m_unicode = INT_UNICODE_4b[s];
				return m_unicode;
			}
		}
	}
	else
	{///GB18030的4个字节（0x90308130-0xE3329A35）
		UINT B1 = m_gb18030 >> 24;
		UINT B2 = (m_gb18030 << 8) >> 24;
		UINT B3 = (m_gb18030 << 16) >> 24;
		UINT B4 = (m_gb18030 << 24) >> 24;
		m_unicode = (B1 - 144) * 12600 + (B2 - 48) * 1260 + (B3 - 129) * 10 + (B4 - 48) * 10 + 65536;
		return m_unicode;
	}
}

UINT UnicodeToGb18030(__in const UINT m_unicode)
{
	UINT s = 0;
	UINT m_gb18030 = 0;
	int Gb18030cnt = 0;

	if (m_unicode < 0x10000)//双字节
	{
		Gb18030cnt = sizeof(INT_GB18030_2b) / sizeof(UINT);
		for (s = 0; s < Gb18030cnt; s++)
		{
			if (m_unicode == INT_UNICODE_2b[s])
			{
				m_gb18030 = INT_GB18030_2b[s];
				return m_gb18030;
			}
		}

		///0X81308130-0X8431A439
		Gb18030cnt = sizeof(INT_GB18030_4b) / sizeof(UINT);
		for (s = 0; s < Gb18030cnt; s++)
		{
			if (m_unicode == INT_UNICODE_4b[s])
			{
				m_gb18030 = INT_GB18030_4b[s];
				return m_gb18030;
			}
		}
	}
	else
	{///GB18030的4个字节（0x90308130-0xE3329A35）
		UINT m1 = (m_unicode - 65536) / 12600;
		UINT n1 = (m_unicode - 65536) % 12600;
		UINT m2 = m1 / 1260;
		UINT n2 = n1 % 1260;
		UINT m3 = n2 / 10;
		UINT n3 = n2 % 10;
		m_gb18030 = (m1 + 144) * 0x1000000 + (m2 + 48) * 0x10000 + (m3 + 129) * 0x100 + n3 + 48;
		return m_gb18030;
	}
}

#define be_32(x)      (((x)<<24) | ((x)>>24) | (((x)<<8)&0x00ff0000) | (((x)>>8)&0x0000ff00))
UINT32 get_bits(UCHAR *buf, UINT bit_indx, UCHAR bits)
{
	UCHAR *ptr = buf + bit_indx / 8;
	UINT32 val;
	UINT count = bit_indx % 8;

	val = *(UINT32 *)ptr;
	val = (be_32(val) << count) >> (32 - bits);
	return val;
}
INT CGetGlyphOutline_VS2010Dlg::ProcessBuff(UCHAR* dst, UINT dstRowNum, UINT dstBytesPerLine, UCHAR* src, UINT srcRowNum, UINT srcBytesPerLine, int xoffset, int yoffset)
{
	UCHAR *dstPtr = dst + yoffset * dstBytesPerLine + xoffset / 8;
	UCHAR *srcPtr = src, bits;

	UINT cnt, bit_indx = 0, bitsPerLine = srcBytesPerLine * 8;
	UINT32 val;
	UINT dstRow, srcRow;

	if (dstPtr > dst + dstRowNum * dstBytesPerLine)
		return -1;

	for (dstRow = yoffset, srcRow = 0; dstRow < dstRowNum && srcRow < srcRowNum;
		dstRow++, srcRow++)
	{

		dstPtr = dst + dstRow * dstBytesPerLine + xoffset / 8;
		srcPtr = src + srcRow * srcBytesPerLine;

		bit_indx = 0;
		cnt = xoffset / 8; bits = xoffset % 8;

		val = get_bits(srcPtr, bit_indx, 8 - bits); bit_indx += 8 - bits;

		*dstPtr++ = (UCHAR)val; cnt++;

		for (; cnt < dstBytesPerLine && bit_indx < bitsPerLine; cnt++) {
			val = get_bits(srcPtr, bit_indx, 8);

			bit_indx += 8;

			if (bit_indx >= bitsPerLine)
				val >>= (8 - bits);

			*dstPtr++ = (UCHAR)val;
		}

	}
	return 0;
}
INT CGetGlyphOutline_VS2010Dlg::ProcessBuff_2(UCHAR* dst, UINT dstRowNum, UINT dstBytesPerLine, UCHAR* src, UINT srcRowNum, UINT srcBytesPerLine, int xoffset, int yoffset)
{
	for (UINT i = 0; i < srcRowNum; i++)
	{
		for (UINT j = 0; j < srcBytesPerLine; j++)
		{
			if ((yoffset + i)*dstBytesPerLine + j >= dstRowNum*dstBytesPerLine)
				continue;
			else
				dst[(yoffset + i)*dstBytesPerLine + j] = src[i* srcBytesPerLine + j];//x 偏移无效
/*			if(i*dstBytesPerLine+j<=dstRowNum*dstBytesPerLine)
				dst[i*dstBytesPerLine+j]=src[i* srcBytesPerLine + j];//x 偏移无效*/
		}
	}

	return 0;
}


////////ASCII////
INT CGetGlyphOutline_VS2010Dlg::CreatePixelFont_ASCII(CString dstFileName, UINT pixelFontRow, UINT pixelFontCol, CDC *pDC)
{
	UINT lineBytes, totalBytes;
	TCHAR cc[32];
	CFile dstFile;
	GLYPHMETRICS gm;
	MAT2 mat2;
	INT  len, xoffset, yoffset;

	dstFile.Open(dstFileName, CFile::modeCreate | CFile::modeWrite, NULL);

	lineBytes = (pixelFontCol + 7) / 8;
	totalBytes = lineBytes * pixelFontRow;

	UCHAR *dstbuf = new UCHAR[totalBytes];

	//c = *(TCHAR *)srcPtr;
	unsigned char chinText[5];
	unsigned char c1 = 0x81, c2 = 0x00, c3 = 0x00, c4 = 0x00;
	char* a = new char[30];
	memset(a, 0x00, 30);
	for (c1 = 0x00; c1 <= 0xFF; c1++)//ASCII
	{
		chinText[0] = c1;
		chinText[1] = c2;
		chinText[2] = c3;
		chinText[3] = c4;
		chinText[4] = 0;

		//			CharToTchar((const char*)a,&chText);
		CharToTchar_CP(437, (const char*)chinText, 1, cc);
		TCHAR c = cc[0];

		memset(dstbuf, 0x00, totalBytes);
		memset(&mat2, 0, sizeof(mat2));
		mat2.eM11.value = 1;   mat2.eM12.value = 0;
		mat2.eM21.value = 0;   mat2.eM22.value = 1;
		len = ::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, 0, 0, &mat2);
		if (len == -1) {
			delete[]dstbuf; dstFile.Close();
			return -1;
		}

		if (len == 0) {
			dstFile.Write(dstbuf, totalBytes);
		}
		else {
			char *buf = new char[len];
			memset(buf, 0x00, len);
			::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, len, buf, &mat2);
			UCHAR *pData = (UCHAR *)buf;
			UINT cnt = ((gm.gmBlackBoxX + 31) >> 5) << 2;
			OUTLINETEXTMETRIC otm;
			memset(&otm, 0, sizeof(otm));
			otm.otmSize = sizeof(otm);
			pDC->GetOutlineTextMetrics(sizeof(otm), &otm);
			xoffset = gm.gmptGlyphOrigin.x;     //x的偏移量   
			//y的偏移量     字的顶部   -   y方向原点   都是相对于baseline   
			yoffset = otm.otmAscent - gm.gmptGlyphOrigin.y;
			if (xoffset < 0)xoffset = 0;
			if (yoffset < 0)yoffset = 0;
#if	Function_Type ==1
			ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
#else
			ProcessBuff_2(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
#endif
#if 0
			UINT i, j, k;
			UCHAR *ptr = dstbuf;
			CBrush brush;
			CRect rect(0, 0, 100, 100);
			brush.CreateSolidBrush(RGB(255, 255, 255));
			pDC->FillRect(&rect, &brush);


			for (j = 0; j < pixelFontRow; j++) {
				for (i = 0; i < lineBytes; i++) {
					for (k = 0; k < 8; k++) {
						if ((*ptr)   &   (0x80 >> k))
							pDC->SetPixel(i * 8 + k, j, RGB(255, 0, 0));
					}
					ptr++;
				}
			}
			brush.DeleteObject();
#endif

			dstFile.Write(dstbuf, totalBytes);
			delete[]buf;
		}
		if (c1 == 0xff)
			break;
	}

	delete[]dstbuf; dstFile.Close();
	return 0;
}
INT CGetGlyphOutline_VS2010Dlg::CreatePixelFont_GB2312(CString dstFileName, UINT pixelFontRow, UINT pixelFontCol, CDC *pDC)
{
	return 0;
}


INT CGetGlyphOutline_VS2010Dlg::CreatePixelFont_GB18030(CString dstFileName, UINT pixelFontRow, UINT pixelFontCol, CDC *pDC)
{
	UINT lineBytes, totalBytes;
	TCHAR cc[32];
	CFile dstFile;
	GLYPHMETRICS gm;
	MAT2 mat2;
	INT  len, xoffset, yoffset;

	dstFile.Open(dstFileName, CFile::modeCreate | CFile::modeWrite, NULL);
	CFile Save18030Hex;
	Save18030Hex.Open(AppPath() + L"data.asm", CFile::modeCreate | CFile::modeWrite, NULL);

	lineBytes = (pixelFontCol + 7) / 8;
	totalBytes = lineBytes * pixelFontRow;

	UCHAR *dstbuf = new UCHAR[totalBytes];

	//c = *(TCHAR *)srcPtr;
	unsigned char chinText[5];
	unsigned char c1 = 0x81, c2 = 0x00, c3 = 0x00, c4 = 0x00;
	char* a = new char[30];
	memset(a, 0x00, 30);





	//	for (c1 = 0xAA; c1 <= 0xAA; c1++)
	//	{
	//		for (c2 = 0xB4; c2 <= 0xfe; c2++)
	//		{
	//			memset(cc, 0, 32);
	//			chinText[0] = c1;
	//			chinText[1] = c2;
	//			chinText[2] = c3;
	//			chinText[3] = c4;
	//			chinText[4] = 0;
	//
	//
	//			CFont font;
	//			VERIFY(font.CreateFont(
	//				m_logFont.lfHeight, m_logFont.lfWidth,
	//				m_logFont.lfEscapement, m_logFont.lfOrientation,
	//				m_logFont.lfWeight, m_logFont.lfItalic,
	//
	//				m_logFont.lfUnderline, m_logFont.lfStrikeOut,
	//				134, m_logFont.lfOutPrecision,
	//				m_logFont.lfCharSet, m_logFont.lfOutPrecision,
	//				m_logFont.lfClipPrecision, m_logFont.lfQuality,
	//				m_logFont.lfPitchAndFamily, L"Arial Unicode MS")
	//			);
	//			pDC->SelectObject(&font);
	//
	//
	//
	//			CharToTchar((const char*)chinText, 2, cc);
	//			INT c = cc[0];
	//
	//			memset(dstbuf, 0x00, totalBytes);
	//			memset(&mat2, 0, sizeof(mat2));
	//			mat2.eM11.value = 1;   mat2.eM12.value = 0;
	//			mat2.eM21.value = 0;   mat2.eM22.value = 1;
	//			len = ::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, 0, 0, &mat2);
	//			if (len == -1) {
	//				delete[]dstbuf; dstFile.Close();
	//				return -1;
	//			}
	//
	//			if (len == 0) {
	//				dstFile.Write(dstbuf, totalBytes);
	//			}
	//			else {
	//				char *buf = new char[len];
	//				memset(buf, 0x00, len);
	//				::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, len, buf, &mat2);
	//				UCHAR *pData = (UCHAR *)buf;
	//				UINT cnt = ((gm.gmBlackBoxX + 31) >> 5) << 2;
	//
	//				OUTLINETEXTMETRIC otm;
	//				memset(&otm, 0, sizeof(otm));
	//				otm.otmSize = sizeof(otm);
	//				pDC->GetOutlineTextMetrics(sizeof(otm), &otm);
	//				xoffset = gm.gmptGlyphOrigin.x;     //x的偏移量   
	//				y的偏移量     字的顶部   -   y方向原点   都是相对于baseline   
	//				yoffset = otm.otmAscent - gm.gmptGlyphOrigin.y;
	//				if (xoffset < 0)
	//					xoffset = 0;
	//				if (yoffset < 0)
	//					yoffset = 0;
	//
	//#if	Function_Type ==1
	//				ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
	//#else
	//				ProcessBuff_2(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
	//#endif
	//#if 0
	//				UINT i, j, k;
	//				UCHAR *ptr = dstbuf;
	//				CBrush brush;
	//				CRect rect(0, 0, 100, 100);
	//				brush.CreateSolidBrush(RGB(255, 255, 255));
	//				pDC->FillRect(&rect, &brush);
	//
	//
	//				for (j = 0; j < pixelFontRow; j++) {
	//					for (i = 0; i < lineBytes; i++) {
	//						for (k = 0; k < 8; k++) {
	//							if ((*ptr)   &   (0x80 >> k))
	//								pDC->SetPixel(i * 8 + k, j, RGB(255, 0, 0));
	//						}
	//						ptr++;
	//					}
	//				}
	//				brush.DeleteObject();
	//#endif
	//
	//				dstFile.Write(dstbuf, totalBytes);
	//				Save18030Hex.Write(chinText, 2);
	//				delete[]buf;
	//			}
	//		}
	//	}



	//中文和其他

		//	for (c1 = 0xA1; c1 <= 0xf7; c1++)
		//	{
		//		for (c2 = 0xA1; c2 <= 0xfe; c2++)
		//		{
		//			if (c1 == 0xa3 && c2 >= 0xc1 && c2 <= 0xda)
		//			{
		//				break;
		//			}
		//			else if (c1 == 0xa3 && c2 >= 0xe1 && c2 <= 0xfa)
		//			{
		//				break;
		//			}
		//			/*else if (c1 == 0xa1 && c2 == 0xee)
		//			{
		//				break;*/
		//				//CFont font;
		//				//VERIFY(font.CreateFont(
		//				//	m_logFont.lfHeight, m_logFont.lfWidth,
		//				//	m_logFont.lfEscapement, m_logFont.lfOrientation,
		//
		//				//	//100, m_logFont.lfItalic,
		//				//	m_logFont.lfWeight, m_logFont.lfItalic,
		//
		//				//	m_logFont.lfUnderline, m_logFont.lfStrikeOut,
		//				//	//130, m_logFont.lfOutPrecision,
		//				//	m_logFont.lfCharSet, m_logFont.lfOutPrecision,
		//				//	m_logFont.lfClipPrecision, m_logFont.lfQuality,
		//				//	//m_logFont.lfPitchAndFamily, L"Arial Unicode MS"/*m_logFont.lfFaceName*/
		//				//	m_logFont.lfPitchAndFamily, m_logFont.lfFaceName
		//				//)
		//				//);
		//				//pDC->SelectObject(&font);
		//			/*}*/
		//
		//			else
		//			{
		//				memset(cc, 0, 32);
		//				chinText[0] = c1;
		//				chinText[1] = c2;
		//				chinText[2] = c3;
		//				chinText[3] = c4;
		//				chinText[4] = 0;
		//
		//				CharToTchar((const char*)chinText, 2, cc);
		//				INT c = cc[0];
		//
		//				memset(dstbuf, 0x00, totalBytes);
		//				memset(&mat2, 0, sizeof(mat2));
		//				mat2.eM11.value = 1;   mat2.eM12.value = 0;
		//				mat2.eM21.value = 0;   mat2.eM22.value = 1;
		//				len = ::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, 0, 0, &mat2);
		//				if (len == -1) {
		//					delete[]dstbuf; dstFile.Close();
		//					return -1;
		//				}
		//
		//				if (len == 0) {
		//					dstFile.Write(dstbuf, totalBytes);
		//				}
		//				else {
		//					char *buf = new char[len];
		//					memset(buf, 0x00, len);
		//					::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, len, buf, &mat2);
		//					UCHAR *pData = (UCHAR *)buf;
		//					UINT cnt = ((gm.gmBlackBoxX + 31) >> 5) << 2;
		//
		//					OUTLINETEXTMETRIC otm;
		//					memset(&otm, 0, sizeof(otm));
		//					otm.otmSize = sizeof(otm);
		//					pDC->GetOutlineTextMetrics(sizeof(otm), &otm);
		//					xoffset = gm.gmptGlyphOrigin.x;     //x的偏移量   
		//					//y的偏移量     字的顶部   -   y方向原点   都是相对于baseline   
		//					yoffset = otm.otmAscent - gm.gmptGlyphOrigin.y;
		//					if (xoffset < 0)
		//						xoffset = 0;
		//					if (yoffset < 0)
		//						yoffset = 0;
		//
		//#if	Function_Type ==1
		//					ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
		//#else
		//					ProcessBuff_2(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
		//#endif
		//#if 0
		//					UINT i, j, k;
		//					UCHAR *ptr = dstbuf;
		//					CBrush brush;
		//					CRect rect(0, 0, 100, 100);
		//					brush.CreateSolidBrush(RGB(255, 255, 255));
		//					pDC->FillRect(&rect, &brush);
		//
		//
		//					for (j = 0; j < pixelFontRow; j++) {
		//						for (i = 0; i < lineBytes; i++) {
		//							for (k = 0; k < 8; k++) {
		//								if ((*ptr)   &   (0x80 >> k))
		//									pDC->SetPixel(i * 8 + k, j, RGB(255, 0, 0));
		//							}
		//							ptr++;
		//						}
		//					}
		//					brush.DeleteObject();
		//#endif
		//
		//					dstFile.Write(dstbuf, totalBytes);
		//					Save18030Hex.Write(chinText, 2);
		//					delete[]buf;
		//				}
		//			}
		//		}
		//	}

		//	for (c1 = 0x81; c1 <= 0xa0; c1++)
		//	{
		//		for (c2 = 0x40; c2 <= 0xfe; c2++)
		//		{
		//			memset(cc, 0, 32);
		//			chinText[0] = c1;
		//			chinText[1] = c2;
		//			chinText[2] = c3;
		//			chinText[3] = c4;
		//			chinText[4] = 0;
		//
		//			CharToTchar((const char*)chinText, 2, cc);
		//			INT c = cc[0];
		//
		//			memset(dstbuf, 0x00, totalBytes);
		//			memset(&mat2, 0, sizeof(mat2));
		//			mat2.eM11.value = 1;   mat2.eM12.value = 0;
		//			mat2.eM21.value = 0;   mat2.eM22.value = 1;
		//			len = ::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, 0, 0, &mat2);
		//			if (len == -1) {
		//				delete[]dstbuf; dstFile.Close();
		//				return -1;
		//			}
		//
		//			if (len == 0) {
		//				dstFile.Write(dstbuf, totalBytes);
		//			}
		//			else {
		//				char *buf = new char[len];
		//				memset(buf, 0x00, len);
		//				::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, len, buf, &mat2);
		//				UCHAR *pData = (UCHAR *)buf;
		//				UINT cnt = ((gm.gmBlackBoxX + 31) >> 5) << 2;
		//				OUTLINETEXTMETRIC otm;
		//				memset(&otm, 0, sizeof(otm));
		//				otm.otmSize = sizeof(otm);
		//				pDC->GetOutlineTextMetrics(sizeof(otm), &otm);
		//				xoffset = gm.gmptGlyphOrigin.x;     //x的偏移量   
		//				//y的偏移量     字的顶部   -   y方向原点   都是相对于baseline   
		//				yoffset = otm.otmAscent - gm.gmptGlyphOrigin.y;
		//				if (xoffset < 0)
		//					xoffset = 0;
		//				if (yoffset < 0)
		//					yoffset = 0;
		//#if	Function_Type ==1
		//				ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
		//#else
		//				ProcessBuff_2(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
		//#endif
		//#if 0
		//				UINT i, j, k;
		//				UCHAR *ptr = dstbuf;
		//				CBrush brush;
		//				CRect rect(0, 0, 100, 100);
		//				brush.CreateSolidBrush(RGB(255, 255, 255));
		//				pDC->FillRect(&rect, &brush);
		//
		//
		//				for (j = 0; j < pixelFontRow; j++) {
		//					for (i = 0; i < lineBytes; i++) {
		//						for (k = 0; k < 8; k++) {
		//							if ((*ptr)   &   (0x80 >> k))
		//								pDC->SetPixel(i * 8 + k, j, RGB(255, 0, 0));
		//						}
		//						ptr++;
		//					}
		//				}
		//				brush.DeleteObject();
		//#endif
		//
		//				dstFile.Write(dstbuf, totalBytes);
		//				Save18030Hex.Write(chinText, 2);
		//				delete[]buf;
		//			}
		//
		//		}
		//	}
		//	for (c1 = 0xaa; c1 <= 0xfe; c1++)
		//	{
		//		for (c2 = 0x40; c2 <= 0xa0; c2++)
		//		{
		//			memset(cc, 0, 32);
		//			chinText[0] = c1;
		//			chinText[1] = c2;
		//			chinText[2] = c3;
		//			chinText[3] = c4;
		//			chinText[4] = 0;
		//
		//			CharToTchar((const char*)chinText, 2, cc);
		//			INT c = cc[0];
		//
		//			memset(dstbuf, 0x00, totalBytes);
		//			memset(&mat2, 0, sizeof(mat2));
		//			mat2.eM11.value = 1;   mat2.eM12.value = 0;
		//			mat2.eM21.value = 0;   mat2.eM22.value = 1;
		//			len = ::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, 0, 0, &mat2);
		//			if (len == -1)
		//			{
		//				delete[]dstbuf; dstFile.Close();
		//				return -1;
		//			}
		//
		//			if (len == 0)
		//			{
		//				dstFile.Write(dstbuf, totalBytes);
		//			}
		//			else
		//			{
		//				char *buf = new char[len];
		//				memset(buf, 0x00, len);
		//				::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, len, buf, &mat2);
		//				UCHAR *pData = (UCHAR *)buf;
		//				UINT cnt = ((gm.gmBlackBoxX + 31) >> 5) << 2;
		//				OUTLINETEXTMETRIC otm;
		//				memset(&otm, 0, sizeof(otm));
		//				otm.otmSize = sizeof(otm);
		//				pDC->GetOutlineTextMetrics(sizeof(otm), &otm);
		//				xoffset = gm.gmptGlyphOrigin.x;     //x的偏移量   
		//				//y的偏移量     字的顶部   -   y方向原点   都是相对于baseline   
		//				yoffset = otm.otmAscent - gm.gmptGlyphOrigin.y;
		//				if (xoffset < 0)
		//					xoffset = 0;
		//				if (yoffset < 0)
		//					yoffset = 0;
		//#if	Function_Type ==1
		//				ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
		//#else
		//				ProcessBuff_2(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
		//#endif
		//#if 0
		//				UINT i, j, k;
		//				UCHAR *ptr = dstbuf;
		//				CBrush brush;
		//				CRect rect(0, 0, 100, 100);
		//				brush.CreateSolidBrush(RGB(255, 255, 255));
		//				pDC->FillRect(&rect, &brush);
		//
		//
		//				for (j = 0; j < pixelFontRow; j++) {
		//					for (i = 0; i < lineBytes; i++) {
		//						for (k = 0; k < 8; k++) {
		//							if ((*ptr)   &   (0x80 >> k))
		//								pDC->SetPixel(i * 8 + k, j, RGB(255, 0, 0));
		//						}
		//						ptr++;
		//					}
		//				}
		//				brush.DeleteObject();
		//#endif
		//
		//				dstFile.Write(dstbuf, totalBytes);
		//				Save18030Hex.Write(chinText, 2);
		//				delete[]buf;
		//			}
		//
		//		}
		//	}
		//	for (c1 = 0x81; c1 <= 0x82; c1++)
		//	{
		//		for (c2 = 0x30; c2 <= 0x39; c2++)
		//		{
		//			for (c3 = 0x81; c3 <= 0xfe; c3++)
		//			{
		//				for (c4 = 0x30; c4 <= 0x39; c4++)
		//				{
		//					memset(cc, 0, 32);
		//					chinText[0] = c1;
		//					chinText[1] = c2;
		//					chinText[2] = c3;
		//					chinText[3] = c4;
		//					chinText[4] = 0;
		//
		//					UINT c18030 = c1 * 0x1000000 + c2 * 0x10000 + c3 * 0x100 + c4;
		//					if ((c18030 >= 0x81339d36 && c18030 <= 0x8133b635) ||//朝鲜
		//						(c18030 >= 0x8139a933 && c18030 <= 0x8139b734) ||
		//						(c18030 >= 0x8237cf35 && c18030 <= 0x8336be36))
		//					{
		//						CFont font;
		//						VERIFY(font.CreateFont(
		//							m_logFont.lfHeight, m_logFont.lfWidth,
		//							m_logFont.lfEscapement, m_logFont.lfOrientation,
		//
		//							//100, m_logFont.lfItalic,
		//							m_logFont.lfWeight, m_logFont.lfItalic,
		//
		//							m_logFont.lfUnderline, m_logFont.lfStrikeOut,
		//							//130, m_logFont.lfOutPrecision,
		//							m_logFont.lfCharSet, m_logFont.lfOutPrecision,
		//							m_logFont.lfClipPrecision, m_logFont.lfQuality,
		//							//m_logFont.lfPitchAndFamily, L"Arial Unicode MS"/*m_logFont.lfFaceName*/
		//							m_logFont.lfPitchAndFamily, m_logFont.lfFaceName
		//						)
		//						);
		//						pDC->SelectObject(&font);
		//					}
		//					else if ((c18030 >= 0x8139ee39 && c18030 <= 0x82358738) ||//中文
		//						(c18030 >= 0x95328236 && c18030 <= 0x9835f336))
		//					{
		//						CFont font;
		//						VERIFY(font.CreateFont(
		//							m_logFont.lfHeight, m_logFont.lfWidth,
		//							m_logFont.lfEscapement, m_logFont.lfOrientation,
		//							m_logFont.lfWeight, m_logFont.lfItalic,
		//
		//							m_logFont.lfUnderline, m_logFont.lfStrikeOut,
		//							//134, m_logFont.lfOutPrecision,
		//							m_logFont.lfCharSet, m_logFont.lfOutPrecision,
		//							m_logFont.lfClipPrecision, m_logFont.lfQuality,
		//							m_logFont.lfPitchAndFamily, m_logFont.lfFaceName)
		//						);
		//						pDC->SelectObject(&font);
		//					}
		//					else
		//					{
		//						CFont font;
		//						VERIFY(font.CreateFont(
		//							m_logFont.lfHeight, m_logFont.lfWidth,
		//							m_logFont.lfEscapement, m_logFont.lfOrientation,
		//							m_logFont.lfWeight, m_logFont.lfItalic,
		//							//100, m_logFont.lfItalic,
		//							m_logFont.lfUnderline, m_logFont.lfStrikeOut,
		//							//178, m_logFont.lfOutPrecision,
		//							m_logFont.lfCharSet, m_logFont.lfOutPrecision,
		//
		//							m_logFont.lfClipPrecision, m_logFont.lfQuality,
		//
		//							//m_logFont.lfPitchAndFamily, L"Arial Unicode MS"
		//							m_logFont.lfPitchAndFamily, m_logFont.lfFaceName)
		//						);
		//						pDC->SelectObject(&font);
		//					}
		//
		//					TCHAR c = 0;
		//					c = Gb18030ToUnicode(c18030);
		//
		//					memset(dstbuf, 0x00, totalBytes);
		//					memset(&mat2, 0, sizeof(mat2));
		//					mat2.eM11.value = 1;   mat2.eM12.value = 0;
		//					mat2.eM21.value = 0;   mat2.eM22.value = 1;
		//					len = ::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, 0, 0, &mat2);
		//					if (len == -1) {
		//						delete[]dstbuf; dstFile.Close();
		//						return -1;
		//					}
		//
		//					if (len == 0) {
		//						dstFile.Write(dstbuf, totalBytes);
		//					}
		//					else {
		//						char *buf = new char[len];
		//						memset(buf, 0x00, len);
		//						::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, len, buf, &mat2);
		//						UCHAR *pData = (UCHAR *)buf;
		//						UINT cnt = ((gm.gmBlackBoxX + 31) >> 5) << 2;
		//						OUTLINETEXTMETRIC otm;
		//						memset(&otm, 0, sizeof(otm));
		//						otm.otmSize = sizeof(otm);
		//						pDC->GetOutlineTextMetrics(sizeof(otm), &otm);
		//						xoffset = gm.gmptGlyphOrigin.x;     //x的偏移量   
		//						//y的偏移量     字的顶部   -   y方向原点   都是相对于baseline   
		//						yoffset = otm.otmAscent - gm.gmptGlyphOrigin.y;
		//						if (xoffset < 0)
		//							xoffset = 0;
		//						if (yoffset < 0)
		//							yoffset = 0;
		//#if	Function_Type ==1
		//						ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
		//#else
		//						ProcessBuff_2(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
		//#endif
		//#if 0
		//						UINT i, j, k;
		//						UCHAR *ptr = dstbuf;
		//						CBrush brush;
		//						CRect rect(0, 0, 100, 100);
		//						brush.CreateSolidBrush(RGB(255, 255, 255));
		//						pDC->FillRect(&rect, &brush);
		//
		//						for (j = 0; j < pixelFontRow; j++) {
		//							for (i = 0; i < lineBytes; i++) {
		//								for (k = 0; k < 8; k++) {
		//									if ((*ptr)   &   (0x80 >> k))
		//										pDC->SetPixel(i * 8 + k, j, RGB(255, 0, 0));
		//								}
		//								ptr++;
		//							}
		//						}
		//						brush.DeleteObject();
		//#endif
		//
		//						dstFile.Write(dstbuf, totalBytes);
		//						Save18030Hex.Write(chinText, 4);
		//						delete[]buf;
		//					}
		//				}
		//			}
		//		}
		//	}


	//英文

	for (c1 = 0xA3; c1 <= 0xa3; c1++)/////////////A-Z
	{
		for (c2 = 0xC1; c2 <= 0xDA; c2++)
		{

			memset(cc, 0, 32);
			chinText[0] = c1;
			chinText[1] = c2;
			chinText[2] = c3;
			chinText[3] = c4;
			chinText[4] = 0;

			//if (c2 == 0xed || c2 == 0xf7)    /////m
		/*	{
				CFont font;
				font.CreateFont(
					m_logFont.lfHeight * 4 / 3 ,7 ,
					m_logFont.lfEscapement, m_logFont.lfOrientation,
					m_logFont.lfWeight, m_logFont.lfItalic,

					m_logFont.lfUnderline, m_logFont.lfStrikeOut,

					m_logFont.lfCharSet, m_logFont.lfOutPrecision,
					m_logFont.lfClipPrecision, m_logFont.lfQuality = 4,
					m_logFont.lfPitchAndFamily, m_logFont.lfFaceName);

				pDC->SelectObject(&font);

			}*/



			CFont font;
			font.CreateFont(
				m_logFont.lfHeight * 5 / 3, 7,
				m_logFont.lfEscapement, m_logFont.lfOrientation,
				m_logFont.lfWeight, m_logFont.lfItalic,

				m_logFont.lfUnderline, m_logFont.lfStrikeOut,

				m_logFont.lfCharSet, m_logFont.lfOutPrecision,
				m_logFont.lfClipPrecision, m_logFont.lfQuality = 4,
				m_logFont.lfPitchAndFamily, m_logFont.lfFaceName);

			pDC->SelectObject(&font);


			CharToTchar((const char*)chinText, 2, cc);
			INT c = cc[0];

			memset(dstbuf, 0x00, totalBytes);
			memset(&mat2, 0, sizeof(mat2));
			mat2.eM11.value = 1;   mat2.eM12.value = 0;
			mat2.eM21.value = 0;   mat2.eM22.value = 1;
			len = ::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, 0, 0, &mat2);
			if (len == -1) {
				delete[]dstbuf; dstFile.Close();
				return -1;
			}

			if (len == 0) {
				dstFile.Write(dstbuf, totalBytes);
			}
			else {
				char *buf = new char[len];
				memset(buf, 0x00, len);
				::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, len, buf, &mat2);
				UCHAR *pData = (UCHAR *)buf;
				UINT cnt = ((gm.gmBlackBoxX + 31) >> 5) << 2;

				OUTLINETEXTMETRIC otm;
				memset(&otm, 0, sizeof(otm));
				otm.otmSize = sizeof(otm);
				pDC->GetOutlineTextMetrics(sizeof(otm), &otm);
				xoffset = (m_RowPixel - gm.gmBlackBoxX) / 2 - 6;
				//	xoffset = gm.gmptGlyphOrigin.x;     //x的偏移量   
														//y的偏移量     字的顶部   -   y方向原点   都是相对于baseline
														//	yoffset   =  pixelFontRow-gm.gmBlackBoxY;//下标
				yoffset = otm.otmAscent - gm.gmptGlyphOrigin.y -9;//+1
				//yoffset = (m_ColPixel - gm.gmBlackBoxY) / 2;
				if (xoffset < 0)
					xoffset = 0;
				if (yoffset < 0)
					yoffset = 0;
#if	Function_Type ==1
				ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
#else
				ProcessBuff_2(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
#endif
#if 0
				UINT i, j, k;
				UCHAR *ptr = dstbuf;
				CBrush brush;
				CRect rect(0, 0, 100, 100);
				brush.CreateSolidBrush(RGB(255, 255, 255));
				pDC->FillRect(&rect, &brush);


				for (j = 0; j < pixelFontRow; j++) {
					for (i = 0; i < lineBytes; i++) {
						for (k = 0; k < 8; k++) {
							if ((*ptr)   &   (0x80 >> k))
								pDC->SetPixel(i * 8 + k, j, RGB(255, 0, 0));
						}
						ptr++;
					}
				}
				brush.DeleteObject();
#endif

				dstFile.Write(dstbuf, totalBytes);
				Save18030Hex.Write(chinText, 2);
				delete[]buf;
			}

		}
	}

	//	for (c1 = 0xA3; c1 <= 0xa3; c1++)
	//	{
	//		for (c2 = 0xdb; c2 <= 0xE0; c2++)
	//		{
	//			memset(cc, 0, 32);
	//			chinText[0] = c1;
	//			chinText[1] = c2;
	//			chinText[2] = c3;
	//			chinText[3] = c4;
	//			chinText[4] = 0;
	//
	//			CharToTchar((const char*)chinText, 2, cc);
	//			INT c = cc[0];
	//
	//			memset(dstbuf, 0x00, totalBytes);
	//			memset(&mat2, 0, sizeof(mat2));
	//			mat2.eM11.value = 1;   mat2.eM12.value = 0;
	//			mat2.eM21.value = 0;   mat2.eM22.value = 1;
	//			len = ::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, 0, 0, &mat2);
	//			if (len == -1) {
	//				delete[]dstbuf; dstFile.Close();
	//				return -1;
	//			}
	//
	//			if (len == 0) {
	//				dstFile.Write(dstbuf, totalBytes);
	//			}
	//			else {
	//				char *buf = new char[len];
	//				memset(buf, 0x00, len);
	//				::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, len, buf, &mat2);
	//				UCHAR *pData = (UCHAR *)buf;
	//				UINT cnt = ((gm.gmBlackBoxX + 31) >> 5) << 2;
	//
	//				OUTLINETEXTMETRIC otm;
	//				memset(&otm, 0, sizeof(otm));
	//				otm.otmSize = sizeof(otm);
	//				pDC->GetOutlineTextMetrics(sizeof(otm), &otm);
	//				//xoffset = (m_RowPixel - gm.gmBlackBoxX) / 2;
	//				xoffset = gm.gmptGlyphOrigin.x;     //x的偏移量   
	//				//y的偏移量     字的顶部   -   y方向原点   都是相对于baseline
	//				//	yoffset   =  pixelFontRow-gm.gmBlackBoxY;//下标
	//				yoffset = otm.otmAscent - gm.gmptGlyphOrigin.y;
	//				//yoffset = (m_ColPixel - gm.gmBlackBoxY) / 2;
	//				if (xoffset < 0)
	//					xoffset = 0;
	//				if (yoffset < 0)
	//					yoffset = 0;
	//#if	Function_Type ==1
	//				ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
	//#else
	//				ProcessBuff_2(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
	//#endif
	//#if 0
	//				UINT i, j, k;
	//				UCHAR *ptr = dstbuf;
	//				CBrush brush;
	//				CRect rect(0, 0, 100, 100);
	//				brush.CreateSolidBrush(RGB(255, 255, 255));
	//				pDC->FillRect(&rect, &brush);
	//
	//
	//				for (j = 0; j < pixelFontRow; j++) {
	//					for (i = 0; i < lineBytes; i++) {
	//						for (k = 0; k < 8; k++) {
	//							if ((*ptr)   &   (0x80 >> k))
	//								pDC->SetPixel(i * 8 + k, j, RGB(255, 0, 0));
	//						}
	//						ptr++;
	//					}
	//				}
	//				brush.DeleteObject();
	//#endif
	//
	//				dstFile.Write(dstbuf, totalBytes);
	//				Save18030Hex.Write(chinText, 2);
	//				delete[]buf;
	//			}
	//
	//		}
	//	}

	for (c1 = 0xA3; c1 <= 0xa3; c1++)/////////////a-z
	{
		for (c2 = 0xe1; c2 <= 0xfa; c2++)
		{
			memset(cc, 0, 32);
			chinText[0] = c1;
			chinText[1] = c2;
			chinText[2] = c3;
			chinText[3] = c4;
			chinText[4] = 0;

			if (c2 == 0xed || c2 == 0xf7)/////m
			{
				CFont font;
				font.CreateFont(
					m_logFont.lfHeight * 4 / 3, 7,
					m_logFont.lfEscapement, m_logFont.lfOrientation,
					m_logFont.lfWeight, m_logFont.lfItalic,

					m_logFont.lfUnderline, m_logFont.lfStrikeOut,

					m_logFont.lfCharSet, m_logFont.lfOutPrecision,
					m_logFont.lfClipPrecision, m_logFont.lfQuality = 4,
					m_logFont.lfPitchAndFamily, m_logFont.lfFaceName);

				pDC->SelectObject(&font);

			}
			else
			{
				CFont font;
				font.CreateFont(
					m_logFont.lfHeight * 4 / 3, m_logFont.lfWidth,
					m_logFont.lfEscapement, m_logFont.lfOrientation,
					m_logFont.lfWeight, m_logFont.lfItalic,

					m_logFont.lfUnderline, m_logFont.lfStrikeOut,

					m_logFont.lfCharSet, m_logFont.lfOutPrecision,
					m_logFont.lfClipPrecision, m_logFont.lfQuality = 4,
					m_logFont.lfPitchAndFamily, m_logFont.lfFaceName);

				pDC->SelectObject(&font);
			}


			CharToTchar((const char*)chinText, 2, cc);
			INT c = cc[0];

			memset(dstbuf, 0x00, totalBytes);
			memset(&mat2, 0, sizeof(mat2));
			mat2.eM11.value = 1;   mat2.eM12.value = 0;
			mat2.eM21.value = 0;   mat2.eM22.value = 1;
			len = ::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, 0, 0, &mat2);
			if (len == -1) {
				delete[]dstbuf; dstFile.Close();
				return -1;
			}

			if (len == 0) {
				dstFile.Write(dstbuf, totalBytes);
			}
			else {
				char *buf = new char[len];
				memset(buf, 0x00, len);
				::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, len, buf, &mat2);
				UCHAR *pData = (UCHAR *)buf;
				UINT cnt = ((gm.gmBlackBoxX + 31) >> 5) << 2;

				OUTLINETEXTMETRIC otm;
				memset(&otm, 0, sizeof(otm));
				otm.otmSize = sizeof(otm);
				pDC->GetOutlineTextMetrics(sizeof(otm), &otm);
				xoffset = (m_RowPixel - gm.gmBlackBoxX) / 2 - 6;
				//xoffset = gm.gmptGlyphOrigin.x;     //x的偏移量   
				//y的偏移量     字的顶部   -   y方向原点   都是相对于baseline
				//	yoffset   =  pixelFontRow-gm.gmBlackBoxY;//下标
				//yoffset = otm.otmAscent - gm.gmptGlyphOrigin.y + 3;
				yoffset = otm.otmAscent - gm.gmptGlyphOrigin.y - 3;
				//yoffset = (m_ColPixel - gm.gmBlackBoxY) / 2;
				if (xoffset < 0)
					xoffset = 0;
				if (yoffset < 0)
					yoffset = 0;
#if	Function_Type ==1
				ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
#else
				ProcessBuff_2(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
#endif
#if 0
				UINT i, j, k;
				UCHAR *ptr = dstbuf;
				CBrush brush;
				CRect rect(0, 0, 100, 100);
				brush.CreateSolidBrush(RGB(255, 255, 255));
				pDC->FillRect(&rect, &brush);


				for (j = 0; j < pixelFontRow; j++) {
					for (i = 0; i < lineBytes; i++) {
						for (k = 0; k < 8; k++) {
							if ((*ptr)   &   (0x80 >> k))
								pDC->SetPixel(i * 8 + k, j, RGB(255, 0, 0));
						}
						ptr++;
					}
				}
				brush.DeleteObject();
#endif

				dstFile.Write(dstbuf, totalBytes);
				Save18030Hex.Write(chinText, 2);
				delete[]buf;
			}

		}
	}




	delete[]dstbuf; dstFile.Close();
	return 0;
}

INT CGetGlyphOutline_VS2010Dlg::CreatePixelFont_TEST(CString dstFileName, UINT pixelFontRow, UINT pixelFontCol, CDC *pDC)
{
	UINT lineBytes, totalBytes;
	TCHAR cc[32];
	CFile dstFile;
	GLYPHMETRICS gm;
	MAT2 mat2;
	INT  len, xoffset, yoffset;

	dstFile.Open(dstFileName, CFile::modeCreate | CFile::modeWrite, NULL);

	lineBytes = (pixelFontCol + 7) / 8;
	totalBytes = lineBytes * pixelFontRow;

	UCHAR *dstbuf = new UCHAR[totalBytes];

	//c = *(TCHAR *)srcPtr;
	unsigned char chinText[5];
	unsigned char c1 = 0x81, c2 = 0x00, c3 = 0x00, c4 = 0x00;
	char* a = new char[30];
	memset(a, 0x00, 30);
	for (c1 = 0x00; c1 <= 0xFF; c1++)//ASCII
	{
		chinText[0] = c1;
		chinText[1] = c2;
		chinText[2] = c3;
		chinText[3] = c4;
		chinText[4] = 0;
		CFont font;
		if (c1 >= ' '&&c1 <= '~')
		{
			if (c1 == 'A')
			{
				VERIFY(font.CreateFont(
					//m_logFont.lfHeight, m_logFont.lfWidth, 
					-30, -12,
					m_logFont.lfEscapement, m_logFont.lfOrientation,
					m_logFont.lfWeight, m_logFont.lfItalic,
					m_logFont.lfUnderline, m_logFont.lfStrikeOut,
					m_logFont.lfCharSet, m_logFont.lfOutPrecision,
					m_logFont.lfClipPrecision, m_logFont.lfQuality,
					m_logFont.lfPitchAndFamily, m_logFont.lfFaceName)
				);
				pDC->SelectObject(&font);
			}
			else if ((c1 >= ' '&&c1 <= '\'') || (c1 >= '*'&&c1 <= '/') || (c1 == '@'))
			{
				VERIFY(font.CreateFont(
					//m_logFont.lfHeight, m_logFont.lfWidth, 
					-28, -12,
					m_logFont.lfEscapement, m_logFont.lfOrientation,
					m_logFont.lfWeight, m_logFont.lfItalic,
					m_logFont.lfUnderline, m_logFont.lfStrikeOut,
					m_logFont.lfCharSet, m_logFont.lfOutPrecision,
					m_logFont.lfClipPrecision, m_logFont.lfQuality,
					m_logFont.lfPitchAndFamily, m_logFont.lfFaceName)
				);
				pDC->SelectObject(&font);
			}
			else if (c1 >= '('&&c1 <= ')')
			{
				VERIFY(font.CreateFont(
					//m_logFont.lfHeight, m_logFont.lfWidth, 
					-27, -12,
					m_logFont.lfEscapement, m_logFont.lfOrientation,
					m_logFont.lfWeight, m_logFont.lfItalic,
					m_logFont.lfUnderline, m_logFont.lfStrikeOut,
					m_logFont.lfCharSet, m_logFont.lfOutPrecision,
					m_logFont.lfClipPrecision, m_logFont.lfQuality,
					m_logFont.lfPitchAndFamily, m_logFont.lfFaceName)
				);
				pDC->SelectObject(&font);
			}
			else
			{
				VERIFY(font.CreateFont(
					//m_logFont.lfHeight, m_logFont.lfWidth, 
					-30, -12,
					m_logFont.lfEscapement, m_logFont.lfOrientation,
					m_logFont.lfWeight, m_logFont.lfItalic,
					m_logFont.lfUnderline, m_logFont.lfStrikeOut,
					m_logFont.lfCharSet, m_logFont.lfOutPrecision,
					m_logFont.lfClipPrecision, m_logFont.lfQuality,
					m_logFont.lfPitchAndFamily, m_logFont.lfFaceName)
				);
				pDC->SelectObject(&font);
			}
		}
		else
		{
			VERIFY(font.CreateFont(
				m_logFont.lfHeight, m_logFont.lfWidth,
				m_logFont.lfEscapement, m_logFont.lfOrientation,
				m_logFont.lfWeight, m_logFont.lfItalic,
				m_logFont.lfUnderline, m_logFont.lfStrikeOut,
				m_logFont.lfCharSet, m_logFont.lfOutPrecision,
				m_logFont.lfClipPrecision, m_logFont.lfQuality,
				m_logFont.lfPitchAndFamily, m_logFont.lfFaceName)
			);
			pDC->SelectObject(&font);
		}

		//			CharToTchar((const char*)a,&chText);
		CharToTchar_CP(437, (const char*)chinText, 1, cc);
		TCHAR c = cc[0];

		memset(dstbuf, 0x00, totalBytes);
		memset(&mat2, 0, sizeof(mat2));
		mat2.eM11.value = 1;   mat2.eM12.value = 0;
		mat2.eM21.value = 0;   mat2.eM22.value = 1;
		len = ::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, 0, 0, &mat2);
		if (len == -1) {
			delete[]dstbuf; dstFile.Close();
			return -1;
		}

		if (len == 0) {
			dstFile.Write(dstbuf, totalBytes);
		}
		else {
			char *buf = new char[len];
			memset(buf, 0x00, len);
			::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, len, buf, &mat2);
			UCHAR *pData = (UCHAR *)buf;
			UINT cnt = ((gm.gmBlackBoxX + 31) >> 5) << 2;
			OUTLINETEXTMETRIC otm;
			memset(&otm, 0, sizeof(otm));
			otm.otmSize = sizeof(otm);
			pDC->GetOutlineTextMetrics(sizeof(otm), &otm);
			xoffset = gm.gmptGlyphOrigin.x;     //x的偏移量   
			//y的偏移量     字的顶部   -   y方向原点   都是相对于baseline   
			yoffset = otm.otmAscent - gm.gmptGlyphOrigin.y;
			//				yoffset   =  pixelFontRow-gm.gmBlackBoxY;//下标
			if (xoffset < 0)xoffset = 0;
			if (yoffset < 0)yoffset = 0;
#if	Function_Type ==1
			if (c1 >= '0'&&c1 <= 'Z')
				ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset - 3);
			else if ((c1 >= ' '&&c1 <= '\'') || (c1 >= '*'&&c1 <= '/') || (c1 == '@'))
				ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset - 2);
			else if (c1 >= '('&&c1 <= ')')
				ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset - 1);
			else
				ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
#else
			ProcessBuff_2(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
			//				ProcessBuff_2(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, 0, 0);
#endif
#if 0
			UINT i, j, k;
			UCHAR *ptr = dstbuf;
			CBrush brush;
			CRect rect(0, 0, 100, 100);
			brush.CreateSolidBrush(RGB(255, 255, 255));
			pDC->FillRect(&rect, &brush);


			for (j = 0; j < pixelFontRow; j++) {
				for (i = 0; i < lineBytes; i++) {
					for (k = 0; k < 8; k++) {
						if ((*ptr)   &   (0x80 >> k))
							pDC->SetPixel(i * 8 + k, j, RGB(255, 0, 0));
					}
					ptr++;
				}
			}
			brush.DeleteObject();
#endif
			//				for(int en=0;en<totalBytes;en++)//加密
			//					dstbuf[en]-=15;
			dstFile.Write(dstbuf, totalBytes);
			delete[]buf;
		}
		if (c1 == 0xff)
			break;
	}

	delete[]dstbuf; dstFile.Close();
	return 0;
}
unsigned short GBK2UNI(unsigned short usGBK)
{
	unsigned char  szEUC[2] = { usGBK >> 8, usGBK & 0xFF };
	unsigned short usUNI;
	MultiByteToWideChar(
		936,
		0,
		(LPCSTR)szEUC,
		2,
		(LPWSTR)&usUNI,
		1
	);
	return usUNI;
}
#define be_16(x) ((x >> 8) | (x<<8))
INT CGetGlyphOutline_VS2010Dlg::CreatePixelFont_OpenFile(PUCHAR srcData, DWORD srcLen, CString dstFileName, UINT pixelFontRow, UINT pixelFontCol, CDC *pDC)
{
	PUCHAR srcPtr = srcData, end_ptr;
	UCHAR encode;  //0:ansi 1:unicode
	UINT lineBytes, totalBytes;
	TCHAR c;
	CFile dstFile;
	GLYPHMETRICS gm;
	MAT2 mat2;
	INT  len, xoffset, yoffset;
	unsigned short x;

	dstFile.Open(dstFileName, CFile::modeCreate | CFile::modeWrite, NULL);

	lineBytes = (pixelFontCol + 7) / 8;
	totalBytes = lineBytes * pixelFontRow;

	UCHAR *dstbuf = new UCHAR[totalBytes];

	if (*srcPtr == 0xFF && *(srcPtr + 1) == 0xFE) {
		srcPtr += 2; srcLen -= 2;
		encode = 1;
	}
	else {
		encode = 0;
	}
	end_ptr = srcPtr + srcLen;

	//c = *(TCHAR *)srcPtr;
	while (srcPtr < end_ptr) {
		if (encode == 0) {
			//ansi encode
			if (*srcPtr < 0xA0) {
				c = *(UCHAR *)srcPtr; srcPtr++;
			}
			else {
				x = *(TCHAR *)srcPtr;
				c = GBK2UNI(be_16(x)); srcPtr += 2;
			}
		}
		else if (encode == 1) {
			//unicode encode
			c = *(TCHAR *)srcPtr; srcPtr += 2;
		}
		memset(dstbuf, 0x00, totalBytes);
		memset(&mat2, 0, sizeof(mat2));
		mat2.eM11.value = 1;   mat2.eM12.value = 0;
		mat2.eM21.value = 0;   mat2.eM22.value = 1;
		len = ::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, 0, 0, &mat2);
		if (len == -1) {
			delete[]dstbuf; dstFile.Close();
			return -1;
		}

		if (len == 0) {
			dstFile.Write(dstbuf, totalBytes);
		}
		else {
			char *buf = new char[len];
			memset(buf, 0x00, len);
			::GetGlyphOutline(pDC->m_hDC, c, GGO_BITMAP, &gm, len, buf, &mat2);
			UCHAR *pData = (UCHAR *)buf;
			UINT cnt = ((gm.gmBlackBoxX + 31) >> 5) << 2;
			OUTLINETEXTMETRIC otm;
			memset(&otm, 0, sizeof(otm));
			otm.otmSize = sizeof(otm);
			pDC->GetOutlineTextMetrics(sizeof(otm), &otm);
			xoffset = gm.gmptGlyphOrigin.x;     //x的偏移量   
			//y的偏移量     字的顶部   -   y方向原点   都是相对于baseline   
			yoffset = otm.otmAscent - gm.gmptGlyphOrigin.y;
			if (xoffset < 0)xoffset = 0;
			if (yoffset < 0)yoffset = 0;
#if	Function_Type ==1
			ProcessBuff(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
#else
			ProcessBuff_2(dstbuf, pixelFontRow, lineBytes, (PUCHAR)buf, gm.gmBlackBoxY, cnt, xoffset, yoffset);
#endif
#if 0
			UINT i, j, k;
			UCHAR *ptr = dstbuf;
			CBrush brush;
			CRect rect(0, 0, 100, 100);
			brush.CreateSolidBrush(RGB(255, 255, 255));
			pDC->FillRect(&rect, &brush);


			for (j = 0; j < pixelFontRow; j++) {
				for (i = 0; i < lineBytes; i++) {
					for (k = 0; k < 8; k++) {
						if ((*ptr)   &   (0x80 >> k))
							pDC->SetPixel(i * 8 + k, j, RGB(255, 0, 0));
					}
					ptr++;
				}
			}
			brush.DeleteObject();
#endif

			dstFile.Write(dstbuf, totalBytes);
			delete[]buf;
		}
	}
	delete[]dstbuf; dstFile.Close();
	return 0;
}

void CGetGlyphOutline_VS2010Dlg::OnBnClickedButton1()///ASCII
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_RowPixel == 0 || m_ColPixel == 0) {
		MessageBox(TEXT("参数不正确！！！"));
		return;
	}
	m_dstBinaryFileName.Format(AppPath() + "DSHZ%d%d.HZ", m_ColPixel, m_RowPixel);

	CDC *pDC = GetDC();
	CFont font;

	VERIFY(font.CreateFont(
		m_logFont.lfHeight, m_logFont.lfWidth,
		m_logFont.lfEscapement, m_logFont.lfOrientation,
		m_logFont.lfWeight, m_logFont.lfItalic,
		m_logFont.lfUnderline, m_logFont.lfStrikeOut,
		m_logFont.lfCharSet, m_logFont.lfOutPrecision,
		m_logFont.lfClipPrecision, m_logFont.lfQuality,
		m_logFont.lfPitchAndFamily, m_logFont.lfFaceName)
	);
	pDC->SelectObject(&font);
	int res = CreatePixelFont_ASCII(m_dstBinaryFileName, m_RowPixel, m_ColPixel, pDC);
	if (res < 0) {
		MessageBox(TEXT("Create PixelFont data error"));
		return;
	}
	//	convert_file.WriteDataFile(m_dstBinaryFileName, m_dstFileName);
	MessageBox(TEXT("OK"));
	ReleaseDC(pDC);
}


void CGetGlyphOutline_VS2010Dlg::OnBnClickedButton2()////////GB2312
{
	UpdateData(TRUE);
	if (m_RowPixel == 0 || m_ColPixel == 0)
	{
		MessageBox(TEXT("参数不正确！！！"));
		return;
	}
	m_dstBinaryFileName.Format(AppPath() + "DSHZ%d%d.HZ", m_ColPixel, m_RowPixel);

	CDC *pDC = GetDC();
	CFont font;

	VERIFY(font.CreateFont(
		m_logFont.lfHeight, m_logFont.lfWidth,
		m_logFont.lfEscapement, m_logFont.lfOrientation,
		m_logFont.lfWeight, m_logFont.lfItalic,
		m_logFont.lfUnderline, m_logFont.lfStrikeOut,
		m_logFont.lfCharSet, m_logFont.lfOutPrecision,
		m_logFont.lfClipPrecision, m_logFont.lfQuality,
		m_logFont.lfPitchAndFamily, m_logFont.lfFaceName)
	);
	pDC->SelectObject(&font);
	int res = CreatePixelFont_GB2312(m_dstBinaryFileName, m_RowPixel, m_ColPixel, pDC);
	if (res < 0) {
		MessageBox(TEXT("Create PixelFont data error"));
		return;
	}
	//	convert_file.WriteDataFile(m_dstBinaryFileName, m_dstFileName);
	MessageBox(TEXT("OK"));
	ReleaseDC(pDC);
}


void CGetGlyphOutline_VS2010Dlg::OnBnClickedButton3()////GB18030
{
	UpdateData(TRUE);

	if (m_RowPixel == 0 || m_ColPixel == 0) {
		MessageBox(TEXT("参数不正确！！！"));
		return;
	}
	DWORD byteNum;
	PUCHAR preadBuf = NULL;
	if (m_OpenFileName != "")
	{
		CFile fin;
		fin.Open(m_OpenFileName, CFile::modeRead, NULL);
		byteNum = fin.GetLength();
		preadBuf = (PUCHAR)malloc(byteNum * sizeof(UCHAR));
		if (preadBuf == NULL) {
			fin.Close();
			return;
		}
		fin.Read(preadBuf, byteNum);
		fin.Close();
	}

	m_dstBinaryFileName.Format(AppPath() + "DSHZ%d%d.HZ", m_ColPixel, m_RowPixel);
	CDC *pDC = GetDC();
	CFont font;

	VERIFY(font.CreateFont(
		m_logFont.lfHeight, m_logFont.lfWidth,
		m_logFont.lfEscapement, m_logFont.lfOrientation,
		m_logFont.lfWeight, m_logFont.lfItalic,
		m_logFont.lfUnderline, m_logFont.lfStrikeOut,
		m_logFont.lfCharSet, m_logFont.lfOutPrecision,
		m_logFont.lfClipPrecision, m_logFont.lfQuality,
		m_logFont.lfPitchAndFamily, m_logFont.lfFaceName)
	);
	pDC->SelectObject(&font);
	int res;
	if (preadBuf == NULL)
		res = CreatePixelFont_GB18030(m_dstBinaryFileName, m_RowPixel, m_ColPixel, pDC);
	else
		res = CreatePixelFont_OpenFile(preadBuf, byteNum, m_dstBinaryFileName, m_RowPixel, m_ColPixel, pDC);

	if (res < 0) {
		MessageBox(TEXT("Create PixelFont data error"));
		return;
	}
	//	convert_file.WriteDataFile(m_dstBinaryFileName, m_dstFileName);
	MessageBox(TEXT("OK"));
	ReleaseDC(pDC);
}


void CGetGlyphOutline_VS2010Dlg::OnBnClickedButton4()////TEST
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_RowPixel == 0 || m_ColPixel == 0) {
		MessageBox(TEXT("参数不正确！！！"));
		return;
	}
	m_dstBinaryFileName.Format(AppPath() + "DSHZ%d%d.HZ", m_ColPixel, m_RowPixel);

	CDC *pDC = GetDC();
	CFont font;

	VERIFY(font.CreateFont(
		m_logFont.lfHeight, m_logFont.lfWidth,
		m_logFont.lfEscapement, m_logFont.lfOrientation,
		m_logFont.lfWeight, m_logFont.lfItalic,
		m_logFont.lfUnderline, m_logFont.lfStrikeOut,
		m_logFont.lfCharSet, m_logFont.lfOutPrecision,
		m_logFont.lfClipPrecision, m_logFont.lfQuality,
		m_logFont.lfPitchAndFamily, m_logFont.lfFaceName)
	);
	pDC->SelectObject(&font);
	int res = CreatePixelFont_TEST(m_dstBinaryFileName, m_RowPixel, m_ColPixel, pDC);
	if (res < 0) {
		MessageBox(TEXT("Create PixelFont data error"));
		return;
	}
	//	convert_file.WriteDataFile(m_dstBinaryFileName, m_dstFileName);
	MessageBox(TEXT("OK"));
	ReleaseDC(pDC);
}



void CGetGlyphOutline_VS2010Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	m_OpenFileName = SelFileName();
	UpdateData(FALSE);
}


void CGetGlyphOutline_VS2010Dlg::OnCbnSelchangeFontnames()
{
	Update4NewFontName();
	FontChanged();
}


void CGetGlyphOutline_VS2010Dlg::OnCbnSelchangeFontsize()
{
	FontChanged();
}

void CGetGlyphOutline_VS2010Dlg::OnCbnEditupdateFontsize()
{
	FontChanged();
}

void CGetGlyphOutline_VS2010Dlg::OnCbnSelchangeScript()
{
	FontChanged();
}

void CGetGlyphOutline_VS2010Dlg::OnBnClickedItalicCheck()
{
	FontChanged();
}


void CGetGlyphOutline_VS2010Dlg::OnBnClickedBoldCheck()
{
	FontChanged();
}


void CGetGlyphOutline_VS2010Dlg::OnBnClickedUnderlineCheck()
{
	FontChanged();
}


void CGetGlyphOutline_VS2010Dlg::FontChanged(void)
{
	//获得新的字体
	UpdateData(TRUE);
	BOOL it = (m_Italic.GetCheck() == 1);
	BOOL bl = (m_bold.GetCheck() == 1);
	BOOL un = (m_Underline.GetCheck() == 1);
	CString str;
	const CWizFontsEnumerator::Font* font = m_FontNamesCombo.GetCurrentFont(m_Fonts);
	if (NULL == font)
	{
		ASSERT(0);
		return;
	}
	str = font->Name();
	/*	char *getchar=new char[20];
		char *getchar2=new char[20];
		::GetWindowTextW(m_SizeCombo,(LPWSTR)getchar,20);
		TCharToChar((const TCHAR*)getchar,getchar2);
		int pp_size = atoi(getchar2);*/
	int pp_size = m_SizeCombo.GetCurrentSize();
	if (pp_size < 0)
	{
		ASSERT(0);
		return;
	}
	//通知静态文本框，按新的字体显示文字
	m_SampleBox.SetFont(str, pp_size, it, bl, un);
}

void CGetGlyphOutline_VS2010Dlg::Update4NewFontName(void)
{
	//获得当前选择字体
	const CWizFontsEnumerator::Font* font = m_FontNamesCombo.GetCurrentFont(m_Fonts);
	if (NULL == font)
	{
		ASSERT(0);
		return;
	}

	//初始化语言和大小列表框
	m_ScriptCombo.Initialize(font);
	m_SizeCombo.Initialize(font);

	int be = 0, ie = 0, ue = 0, bc = 0, ic = 0, uc = 0;

	if (!font->MustBeRegular())
	{
		if (font->CanBeBold())
		{
			if (font->MustBeBold())
				bc = 1;
			else
				be = 1;
		}
		if (font->CanBeItalics())
		{
			if (font->MustBeItalics())
				ic = 1;
			else
				ie = 1;
		}
		if (font->CanBeUnderline())
		{
			if (font->MustBeUnderline())
				uc = 1;
			else
				ue = 1;
		}

	}

	m_bold.EnableWindow(be);
	m_Italic.EnableWindow(ie);
	m_Underline.EnableWindow(ue);

	m_bold.SetCheck(bc);
	m_Italic.SetCheck(ic);
	m_Underline.SetCheck(uc);
}




void CGetGlyphOutline_VS2010Dlg::OnEnChangeEdit1()//高点数
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CGetGlyphOutline_VS2010Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CGetGlyphOutline_VS2010Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
