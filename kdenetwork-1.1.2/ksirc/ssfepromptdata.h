/**********************************************************************

	--- Qt Architect generated file ---

	File: ssfepromptdata.h
	Last generated: Thu Jan 15 21:21:29 1998

	DO NOT EDIT!!!  This file will be automatically
	regenerated by qtarch.  All changes will be lost.

 *********************************************************************/

#ifndef ssfepromptdata_included
#define ssfepromptdata_included

#include <qdialog.h>
#include <qlabel.h>
#include <qlined.h>

class ssfepromptdata : public QDialog
{
    Q_OBJECT

public:

    ssfepromptdata
    (
        QWidget* parent = NULL,
        const char* name = NULL
    );

    virtual ~ssfepromptdata();

public slots:


protected slots:

    virtual void terminate();

protected:
    QLabel* prompt;
    QLineEdit* SLine;

};

#endif // ssfepromptdata_included
