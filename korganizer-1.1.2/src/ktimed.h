/* 	$Id: ktimed.h,v 1.7 1998/09/18 04:44:57 pbrown Exp $	 */

#ifndef _KTIMED_H
#define _KTIMED_H

#include <qevent.h>
#include <qkeycode.h>
#include <qdatetm.h>
#include <qstring.h>
#include <qcombo.h>
#include <kcombo.h>
#include <qmsgbox.h>
#include <kapp.h>

/** 
 * This is a class that provides an easy, user friendly way to edit times.
 * times are displayed in 12 hour format (i.e. am, pm) but kept internally 
 * in 24 hour format.  up/down/ increase or decrease time, respectively.
 *
 * @short Provides a way to edit times in a user-friendly manner.
 * @author Preston Brown, Ian Dawes
 * @version $Revision: 1.7 $
 *
 */
class KTimeEdit : public QComboBox
{
  Q_OBJECT

public:
  /** constructs a new time edit. */
  KTimeEdit(QWidget *parent=0, QTime qt=QTime(12,0), const char *name=0);
  
  virtual ~KTimeEdit();
  
  /** returns the time that is currently set in the timeLineEdit. */
  QTime getTime(bool &ok);
  
signals:
  /** emitted every time the time displayed changes. "newt" is the new
      time, and wrap specifies whether or not the time has wrapped
      around, and if it has, by how many days. It can be positive,
      negative or zero. Negative indicates a wrap backwards. Positive
      indicates a wrap forwards. 0 indicates no wrap. */
  void timeChanged(QTime newt, int wrap);
 
public slots:
  /** used to set the time which is displayed to a specific value. */
  void setTime(QTime qt);
  void updateConfig();

protected slots: 
  void activ(int);
  void hilit(int); 

protected:
  void insertTimes();
  void addTime(QTime qt);
  void subTime(QTime qt);
  void keyPressEvent(QKeyEvent *qke);
  void validateEntry();
  void updateDisp();
  
  QTime time;                   // the widget's displayed time.
  QTime min_time;               // the widget's lower time bound.
  int  user_inserted;           /* index of the last user typed string
				   if there is one. */
  bool current_display_valid;   /* TRUE if what is currently displayed
				   in the widget corresponds to the
				   stored time, FALSE otherwise. */
  bool timeAmPm;
  KConfig *config;
};

#endif
