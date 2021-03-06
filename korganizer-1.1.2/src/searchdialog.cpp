// SearchDialog for KOrganizer
// (c) 1998 by Preston Brown
//

#include <qlayout.h>
#include <qmessagebox.h>
#include <kbuttonbox.h>

#include "searchdialog.h"
#include "searchdialog.moc"

SearchDialog::SearchDialog(CalObject *_cal) :
  QDialog(0, "Search - KOrganizer")
{
  cal = _cal;
  QVBoxLayout *layout = new QVBoxLayout(this, 10);

  QHBoxLayout *subLayout = new QHBoxLayout();
  layout->addLayout(subLayout);

  searchLabel = new QLabel(this, "searchLabel");
  searchLabel->setText(i18n("Search For:"));
  searchLabel->setFixedSize(searchLabel->sizeHint());
  subLayout->addWidget(searchLabel);

  searchEdit = new QLineEdit(this);
  searchEdit->setMinimumWidth(300);
  searchEdit->setFixedHeight(searchEdit->sizeHint().height());
  subLayout->addWidget(searchEdit);
  
  searchButton = new QPushButton(this, "searchButton");
  searchButton->setText(i18n("&Search"));
  searchButton->setFixedHeight(searchButton->sizeHint().height());
  searchButton->setMinimumWidth(searchButton->sizeHint().width());
  searchButton->setDefault(TRUE);
  connect(searchButton, SIGNAL(clicked()),
	  this, SLOT(doSearch()));
  subLayout->addWidget(searchButton);
  
  listView = new BaseListView(cal, this);
  listView->setMinimumWidth(300);
  listView->setMinimumHeight(200);
  layout->addWidget(listView);
  
  QFrame *hLine = new QFrame(this);
  hLine->setFrameStyle(QFrame::HLine | QFrame::Sunken);
  hLine->setMinimumWidth(listView->minimumSize().width());
  hLine->setFixedHeight(hLine->sizeHint().height());
  layout->addWidget(hLine);

  KButtonBox *buttonBox = new KButtonBox(this);
  buttonBox->addStretch();
  QPushButton *okButton = buttonBox->addButton(i18n("&Close"));
  buttonBox->setMinimumWidth(buttonBox->sizeHint().width());
  buttonBox->setFixedHeight(buttonBox->sizeHint().height());
  connect(okButton, SIGNAL(clicked()), SLOT(accept()));
  layout->addWidget(buttonBox);
  
  layout->activate();
  adjustSize();

  listView->showDates();
  searchEdit->setFocus();

  connect(listView, SIGNAL(editEventSignal(KDPEvent *)),
	  this, SIGNAL(editEventSignal(KDPEvent *)));
  connect(listView, SIGNAL(deleteEventSignal(KDPEvent *)),
	  this, SIGNAL(deleteEventSignal(KDPEvent *)));
}

void SearchDialog::doSearch()
{
  QRegExp re;
  QList<KDPEvent> matchedEvents;

  re.setWildcard(TRUE); // most people understand these better.
  re.setCaseSensitive(FALSE);
  re = searchEdit->text();
  if (!re.isValid()) {
    QMessageBox::warning(this, i18n("KOrganizer Error"),
			 i18n("Invalid search expression, cannot perform\n"
			      "the search.  Please enter a search expression\n"
			      "using the wildcard characters '*' and '?'\n"
			      "where needed."));
    return;
  }
  matchedEvents = cal->search(re);

  listView->setEventList(matchedEvents);
}

SearchDialog::~SearchDialog()
{
}

/***************************************************************************/
void SearchDialog::closeEvent(QCloseEvent *)
{
  // we clean up after ourselves...
  emit closed(this);
}

void SearchDialog::updateView()
{
  doSearch();
}

void SearchDialog::cancel()
{
  close();
}
