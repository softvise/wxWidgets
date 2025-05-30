///////////////////////////////////////////////////////////////////////////////
// Name:        src/msw/utilsgui.cpp
// Purpose:     Various utility functions only available in wxMSW GUI
// Author:      Vadim Zeitlin
// Created:     21.06.2003 (extracted from msw/utils.cpp)
// Copyright:   (c) Julian Smart
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// for compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"


#ifndef WX_PRECOMP
    #include "wx/cursor.h"
    #include "wx/window.h"
    #include "wx/utils.h"
#endif //WX_PRECOMP

#include "wx/msw/private/resource_usage.h"

#include "wx/msw/private.h"     // includes <windows.h>

#include "wx/msw/wrapwin.h"
#include <shlwapi.h>

// ============================================================================
// implementation
// ============================================================================

// Emit a beeeeeep
void wxBell()
{
    ::MessageBeep((UINT)-1);        // default sound
}

// ---------------------------------------------------------------------------
// helper functions for showing a "busy" cursor
// ---------------------------------------------------------------------------

static HCURSOR gs_wxBusyCursor = 0;     // new, busy cursor
static HCURSOR gs_wxBusyCursorOld = 0;  // old cursor
static int gs_wxBusyCursorCount = 0;

extern HCURSOR wxGetCurrentBusyCursor()
{
    return gs_wxBusyCursor;
}

// Set the cursor to the busy cursor for all windows
void wxBeginBusyCursor(const wxCursor *cursor)
{
    if ( gs_wxBusyCursorCount++ == 0 )
    {
        gs_wxBusyCursor = (HCURSOR)cursor->GetHCURSOR();
        gs_wxBusyCursorOld = ::SetCursor(gs_wxBusyCursor);
    }
    //else: nothing to do, already set
}

// Restore cursor to normal
void wxEndBusyCursor()
{
    wxCHECK_RET( gs_wxBusyCursorCount > 0,
                 wxT("no matching wxBeginBusyCursor() for wxEndBusyCursor()") );

    if ( --gs_wxBusyCursorCount == 0 )
    {
        ::SetCursor(gs_wxBusyCursorOld);
        gs_wxBusyCursorOld = 0;
    }
}

// true if we're between the above two calls
bool wxIsBusy()
{
  return gs_wxBusyCursorCount > 0;
}

// Check whether this window wants to process messages, e.g. Stop button
// in long calculations.
bool wxCheckForInterrupt(wxWindow *wnd)
{
    wxCHECK( wnd, false );

    MSG msg;
    while ( ::PeekMessage(&msg, GetHwndOf(wnd), 0, 0, PM_REMOVE) )
    {
        ::TranslateMessage(&msg);
        ::DispatchMessage(&msg);
    }

    return true;
}

// ----------------------------------------------------------------------------
// get mouse position
// ----------------------------------------------------------------------------

void wxGetMousePosition( int* x, int* y )
{
    POINT pt;
    wxGetCursorPosMSW( & pt );
    if ( x ) *x = pt.x;
    if ( y ) *y = pt.y;
}

// ---------------------------------------------------------------------------
// window information functions
// ---------------------------------------------------------------------------

wxString WXDLLEXPORT wxGetWindowText(WXHWND hWnd)
{
    wxString str;

    if ( hWnd )
    {
        int len = GetWindowTextLength((HWND)hWnd) + 1;
        ::GetWindowText((HWND)hWnd, wxStringBuffer(str, len), len);
    }

    return str;
}

wxString WXDLLEXPORT wxGetWindowClass(WXHWND hWnd)
{
    wxString str;

    if ( hWnd )
    {
        int len = 256; // some starting value

        for ( ;; )
        {
            int count = ::GetClassName((HWND)hWnd, wxStringBuffer(str, len), len);

            if ( count == len )
            {
                // the class name might have been truncated, retry with larger
                // buffer
                len *= 2;
            }
            else
            {
                break;
            }
        }
    }

    return str;
}

int WXDLLEXPORT wxGetWindowId(WXHWND hWnd)
{
    return ::GetWindowLong((HWND)hWnd, GWL_ID);
}

// ----------------------------------------------------------------------------
// Metafile helpers
// ----------------------------------------------------------------------------

void PixelToHIMETRIC(LONG *x, LONG *y, HDC hdcRef)
{
    int iWidthMM = GetDeviceCaps(hdcRef, HORZSIZE),
        iHeightMM = GetDeviceCaps(hdcRef, VERTSIZE),
        iWidthPels = GetDeviceCaps(hdcRef, HORZRES),
        iHeightPels = GetDeviceCaps(hdcRef, VERTRES);

    // Take care to use MulDiv() here to avoid overflow.
    *x = ::MulDiv(*x, iWidthMM * 100, iWidthPels);
    *y = ::MulDiv(*y, iHeightMM * 100, iHeightPels);
}

void HIMETRICToPixel(LONG *x, LONG *y, HDC hdcRef)
{
    int iWidthMM = GetDeviceCaps(hdcRef, HORZSIZE),
        iHeightMM = GetDeviceCaps(hdcRef, VERTSIZE),
        iWidthPels = GetDeviceCaps(hdcRef, HORZRES),
        iHeightPels = GetDeviceCaps(hdcRef, VERTRES);

    *x = ::MulDiv(*x, iWidthPels, iWidthMM * 100);
    *y = ::MulDiv(*y, iHeightPels, iHeightMM * 100);
}

void HIMETRICToPixel(LONG *x, LONG *y)
{
    HIMETRICToPixel(x, y, ScreenHDC());
}

void PixelToHIMETRIC(LONG *x, LONG *y)
{
    PixelToHIMETRIC(x, y, ScreenHDC());
}

void wxDrawLine(HDC hdc, int x1, int y1, int x2, int y2)
{
    MoveToEx(hdc, x1, y1, nullptr); LineTo(hdc, x2, y2);
}

// Function dedicated to drawing horizontal/vertical lines with solid color
// It fills rectangle representing the line with ::ExtTextOut() API which
// apparently is faster than ::MoveTo()/::LineTo() on DC with a non-rotated
// coordinate system.
void wxDrawHVLine(HDC hdc, int x1, int y1, int x2, int y2, COLORREF color, int width)
{
    wxASSERT(x1 == x2 || y1 == y2);

    int w1 = width / 2;
    int w2 = width - w1;
    RECT r;
    if ( y1 == y2 )
    {
        if ( x1 == x2 )
            return;
        ::SetRect(&r, x1, y1 - w1, x2, y1 + w2);
    }
    else
    {
        ::SetRect(&r, x1 - w1, y1, x2 + w2, y2);
    }

    COLORREF bgColorOrig = ::GetBkColor(hdc);
    ::SetBkColor(hdc, color);

    ::ExtTextOutW(hdc, 0, 0, ETO_OPAQUE, &r, L"", 0, nullptr);

    ::SetBkColor(hdc, bgColorOrig);
}

// ----------------------------------------------------------------------------
// Shell API wrappers
// ----------------------------------------------------------------------------

extern bool wxEnableFileNameAutoComplete(HWND hwnd)
{
    HRESULT hr = ::SHAutoComplete(hwnd, 0x10 /* SHACF_FILESYS_ONLY */);
    if ( FAILED(hr) )
    {
        wxLogApiError(wxT("SHAutoComplete"), hr);
        return false;
    }

    return true;
}

// ----------------------------------------------------------------------------
// GUI resources usage
// ----------------------------------------------------------------------------

namespace
{

// Common implementation of the public functions we provide.

enum class UseType
{
    Current,
    Peak
};

wxGUIObjectUsage wxGetUsedResources(UseType useType)
{
    DWORD flagsGDI = 0,
          flagsUSER = 0;

    switch ( useType )
    {
        case UseType::Current:
            flagsGDI = GR_GDIOBJECTS;
            flagsUSER = GR_USEROBJECTS;
            break;

        case UseType::Peak:
            flagsGDI = GR_GDIOBJECTS_PEAK;
            flagsUSER = GR_USEROBJECTS_PEAK;
            break;
    }

    const auto hProcess = ::GetCurrentProcess();

    wxGUIObjectUsage usage;
    usage.numGDI = ::GetGuiResources(hProcess, flagsGDI);
    usage.numUSER = ::GetGuiResources(hProcess, flagsUSER);
    return usage;
}

} // anonymous namespace

wxGUIObjectUsage wxGetCurrentlyUsedResources()
{
    return wxGetUsedResources(UseType::Current);
}

wxGUIObjectUsage wxGetMaxUsedResources()
{
    return wxGetUsedResources(UseType::Peak);
}
