#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H


#include <QtGui/QDialog>
#include <QtGui/QWidget>
#include <QtGui/QListView>
#include <QtGui/QStyledItemDelegate>
#include <QList>

#include "ioptionspage.h"

//forward declaration of classes
class QLabel;
class QHBoxLayout;
class QStackedLayout;
class QEvent;
class QModelIndex;
class QStyleOptionViewItem;
class CategoryListView;
class QString;

class IOptionsPage;
class IOptionsPageProvider;
class QTabWidget;
class QIcon;
class QSize;



class SettingsDialog: public QDialog {
Q_OBJECT

public:
    SettingsDialog(QWidget *parent);
    virtual ~SettingsDialog(); 
    
    QDialog::DialogCode showDialog();
    
private slots:
  void done(int val);
  void accept();
  void apply();
  int exec();
  //void open();
  void reject();  
  
private: 
  
  QLabel *header_label;
  QHBoxLayout *headerHLayout;
  QStackedLayout *stackedLayout;
  CategoryListView *categoryListView;
  
  
  void createGui();
  //void accept();
  //void reject();
  //void apply();
  //void currentChanged(const QModelIndex &current);
  //void currentTabChanged(int);
  //void filter(const QString &text);
  
  //void createGui();
  //void showCategory(int index);
  //void showPage(Id pageId);
  //void updateEnabledTabs(Category *category, const QString &searchText);
  //void ensureCategoryWidget(Category *category);
  //void disconnectTabWidgets();  
};


/*
 * These classes are taken from the QtCreator 3.3.2 
 * source: plugins/coreplugin/dialogs/settingsdialog.cpp
 * 
 */

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