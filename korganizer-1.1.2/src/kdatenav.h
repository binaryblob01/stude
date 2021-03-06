/* 	$Id: kdatenav.h,v 1.16 1999/01/23 05:19:52 pbrown Exp $	 */

#ifndef _KDATENAV_H 
#define _KDATENAV_H

#include <qframe.h>
#include <qdatetm.h>
#include <qlabel.h>

#include "qdatelist.h"
#include "calobject.h"
#include "kpbutton.h"
#include "kdpdatebutton.h"

class KDateNavigator: public QFrame {
   Q_OBJECT
 public:
   KDateNavigator(QWidget *parent=0, CalObject *calendar=0,
		  bool show_week_numbers=FALSE,
		  QDate date=QDate::currentDate(), 
		  const char *name=0);

   ~KDateNavigator();
   const QDateList getSelected();

 public slots:
   void selectDates(const QDateList);
   void selectDates(QDate);
   void addSelection(QDate, int, bool);
   void setShowWeekNums(bool enabled);
   void updateView();
   void updateConfig();
   
 signals:
   void datesSelected(const QDateList);

 protected slots:
   void goNextMonth();
   void goPrevMonth();
   void goNextYear();
   void goPrevYear();
   inline void updateButton(int);

 protected:
   void updateDates();
   void resizeEvent(QResizeEvent *);

 private:
   QFrame   *ctrlFrame;
   KPButton *prevYear;
   KPButton *prevMonth;
   KPButton *nextMonth;
   KPButton *nextYear;
   QLabel *dateLabel;
   QFrame *viewFrame;
   QFrame *headingSep;
   QFrame *weeknumSep;
   QLabel *headings[7];
   QLabel *weeknos[7];
   KDateButton *buttons[42];

   QDateList selectedDates;
   QDate m_MthYr;
   int m_fstDayOfWk;
   bool m_bShowWeekNums;
   bool weekStartsMonday;
   bool showDailyRecurrences;

   int dayNum(int row, int col);
   inline int dayToIndex(int dayNum);
   void fixupSelectedDates(int yr, int mth);

   KDateNavigator(const KDateNavigator & ) {}
   KDateNavigator &operator=(const KDateNavigator &) { return *this; }
   CalObject *calendar;

   const char **curHeaders;
};

#endif



