#include <afxwin.h> // Core MFC components
#include <cmath>    // For sin()

// 1. The Main Window Class
class CSineWindow : public CFrameWnd {
public:
    CSineWindow() {
        Create(NULL, _T("MFC Sine Wave Demo"));
    }

protected:
    // Message Map handles drawing events
    afx_msg void OnPaint() {
        CPaintDC dc(this); // Device context for painting
        CRect rect;
        GetClientRect(&rect);

        int width = rect.Width();
        int height = rect.Height();
        int midY = height / 2;

        // Draw horizontal center line
        CPen axisPen(PS_DOT, 1, RGB(128, 128, 128));
        dc.SelectObject(&axisPen);
        dc.MoveTo(0, midY);
        dc.LineTo(width, midY);

        // Draw the Sine Wave
        CPen wavePen(PS_SOLID, 2, RGB(0, 0, 255)); // Blue wave
        dc.SelectObject(&wavePen);

        double amplitude = height * 0.4; // Wave height is 40% of window
        double frequency = 2.0 * 3.14159 / width; // One full cycle across width

        dc.MoveTo(0, midY);
        for (int x = 0; x < width; x++) {
            // y = A * sin(B * x)
            int y = midY - static_cast<int>(amplitude * sin(frequency * x * 2)); // 2 cycles
            dc.LineTo(x, y);
        }
    }

    DECLARE_MESSAGE_MAP()
};

// 2. Define the message map for the window
BEGIN_MESSAGE_MAP(CSineWindow, CFrameWnd)
    ON_WM_PAINT()
END_MESSAGE_MAP()

// 3. The Application Class
class CSineApp : public CWinApp {
public:
    virtual BOOL InitInstance() {
        m_pMainWnd = new CSineWindow();
        m_pMainWnd->ShowWindow(m_nCmdShow);
        m_pMainWnd->UpdateWindow();
        return TRUE;
    }
};

// 4. Start the Application
CSineApp theApp;
//~ IMPLEMENT_APP(CSineApp)
