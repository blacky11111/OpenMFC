#include <wx/wxprec.h> 
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "afxwin.h"
#include <wx/app.h> 

// ============================================================================
// 2. CString CLASS - Ambiguity-Free Version
// ============================================================================
CStringBase::CStringBase() : wxString() {}
CStringBase::CStringBase(const wxString& s) : wxString(s) {}

CStringBase CStringBase::FormatS(const wxString& f, int i) { return CStringBase(wxString::Format(f, i)); }
CStringBase CStringBase::FormatS(const wxString& f, const wxChar* s) { return CStringBase(wxString::Format(f, s)); }

template<typename T>
CStringBase CStringBase::Format(const wxString& f, T val) { return FormatS(f, val); }

CString::CString() : CStringBase() {}
CString::CString(const wxChar* s) : CStringBase(wxString(s)) {}
CString::CString(const wxString& s) : CStringBase(s) {}

void CString::Format(const wxChar* format, ...) {
	va_list argList;
	va_start(argList, format);
	this->PrintfV(format, argList);
	va_end(argList);
}
// Global helpers for Program 1
//~ inline double _tstof(const wxString& s) { return wxAtof(s); }
//~ inline int _ttoi(const wxString& s) { return wxAtoi(s); }

// ============================================================================
// 3. Dasar Geometri & Font
// ============================================================================

CRect::CRect() : wxRect() {}
CRect::CRect(int l, int t, int r, int b) : wxRect(l, t, r - l, b - t) {}
int CRect::Width() const { return width; }
int CRect::Height() const { return height; }



CPen::CPen(int style, int width, const wxColour& color) : wxPen(color, width, style) {}


//~ class CDC {
//~ public:
    //~ virtual ~CDC() {}
    //~ virtual void SelectObject(wxPen* pen) = 0;
    //~ virtual void MoveTo(int x, int y) = 0;
    //~ virtual void LineTo(int x, int y) = 0;
//~ };


CPaintDC::CPaintDC(wxWindow* win) : wxPaintDC(win) { m_x = 0; m_y = 0; }
void CPaintDC::SelectObject(wxPen* pen) { SetPen(*pen); }
void CPaintDC::MoveTo(int x, int y) { m_x = x; m_y = y; }
void CPaintDC::LineTo(int x, int y) { DrawLine(m_x, m_y, x, y); m_x = x; m_y = y; }


CFont::CFont() : wxFont() {}
BOOL CFont::CreatePointFont(int nPointSize, const wxString& lpszFaceName) {
	return wxFont::Create(nPointSize/10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, 
						  wxFONTWEIGHT_NORMAL, false, lpszFaceName);
}

// ============================================================================
// 4. Base Class CWnd
// ============================================================================
CWnd::CWnd() : m_pWnd(NULL) {}

// Scoped MessageBox so the main program finds it via inheritance
void CWnd::MessageBox(const wxString& msg, const wxString& title = wxT("MFC Alert")) {
	wxMessageBox(msg, title);
}


bool CEdit::Create(long s, const CRect& r, wxWindow* p, int id) {
	return wxTextCtrl::Create(p, id, wxEmptyString, r.GetPosition(), r.GetSize());
}
void CEdit::SetWindowText(const wxString& t) { SetValue(t); }
void CEdit::GetWindowText(wxString& t) { t = GetValue(); }
// ============================================================================
// 5. Kontrol GUI
// ============================================================================
CStatic::CStatic() { m_pWnd = this; }

// Signature Create harus cocok dengan pemanggilan di Main Program
bool CStatic::Create(const wchar_t* t, long s, const wxRect& r, wxWindow* p, int id) {
	m_label = wxString(t);
	// Casting p secara eksplisit ke wxWindow*
	bool success = wxWindow::Create(p, id, r.GetPosition(), r.GetSize(), wxST_NO_AUTORESIZE);
	
	if(success) {
		this->SetBackgroundStyle(wxBG_STYLE_CUSTOM);
		// Gunakan Connect untuk wxWidgets 2.8
		this->Connect(wxID_ANY, wxEVT_PAINT, 
			(wxObjectEventFunction)(wxEventFunction)(wxPaintEventFunction)&CStatic::OnPaintChart);
	}
	return success;
}

void CStatic::SetWindowText(const wxString& t) { 
	m_label = t;      // TAMBAHKAN INI: Update variabel agar OnPaintChart tahu teks barunya
	SetLabel(t); 
	
	// Paksa sistem menggambar ulang area ini dengan data m_label yang baru
	this->Refresh();
	this->Update();
}

// Simpan label untuk digambar manual
wxString CStatic::GetLabel() { return m_label; }

void CStatic::OnPaintChart(wxPaintEvent& event) {
	wxPaintDC dc(this);
	wxSize sz = GetClientSize();
	if (this->GetId() == 1003 || this->GetId() == 1004) {
        //Background Gelap (Khas terminal trading)
        dc.SetBrush(wxBrush(wxColour(10, 15, 20))); 
        dc.SetPen(*wxTRANSPARENT_PEN);
        dc.DrawRectangle(0, 0, sz.x, sz.y);

        //Gambar Grid Abu-abu
        dc.SetPen(wxPen(wxColour(40, 40, 40), 1, wxDOT));
        for(int i = 0; i < sz.y; i += 30) dc.DrawLine(0, i, sz.x, i);
        for(int i = 0; i < sz.x; i += 40) dc.DrawLine(i, 0, i, sz.y);
        
        dc.SetTextForeground(*wxCYAN);
        //Simulasi Grafik (Hanya untuk ID Chart 1004)
        if (this->GetId() == 1004) {
            dc.SetPen(wxPen(*wxGREEN, 2));
            int baseLine = sz.y - 50;
            
            // Garis Tren Naik
            dc.DrawLine(20, baseLine, 100, baseLine - 40);
            dc.DrawLine(100, baseLine - 40, 180, baseLine - 20);
            dc.DrawLine(180, baseLine - 20, 260, baseLine - 80);

            // Candlesticks Hijau
            dc.SetBrush(*wxGREEN_BRUSH);
            dc.DrawRectangle(90, baseLine - 55, 12, 30);
            dc.DrawRectangle(140, baseLine - 45, 12, 20);
            
            // Candlesticks Merah
            dc.SetBrush(*wxRED_BRUSH);
            dc.SetPen(*wxRED_PEN);
            dc.DrawRectangle(250, baseLine - 95, 12, 40);
        }
	}
	//Gambar Teks dari Main Program
	dc.SetFont(this->GetFont());
	dc.DrawText(m_label, 10, 10);
}

void CStatic::SetFont(CFont* pFont) { if(pFont) wxWindow::SetFont(*(static_cast<wxFont*>(pFont))); }



CButton::CButton() : wxButton() {}
BOOL CButton::Create(long style, const CRect& rect, wxWindow* parent, int id) {
	return wxButton::Create(parent, id, wxEmptyString, rect.GetPosition(), rect.GetSize());
}

void CButton::Create(const CString& text, long style, const CRect& rect, wxWindow* parent, int id) {
	wxButton::Create(parent, id, text, rect.GetPosition(), rect.GetSize());
}

void CButton::SetFont(CFont* pFont) { if(pFont) wxButton::SetFont(*(static_cast<wxFont*>(pFont))); }

template<typename T>
void CButton::Bind(wxEventType tag, void (T::*method)(wxCommandEvent&), T* handler) {
	handler->Connect(this->GetId(), tag, (wxObjectEventFunction)(wxEventFunction)
					static_cast<wxCommandEventFunction>(method));
}



CFrameWnd::CFrameWnd() : wxFrame(NULL, wxID_ANY, wxEmptyString) {
	m_pWnd = this; // Set pointer m_pWnd ke objek ini sendiri
}

void CFrameWnd::Create(void* dummy, const wxString& title) {
	SetTitle(title);
	SetSize(400, 300);
	// Simulasi WM_CREATE
	CREATESTRUCT cs = {0};
	OnCreate(&cs); 
}

// Override methods dari CWnd
void CFrameWnd::ShowWindow(int cmd) { Show(true); }
void CFrameWnd::UpdateWindow() { Refresh(); Update(); }
void CFrameWnd::SetWindowText(const wxString& t) { SetTitle(t); }
void CFrameWnd::GetClientRect(CRect* r) {
	wxSize s = GetClientSize();
	r->x = 0; r->y = 0; r->width = s.x; r->height = s.y;
}
void CFrameWnd::OnPaintInternal(wxPaintEvent& e) { OnPaint(); }

// Bridge untuk event handler MFC tanpa parameter
void CFrameWnd::OnButtonClicked_Internal(wxCommandEvent& event) { OnButtonClicked(); }

// ============================================================================
// 6. Dialog & App
// ============================================================================
CDialog::CDialog() : wxDialog(NULL, wxID_ANY, wxT("Dialog"), wxDefaultPosition, wxSize(400, 450)) { CommonInit(); }
CDialog::CDialog(int id) : wxDialog(NULL, wxID_ANY, wxT("Dialog"), wxDefaultPosition, wxSize(400, 450)) { CommonInit(); }

void CDialog::CommonInit() { 
	m_pWnd = this; 
	// Tambahkan koneksi event klik tombol ke handler internal:
	this->Connect(wxID_ANY, wxEVT_COMMAND_BUTTON_CLICKED, 
				  (wxObjectEventFunction)(wxEventFunction)(wxCommandEventFunction)&CDialog::OnCommandInternal);
}

// Handler internal yang meneruskan ke OnCommand virtual
void CDialog::OnCommandInternal(wxCommandEvent& event) {
	// Panggil fungsi OnCommand virtual di CTradingDlg
	OnCommand(event.GetId(), 0); // MFC style call
	event.Skip();
}

void CDialog::OnCalculate_Internal(wxCommandEvent& e) { 
	OnCalculate(); 
	wxSafeYield(); 
	this->Refresh();
	this->Update();
	e.Skip(); 
}

void CDialog::SetWindowText(const wxString& t) { this->SetTitle(t); }
int CDialog::DoModal() { this->OnInitDialog(); return ShowModal(); }
    

CWinApp::CWinApp() : m_nCmdShow(1), m_pMainWnd(NULL) {}

// Kelas ini harus didefinisikan secara LENGKAP sebelum makro dipanggil
class UniversalApp : public CWinApp {
public:
    UniversalApp() {}
    virtual bool OnInit() { return true; }
};

// Pada wxWidgets 2.8, gunakan IMPLEMENT_APP_NO_MAIN tanpa awalan 'wx'
// Pastikan nama kelas sesuai dengan definisi di atas
IMPLEMENT_APP_NO_MAIN(UniversalApp)

// BUAT FUNGSI MAIN MANUAL AGAR TERDETEKSI 'nm'
extern "C" int main(int argc, char **argv) {
    return wxEntry(argc, argv);
}
