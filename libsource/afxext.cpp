
#include "afxext.h"
#include "afxwin.h"


void CStatusBar::Create(wxWindow* parent) {
	// In wxWidgets 2.8, StatusBars are usually created by Frames
	// For Dialogs, we create it as a child.
	wxStatusBar::Create(parent, wxID_ANY);
}
void CStatusBar::SetPaneText(int pane, const wxString& text) {
	SetStatusText(text, pane);
}

