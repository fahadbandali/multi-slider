#include "mysingleslider.h"
#include "thumb_up.xpm"
#include "thumb_down.xpm"
#include "play.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "selectslidercontrol.h"


static const int BORDER_THICKNESS = 1;

static const wxCoord SLIDER_MARGIN = 1; // margin around slider
static const wxCoord SLIDER_THUMB_LENGTH = 1;
static const wxCoord SLIDER_TICK_LENGTH = 1;
//create oninit (regular method), constructor calls it
//takes number of sensors 
//moves sldiers to the top, they can overlap too
mysingleslider::mysingleslider(wxPanel *parent,
	wxWindowID id,
	int mainValue, int minValue, int maxValue,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxValidator& val,
	const wxString& name) : wxPanel(parent, id, pos, size, wxBORDER_NONE)

{
	Connect(wxID_ANY, wxSizeEventHandler(mysingleslider::OnSize));
	m_parent = parent;
	SetBackgroundColour(parent->GetBackgroundColour());
	SetDoubleBuffered(true);
	mainval = mainValue; minval = minValue; maxval = maxValue;
	upthumb = wxBitmap(thumb_up_xpm);
	downthumb = wxBitmap(thumb_down_xpm);
	selectedslider = 0;
	Bind(wxEVT_PAINT, &mysingleslider::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &mysingleslider::OnLeftDown, this);
	Bind(wxEVT_SIZE, &mysingleslider::OnSize, this);
	Bind(wxEVT_MOTION, &mysingleslider::OnMotion, this);
	Bind(wxEVT_LEFT_UP, &mysingleslider::OnLeftUp, this);
	Bind(wxEVT_LEAVE_WINDOW, &mysingleslider::OnLeftUp, this);
	Bind(wxEVT_MOUSEWHEEL, &mysingleslider::OnWheel, this);

	Refresh();
	Update();
}


void mysingleslider::SetMainValue(int mval)
{
	mainval = mval;
	Refresh();
	Update();
}


int mysingleslider::GetMainValue()
{
	return mainval;
}


wxSize mysingleslider::DoGetBestSize()
{
	return (wxSize(300, 300));
}


void mysingleslider::OnPaint(wxPaintEvent&)
{
	wxPaintDC dc(this);
	render(dc);

}

void mysingleslider::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void  mysingleslider::DrawThumb(wxDC& dc, wxCoord x, wxCoord y)
{

	dc.SetPen(wxColour("#447aee")); //for right pointer tip
	dc.DrawLine(x + 10, y + 16, x + 4, y + 22);
	dc.DrawLine(x + 10, y + 0, x + 10, y + 17);
	dc.DrawLine(x + 3, y + 17, x + 8, y + 17);

	dc.SetPen(wxColour("#447aee")); //for right pointer tip
	dc.DrawLine(x + 5, y + 20, x + 10, y + 15);
	dc.DrawLine(x + 9, y + 1, x + 9, y + 17);

	dc.SetPen(wxColour("#447aee")); //red right slider
	dc.DrawLine(x + 4, y + 21, x + 0, y + 17);
	dc.DrawLine(x + 5, y + 20, x + 0, y + 15);
	dc.DrawLine(x + 5, y + 19, x + 3, y + 17);
	dc.DrawLine(x + 5, y + 18, x + 7, y + 18);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i - 5, y + 15, x + i - 5, y - 30);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i + 3, y + 15, x + i + 3, y - 30);

}

void mysingleslider::render(wxDC& dc)
{
	int w, h;
	GetSize(&w, &h);
	wxCoord tw, th;

	//media bar
	dc.SetPen(wxPen(wxColor(0, 0, 0), 7));
	dc.DrawLine(SLIDER_MARGIN, h / 2 - 1, w / 1.3 + 15, h / 2 - 1);
	dc.SetPen(wxPen(wxColor(0, 0, 0), 7));
	dc.DrawLine(SLIDER_MARGIN, h / 2, w / 1.3 + 15, h / 2);
	dc.SetPen(wxPen(wxColor(0, 0, 0), 7));
	dc.DrawLine(SLIDER_MARGIN, h / 2 + 1, w / 1.3 + 15, h / 2 + 1);
	dc.SetPen(wxPen(wxColor(0, 0, 0), 10));
	dc.DrawLine(SLIDER_MARGIN, h / 2 + 1, w / 1.3 + 15, h / 2 + 1);


	//main slider:
	double mainslidervalue = ((double)mainval / (double)maxval) * (double)w / 1.3;
	dc.GetTextExtent(wxString::Format("%d", mainval), &tw, &th);
	DrawThumb(dc, SLIDER_MARGIN + mainslidervalue + 2, h*0.5 - th + 10);
	if (mainval < maxval / 2)
		dc.DrawText(wxString::Format("%d", mainval), SLIDER_MARGIN + mainslidervalue + 20, h*0.5 + 5);
	else
		dc.DrawText(wxString::Format("%d", mainval), SLIDER_MARGIN + mainslidervalue - tw - 12, h*0.5 + 5);

}


void mysingleslider::OnLeftDown(wxMouseEvent& event)
{
	int w, h;
	wxClientDC dc(this);
	dc.GetSize(&w, &h);
	double mainslidervalue = ((double)mainval / (double)maxval) * (double)w / 1.3;
	wxPoint pos = event.GetLogicalPosition(dc);
	pos.x = pos.x - SLIDER_MARGIN;
	pos.y = h - SLIDER_MARGIN - pos.y;
	slidercontrol* checkslider;
	selectedslider = checkslider->getselect();

	//if (pos.x = mainslidervalue) {
	//	selectedslider = 1; //pos.y < h / 2
	//}

	//if (pos.x > mainslidervalue) {
	//	selectedslider = 1; //pos.y < h / 2
	//}
	prevx = pos.x;
	prevy = pos.y;
	event.Skip();
}

void mysingleslider::OnMotion(wxMouseEvent& event)
{
	int w, h;
	play* spinctrl = (play*)m_parent->GetParent();
	int test = spinctrl->Getstep();
	int m = test;
	//int m = step;
	if (selectedslider != 0) {
		wxClientDC dc(this);
		dc.GetSize(&w, &h);
		wxPoint pos = event.GetLogicalPosition(dc);
		pos.x = pos.x - SLIDER_MARGIN;
		pos.y = h - SLIDER_MARGIN - pos.y;

		if (prevx - pos.x > 0)
			m = -m; //THESE CHANGE THE STEP SIZE
		if (test == 1) m = pos.x - prevx;

		if (selectedslider == 1) {
			mainval += m;
			if (mainval < minval)  mainval = minval;
			if (mainval >= maxval) mainval = maxval;
		}
		prevx = pos.x;
		prevy = pos.y;
		Refresh();
		Update();
	}
	event.Skip();
}

void mysingleslider::OnLeftUp(wxMouseEvent& event)
{
	event.Skip();
	if (selectedslider != 0) {
		selectedslider = 0;
		wxCommandEvent e(wxEVT_SCROLL_CHANGED);
		e.SetEventObject(this);
		e.SetString("update");
		ProcessWindowEvent(e);
	}
}

void mysingleslider::OnWheel(wxMouseEvent& event)
{
	int w, h;
	play* spinctrl = (play*)m_parent->GetParent();
	int test = spinctrl->Getstep();
	int m = test;
	wxClientDC dc(this);
	dc.GetSize(&w, &h);
	wxPoint pos = event.GetLogicalPosition(dc);
	pos.x = pos.x - SLIDER_MARGIN;
	pos.y = h - SLIDER_MARGIN - pos.y;
	if (event.GetWheelRotation() > 0)
		m = m; //THESE CHANGE THE STEP SIZE
	else
		m = -m;
	if (pos.y < h / 2) {
		mainval -= m;
		if (mainval < minval)  mainval = minval;
		if (mainval >= maxval) mainval = maxval;
	}
	Refresh();
	Update();
	wxCommandEvent e(wxEVT_SCROLL_CHANGED);
	e.SetEventObject(this);
	e.SetString("update");
	ProcessWindowEvent(e);
	event.Skip();
}


void mysingleslider::OnSize(wxSizeEvent& event)
{
	Refresh();
	Update();
}

