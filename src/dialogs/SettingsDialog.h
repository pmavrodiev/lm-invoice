#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H


#include <QtGui/QDialog>
#include <QtGui/QWidget>
#include <QtGui/QListView>
#include <QtGui/QStyledItemDelegate>
#include <QList>
#include <QSet>
#include <QtPlugin>
#include <QDebug>
#include <functional>

#include "ioptionspage.h"
#include "../libs/pluginmanager/pluginmanager.h"

//forward declaration of classes
class QLabel;
class QHBoxLayout;
class QStackedLayout;
class QEvent;
class QModelIndex;
class QStyleOptionViewItem;
class QString;
class QTabWidget;
class QIcon;
class QSize;

class CategoryModel;
class CategoryListView;
class IOptionsPage;
class IOptionsPageProvider;
class Category;



/*
// Helpers to sort by category. id
bool optionsPageLessThan(const IOptionsPage *p1, const IOptionsPage *p2) {
    return p1->category() < p2->category();
    //if (p1->category() != p2->category())
    //    return p1->category().alphabeticallyBefore(p2->category());
    //return p1->id().alphabeticallyBefore(p2->id());
}

inline QList<IOptionsPage*> sortedOptionsPages()
{
    QList<IOptionsPage*> rc = ExtensionSystem::PluginManager::getObjects<IOptionsPage>();
    qStableSort(rc.begin(), rc.end(), optionsPageLessThan);
    return rc;
}

*/

class SettingsDialog: public QDialog {
Q_OBJECT

public:
    SettingsDialog(QWidget *parent);
    virtual ~SettingsDialog(); 
    
    static SettingsDialog *getSettingsDialog(QWidget *parent,int id_initialPage);
    void execDialog();
    //QDialog::DialogCode showDialog();
    
private slots:
  void done(int val);
  void accept();
  void apply();
  int exec();
  //void open();
  void reject();
  void currentChanged(const QModelIndex &current) {qDebug() << "current changed";};
  void currentTabChanged(int);
  
private: 
  
  QLabel *m_headerLabel;
  QHBoxLayout *headerHLayout;
  QStackedLayout *stackedLayout;
  CategoryListView *categoryListView;
  CategoryModel *m_model;
  int m_currentCategory;
  int m_currentPage;
  QListView *m_categoryList;
  
  //contains all options pages available in this dialog
  QList<IOptionsPage *> m_pages;
  QSet<IOptionsPage *> m_visitedPages;
  
  bool m_running;
  bool m_applied;
  bool m_finished;
  
  
  void createGui();
  
  //void accept();
  //void reject();
  //void apply();
  //void currentChanged(const QModelIndex &current);
  
  //void filter(const QString &text);
  
  //void showCategory(int index);
  void showPage(int pageId);
  //void updateEnabledTabs(Category *category, const QString &searchText);
  void ensureCategoryWidget(Category *category);
  void disconnectTabWidgets();
  


  
};


/*
 * These classes are taken from the QtCreator 3.3.2 
 * source: plugins/coreplugin/dialogs/settingsdialog.cpp
 * 
 */

// ----------------- Category model
class Category {
public:
    Category();

    bool findPageById(const int id, int *pageIndex) const;

    int id;
    int index;
    QString displayName;
    QIcon icon;
    QList<IOptionsPage *> pages;
    QList<IOptionsPageProvider *> providers;
    bool providerPagesCreated;
    QTabWidget *tabWidget;
};


class CategoryModel: public QAbstractListModel {
private:
    QList<Category *> m_categories;
    QIcon m_emptyIcon;
    
    Category *findCategoryById(int id);
public:
    CategoryModel(QObject *parent = 0);
    ~CategoryModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    void setPages(const QList<IOptionsPage*> &pages,
                  const QList<IOptionsPageProvider *> &providers);
    const QList<Category*> &categories() const { return m_categories; }
  
};


class CategoryListViewDelegate : public QStyledItemDelegate {
public:
    CategoryListViewDelegate(QObject *parent);
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index);
};

/*
 * The only extension to the QListView is implementing
 * a minimum size policy for the width of the List.
 * The width is constant regardless of the presence of 
 * a vertical scroll bar. In case such a scroll bar is 
 * needed, e.g. when the height of the dialog is change 
 * upon resizing, the width is increased to keep it the same
 * as when a scroll bar is not displayed. 
 */
class CategoryListView : public QListView {
public:
    CategoryListView(QWidget *parent);

    virtual QSize sizeHint() const;

    // QListView installs a event filter on its scrollbars
    virtual bool eventFilter(QObject *obj, QEvent *event);
};



#endif