/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company.  For licensing terms and
** conditions see http://www.qt.io/terms-conditions.  For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, The Qt Company gives you certain additional
** rights.  These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef IOPTIONSPAGE_H
#define IOPTIONSPAGE_H



#include <QObject>
#include <QStringList>

class QIcon;
class QWidget;


class IOptionsPage : public QObject {
    Q_OBJECT

public:
    IOptionsPage(QObject *parent = 0);
    virtual ~IOptionsPage();
    /* 
    * Returns a unique identifier for referencing 
    * the options page. 
    */
    int id() const { return m_id; }
    /* Returns the translated display name of the options page.*/
    QString displayName() const { return m_displayName; }
    /*
    * Returns the unique id for the category that the options page should be displayed in. 
    * This id is used for sorting the list on the left side of the dialog.
    */
    QString category() const { return m_category; }
    /*
     * Returns the translated category name of the options page. 
     * This name is displayed in the list on the left side of the dialog.
    */
    QString displayCategory() const { return m_displayCategory;}
    /*
     * Returns the category icon of the options page. 
     * This icon is displayed in the list on the left side of the dialog.
    */
    QIcon categoryIcon() const;
    /*
     * Is used by the dialog search filter to match 
     * searchKeyWord to this options page. 
     * This defaults to taking the widget and then looking 
     * for all child labels, check boxes, push buttons, 
     * and group boxes. Should return true when a match is found.
    */
    virtual bool matches(const QString &searchKeyWord);
    /*
     * Returns the widget to show in the dialog. 
     * You should create a widget lazily here, and delete it 
     * again in the finish() method. This method can be called 
     * multiple times, so you should only create a new widget 
     * if the old one was deleted.
    */
    virtual QWidget *widget() = 0;
    /*
     * This is called when selecting the Apply button 
     * on the options page dialog. It should detect 
     * whether any changes were made and store those.
    */
    virtual void apply() = 0;
    /*
     * Is called directly before the dialog closes. 
     * Here you should delete the widget that was created 
     * in widget() to free resources.
    */
    virtual void finish() = 0;
    
protected:
    void setId(int id) { m_id = id; }
    void setDisplayName(const QString &displayName) { m_displayName = displayName; }
    void setCategory(QString category) { m_category = category; }
    void setDisplayCategory(const QString &displayCategory) { m_displayCategory = displayCategory; }
    void setCategoryIcon(const QString &categoryIcon) { m_categoryIcon = categoryIcon; }

    int m_id;
    QString m_category;
    QString m_displayName;
    QString m_displayCategory;
    QString m_categoryIcon;

    bool m_keywordsInitialized;
    /*
     * used to store the keywords (e.g. button labels, 
     * check box text, push buttons text, etc) needed for
     * filtering. The user-supplied filter keyword is then
     * matched against this list.
    */
    QStringList m_keywords;
};

/*
 * Alternative way for providing option pages instead of adding 
 * IOptionsPage objects into the plugin manager pool. 
 * Should only be used if creation of the actual option pages 
 * is not possible or too expensive at Qt Creator startup.
 * (Like the designer integration, which needs to initialize 
 * designer plugins before the options pages get available.)
*/

class IOptionsPageProvider : public QObject
{
    Q_OBJECT

public:
    IOptionsPageProvider(QObject *parent = 0) : QObject(parent) {}

    QString category() const { return m_category; }
    QString displayCategory() const { return m_displayCategory; }
    QIcon categoryIcon() const;

    virtual QList<IOptionsPage *> pages() const = 0;
    virtual bool matches(const QString & /* searchKeyWord*/) const = 0;

protected:
    void setCategory(QString category) { m_category = category; }
    void setDisplayCategory(const QString &displayCategory) { m_displayCategory = displayCategory; }
    void setCategoryIcon(const QString &categoryIcon) { m_categoryIcon = categoryIcon; }

    QString m_category;
    QString m_displayCategory;
    QString m_categoryIcon;
};



#endif // IOPTIONSPAGE_H
