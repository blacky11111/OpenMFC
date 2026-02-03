#include <afxwin.h>      // MFC core and standard components
#include <afxext.h>      // MFC extensions
#include <cmath>         // For pow() function
#include <string>

// 1. Define the UI Resource IDs
#define IDC_EDIT_LOAN    101
#define IDC_EDIT_RATE    102
#define IDC_EDIT_TERM    103
#define IDC_BTN_CALC     104
#define IDC_STATIC_RES   105

// 2. The Dialog Class
class CFinancialDlg : public CDialog {
public:
    CFinancialDlg() : CDialog(IDD_BLANK) {}

    enum { IDD_BLANK = 0 }; // Required for minimal setup

protected:
    CEdit m_editLoan, m_editRate, m_editTerm;
    CStatic m_staticResult;

    virtual BOOL OnInitDialog() {
        CDialog::OnInitDialog();
        SetWindowText(_T("MFC Loan Calculator 2026"));

        // Programmatically create basic UI elements
        m_editLoan.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(20, 20, 150, 45), this, IDC_EDIT_LOAN);
        m_editLoan.SetWindowText(_T("10000")); // Default Principal

        m_editRate.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(20, 60, 150, 85), this, IDC_EDIT_RATE);
        m_editRate.SetWindowText(_T("5.0"));   // Default Annual Interest %

        m_editTerm.Create(WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(20, 100, 150, 125), this, IDC_EDIT_TERM);
        m_editTerm.SetWindowText(_T("36"));    // Default Months

        CButton* btn = new CButton();
        btn->Create(_T("Calculate"), WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, CRect(20, 140, 150, 175), this, IDC_BTN_CALC);

        m_staticResult.Create(_T("Result: $0.00"), WS_CHILD | WS_VISIBLE, CRect(20, 190, 250, 215), this, IDC_STATIC_RES);

        return TRUE;
    }

    // 3. The Financial Calculation Logic
    void OnCalculate() {
        CString strLoan, strRate, strTerm;
        m_editLoan.GetWindowText(strLoan);
        m_editRate.GetWindowText(strRate);
        m_editTerm.GetWindowText(strTerm);

        double P = _tstof(strLoan);             // Principal
        double annualRate = _tstof(strRate);    // Annual %
        int n = _ttoi(strTerm);                // Months

        if (P > 0 && annualRate > 0 && n > 0) {
            double r = (annualRate / 100) / 12; // Monthly rate
            double M = P * (r * pow(1 + r, n)) / (pow(1 + r, n) - 1);

            CString result;
            result.Format(_T("Monthly Payment: $%.2f"), M);
            m_staticResult.SetWindowText(result);
        } else {
            m_staticResult.SetWindowText(_T("Error: Invalid Input"));
        }
    }

    DECLARE_MESSAGE_MAP()
};

// 4. Message Map: Link UI ID to the Function
BEGIN_MESSAGE_MAP(CFinancialDlg, CDialog)
    ON_BN_CLICKED(IDC_BTN_CALC, OnCalculate)
END_MESSAGE_MAP()

// 5. The Application Class
class CFinancialApp : public CWinApp {
public:
    virtual BOOL InitInstance() {
        CFinancialDlg dlg;
        m_pMainWnd = &dlg;
        dlg.DoModal();
        return FALSE;
    }
};

CFinancialApp theApp;
//~ IMPLEMENT_APP(CFinancialApp)
