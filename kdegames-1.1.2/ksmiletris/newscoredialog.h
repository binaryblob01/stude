/****************************************************************
Copyright (c) 1998 Sandro Sigala <ssigala@globalnet.it>.
All rights reserved.

Permission to use, copy, modify, and distribute this software
and its documentation for any purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that the copyright notice and this
permission notice and warranty disclaimer appear in supporting
documentation, and that the name of the author not be used in
advertising or publicity pertaining to distribution of the
software without specific, written prior permission.

The author disclaim all warranties with regard to this
software, including all implied warranties of merchantability
and fitness.  In no event shall the author be liable for any
special, indirect or consequential damages or any damages
whatsoever resulting from loss of use, data or profits, whether
in an action of contract, negligence or other tortious action,
arising out of or in connection with the use or performance of
this software.
****************************************************************/

#ifndef NEWSCOREDIALOG_H
#define NEWSCOREDIALOG_H

#include <qdialog.h>

class QLineEdit;

class NewScoreDialog : public QDialog {
public:
	NewScoreDialog(QWidget *parent=0, const char *name=0);
	const char *name();

private:
	QLineEdit *le;
};

#endif // !NEWSCOREDIALOG_H
