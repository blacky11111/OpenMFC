#include "COleCurrency.h"
// ============================================================================
// 2. MFC GLOBAL FUNCTION SHIMS (Hides Afx calls)
// ============================================================================
inline void AfxMessageBox(const wxString& text) { 
    wxMessageBox(text, wxT("Application Message"), wxOK); 
}

#include "afxwin.h"


// ============================================================================
// 2. COleCurrency CLASS IMPLEMENTATION (Cumulative Fixes)
// ============================================================================

// Constructors
COleCurrency::COleCurrency() : m_cur(0), m_status(null) {}
COleCurrency::COleCurrency(long nUnits, long nFractional) { SetCurrency(nUnits, nFractional); }

// Core Initialization
void COleCurrency::SetCurrency(long nUnits, long nFractional) {
	m_cur = ((long long)nUnits * SCALE) + (nFractional % SCALE);
	m_status = valid;
}

// Parsing Logic (Fixed for wxString)
BOOL COleCurrency::ParseCurrency(const CString& lpszCurrency) {
	double dblVal;
	if (lpszCurrency.ToDouble(&dblVal)) {
		m_cur = static_cast<long long>(std::round(dblVal * SCALE));
		m_status = valid;
		return TRUE;
	}
	m_status = invalid;
	return FALSE;
}

// Formatting Logic (Fixed for Unicode literals)
CString COleCurrency::Format() const {
    if (m_status != valid) return _T("0.00");
    double dblVal = static_cast<double>(m_cur) / SCALE;
    // Call wxString::Format directly to bypass CString ambiguity
    return CString(wxString::Format(_T("%.2f"), dblVal)); 
}

// --- Cumulative Arithmetic Operators ---

COleCurrency COleCurrency::operator+(const COleCurrency& cur) const {
	COleCurrency res;
	if (m_status == valid && cur.m_status == valid) {
		res.m_cur = m_cur + cur.m_cur;
		res.m_status = valid;
	}
	return res;
}

const COleCurrency& COleCurrency::operator+=(const COleCurrency& cur) {
	if (m_status == valid && cur.m_status == valid) m_cur += cur.m_cur;
	else m_status = invalid;
	return *this;
}

const COleCurrency& COleCurrency::operator-=(const COleCurrency& cur) {
	if (m_status == valid && cur.m_status == valid) m_cur -= cur.m_cur;
	else m_status = invalid;
	return *this;
}

// --- Cumulative Trading & Relational Operators ---

COleCurrency COleCurrency::operator*(double dblMultiplier) const {
	COleCurrency res;
	if (m_status == valid) {
		res.m_cur = static_cast<long long>(std::round(m_cur * dblMultiplier));
		res.m_status = valid;
	}
	return res;
}

BOOL COleCurrency::operator>=(const COleCurrency& cur) const {
	return (m_status == valid && cur.m_status == valid && m_cur >= cur.m_cur);
}

BOOL COleCurrency::operator>(const COleCurrency& cur) const {
	return (m_status == valid && cur.m_status == valid && m_cur > cur.m_cur);
}

COleCurrency::CurrencyStatus COleCurrency::GetStatus() const { return m_status; }

void COleCurrency::SetCurrency(double dblVal) {
    m_cur = static_cast<long long>(std::round(dblVal * SCALE));
    m_status = valid;
}

