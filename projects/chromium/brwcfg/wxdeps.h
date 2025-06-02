#if !defined(__BC18A0BC_9395_4127_B5E1_F616AF02383C__)
#define __BC18A0BC_9395_4127_B5E1_F616AF02383C__
#if ENABLE_WXUI
#if defined(__OSMAC__)
#ifndef __WXOSX_COCOA__
#undef __WXOSX_COCOA__
#define __WXOSX_COCOA__ 1
#endif
#elif defined(__OSWIN__)
#if !defined(__WXMSW__)
#define __WXMSW__
#endif
#if !defined(NOPCH)
#define NOPCH
#endif
#endif

// for compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "wx/wx.h"
#include "wx/nativewin.h"
#include "wx/mdi.h"
#include "wx/docmdi.h"
#include "wx/aui/aui.h"
#include "wx/app.h"
#include "wx/log.h"
#include "wx/frame.h"
#include "wx/menu.h"
#include "wx/image.h"
#include "wx/button.h"
#include "wx/checkbox.h"
#include "wx/listbox.h"
#include "wx/statbox.h"
#include "wx/stattext.h"
#include "wx/textctrl.h"
#include "wx/msgdlg.h"
#include "wx/grid.h"
#include "wx/propgrid/manager.h"
#include "wx/spinctrl.h"
#include "wx/artprov.h"
#include "wx/clipbrd.h"
#include "wx/colordlg.h"
#include "wx/wxhtml.h"
#include "wx/imaglist.h"
#include "wx/dataobj.h"
#include "wx/dcclient.h"
#include "wx/bmpbuttn.h"
#include "wx/region.h"
#include "wx/toolbar.h"
#include "wx/statusbr.h"
#include "wx/sysopt.h"
#include "wx/bookctrl.h"
#include "wx/treebook.h"
#include "wx/treectrl.h"
#include "wx/treelist.h"
#include "wx/sizer.h"
#include "wx/fontdlg.h"
#include "wx/numdlg.h"
#include "wx/textdlg.h"
#include "wx/wupdlock.h"
#include "wx/textcompleter.h"
#include "wx/persist/toplevel.h"
#include "wx/persist/treebook.h"
#include "wx/listctrl.h"
#include "wx/glcanvas.h"
#include "wx/rawbmp.h"
#include "wx/popupwin.h"
#include "wx/spinctrl.h"
#include "wx/colordlg.h"
#include "wx/fontdlg.h"
#include "wx/aboutdlg.h"
#include "wx/combo.h"
#include "wx/odcombo.h"
#include "wx/dynlib.h"
#if defined(__WXMSW__)
#include "wx/msw/wrapwin.h"
#endif
#include "wx/dcbuffer.h"
#include "wx/mstream.h"
#include "wx/graphics.h"
#include "wx/notebook.h"
#include "wx/artprov.h"
#include "wx/creddlg.h"
#include "wx/filedlg.h"
#include "wx/cmdline.h"
#include "wx/notifmsg.h"
#include "wx/settings.h"
#include "wx/infobar.h"
#include "wx/filesys.h"
#include "wx/fs_arc.h"
#include "wx/fs_mem.h"
#include "wx/stdpaths.h"
#if wxUSE_STC
#include "wx/stc/stc.h"
#else
#include "wx/textctrl.h"
#endif
#include <wx/display.h>
#include <wx/image.h>
#include <wx/mstream.h>
#include "wx/richtext/richtextctrl.h"
#include "wx/richtext/richtextstyles.h"
#include "wx/richtext/richtextxml.h"
#include "wx/richtext/richtexthtml.h"
#include "wx/richtext/richtextformatdlg.h"
#include "wx/richtext/richtextsymboldlg.h"
#include "wx/richtext/richtextstyledlg.h"
#include "wx/richtext/richtextprint.h"
#include "wx/richtext/richtextimagedlg.h"
class wxComm {
public:
#if 0
  class TransparentBitmapButton : public wxBitmapButton {
  public:
    TransparentBitmapButton(
        wxWindow *parent, wxWindowID id, const wxBitmapBundle &bitmap,
        const wxPoint &pos = wxDefaultPosition,
        const wxSize &size = wxDefaultSize, long style = 0,
        const wxValidator &validator = wxDefaultValidator,
        const wxString &name = wxASCII_STR(wxButtonNameStr));

  private:
    void OnPaint(wxPaintEvent &event);
  };
#endif
public:
  wxComm() = default;
  ~wxComm() = default;

public:
  static bool GetImgStream(const wxImage *img, std::string &imgStream);
  static bool LoadImg(const std::u16string &imgPath, wxImage **outputImg);
  static bool LoadImgFormStream(const std::string &imageStream,
                                wxImage **outputImg);
};
#endif
/// /*_ Memade®（新生™） _**/
/// /*_ Sun, 02 Mar 2025 12:23:37 GMT _**/
/// /*_____ https://www.skstu.com/ _____ **/
#endif ///__BC18A0BC_9395_4127_B5E1_F616AF02383C__
