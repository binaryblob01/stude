// $Id: kdpdatebutton.cpp,v 1.23.2.1 1999/04/16 07:45:16 pbrown Exp $	

#include <qstring.h>
#include <kapp.h>
#include "vcaldrag.h"
#include "calobject.h"

#include "kdpdatebutton.h"
#include "kdpdatebutton.moc"

// static member initialization
QPalette KDateButton::my_OrigPalette;
QPalette KDateButton::my_NormalPalette;
QPalette KDateButton::my_HilitePalette;
QPalette KDateButton::my_TodayPalette;
QPalette KDateButton::my_TodaySelectPalette;
QPalette KDateButton::my_EventPalette;
QPalette KDateButton::my_HolidayPalette;
QPalette KDateButton::my_HolidaySelectPalette;
QColorGroup KDateButton::my_NormalGroup;
QColorGroup KDateButton::my_DisabledGroup;
QColorGroup KDateButton::my_HiliteGroup;
QColorGroup KDateButton::my_HiDisabledGroup;
QColorGroup KDateButton::my_TodayGroup;
QColorGroup KDateButton::my_TodaySelectGroup;
QColorGroup KDateButton::my_EventGroup;
QColorGroup KDateButton::my_HolidayGroup;
QColorGroup KDateButton::my_HolidaySelectGroup;


KDateButton::KDateButton(QDate date, int index, CalObject *_calendar,
			 QWidget *parent, const char *name)
  : QLabel(parent, name), QDropSite(this), currHiliteStyle(NoHilite)
{

  selFlag = FALSE;

  calendar = _calendar;

  myFont = font();
  setFrameStyle(QFrame::Box|QFrame::Plain);
  setLineWidth(2);
  setAlignment(AlignCenter);
  my_index = index;
  bt_Date = date;
  QString tstr;
  tstr.setNum(date.day());
  setText(tstr);
  adjustSize();

  my_OrigPalette = palette();
  my_NormalPalette = my_OrigPalette;
  my_HilitePalette = my_NormalPalette;
  my_TodayPalette = my_NormalPalette;
  my_TodaySelectPalette = my_NormalPalette;
  my_EventPalette = my_NormalPalette;
  my_HolidayPalette = my_NormalPalette;
  my_HolidaySelectPalette = my_NormalPalette;
  
  updateConfig();
  
  setPalette(my_NormalPalette);
}

KDateButton::~KDateButton()
{
}

void KDateButton::updateConfig()
{
  KConfig *config = kapp->getConfig();
  config->setGroup ("Colors");
  QColor *tmpColor = new QColor("#cccccc");
  QColor todayColor = config->readColorEntry("Today Color", tmpColor);
  QColor hiliteColor = config->readColorEntry("List Color",
					      &kapp->winStyleHighlightColor());
  delete tmpColor;
  tmpColor = new QColor("#cc3366");
  QColor holidayColor = config->readColorEntry( "Holiday Color", tmpColor);
  
  my_NormalGroup = QColorGroup(my_OrigPalette.normal().base(),
			       my_OrigPalette.normal().base(),
			       my_OrigPalette.normal().base(),
			       my_OrigPalette.normal().base(),
			       my_OrigPalette.normal().base(),
			       my_OrigPalette.normal().dark(),
			       my_OrigPalette.normal().base());
  
  my_DisabledGroup = QColorGroup(my_OrigPalette.normal().base(),
				 my_OrigPalette.normal().base(),
				 my_OrigPalette.normal().base(),
				 my_OrigPalette.normal().base(),
				 my_OrigPalette.normal().base(),
				 my_OrigPalette.normal().mid(),
				 my_OrigPalette.normal().base());
  
  my_HiDisabledGroup = QColorGroup(hiliteColor,
                                   hiliteColor,
				   my_OrigPalette.normal().base(),
				   my_OrigPalette.normal().base(),
				   my_OrigPalette.normal().base(),
				   my_OrigPalette.normal().mid(),
				   my_OrigPalette.normal().base());
  
  my_HiliteGroup = QColorGroup(hiliteColor,
                               hiliteColor,
                               hiliteColor,
                               hiliteColor,
                               hiliteColor,
			       my_OrigPalette.normal().light(),
			       hiliteColor);

  my_TodayGroup = QColorGroup(todayColor,
			      todayColor,
			      my_OrigPalette.normal().dark(),
			      my_OrigPalette.normal().dark(),
			      my_OrigPalette.normal().dark(),
			      my_OrigPalette.normal().light(),
			      my_OrigPalette.normal().base());
  
  my_TodaySelectGroup = QColorGroup(todayColor,
				    hiliteColor,
				    my_OrigPalette.normal().dark(),
				    my_OrigPalette.normal().dark(),
				    my_OrigPalette.normal().dark(),
				    my_OrigPalette.normal().light(),
				    my_OrigPalette.normal().base());
  
  my_EventGroup =  QColorGroup(my_OrigPalette.normal().base(),
			       my_OrigPalette.normal().base(),
			       my_OrigPalette.normal().base(),
			       my_OrigPalette.normal().base(),
			       my_OrigPalette.normal().base(),
			       hiliteColor,
			       my_OrigPalette.normal().base());


  my_HolidayGroup = QColorGroup(my_OrigPalette.normal().base(),
				my_OrigPalette.normal().base(),
				my_OrigPalette.normal().base(),
				my_OrigPalette.normal().base(),
				my_OrigPalette.normal().base(),
				holidayColor,
				my_OrigPalette.normal().base());

  my_HolidaySelectGroup = QColorGroup(holidayColor,
				      hiliteColor,
				      my_OrigPalette.normal().dark(),
				      my_OrigPalette.normal().dark(),
				      my_OrigPalette.normal().dark(),
				      my_OrigPalette.normal().light(),
				      my_OrigPalette.normal().base());

  my_NormalPalette.setNormal(my_NormalGroup);
  my_NormalPalette.setDisabled(my_DisabledGroup);
  
  my_HilitePalette.setNormal(my_HiliteGroup);
  my_HilitePalette.setDisabled(my_HiDisabledGroup);
  
  my_TodayPalette.setNormal(my_TodayGroup);
  my_TodayPalette.setDisabled(my_DisabledGroup);
  
  my_TodaySelectPalette.setNormal(my_TodaySelectGroup);
  my_TodaySelectPalette.setDisabled(my_DisabledGroup);
  
  my_EventPalette.setNormal(my_EventGroup);
  my_EventPalette.setDisabled(my_DisabledGroup);
  
  my_HolidayPalette.setNormal(my_HolidayGroup);
  my_HolidayPalette.setDisabled(my_DisabledGroup);
  my_HolidaySelectPalette.setNormal(my_HolidaySelectGroup);
  my_HolidaySelectPalette.setDisabled(my_HiDisabledGroup);

}

inline QDate KDateButton::date()
{
  return bt_Date;
}

void KDateButton::setItalics(bool ital)
{
  QFont fnt(font());
  fnt.setItalic(ital);
  setFont(fnt);
  update();
}

void KDateButton::setHiliteStyle(int HiliteStyle)
{
  // we have to turn off the boldness of the font here
  // so that it doesn't stay where it shouldn't be.
  myFont.setBold(FALSE);
  setFont(myFont);
  switch(HiliteStyle) {
  case NoHilite:
    setPalette(my_NormalPalette);
    selFlag = FALSE;
    break;
  case EventHilite:    
    myFont.setBold(TRUE);
    setFont(myFont);
    setPalette(my_EventPalette);
    selFlag = FALSE;
    break;
  case SelectHilite:
    setPalette(my_HilitePalette);
    selFlag = TRUE;
    break;
  case TodayHilite:
    setPalette(my_TodayPalette);
    selFlag = FALSE;
    break;
  case TodaySelectHilite:
    setPalette(my_TodaySelectPalette);
    selFlag = TRUE;
    break;
  case HolidayHilite:
    setPalette(my_HolidayPalette);
    selFlag = FALSE;
    break;
  case HolidaySelectHilite:
    setPalette(my_HolidaySelectPalette);
    selFlag = TRUE;
    break;
  default:
    setPalette(my_NormalPalette);
    selFlag = FALSE;
    break;
  }
  currHiliteStyle = HiliteStyle;
  update();
}

inline int KDateButton::hiliteStyle()
{
  return currHiliteStyle;
}

void KDateButton::setDate(QDate date)
{
  bt_Date = date;
  QString tstr;
  tstr.setNum(date.day());
  setText(tstr);
}

void KDateButton::mousePressEvent(QMouseEvent *e)
{
  bool c;

  c = (e->state() & ControlButton);
  // do the actual work.... :)
  emit selected(bt_Date, my_index, c);
}

void KDateButton::dragEnterEvent(QDragEnterEvent *de)
{
  if (VCalDrag::canDecode(de)) {
    de->accept();
  }
  
  // some visual feedback
  oldPalette = palette();
  setPalette(my_HilitePalette);
  update();
}

void KDateButton::dragLeaveEvent(QDragLeaveEvent */*dl*/)
{
  setPalette(oldPalette);
  update();
}

// some of this really doesn't belong here, but rather probably in calobject.
// KOrganizer is starting to get messy.  Needs some major reorganization and
// re-architecting after 1.0.
void KDateButton::dropEvent(QDropEvent *de)
{
  VObject *vcal;

  if (VCalDrag::decode(de, &vcal)) {
    // note that vcal is destroyed in pasteEvent(), so we don't have to
    // free it here.  No leak.
    KDPEvent *newEvent, *oldEvent;

    VObjectIterator i;
    VObject *curvo;
    initPropIterator(&i, vcal);
    
    // we only take the first object.
    do  {
      curvo = nextVObject(&i);
    } while (strcmp(vObjectName(curvo), VCEventProp) &&
	     strcmp(vObjectName(curvo), VCTodoProp));

    if ((curvo = isAPropertyOf(curvo, VCUniqueStringProp))) {
      char *s;
      s = fakeCString(vObjectUStringZValue(curvo));
      oldEvent = calendar->getEvent(s);
      deleteStr(s);
      if (oldEvent) {
	if (oldEvent->doesRecur()) { // only add an exception if it recurs
	  oldEvent->addExDate(bt_Date);
	} else {
	  calendar->deleteEvent(oldEvent); // do the full delete
	}
      }
    }
    newEvent = calendar->pasteEvent(&bt_Date, (QTime *) 0L, vcal);
    updateMe(my_index);
  }
}

