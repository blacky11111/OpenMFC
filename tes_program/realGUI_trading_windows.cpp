#include <afxwin.h>
#include <afxcmn.h>

// 1. Definisikan ID Kontrol secara Manual
#define ID_BTN_BUY   1001
#define ID_BTN_SELL  1002
#define ID_LBL_WATCH 1003
#define ID_LBL_CHART 1004

// 2. Kelas Dialog Utama
class CTradingDlg : public CDialog {
public:
    CTradingDlg() : CDialog() {
        // Membuat template dialog di memori (Tanpa file .rc)
        m_pTemplate = (DLGTEMPLATE*)GlobalAlloc(GPTR, sizeof(DLGTEMPLATE) + 100);
        m_pTemplate->style = WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | DS_CENTER;
        m_pTemplate->dwExtendedStyle = 0;
        m_pTemplate->cdit = 0;  // Kita akan menambah kontrol secara dinamis
        m_pTemplate->x = 0;  m_pTemplate->y = 0;
        m_pTemplate->cx = 400; m_pTemplate->cy = 250;
    }

    ~CTradingDlg() { GlobalFree(m_pTemplate); }

    BOOL Create() { return CDialog::CreateIndirect(m_pTemplate); }

protected:
    CFont m_fontTitle;
    CStatic m_lblWatch, m_lblChart;
    CButton m_btnBuy, m_btnSell;

    virtual BOOL OnInitDialog() {
        CDialog::OnInitDialog();
        SetWindowText(L"Pro Financial Trader - Live Market");

        // Membuat Font Profesional
        m_fontTitle.CreatePointFont(100, L"Segoe UI");

        // 3. Membuat Kontrol GUI secara Dinamis (Programmatic)
        
        // Panel Watchlist (Kiri)
        m_lblWatch.Create(L"WATCHLIST\n\nBTC/USD: 64,210\nETH/USD: 3,450\nAAPL: 189.20", 
            WS_CHILD | WS_VISIBLE | SS_SUNKEN, CRect(10, 10, 120, 200), this, ID_LBL_WATCH);
        
        // Panel Chart (Kanan)
        m_lblChart.Create(L"--- REAL-TIME CANDLESTICK CHART ---\n\n[Grafik Simulasi Aktif]", 
            WS_CHILD | WS_VISIBLE | SS_CENTER | SS_SUNKEN, CRect(130, 10, 385, 150), this, ID_LBL_CHART);

        // Tombol Trading
        m_btnBuy.Create(L"BUY / LONG", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
            CRect(130, 165, 250, 200), this, ID_BTN_BUY);
        
        m_btnSell.Create(L"SELL / SHORT", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
            CRect(265, 165, 385, 200), this, ID_BTN_SELL);

        // Terapkan Font
        m_lblWatch.SetFont(&m_fontTitle);
        m_btnBuy.SetFont(&m_fontTitle);
        m_btnSell.SetFont(&m_fontTitle);

        return TRUE;
    }

    // Response saat tombol diklik
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) {
        if (LOWORD(wParam) == ID_BTN_BUY) MessageBox(L"Executing BUY Order...", L"Trade Executed");
        if (LOWORD(wParam) == ID_BTN_SELL) MessageBox(L"Executing SELL Order...", L"Trade Executed");
        return CDialog::OnCommand(wParam, lParam);
    }

private:
    DLGTEMPLATE* m_pTemplate;
};

// 4. Kelas Aplikasi Utama (theApp)
class CTradingApp : public CWinApp {
public:
    virtual BOOL InitInstance() {
        CWinApp::InitInstance();
        CTradingDlg dlg;
        m_pMainWnd = &dlg;
        dlg.DoModal(); // Menampilkan GUI
        return FALSE;  // Selesai
    }
};

// Instansi global tunggal
CTradingApp theApp;
//~ IMPLEMENT_APP(CTradingApp)
