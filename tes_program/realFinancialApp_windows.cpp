#include <afxwin.h>      
#include <afxext.h>      // Now used for CStatusBar
#include <cmath>         

#define IDC_EDIT_LOAN    101
#define IDC_EDIT_RATE    102
#define IDC_EDIT_TERM    103
#define IDC_BTN_CALC     104
#define IDC_STATIC_RES   105

class CFinancialDlg : public CDialog {
public:
    CFinancialDlg() : CDialog(0) {}

protected:
    CEdit m_editLoan, m_editRate, m_editTerm;
    CStatic m_staticResult;
    CStatusBar m_statusBar; // Extension Control

    virtual BOOL OnInitDialog() {
        CDialog::OnInitDialog();
        SetWindowText(_T("Financial Calc 2026 w/ Extensions"));

        m_editLoan.Create(0, CRect(20, 20, 150, 45), this, IDC_EDIT_LOAN);
        m_editLoan.SetWindowText(_T("10000"));

        m_editRate.Create(0, CRect(20, 60, 150, 85), this, IDC_EDIT_RATE);
        m_editRate.SetWindowText(_T("5.0"));

        m_editTerm.Create(0, CRect(20, 100, 150, 125), this, IDC_EDIT_TERM);
        m_editTerm.SetWindowText(_T("36"));

        CButton* btn = new CButton();
        btn->Create(_T("Calculate"), 0, CRect(20, 140, 150, 175), this, IDC_BTN_CALC);

        m_staticResult.Create(_T("Result: $0.00"), 0, CRect(20, 190, 250, 215), this, IDC_STATIC_RES);

        // --- Extension Feature: Status Bar ---
        m_statusBar.Create(this);
        m_statusBar.SetPaneText(0, _T("Ready"));

        return TRUE;
    }

    void OnCalculate() {
        CString strLoan, strRate, strTerm;
        m_editLoan.GetWindowText(strLoan);
        m_editRate.GetWindowText(strRate);
        m_editTerm.GetWindowText(strTerm);

        double P = _tstof(strLoan);
        double annualRate = _tstof(strRate);
        int n = _ttoi(strTerm);

        if (P > 0 && annualRate > 0 && n > 0) {
            double r = (annualRate / 100) / 12;
            double M = P * (r * pow(1 + r, n)) / (pow(1 + r, n) - 1);

            CString result;
            result.Format(_T("Monthly Payment: $%.2f"), M);
            m_staticResult.SetWindowText(result);
            
            // --- Update Extension Feature ---
            m_statusBar.SetPaneText(0, _T("Calculation Successful"));
        } else {
            m_statusBar.SetPaneText(0, _T("Input Error!"));
        }
    }

    DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CFinancialDlg, CDialog)
    ON_BN_CLICKED(IDC_BTN_CALC, OnCalculate)
END_MESSAGE_MAP()

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
