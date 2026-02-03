#ifndef AFXCMN_H
#define AFXCMN_H

#include "afxwin.h"

typedef struct {
    unsigned long  style;
    unsigned long  dwExtendedStyle;
    unsigned short cdit;
    short          x; short          y;
    short          cx; short          cy;
} DLGTEMPLATE;

#define GPTR 0x0040
#define DS_CENTER 0
#define WS_POPUP 0
#define WS_CAPTION 0
#define WS_SYSMENU 0
#define SS_SUNKEN 0
#define SS_CENTER 0
#define LOWORD(l) ((unsigned short)((unsigned long)(l) & 0xffff))

inline void* GlobalAlloc(int flags, size_t size) { return malloc(size); }
inline void  GlobalFree(void* ptr) { if(ptr) free(ptr); }

#endif
