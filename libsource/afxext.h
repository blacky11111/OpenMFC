#ifndef AFXEXT_H
#define AFXEXT_H

#include "afxwin.h"
#include <wx/statusbr.h>

class CStatusBar : public wxStatusBar {
public:
    void Create(wxWindow* parent) ;
    void SetPaneText(int pane, const wxString& text);
};

#endif
