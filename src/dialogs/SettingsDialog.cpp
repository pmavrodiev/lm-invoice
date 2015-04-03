#include "SettingsDialog.h"

#include <QtGui/QApplication>
#include <QDebug>
#include <QtGui/QFont>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
#include <QtGui/QStyle>
#include <QtGui/QSizePolicy>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QPushButton>
#include <QtGui/QAbstractButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStackedLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QListView>
#include <QtGui/QScrollBar>
#include <QtGui/QListView>
#include <QtGui/QScrollBar>
#include <QEvent>
#include <QtGui/QStyledItemDelegate>
#include <QModelIndex>
#include <QString>
#include <QtGui/QIcon>



/*Some methods to construct this dialog (e.g. fonts, Gui elements) 
 * have been adopted from QCreator's Settings dialog:
   src/plugins/coreplugin/dialogs/settingsdialog.cpp*/

/***
 *** CONSTRUCTORS AND DESTRUCTOR
 */
SettingsDialog::SettingsDialog ( QWidget* parent ) : QDialog ( parent ) {
  header_label = new QLabel;
  stackedLayout = new QStackedLayout;
  categoryListView = new CategoryListView(parent);
}


SettingsDialog::~SettingsDialog() {
  qDebug() << "In ~SettingsDialog";
  delete header_label;
  //delete headerHLayout;
  delete stackedLayout;
  delete categoryListView;
  qDebug() << "Out of ~SettingsDialog";
}


void SettingsDialog::done(int val) {
  QDialog::done(val);
}

void SettingsDialog::accept() {
  qDebug() << "Pressed Accept";
  done(QDialog::Accepted);
}

void SettingsDialog::reject() {
  qDebug() << "Pressed Reject";
  done(QDialog::Rejected);
}

void SettingsDialog::apply() {
  qDebug() << "Pressed Apply";
}

QDialog::DialogCode SettingsDialog::showDialog() {
  createGui();
  exec();
}

int SettingsDialog::exec() {
  return QDialog::exec();
}

void SettingsDialog::createGui() {
  // Header label with large font and 
  //a bit of spacing (align with group boxes)
  QFont headerLabelFont = header_label->font();
  headerLabelFont.setBold(true);
  const int pointSize = headerLabelFont.pointSize();
  if (pointSize > 0)
    headerLabelFont.setPointSize(pointSize+2);
  header_label->setFont(headerLabelFont);
  //
  QHBoxLayout *headerHLayout = new QHBoxLayout;
  const int leftMargin = qApp->style()->pixelMetric(QStyle::PM_LayoutLeftMargin);
  headerHLayout->addSpacerItem(new QSpacerItem(leftMargin, 0, QSizePolicy::Fixed, QSizePolicy::Ignored));
  headerHLayout->addWidget(header_label);
 
  stackedLayout->setMargin(0);
  stackedLayout->addWidget(new QWidget(this)); // no category selected, for example when filtering
 
  QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                                     QDialogButtonBox::Apply |
                                                     QDialogButtonBox::Cancel);
  buttonBox->button(QDialogButtonBox::Ok)->setDefault(true);
  //connect the OK button
  connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
  //connect the Reject button
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
  //connect the Apply button
  connect(buttonBox->button(QDialogButtonBox::Apply), SIGNAL(clicked()),
          this,SLOT(apply()));
  //
  
  QGridLayout *mainGridLayout = new QGridLayout;
  //mainGridLayout->addWidget(m_filterLineEdit, 0, 0, 1, 1);
  mainGridLayout->addLayout(headerHLayout,    0, 1, 1, 1);
  mainGridLayout->addWidget(categoryListView,   1, 0, 1, 1);
  mainGridLayout->addLayout(stackedLayout,  1, 1, 1, 1);
  mainGridLayout->addWidget(buttonBox,        2, 0, 1, 2);
  mainGridLayout->setColumnStretch(1, 4);
  setLayout(mainGridLayout); 
 
  setMinimumSize(1000, 550);
  setWindowTitle(tr("Configure InvoiceGenerator"));
  //if (Utils::HostOsInfo::isMacHost())
  //    setMinimumHeight(minimumHeight() * 1.1);
  
}
/********/

// ----------------- Cateogry List View

/*
 * These classes are taken from the QtCreator 3.3.2 
 * source: plugins/coreplugin/dialogs/settingsdialog.cpp
 * 
 */

bool Category::findPageById(const int id, int *pageIndex) const {
  for (int j = 0; j < pages.size(); ++j) {
    IOptionsPage *page = pages.at(j);
    if (page->id() == id) {
      *pageIndex = j;
       return true;
    }
  }
  return false;
}

Category::Category() {
  index=-1;
  id = -1;
  providerPagesCreated=false;
}



CategoryListViewDelegate::CategoryListViewDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

QSize CategoryListViewDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) {
  QSize size = QStyledItemDelegate::sizeHint(option, index);
  size.setHeight(qMax(size.height(), 32));
  return size;
}

/*
 * The only extension to the QListView is implementing
 * a minimum size policy for the width of the List.
 * The width is constant regardless of the presence of 
 * a vertical scroll bar. In case such a scroll bar is 
 * needed, e.g. when the height of the dialog is change 
 * upon resizing, the width is increased to keep it the same
 * as when a scroll bar is not displayed. 
*/
CategoryListView::CategoryListView(QWidget *parent = 0) : QListView(parent) {
  setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
  setItemDelegate(new CategoryListViewDelegate(this));
  setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}
QSize CategoryListView::sizeHint() const {
  int width = sizeHintForColumn(0) + frameWidth() * 2 + 5;
  if (verticalScrollBar()->isVisible())
    width += verticalScrollBar()->width();
  return QSize(width, 100);
}

// QListView installs a event filter on its scrollbars
bool CategoryListView::eventFilter(QObject *obj, QEvent *event) {
  if (obj == verticalScrollBar()
      && (event->type() == QEvent::Show || event->type() == QEvent::Hide))
        updateGeometry();
  return QListView::eventFilter(obj, event);
}
    

