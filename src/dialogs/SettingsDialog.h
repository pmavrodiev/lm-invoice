#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H


#include <QtGui/QDialog>
#include <QtGui/QWidget>
#include <QtGui/QListView>
#include <QtGui/QStyledItemDelegate>

//forward declaration of classes
class QLabel;
class QHBoxLayout;
class QStackedLayout;
class QEvent;
class QModelIndex;
class QStyleOptionViewItem;
class CategoryListView;
class Qstring;

class SettingsDialog: public QDialog {
Q_OBJECT

public:
    // Returns a settings dialog. This makes sure that always only
    // a single settings dialog instance is running.
    // The dialog will be deleted automatically on close.    
    static SettingsDialog *getSettingsDialog(QWidget *parent);
    
    // Run the dialog and wait for it to finish.
    // Returns if the changes have been applied.
    //bool execDialog();
    QString name;
    QDialog::DialogCode showDialog();
    virtual ~SettingsDialog(); 
    
private slots:
  void done(int val);
  void accept();
  int exec();
  //void open();
  void reject();  
  
private: 
  static SettingsDialog *instance;
  
  QLabel *header_label;
  QHBoxLayout *headerHLayout;
  QStackedLayout *stackedLayout;
  CategoryListView *categoryListView;
  
  SettingsDialog(QWidget *parent);
  
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
 * These two classes are taken from the QtCreator 3.3.2 
 * source: plugins/coreplugin/dialogs/settingsdialog.cpp
 * 
 */

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