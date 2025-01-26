#include "ui/ui.h"
using namespace ui;
IFrame::IFrame(wxWindow *parent, wxWindowID id, const wxString &title,
               const wxPoint &pos, const wxSize &size, long style,
               const wxString &name)
    : wxFrame(parent, id, title, pos, size, style) {
  wxEvtHandler::Bind(wxEVT_CLOSE_WINDOW, &IFrame::OnClose, this);
  wxEvtHandler::Bind(wxEVT_SIZE, &IFrame::OnSize, this);
  wxEvtHandler::Bind(wxEVT_PAINT, &IFrame::OnPaint, this);
  wxEvtHandler::Bind(wxEVT_ERASE_BACKGROUND, &IFrame::OnEraseBackground, this);
  wxEvtHandler::Bind(wxEVT_MOTION, &IFrame::OnMouseMove, this);
  wxEvtHandler::Bind(wxEVT_MOVE, &IFrame::OnMove, this);
  wxEvtHandler::Bind(wxEVT_LEFT_DOWN, &IFrame::OnMouseLeftDown, this);
  wxEvtHandler::Bind(wxEVT_LEFT_UP, &IFrame::OnMouseLeftUp, this);
  wxEvtHandler::Bind(wxEVT_MOUSE_CAPTURE_LOST, &IFrame::OnMouseCaptureLost,
                     this);
  //   SetBackgroundStyle(wxBG_STYLE_CUSTOM);
}

IFrame::~IFrame() {
  wxEvtHandler::Unbind(wxEVT_SIZE, &IFrame::OnSize, this);
  wxEvtHandler::Unbind(wxEVT_CLOSE_WINDOW, &IFrame::OnClose, this);
  wxEvtHandler::Unbind(wxEVT_PAINT, &IFrame::OnPaint, this);
  wxEvtHandler::Unbind(wxEVT_ERASE_BACKGROUND, &IFrame::OnEraseBackground,
                       this);
  wxEvtHandler::Unbind(wxEVT_MOTION, &IFrame::OnMouseMove, this);
  wxEvtHandler::Unbind(wxEVT_MOVE, &IFrame::OnMove, this);
  wxEvtHandler::Unbind(wxEVT_LEFT_DOWN, &IFrame::OnMouseLeftDown, this);
  wxEvtHandler::Unbind(wxEVT_LEFT_UP, &IFrame::OnMouseLeftUp, this);
  wxEvtHandler::Unbind(wxEVT_MOUSE_CAPTURE_LOST, &IFrame::OnMouseCaptureLost,
                       this);
}
void IFrame::OnSize(wxSizeEvent &evt) {
  evt.Skip();
}
void IFrame::OnMove(wxMoveEvent &evt) {
  evt.Skip();
}
void IFrame::OnClose(wxCloseEvent &evt) {
  evt.Skip();
}
void IFrame::OnPaint(wxPaintEvent &evt) {
  evt.Skip();
}
void IFrame::OnEraseBackground(wxEraseEvent &evt) {
  evt.Skip();
}
void IFrame::OnMouseMove(wxMouseEvent &evt) {
  evt.Skip();
}
void IFrame::OnMouseLeftDown(wxMouseEvent &evt) {
  evt.Skip();
}
void IFrame::OnMouseLeftUp(wxMouseEvent &evt) {
  evt.Skip();
}
void IFrame::OnMouseCaptureLost(wxMouseCaptureLostEvent &evt) {
  evt.Skip();
}