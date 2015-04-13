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
#include <QItemSelectionModel>


static QPointer<SettingsDialog> m_instance=0;

static const char pageKeyC[] = "General/LastPreferencePage";
const int categoryIconSize = 24;

/*Some methods to construct this dialog (e.g. fonts, Gui elements) 
 * have been adopted from QCreator's Settings dialog:
   src/plugins/coreplugin/dialogs/settingsdialog.cpp*/

/***
 *** CONSTRUCTORS AND DESTRUCTOR
 */
SettingsDialog::SettingsDialog ( QWidget* parent ) : QDialog ( parent ) {
  m_headerLabel = new QLabel;
  stackedLayout = new QStackedLayout;
  categoryListView = new CategoryListView(parent);
  
  m_model = new CategoryModel(/*parent=*/this);
  //m_pages = sortedOptionsPages();
  m_pages = ExtensionSystem::PluginManager::getObjects<IOptionsPage>();
  

  m_running=false;
  m_applied=false;
  m_finished=false;
  
  createGui();
  setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
  
  m_model->setPages(m_pages,ExtensionSystem::PluginManager::getObjects<IOptionsPageProvider>());
  categoryListView->setIconSize(QSize(categoryIconSize,categoryIconSize));
  //categoryListView->setModel(m_proxyModel);
  categoryListView->setSelectionMode(QAbstractItemView::SingleSelection);
  categoryListView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
  
  connect(categoryListView->selectionModel(),SIGNAL(QItemSelectionModel::currentRowChanged()),
	  this, SLOT(currentChanged(const QModelIndex &)));
  
  categoryListView->setFocus();
}


SettingsDialog::~SettingsDialog() {
  qDebug() << "In ~SettingsDialog";
  delete m_headerLabel;
  //delete headerHLayout;
  delete stackedLayout;
  delete categoryListView;
  if (m_instance)
    delete m_instance;
  qDebug() << "Out of ~SettingsDialog";
}


void SettingsDialog::done(int val) {
  QSettings *settings = ExtensionSystem::PluginManager::getGlobalSettings();
  settings->setValue(QLatin1String(pageKeyC), m_currentPage);

  ExtensionSystem::PluginManager::saveGlobalSettings(); // save all settings 
  QDialog::done(val);
}

void SettingsDialog::accept() {
  qDebug() << "Pressed Accept";
  if (m_finished)
      return;
  m_finished = true;
  disconnectTabWidgets();
  m_applied = true;
  foreach (IOptionsPage *page, m_visitedPages)
      page->apply();
  foreach (IOptionsPage *page, m_pages)
      page->finish();
  
  done(QDialog::Accepted);
}

void SettingsDialog::reject() {
  qDebug() << "Pressed Reject";
  
  if (m_finished)
     return;
  m_finished = true;
  disconnectTabWidgets();
  foreach (IOptionsPage *page, m_pages)
     page->finish();
  
  done(QDialog::Rejected);
}

void SettingsDialog::apply() {
  qDebug() << "Pressed Apply";
  
  foreach (IOptionsPage *page, m_visitedPages)
     page->apply();
  m_applied = true;
}

void SettingsDialog::ensureCategoryWidget(Category* category) {
  if (category->tabWidget != 0)
    return;
  
  if (!category->providerPagesCreated) {
    foreach (const IOptionsPageProvider *provider, category->providers)
            category->pages += provider->pages();
    category->providerPagesCreated = true;    
  }
  
  //qStableSort(category->pages.begin(), category->pages.end(), optionsPageLessThan);
  
  QTabWidget *tabWidget = new QTabWidget;
  for (int j = 0; j < category->pages.size(); ++j) {
     IOptionsPage *page = category->pages.at(j);
     QWidget *widget = page->widget();
     tabWidget->addTab(widget, page->displayName());
  }
  connect(tabWidget,SIGNAL(currentChanged(int)),
	  this,SLOT(currentTabChanged(int)));
  
  category->tabWidget=tabWidget;
  category->index = stackedLayout->addWidget(tabWidget);
  
}

void SettingsDialog::disconnectTabWidgets() {
    foreach (Category *category, m_model->categories()) {
        if (category->tabWidget)
            disconnect(category->tabWidget,SIGNAL(QTabWidget::currentChanged(int)),
		       this,SLOT(currentTabChanged(int)));
    }
}

void SettingsDialog::currentTabChanged(int index) {
    if (index == -1)
        return;

    //const QModelIndex modelIndex = m_proxyModel->mapToSource(m_categoryList->currentIndex());
    //if (!modelIndex.isValid())
    //    return;

    // Remember the current tab and mark it as visited
    const Category *category = m_model->categories().at(m_categoryList->currentIndex().row());
    IOptionsPage *page = category->pages.at(index);
    m_currentPage = page->id();
    m_visitedPages.insert(page);
}

void SettingsDialog::execDialog() {
   if (!m_running) {
        m_running = true;
        m_finished = false;
        exec();
        m_running = false;
        m_instance = 0;
	deleteLater();
   }
}

void SettingsDialog::showPage(int pageId) {
  // handle the case of 'show last page'
  int initialPageId=pageId;
  if (initialPageId == -1) {
    QSettings *settings = ExtensionSystem::PluginManager::getGlobalSettings();
    bool ok;
    initialPageId = settings->value(QLatin1String(pageKeyC)).toInt(&ok);
    if (!ok)
      initialPageId=-1;
  }
  
  int initialCategoryIndex = -1;
  int initialPageIndex = -1;

  const QList<Category*> &categories = m_model->categories();
  if (initialPageId != -1) {
      // First try categories without lazy items.
      for (int i = 0; i < categories.size(); ++i) {
         Category *category = categories.at(i);
         if (category->providers.isEmpty()) {  // no providers
             ensureCategoryWidget(category);
             if (category->findPageById(initialPageId, &initialPageIndex)) {
                 initialCategoryIndex = i;
                 break;
             }
         }
      }
      if (initialPageIndex == -1) {
          // On failure, expand the remaining items.
          for (int i = 0; i < categories.size(); ++i) {
              Category *category = categories.at(i);
              if (!category->providers.isEmpty()) { // has providers
                  ensureCategoryWidget(category);
                  if (category->findPageById(initialPageId, &initialPageIndex)) {
                      initialCategoryIndex = i;
                      break;
                  }
              }
          }
      }
  }
  if (initialPageId != -1 && initialPageIndex == -1)
      return; // Unknown settings page, probably due to missing plugin.
  if (initialPageIndex != -1)
      categories.at(initialCategoryIndex)->tabWidget->setCurrentIndex(initialPageIndex);

  
}


SettingsDialog* SettingsDialog::getSettingsDialog(QWidget* parent, int id_initialPage) {
  if (!m_instance) 
      m_instance = new SettingsDialog(parent);
  m_instance->showPage(id_initialPage);
  return m_instance;  

}



int SettingsDialog::exec() {
  return QDialog::exec();
}

void SettingsDialog::createGui() {
  // Header label with large font and 
  //a bit of spacing (align with group boxes)
  QFont headerLabelFont = m_headerLabel->font();
  headerLabelFont.setBold(true);
  const int pointSize = headerLabelFont.pointSize();
  if (pointSize > 0)
    headerLabelFont.setPointSize(pointSize+2);
  m_headerLabel->setFont(headerLabelFont);
  //
  QHBoxLayout *headerHLayout = new QHBoxLayout;
  const int leftMargin = qApp->style()->pixelMetric(QStyle::PM_LayoutLeftMargin);
  headerHLayout->addSpacerItem(new QSpacerItem(leftMargin, 0, QSizePolicy::Fixed, QSizePolicy::Ignored));
  headerHLayout->addWidget(m_headerLabel);
 
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


/*
 * These classes are taken from the QtCreator 3.3.2 
 * source: plugins/coreplugin/dialogs/settingsdialog.cpp
 * 
 */

// ----------------- Category model

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

Category *CategoryModel::findCategoryById(int id)
{
    for (int i = 0; i < m_categories.size(); ++i) {
        Category *category = m_categories.at(i);
        if (category->id == id)
            return category;
    }

    return 0;
}

// ----------------- CategoryModel


CategoryModel::CategoryModel(QObject *parent)
    : QAbstractListModel(parent) {
    QPixmap empty(categoryIconSize, categoryIconSize);
    empty.fill(Qt::transparent);
    m_emptyIcon = QIcon(empty);
}

CategoryModel::~CategoryModel() {
    qDeleteAll(m_categories);
}

int CategoryModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : m_categories.size();
}

QVariant CategoryModel::data(const QModelIndex &index, int role) const {
    switch (role) {
    case Qt::DisplayRole:
        return m_categories.at(index.row())->displayName;
    case Qt::DecorationRole: {
            QIcon icon = m_categories.at(index.row())->icon;
            if (icon.isNull())
                icon = m_emptyIcon;
            return icon;
        }
    }
    return QVariant();
}



void CategoryModel::setPages(const QList<IOptionsPage*> &pages,
                             const QList<IOptionsPageProvider *> &providers) {
    beginResetModel();

    // Clear any previous categories
    qDeleteAll(m_categories);
    m_categories.clear();

    // Put the pages in categories
    foreach (IOptionsPage *page, pages) {
        //const int categoryId = page->category();
	const int categoryId = page->id();
        Category *category = findCategoryById(categoryId);
        if (!category) {
            category = new Category;
            category->id = categoryId;
            category->tabWidget = 0;
            category->index = -1;
            m_categories.append(category);
        }
        if (category->displayName.isEmpty())
            category->displayName = page->displayCategory();
        if (category->icon.isNull())
            category->icon = page->categoryIcon();
        category->pages.append(page);
    }
    //Populate the pool of IOptionsPages
    foreach (IOptionsPageProvider *provider, providers) {
        const int categoryId = provider->category();
        Category *category = findCategoryById(categoryId);
        if (!category) {
            category = new Category;
            category->id = categoryId;
            category->tabWidget = 0;
            category->index = -1;
            m_categories.append(category);
        }
        if (category->displayName.isEmpty())
            category->displayName = provider->displayCategory();
        if (category->icon.isNull())
            category->icon = provider->categoryIcon();
        category->providers.append(provider);
    }

    endResetModel();
}


// ----------------- Category List View

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
    

