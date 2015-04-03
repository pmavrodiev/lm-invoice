/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Copyright (C) 2015 Falko Arps
** Copyright (C) 2015 Sven Klein
** Copyright (C) 2015 Giuliano Schneider
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

#include "ioptionspage.h"

#include <QCheckBox>
#include <QGroupBox>
#include <QIcon>
#include <QLabel>
#include <QPushButton>
#include <QWidget>



QIcon IOptionsPage::categoryIcon() const {
    return QIcon(m_categoryIcon);
}

/*
    Constructs an options page with the given \a parent.
*/
IOptionsPage::IOptionsPage(QObject *parent)
: QObject(parent), m_keywordsInitialized(false) {

}

/*
    Destroys the options page.
 */
IOptionsPage::~IOptionsPage(){}


bool IOptionsPage::matches(const QString &searchKeyWord)  {
    if (!m_keywordsInitialized) {
        IOptionsPage *that = const_cast<IOptionsPage *>(this);
        QWidget *widget = that->widget();
        if (!widget)
            return false;
        // find common subwidgets
        foreach (const QLabel *label, widget->findChildren<QLabel *>())
            m_keywords << label->text();
        foreach (const QCheckBox *checkbox, widget->findChildren<QCheckBox *>())
            m_keywords << checkbox->text();
        foreach (const QPushButton *pushButton, widget->findChildren<QPushButton *>())
            m_keywords << pushButton->text();
        foreach (const QGroupBox *groupBox, widget->findChildren<QGroupBox *>())
            m_keywords << groupBox->title();

        // clean up accelerators
        QMutableStringListIterator it(m_keywords);
        while (it.hasNext())
            it.next().remove(QLatin1Char('&'));
        m_keywordsInitialized = true;
    }
    foreach (const QString &keyword, m_keywords)
        if (keyword.contains(searchKeyWord, Qt::CaseInsensitive))
            return true;
    return false;
}

QIcon IOptionsPageProvider::categoryIcon() const {
    return QIcon(m_categoryIcon);
}
