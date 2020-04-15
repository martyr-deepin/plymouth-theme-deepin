/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     fpc_diesel <fanpengcheng@uniontech.com>
 *
 * Maintainer: fpc_diesel <fanpengcheng@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "accessible.h"
#define SEPARATOR "_"

QString getAccesibleName(QWidget *w, QAccessible::Role r, QString fallback)
{
    // 避免重复生成
    static QMap< QObject *, QString > objnameMap;
    if (!objnameMap[w].isEmpty())
        return objnameMap[w];

    static QMap< QAccessible::Role, QList< QString > > accessibleMap;
    QString oldAccessName = w->accessibleName();
    oldAccessName.replace(SEPARATOR, "");

    // 按照类型添加固定前缀
    QMetaEnum metaEnum = QMetaEnum::fromType<QAccessible::Role>();
    QByteArray prefix = metaEnum.valueToKeys(r);
    switch (r) {
    case QAccessible::Button:       prefix = "Btn";         break;
    case QAccessible::StaticText:   prefix = "Label";       break;
    default:                        break;
    }

    // 再加上标识
    QString accessibleName = QString::fromLatin1(prefix) + SEPARATOR;
    accessibleName += oldAccessName.isEmpty() ? fallback : oldAccessName;
    // 检查名称是否唯一
    if (accessibleMap[r].contains(accessibleName)) {
        if (objnameMap.key(accessibleName)) {
            objnameMap.remove(objnameMap.key(accessibleName));
            objnameMap.insert(w, accessibleName);
            return accessibleName;
        }
        // 获取编号，然后+1
        int pos = accessibleName.indexOf(SEPARATOR);
        int id = accessibleName.mid(pos + 1).toInt();

        QString newAccessibleName;
        do {
            // 一直找到一个不重复的名字
            newAccessibleName = accessibleName + SEPARATOR + QString::number(++id);
        } while (accessibleMap[r].contains(newAccessibleName));

        accessibleMap[r].append(newAccessibleName);
        objnameMap.insert(w, newAccessibleName);

        return newAccessibleName;
    } else {
        accessibleMap[r].append(accessibleName);
        objnameMap.insert(w, accessibleName);

        return accessibleName;
    }
}

QString AccessibleMainWindow::text(QAccessible::Text t) const
{
    switch (t) {
    case QAccessible::Name:
        return getAccesibleName(m_w, this->role(), "mainwindow");
    case QAccessible::Description:
        return m_description;
    default:
        return QString();
    }
}

QString AccessiblePersonalizationList::text(QAccessible::Text t) const
{
    switch (t) {
    case QAccessible::Name:
        return getAccesibleName(m_w, this->role(), "personalizationlist");
    case QAccessible::Description:
        return m_description;
    default:
        return QString();
    }
}

QString AccessiblePersonalizationGeneral::text(QAccessible::Text t) const
{
    switch (t) {
    case QAccessible::Name:
        return getAccesibleName(m_w, this->role(), "personalizationgeneral");
    case QAccessible::Description:
        return m_description;
    default:
        return QString();
    }
}

QString AccessiblePerssonalizationThemeWidget::text(QAccessible::Text t) const
{
    switch (t) {
    case QAccessible::Name:
        return getAccesibleName(m_w, this->role(), "perssonalizationthemewidget");
    case QAccessible::Description:
        return m_description;
    default:
        return QString();
    }
}

QString AccessibleDCCSlider::text(QAccessible::Text t) const
{
    switch (t) {
    case QAccessible::Name:
        return getAccesibleName(m_w, this->role(), "dccslider");
    case QAccessible::Description:
        return m_description;
    default:
        return QString();
    }
}

QString AccessibleThemeItemPic::text(QAccessible::Text t) const
{
    switch (t) {
    case QAccessible::Name:
        return getAccesibleName(m_w, this->role(), "themeitempic");
    case QAccessible::Description:
        return m_description;
    default:
        return QString();
    }
}

QString AccessibleThemeItem::text(QAccessible::Text t) const
{
    switch (t) {
    case QAccessible::Name:
        return getAccesibleName(m_w, this->role(), "themeitem");
    case QAccessible::Description:
        return m_description;
    default:
        return QString();
    }
}

QString AccessibleRoundColorWidget::text(QAccessible::Text t) const
{
    switch (t) {
    case QAccessible::Name:
        return getAccesibleName(m_w, this->role(), "roundcolorwidget");
    case QAccessible::Description:
        return m_description;
    default:
        return QString();
    }
}

QString AccessibleSettingsItem::text(QAccessible::Text t) const
{
    switch (t) {
    case QAccessible::Name:
        return getAccesibleName(m_w, this->role(), "settingsitem");
    case QAccessible::Description:
        return m_description;
    default:
        return QString();
    }
}

QString AccessibleDBackgroundGroup::text(QAccessible::Text t) const
{
    switch (t) {
    case QAccessible::Name:
        return m_w->objectName();
    case QAccessible::Description:
        return m_description;
    default:
        return QString();
    }
}

QString AccessibleQWidget::text(QAccessible::Text t) const
{
    switch (t) {
    case QAccessible::Name:
        return m_w->objectName();
    case QAccessible::Description:
        return m_description;
    default:
        return QString();
    }
}

QString AccessibleDSwitchButton::text(QAccessible::Text t) const
{
    switch (t) {
    case QAccessible::Name:
        return getAccesibleName(m_w, this->role(), m_w->text());
    case QAccessible::Description:
        return m_description;
    default:
        return QString();
    }
}
