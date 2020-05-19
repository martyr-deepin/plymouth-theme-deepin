/*
 * Copyright (C) 2011 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *
 * Maintainer: sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
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

#ifndef POWERDISPLAYWIDGET_H
#define POWERDISPLAYWIDGET_H

#include "widgets/settingsitem.h"
#include <dswitchbutton.h>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

namespace dcc {
namespace widgets {

class PowerDisplayWidget : public SettingsItem
{
    Q_OBJECT

public:
//    explicit SwitchWidget(QWidget *parent = nullptr);
    explicit PowerDisplayWidget(const QString &title, QWidget *parent = nullptr);
    explicit PowerDisplayWidget(QWidget *parent = nullptr, QLabel *leftwidget = nullptr, QLabel *rightWidget = nullptr);
    void setTitle(const QString &title);
    void setText(const QString &text);

private:
    QLabel *m_leftWidget;
    QLabel *m_rightWidget;
};
}
}

#endif // POWERDISPLAYWIDGET_H

