#ifndef AFXWIN_H
#define AFXWIN_H

#include <wx/wx.h>
#include <wx/toplevel.h>
#include <wx/dcclient.h>
#include <cmath>

// ============================================================================
// 1. Define section
// ============================================================================

#ifndef TRUE
    #define TRUE 1
    #define FALSE 0
#endif
#define RGB(r,g,b) wxColour(r,g,b)
#define afx_msg
#define _T(x) wxT(x)
#define SW_SHOW 1
typedef bool BOOL; 
typedef long WPARAM;
typedef long LPARAM;

struct CREATESTRUCT { void* lpCreateParams; int cx, cy, x, y; long style; };
typedef CREATESTRUCT* LPCREATESTRUCT;
// Flags MFC
#define WS_CHILD 0
#define WS_VISIBLE 0
#define WS_BORDER 0
#define BS_PUSHBUTTON 0
#define PS_DOT wxDOT
#define PS_SOLID wxSOLID
#define SS_SUNKEN 0
#define SS_CENTER 0
#define DS_CENTER 0
#define WS_POPUP 0
#define WS_CAPTION 0
#define WS_SYSMENU 0

#define DECLARE_MESSAGE_MAP() DECLARE_EVENT_TABLE()
#define BEGIN_MESSAGE_MAP(theClass, baseClass) typedef theClass theClassTypedef;BEGIN_EVENT_TABLE(theClass, baseClass)
#define END_MESSAGE_MAP() END_EVENT_TABLE()
#define ON_WM_CREATE() 
#define ON_BN_CLICKED(id, func) EVT_BUTTON(id, theClassTypedef::func##_Internal)


// ============================================================================
// 2. CString CLASS - Ambiguity-Free Version
// ============================================================================
class CStringBase : public wxString {
public:
    CStringBase();
    CStringBase(const wxString& s);

    static CStringBase FormatS(const wxString& f, int i) ;
    static CStringBase FormatS(const wxString& f, const wxChar* s) ;

    template<typename T>
    static CStringBase Format(const wxString& f, T val) ;
};

class CString : public CStringBase {
public:
    CString();
    CString(const wxChar* s);
    CString(const wxString& s);

    void Format(const wxChar* format, ...);
};
// Global helpers for Program 1
inline double _tstof(const wxString& s) { return wxAtof(s); }
inline int _ttoi(const wxString& s) { return wxAtoi(s); }

// ============================================================================
// 3. Dasar Geometri & Font
// ============================================================================
class CRect : public wxRect {
public:
    CRect();
    CRect(int l, int t, int r, int b);
    int Width() const ;
    int Height() const ;
};

class CPen : public wxPen {
public:
    CPen(int style, int width, const wxColour& color);
};

class CDC {
public:
    virtual ~CDC() {}
    virtual void SelectObject(wxPen* pen) = 0;
    virtual void MoveTo(int x, int y) = 0;
    virtual void LineTo(int x, int y) = 0;
};

class CPaintDC : public wxPaintDC, public CDC {
public:
    CPaintDC(wxWindow* win);
    void SelectObject(wxPen* pen);
    void MoveTo(int x, int y);
    void LineTo(int x, int y);
private:
    int m_x, m_y;
};

class CFont : public wxFont {
public:
    CFont();
    BOOL CreatePointFont(int nPointSize, const wxString& lpszFaceName);
};
// ============================================================================
// 4. Base Class CWnd
// ============================================================================
class CWnd {
public:
    wxWindow* m_pWnd;
    CWnd();
    virtual void ShowWindow(int cmd) { if(m_pWnd) m_pWnd->Show(true); }
    virtual void UpdateWindow() { if(m_pWnd) m_pWnd->Update(); }
    
    // Scoped MessageBox so the main program finds it via inheritance
    void MessageBox(const wxString& msg, const wxString& title);
    virtual int OnCreate(LPCREATESTRUCT lp) { return 0; }
};

class CEdit : public wxTextCtrl {
public:
    bool Create(long s, const CRect& r, wxWindow* p, int id);
    void SetWindowText(const wxString& t);
    void GetWindowText(wxString& t);
};
// ============================================================================
// 5. Kontrol GUI
// ============================================================================
class CStatic : public wxWindow, public CWnd {
    wxString m_label;
public:
    CStatic();
    
    // Signature Create harus cocok dengan pemanggilan di Main Program
    bool Create(const wchar_t* t, long s, const wxRect& r, wxWindow* p, int id);

	void SetWindowText(const wxString& t);

    // Simpan label untuk digambar manual
    wxString GetLabel();

    void OnPaintChart(wxPaintEvent& event);

    void SetFont(CFont* pFont);
};

class CButton : public wxButton, public CWnd {
public:
    CButton();
    BOOL Create(long style, const CRect& rect, wxWindow* parent, int id);
    
    void Create(const CString& text, long style, const CRect& rect, wxWindow* parent, int id);
    // Tambahkan destructor virtual untuk memastikan pembersihan bersih
    virtual ~CButton() {
        // Jangan biarkan wxWidgets mencoba menghapus pointer ini lagi
    }
    
    void SetFont(CFont* pFont);
    
    template<typename T>
    void Bind(wxEventType tag, void (T::*method)(wxCommandEvent&), T* handler) ;
};

class CFrameWnd : public wxFrame, public CWnd {
public:
    CFrameWnd();

    void Create(void* dummy, const wxString& title);

    virtual int OnCreate(LPCREATESTRUCT lp) { return 0; }
    
    // Override methods dari CWnd
    void ShowWindow(int cmd);
    void UpdateWindow();
    void SetWindowText(const wxString& t);
    void GetClientRect(CRect* r);
    void OnPaintInternal(wxPaintEvent& e);

    // Bridge untuk event handler MFC tanpa parameter
    void OnButtonClicked_Internal(wxCommandEvent& event);
    virtual void OnButtonClicked() {} 
    virtual void OnPaint() {}
};
// ============================================================================
// 6. Dialog & App
// ============================================================================
class CDialog : public wxDialog, public CWnd {
public:
    CDialog();
    CDialog(int id);
    
    void CommonInit();
    
    // Handler internal yang meneruskan ke OnCommand virtual
    void OnCommandInternal(wxCommandEvent& event);
    
    void OnCalculate_Internal(wxCommandEvent& e);
    // Fungsi virtual OnCommand yang di-override di program utama
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam) { return TRUE; }
    virtual BOOL CreateIndirect(void* lpTemplate) { return TRUE; }
    virtual BOOL OnInitDialog() { return TRUE; }
    
    void SetWindowText(const wxString& t);
    int DoModal();
    
    virtual void OnCalculate() {}
};

class CWinApp : public wxApp {
public:
    int m_nCmdShow;
    CWnd* m_pMainWnd; 
    CWinApp();
    virtual bool OnInit() { return (bool)InitInstance(); }
    virtual bool InitInstance() { return true; }
};

#define ON_WM_PAINT() EVT_PAINT(CFrameWnd::OnPaintInternal)

inline wxApp* GetTheApp() { 
    return static_cast<wxApp*>(wxApp::GetInstance()); 
}

// Gunakan macro yang tidak merusak deklarasi di main.cpp
// Kita gunakan wxGetApp() yang merupakan standar wxWidgets
#define AfxGetApp() GetTheApp()

#endif
