#include "myquadslider.h"
#include "thumb_up.xpm"
#include "thumb_down.xpm"
#include "play.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include <math.h>


static const int BORDER_THICKNESS = 1;

static const wxCoord SLIDER_MARGIN = 1; // margin around slider
static const wxCoord SLIDER_THUMB_LENGTH = 1;
static const wxCoord SLIDER_TICK_LENGTH = 1;
//create oninit (regular method), constructor calls it
//takes number of sensors 
//moves sldiers to the top, they can overlap too
myquadslider::myquadslider(wxPanel *parent,
	wxWindowID id,
	int leftValue, int rightValue, int leftmiddleValue, int rightmiddleValue, int minValue, int maxValue,
	const wxPoint& pos,
	const wxSize& size,
	long style,
	const wxValidator& val,
	const wxString& name) : wxPanel(parent, id, pos, size, wxBORDER_NONE)

{
	Connect(wxID_ANY, wxSizeEventHandler(myquadslider::OnSize));
	m_parent = parent;
	SetBackgroundColour(parent->GetBackgroundColour());
	SetDoubleBuffered(true);
	leftval = leftValue; rightval = rightValue; leftmiddleval = leftmiddleValue; rightmiddleval = rightmiddleValue; minval = minValue; maxval = maxValue;
	upthumb = wxBitmap(thumb_up_xpm);
	downthumb = wxBitmap(thumb_down_xpm);
	selectedslider = 0;
	Bind(wxEVT_PAINT, &myquadslider::OnPaint, this);
	Bind(wxEVT_LEFT_DOWN, &myquadslider::OnLeftDown, this);
	Bind(wxEVT_SIZE, &myquadslider::OnSize, this);
	Bind(wxEVT_MOTION, &myquadslider::OnMotion, this);
	Bind(wxEVT_LEFT_UP, &myquadslider::OnLeftUp, this);
	Bind(wxEVT_LEAVE_WINDOW, &myquadslider::OnLeftUp, this);
	Bind(wxEVT_MOUSEWHEEL, &myquadslider::OnWheel, this);

	Refresh();
	Update();
}


void myquadslider::SetLeftValue(int lval)
{
	leftval = lval;
	Refresh();
	Update();
}

void myquadslider::SetRightValue(int rval)
{
	rightval = rval;
	Refresh();
	Update();
}

void myquadslider::SetLeftMiddleValue(int lmval)
{
	leftmiddleval = lmval;
	Refresh();
	Update();
}

void myquadslider::SetRightMiddleValue(int rmval)
{
	rightmiddleval = rmval;
	Refresh();
	Update();
}

int myquadslider::GetLeftValue()
{
	return leftval;
}

int myquadslider::GetRightValue()
{
	return rightval;
}

int myquadslider::GetLeftMiddleValue()
{
	return leftmiddleval;
}

int myquadslider::GetRightMiddleValue()
{
	return rightmiddleval;
}

wxSize myquadslider::DoGetBestSize()
{
	return (wxSize(300, 300));
}


void myquadslider::OnPaint(wxPaintEvent&)
{
	wxPaintDC dc(this);
	render(dc);

}

void myquadslider::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void  myquadslider::DrawUpThumb(wxDC& dc, wxCoord x, wxCoord y)
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


void  myquadslider::DrawDownThumb(wxDC& dc, wxCoord x, wxCoord y)
{
	dc.SetPen(wxColour("#FF0000")); //for right pointer tip
	dc.DrawLine(x + 10, y + 16, x + 4, y + 22);
	dc.DrawLine(x + 10, y + 0, x + 10, y + 17);
	dc.DrawLine(x + 3, y + 17, x + 8, y + 17);

	dc.SetPen(wxColour("#FF0000")); //for right pointer tip
	dc.DrawLine(x + 5, y + 20, x + 10, y + 15);
	dc.DrawLine(x + 9, y + 1, x + 9, y + 17);

	dc.SetPen(wxColour("#FF0000")); //red right slider
	dc.DrawLine(x + 4, y + 21, x + 0, y + 17);
	dc.DrawLine(x + 5, y + 20, x + 0, y + 15);
	dc.DrawLine(x + 5, y + 19, x + 3, y + 17);
	dc.DrawLine(x + 5, y + 18, x + 7, y + 18);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i - 5, y + 15, x + i - 5, y - 30);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i + 3, y + 15, x + i + 3, y - 30);


}

void  myquadslider::DrawLeftMiddleThumb(wxDC& dc, wxCoord x, wxCoord y)
{
	dc.SetPen(wxColour("#39FF14")); //for middle pointer tip
	dc.DrawLine(x + 10, y + 16, x + 4, y + 22);
	dc.DrawLine(x + 10, y + 0, x + 10, y + 17);
	dc.DrawLine(x + 3, y + 17, x + 8, y + 17);

	dc.SetPen(wxColour("#39FF14")); //for middle pointer tip
	dc.DrawLine(x + 5, y + 20, x + 10, y + 15);
	dc.DrawLine(x + 9, y + 1, x + 9, y + 17);

	dc.SetPen(wxColour("#39FF14")); //green left middle slider
	dc.DrawLine(x + 4, y + 21, x + 0, y + 17);
	dc.DrawLine(x + 5, y + 20, x + 0, y + 15);
	dc.DrawLine(x + 5, y + 19, x + 3, y + 17);
	dc.DrawLine(x + 5, y + 18, x + 7, y + 18);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i - 5, y + 15, x + i - 5, y - 30);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i + 3, y + 15, x + i + 3, y - 30);
}

void  myquadslider::DrawRightMiddleThumb(wxDC& dc, wxCoord x, wxCoord y)
{

	dc.SetPen(wxColour("#39FF14")); //for middle pointer tip
	dc.DrawLine(x + 10, y + 16, x + 4, y + 22);
	dc.DrawLine(x + 10, y + 0, x + 10, y + 17);
	dc.DrawLine(x + 3, y + 17, x + 8, y + 17);

	dc.SetPen(wxColour("#39FF14")); //for middle pointer tip
	dc.DrawLine(x + 5, y + 20, x + 10, y + 15);
	dc.DrawLine(x + 9, y + 1, x + 9, y + 17);

	dc.SetPen(wxColour("#FFFF00")); //yellow right middle slider
	dc.DrawLine(x + 4, y + 21, x + 0, y + 17);
	dc.DrawLine(x + 5, y + 20, x + 0, y + 15);
	dc.DrawLine(x + 5, y + 19, x + 3, y + 17);
	dc.DrawLine(x + 5, y + 18, x + 7, y + 18);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i - 5, y + 15, x + i - 5, y - 30);
	for (int i = 1; i <= 8; i++) dc.DrawLine(x + i + 3, y + 15, x + i + 3, y - 30);

}


void myquadslider::render(wxDC& dc)
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


	//left slider:
	double leftslidervalue = ((double)leftval / (double)maxval) * (double)w / 1.3;
	dc.GetTextExtent(wxString::Format("%d", leftval), &tw, &th);
	DrawUpThumb(dc, SLIDER_MARGIN + leftslidervalue + 2, h*0.5 - th + 10);
	if (leftval < maxval / 2)
		dc.DrawText(wxString::Format("%d", leftval), SLIDER_MARGIN + leftslidervalue + 20, h*0.5 + 5);
	else
		dc.DrawText(wxString::Format("%d", leftval), SLIDER_MARGIN + leftslidervalue - tw - 12, h*0.5 + 5);
	//right slider:
	double rightslidervalue = ((double)rightval / (double)maxval) * (double)w / 1.3;
	dc.GetTextExtent(wxString::Format("%d", rightval), &tw, &th);
	DrawDownThumb(dc, SLIDER_MARGIN + rightslidervalue + 4, h*0.5 - th + 10);
	if (rightval < maxval / 2)
		dc.DrawText(wxString::Format("%d", rightval), SLIDER_MARGIN + rightslidervalue + 20, h*0.5 - th - 4);
	else
		dc.DrawText(wxString::Format("%d", rightval), SLIDER_MARGIN + rightslidervalue - tw - 7, h*0.5 - th - 4);
	//left middle slider:
	double leftmiddleslidervalue = ((double)leftmiddleval / (double)maxval) * (double)w / 1.3;
	dc.GetTextExtent(wxString::Format("%d", leftmiddleval), &tw, &th);
	DrawLeftMiddleThumb(dc, SLIDER_MARGIN + leftmiddleslidervalue + 4, h*0.5 - th + 10);
	if (leftmiddleval < maxval / 2)
		dc.DrawText(wxString::Format("%d", leftmiddleval), SLIDER_MARGIN + leftmiddleslidervalue + 20, h*0.5 - th - 4);
	else
		dc.DrawText(wxString::Format("%d", leftmiddleval), SLIDER_MARGIN + leftmiddleslidervalue - tw - 7, h*0.5 - th - 4);
	//right middle slider:
	double rightmiddleslidervalue = ((double)rightmiddleval / (double)maxval) * (double)w / 1.3;
	dc.GetTextExtent(wxString::Format("%d", rightmiddleval), &tw, &th);
	DrawRightMiddleThumb(dc, SLIDER_MARGIN + rightmiddleslidervalue + 4, h*0.5 - th + 10);
	if (rightmiddleval < maxval / 2)
		dc.DrawText(wxString::Format("%d", rightmiddleval), SLIDER_MARGIN + rightmiddleslidervalue + 20, h*0.5 - th - 4);
	else
		dc.DrawText(wxString::Format("%d", rightmiddleval), SLIDER_MARGIN + rightmiddleslidervalue - tw - 7, h*0.5 - th - 4);
}


void myquadslider::OnLeftDown(wxMouseEvent& event)
{
	int w, h;
	wxClientDC dc(this);
	dc.GetSize(&w, &h);
	double leftslidervalue = ((double)leftval / (double)maxval) * (double)w / 1.3;
	double rightslidervalue = ((double)rightval / (double)maxval) * (double)w / 1.3;
	double leftmiddleslidervalue = ((double)leftmiddleval / (double)maxval) * (double)w / 1.3;
	double rightmiddleslidervalue = ((double)rightmiddleval / (double)maxval) * (double)w / 1.3;
	wxPoint pos = event.GetLogicalPosition(dc);
	pos.x = pos.x - SLIDER_MARGIN;
	pos.y = h - SLIDER_MARGIN - pos.y;

	//if (rightslidervalue > middleslidervalue && middleslidervalue > leftslidervalue) {
	//	if (pos.x <= leftslidervalue) selectedslider = 1;
	//	if (leftslidervalue <= pos.x) selectedslider = 3;
	//	if (middleslidervalue <= pos.x) selectedslider = 2;
	//}

	//else if (leftslidervalue > middleslidervalue && middleslidervalue > rightslidervalue) {
	//	if (pos.x <= rightslidervalue) selectedslider = 2;
	//	if (rightslidervalue <= pos.x) selectedslider = 3;
	//	if (middleslidervalue <= pos.x) selectedslider = 1;
	//}

	//else if (rightslidervalue > leftslidervalue && leftslidervalue > middleslidervalue) {
	//	if (pos.x <= middleslidervalue) selectedslider = 3;
	//	if (middleslidervalue <= pos.x) selectedslider = 1;
	//	if (leftslidervalue <= pos.x) selectedslider = 2;
	//}

	//else if (leftslidervalue > rightslidervalue && rightslidervalue > middleslidervalue) {
	//	if (pos.x <= middleslidervalue) selectedslider = 3;
	//	if (middleslidervalue <= pos.x) selectedslider = 2;
	//	if (rightslidervalue <= pos.x) selectedslider = 1;
	//}

	//else if (middleslidervalue > rightslidervalue && rightslidervalue > leftslidervalue) {
	//	if (pos.x <= leftslidervalue) selectedslider = 1;
	//	if (leftslidervalue <= pos.x) selectedslider = 2;
	//	if (rightslidervalue <= pos.x) selectedslider = 3;
	//}

	//else if (middleslidervalue > leftslidervalue && leftslidervalue > rightslidervalue) {
	//	if (pos.x <= rightslidervalue) selectedslider = 2;
	//	if (rightslidervalue <= pos.x) selectedslider = 1;
	//	if (leftslidervalue <= pos.x) selectedslider = 3;
	//}

	//if (pos.x = leftslidervalue) {
	//	selectedslider = 1;
	//}
	//if (pos.x = rightslidervalue) {
	//	selectedslider = 2;
	//}
	//if (pos.x = leftmiddleslidervalue) {
	//	selectedslider = 3;
	//}
	//if (pos.x = rightmiddleslidervalue) {
	//	selectedslider = 4;
	//}

	//if (pos.x > leftslidervalue) {
	//	if (pos.x <= leftmiddleslidervalue) selectedslider = 3;
	//	if (leftslidervalue <= pos.x) selectedslider = 4;
	//	if (rightmiddleslidervalue <= pos.x) selectedslider = 2;
	//}

	int diffslider1 = pos.x - leftslidervalue;
	int diffslider2 = pos.x - rightslidervalue;
	int diffslider3 = pos.x - leftmiddleslidervalue;
	int diffslider4 = pos.x - rightmiddleslidervalue;

	int absdiffslider1 = abs(diffslider1);
	int absdiffslider2 = abs(diffslider2);
	int absdiffslider3 = abs(diffslider3);
	int absdiffslider4 = abs(diffslider4);

	if (absdiffslider1 < 10) selectedslider = 1;
	if (absdiffslider2 < 10) selectedslider = 2;
	if (absdiffslider3 < 10) selectedslider = 3;
	if (absdiffslider4 < 10) selectedslider = 4;

	prevx = pos.x;
	prevy = pos.y;
	event.Skip();

	//left is 1 leftMiddle is 3 right is 2 rightMiddle is 4
	//24 combinations
	//least to greatest
	//left leftmiddle rightmiddle right
	//left rightmiddle leftmiddle right
	//left leftmiddle right rightmiddle
	//left rightmiddle right leftmiddle
	//left right leftmiddle rightmiddle
	//left right rightmiddle leftmiddle

	//leftmiddle left rightmiddle right
	//leftmiddle left right rightmiddle
	//leftmiddle rightmiddle left right
	//leftmiddle right left right middle
	//leftmiddle right rightmiddle left
	//leftmiddle rightmiddle right left

	//right leftmiddle rightmiddle left
	//right rightmiddle leftmiddle left
	//right rightmiddle left leftmiddle
	//right leftmiddle left rightmiddle
	//right left rightmiddle leftmiddle
	//right left leftmiddle rightmiddle

	//rightmiddle leftmiddle left right
	//rightmiddle left leftmiddle right
	//rightmiddle left right leftmiddle
	//rightmiddle leftmiddle right left
	//rightmiddle right leftmiddle left
	//rightmiddle right left leftmiddle

}

void myquadslider::OnMotion(wxMouseEvent& event)
{
	int w, h;
	play* spinctrl = (play*)m_parent->GetParent();
	int test = spinctrl->Getstep();
	int m = test;
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
			leftval += m;
			if (leftval < minval)  leftval = minval;
			if (leftval > maxval) leftval = maxval;
		}
		else if (selectedslider == 2) {
			rightval += m;
			if (rightval < minval)  rightval = minval;
			if (rightval > maxval) rightval = maxval;
		}
		else if (selectedslider == 3) {
			leftmiddleval += m;
			if (leftmiddleval < minval)  leftmiddleval = minval;
			if (leftmiddleval > maxval) leftmiddleval = maxval;
		}
		else if (selectedslider == 4) {
			rightmiddleval += m;
			if (rightmiddleval < minval)  rightmiddleval = minval;
			if (rightmiddleval > maxval) rightmiddleval = maxval;
		}
		prevx = pos.x;
		prevy = pos.y;
		Refresh();
		Update();
	}
	event.Skip();
}

void myquadslider::OnLeftUp(wxMouseEvent& event)
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

void myquadslider::OnWheel(wxMouseEvent& event)
{
	int w, h;
	play* spinctrl = (play*)m_parent->GetParent();
	int test = spinctrl->Getstep();
	int m = test;
	//int m = step;
	wxClientDC dc(this);
	dc.GetSize(&w, &h);
	wxPoint pos = event.GetLogicalPosition(dc);
	pos.x = pos.x - SLIDER_MARGIN;
	pos.y = h - SLIDER_MARGIN - pos.y;

	double leftslidervalue = ((double)leftval / (double)maxval) * (double)w / 1.3;
	double rightslidervalue = ((double)rightval / (double)maxval) * (double)w / 1.3;
	double leftmiddleslidervalue = ((double)leftmiddleval / (double)maxval) * (double)w / 1.3;
	double rightmiddleslidervalue = ((double)rightmiddleval / (double)maxval) * (double)w / 1.3;

	int diffslider1 = pos.x - leftslidervalue;
	int diffslider2 = pos.x - rightslidervalue;
	int diffslider3 = pos.x - leftmiddleslidervalue;
	int diffslider4 = pos.x - rightmiddleslidervalue;

	int absdiffslider1 = abs(diffslider1);
	int absdiffslider2 = abs(diffslider2);
	int absdiffslider3 = abs(diffslider3);
	int absdiffslider4 = abs(diffslider4);

	if (absdiffslider1 < 10) selectedslider = 1;
	if (absdiffslider2 < 10) selectedslider = 2;
	if (absdiffslider3 < 10) selectedslider = 3;
	if (absdiffslider4 < 10) selectedslider = 4;

	if (event.GetWheelRotation() > 0)
		m = m; //THESE CHANGE THE STEP SIZE
	else
		m = -m;
	if (absdiffslider1 < 10) {
		leftval -= m;
		if (leftval < minval)  leftval = minval;
		if (leftval >= maxval) leftval = maxval;
	}
	else if (absdiffslider2 < 10) {
		rightval -= m;
		if (rightval > maxval) rightval = maxval;
		if (rightval <= leftval) rightval = maxval;;
	}
	if (absdiffslider3 < 10) {
		leftmiddleval -= m;
		if (leftmiddleval < minval)  leftmiddleval = minval;
		if (leftmiddleval >= maxval) leftmiddleval = maxval;
	}
	else if (absdiffslider4 < 10) {
		rightmiddleval -= m;
		if (rightmiddleval > maxval) rightmiddleval = maxval;
		if (rightmiddleval <= maxval) rightmiddleval = maxval;;
	}

	Refresh();
	Update();
	wxCommandEvent e(wxEVT_SCROLL_CHANGED);
	e.SetEventObject(this);
	e.SetString("update");
	ProcessWindowEvent(e);
	event.Skip();
}


void myquadslider::OnSize(wxSizeEvent& event)
{
	Refresh();
	Update();
}

