#include <afxwin.h> // Main MFC header

// 1. Define the Window/Dialog class
class CSimpleWindow : public CFrameWnd {
public:
    CSimpleWindow() {
        // Create the window frame
        Create(NULL, _T("Simple MFC GUI 2026"));
    }

    // Define a button ID
    static const int ID_MYBUTTON = 1001;

protected:
    // This function runs when the window is created
    int OnCreate(LPCREATESTRUCT lpCreateStruct) {
        if (CFrameWnd::OnCreate(lpCreateStruct) == -1) return -1;

        // Create a button manually
        m_button.Create(_T("Click Me"), WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            CRect(50, 50, 200, 100), this, ID_MYBUTTON);
        return 0;
    }

    // Handler for the button click
    void OnButtonClicked() {
        MessageBox(_T("Button clicked! Program running on Windows 2026."), _T("MFC Alert"));
    }

    CButton m_button;

    // Link events to functions
    DECLARE_MESSAGE_MAP()
};

// 2. Map the button click event to the handler function
BEGIN_MESSAGE_MAP(CSimpleWindow, CFrameWnd)
    ON_WM_CREATE()
    ON_BN_CLICKED(CSimpleWindow::ID_MYBUTTON, OnButtonClicked)
END_MESSAGE_MAP()

// 3. Define the Application class
class CSimpleApp : public CWinApp {
public:
    virtual BOOL InitInstance() {
        m_pMainWnd = new CSimpleWindow();
        m_pMainWnd->ShowWindow(SW_SHOW);
        m_pMainWnd->UpdateWindow();
        return TRUE;
    }
};

// 4. Instantiate the application
CSimpleApp theApp;
//~ IMPLEMENT_APP(CSimpleApp)
