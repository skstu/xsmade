/////////////////////////////////////////////////////////////////////////////
// Name:        wx/overlay.h
// Purpose:     wxOverlay class
// Author:      Stefan Csomor
// Created:     2006-10-20
// Copyright:   (c) wxWidgets team
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

#ifndef _WX_OVERLAY_H_
#define _WX_OVERLAY_H_

#include "wx/defs.h"

#include "wx/dcclient.h"

// ----------------------------------------------------------------------------
// creates an overlay over an existing window, allowing for manipulations like
// rubberbanding etc.
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_CORE wxOverlay
{
public:
    class Impl;

    wxOverlay();
    ~wxOverlay();

    // clears the overlay without restoring the former state
    // to be done eg when the window content has been changed and repainted
    void Reset();

    bool IsNative() const;

    void SetOpacity(int alpha);

private:
    friend class WXDLLIMPEXP_FWD_CORE wxDCOverlay;

    static Impl* Create();

    // returns true if it has been setup
    bool IsOk();

    void Init(wxDC* dc, int x , int y , int width , int height);

    void BeginDrawing(wxDC* dc);

    void EndDrawing(wxDC* dc);

    void Clear(wxDC* dc);

    Impl* m_impl;

    bool m_inDrawing;


    wxDECLARE_NO_COPY_CLASS(wxOverlay);
};


class WXDLLIMPEXP_CORE wxDCOverlay
{
public:
    // connects this overlay to the corresponding drawing dc, if the overlay is
    // not initialized yet this call will do so
    wxDCOverlay(wxOverlay &overlay, wxDC *dc, int x , int y , int width , int height);

    // convenience wrapper that behaves the same using the entire area of the dc
    wxDCOverlay(wxOverlay &overlay, wxDC *dc);

    // removes the connection between the overlay and the dc
    virtual ~wxDCOverlay();

    // clears the layer, restoring the state at the last init
    void Clear();

private:
    void Init(wxDC *dc, int x , int y , int width , int height);

    wxOverlay& m_overlay;

    wxDC* m_dc;


    wxDECLARE_NO_COPY_CLASS(wxDCOverlay);
};

// Convenient class combining wxClientDC with wxDCOverlay.
class wxOverlayDC : public wxClientDC
{
public:
    wxOverlayDC(wxOverlay& overlay, wxWindow* win)
        : wxClientDC(win),
          m_dcOverlay(overlay, this)
    {
    }

    wxOverlayDC(wxOverlay& overlay, wxWindow* win, const wxRect& rect)
        : wxClientDC(win),
          m_dcOverlay(overlay, this, rect.x, rect.y, rect.width, rect.height)
    {
    }

    void Clear()
    {
        m_dcOverlay.Clear();
    }

private:
    wxDCOverlay m_dcOverlay;

    wxDECLARE_NO_COPY_CLASS(wxOverlayDC);
};

#endif // _WX_OVERLAY_H_