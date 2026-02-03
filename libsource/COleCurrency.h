#ifndef COleCurrency_H
#define COleCurrency_H

// ============================================================================
// 1. WIN32 TYPE SHIMS (Allows compiler to recognize raw Windows types)
// ============================================================================
typedef void*           HWND;        // Window Handle
typedef void*           HDC;         // Device Context Handle
typedef long            LPARAM;      // Message Parameter
//~ typedef unsigned int    WPARAM;      // Message Parameter
typedef long            LRESULT;     // Return value
#define CALLBACK                     // Calling convention
#define WINAPI                       // Entry point convention
#define AFX_MSG                      // MFC message markers

// ============================================================================
// 2. MFC GLOBAL FUNCTION SHIMS (Hides Afx calls)
// ============================================================================
#include <wx/msgdlg.h>
inline void AfxMessageBox(const wxString& text);

/**
 * --- 2026 Multiplatform Stealth Engine ---
 * Perfectly mimicking MFC using wxWidgets (Compatible with 2.8, 3.x, and 3.2+)
 * Includes: Financial Math, GUI Framework, and Graphics (CDC) Logic.
 */

#include <wx/wx.h>
#include <wx/string.h> 
#include <wx/init.h>   
#include <wx/event.h>
#include <wx/dcclient.h>
#include <wx/mdi.h> // Essential for Multiple Window Interface
#include <cmath>     
#include "afxwin.h"  

// ============================================================================
// 1. MFC STEALTH COMPATIBILITY LAYER
// ============================================================================

// Core Types
typedef bool          BOOL;       
#define TRUE         1
#define FALSE        0
#define _T(x)        wxT(x)      // Unicode-safe literal macro
#define LPCTSTR      const wxChar*

// --- Stealth MDI Framework Aliases ---
typedef wxMDIParentFrame  CMDIFrameWnd;   // Programmer sees CMDIFrameWnd
typedef wxMDIChildFrame   CMDIChildFrame; // Programmer sees CMDIChildFrame
     
typedef wxPoint      CPoint;     

// Pen Style Fixes (Maps modern names to legacy wxWidgets 2.8 constants)
#ifndef wxPENSTYLE_DOT
    #define wxPENSTYLE_DOT    wxDOT
#endif
#ifndef wxPENSTYLE_SOLID
    #define wxPENSTYLE_SOLID  wxSOLID
#endif

// ============================================================================
// 2. COleCurrency CLASS IMPLEMENTATION (Cumulative Fixes)
// ============================================================================

class COleCurrency {
public:
    enum CurrencyStatus { valid = 0, invalid = 1, null = 2 };

    // MFC Data Members (Standard names)
    long long m_cur;            // 8-byte integer scaled by 10,000
    CurrencyStatus m_status;
    static const int SCALE = 10000;

    // Constructors
    COleCurrency();
    COleCurrency(long nUnits, long nFractional) ;

    // Core Initialization
    void SetCurrency(long nUnits, long nFractional) ;

    // Parsing Logic (Fixed for wxString)
    BOOL ParseCurrency(const CString& lpszCurrency) ;

    // Formatting Logic (Fixed for Unicode literals)
    CString Format() const ;

    // --- Cumulative Arithmetic Operators ---
    
    COleCurrency operator+(const COleCurrency& cur) const ;

    const COleCurrency& operator+=(const COleCurrency& cur) ;

    const COleCurrency& operator-=(const COleCurrency& cur) ;

    // --- Cumulative Trading & Relational Operators ---

    COleCurrency operator*(double dblMultiplier) const ;

    BOOL operator>=(const COleCurrency& cur) const ;

    BOOL operator>(const COleCurrency& cur) const ;

    CurrencyStatus GetStatus() const ;
    
    void SetCurrency(double dblVal) ;
};
//~ typedef wxDC CDC; typedef wxPaintDC CPaintDC;
#endif // COleCurrency_H
