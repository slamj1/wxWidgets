///////////////////////////////////////////////////////////////////////////////
// Name:        wx/msw/toplevel.h
// Purpose:     wxTopLevelWindowMSW is the MSW implementation of wxTLW
// Author:      Vadim Zeitlin
// Modified by:
// Created:     20.09.01
// RCS-ID:      $Id$
// Copyright:   (c) 2001 SciTech Software, Inc. (www.scitechsoft.com)
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_MSW_TOPLEVEL_H_
#define _WX_MSW_TOPLEVEL_H_

#ifdef __GNUG__
    #pragma interface "toplevel.h"
#endif

// ----------------------------------------------------------------------------
// wxTopLevelWindowMSW
// ----------------------------------------------------------------------------

class WXDLLEXPORT wxTopLevelWindowMSW : public wxTopLevelWindowBase
{
public:
    // constructors and such
    wxTopLevelWindowMSW() { Init(); }

    wxTopLevelWindowMSW(wxWindow *parent,
                        wxWindowID id,
                        const wxString& title,
                        const wxPoint& pos = wxDefaultPosition,
                        const wxSize& size = wxDefaultSize,
                        long style = wxDEFAULT_FRAME_STYLE,
                        const wxString& name = wxFrameNameStr)
    {
        Init();

        (void)Create(parent, id, title, pos, size, style, name);
    }

    bool Create(wxWindow *parent,
                wxWindowID id,
                const wxString& title,
                const wxPoint& pos = wxDefaultPosition,
                const wxSize& size = wxDefaultSize,
                long style = wxDEFAULT_FRAME_STYLE,
                const wxString& name = wxFrameNameStr);

    virtual ~wxTopLevelWindowMSW();

    // implement base class pure virtuals
    virtual void Maximize(bool maximize = TRUE);
    virtual bool IsMaximized() const;
    virtual void Iconize(bool iconize = TRUE);
    virtual bool IsIconized() const;
    virtual void SetIcon(const wxIcon& icon);
    virtual void SetIcons(const wxIconBundle& icons );
    virtual void Restore();

    virtual bool Show(bool show = TRUE);

    virtual bool ShowFullScreen(bool show, long style = wxFULLSCREEN_ALL);
    virtual bool IsFullScreen() const { return m_fsIsShowing; }

    // wxMSW only: EnableCloseButton(FALSE) may be used to remove the "Close"
    // button from the title bar
    bool EnableCloseButton(bool enable = TRUE);

    // implementation from now on
    // --------------------------

protected:
    // common part of all ctors
    void Init();

    // create a new frame, return FALSE if it couldn't be created
    bool CreateFrame(const wxString& title,
                     const wxPoint& pos,
                     const wxSize& size);

    // create a new dialog using the given dialog template from resources,
    // return FALSE if it couldn't be created
    bool CreateDialog(const void *dlgTemplate,
                      const wxString& title,
                      const wxPoint& pos,
                      const wxSize& size);

    // common part of Iconize(), Maximize() and Restore()
    void DoShowWindow(int nShowCmd);

    // prevent the window from being deactivated sometimes (see comments in the
    // code)
    long HandleNcActivate(bool activate);

    // translate wxWindows flags to Windows ones
    virtual WXDWORD MSWGetStyle(long flags, WXDWORD *exstyle) const;

    // we handle WM_NCACTIVATE specially here
    virtual long MSWWindowProc(WXUINT msg, WXWPARAM wParam, WXLPARAM lParam);

    // is the window currently iconized?
    bool m_iconized;

    // should the frame be maximized when it will be shown? set by Maximize()
    // when it is called while the frame is hidden
    bool m_maximizeOnShow;

    // Data to save/restore when calling ShowFullScreen
    long                  m_fsStyle; // Passed to ShowFullScreen
    wxRect                m_fsOldSize;
    long                  m_fsOldWindowStyle;
    bool                  m_fsIsMaximized;
    bool                  m_fsIsShowing;
};

// list of all frames and modeless dialogs
extern WXDLLEXPORT_DATA(wxWindowList) wxModelessWindows;

#endif // _WX_MSW_TOPLEVEL_H_

