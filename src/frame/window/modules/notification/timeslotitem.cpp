/*
 * Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     guoyao <guoyao@uniontech.com>
 *
 * Maintainer: guoyao <guoyao@uniontech.com>
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
#include "timeslotitem.h"

#include <DLineEdit>

#include <QCheckBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QTime>

DWIDGET_USE_NAMESPACE
using namespace dcc;
using namespace dcc::widgets;
using namespace DCC_NAMESPACE::notification;

//消息通知时间段项
TimeSlotItem::TimeSlotItem(QWidget *parent)
    : SettingsItem(parent)
    , m_chkState(new QCheckBox)
    , m_editStart(new DLineEdit)
    , m_editEnd(new DLineEdit)
{
    setFixedHeight(45);

    QLabel *lblFrom = new QLabel(tr("From"));
    lblFrom->adjustSize();
    QLabel *lblTo = new QLabel(tr("To"));
    lblTo->adjustSize();

    m_editStart->setMaximumWidth(120);
    m_editEnd->setMaximumWidth(120);

    auto layout = new QHBoxLayout;
    layout->setContentsMargins(10, 0, 10, 0);
    layout->addWidget(m_chkState);
    layout->addWidget(lblFrom);
    layout->addWidget(m_editStart);
    layout->addWidget(lblTo);
    layout->addWidget(m_editEnd);
    layout->addStretch();

    setLayout(layout);

    connect(m_chkState, &QCheckBox::click, this, [ = ]() {
        stateChanged(getState());
    });
    connect(m_editStart, &DLineEdit::textEdited, this, [ = ](const QString & strtime) {
        QTime time = QTime::fromString(strtime, "h:mm");
        if (time.isValid()) {
            Q_EMIT timeStartChanged(time);
        } else {
            m_editStart->showAlertMessage("请输入正确的时间格式：‘0:00’", qobject_cast<QWidget *>(this->parent()));
        }
    });
    connect(m_editEnd, &DLineEdit::textEdited, this, [ = ](const QString & strtime) {
        QTime time = QTime::fromString(strtime, "h:mm");
        if (time.isValid()) {
            Q_EMIT timeEndChanged(time);
        } else {
            m_editStart->showAlertMessage("请输入正确的时间格式：‘0:00’", qobject_cast<QWidget *>(this->parent()));
        }
    });
}

bool TimeSlotItem::getState() const
{
    return m_chkState->isChecked();
}

void TimeSlotItem::setState(const bool &state)
{
    if (getState() != state) {
        m_chkState->setChecked(state);
    }
    Q_EMIT stateChanged(state);
}

QTime TimeSlotItem::getTimeStart() const
{
    return QTime::fromString(m_editStart->text(), "h:mm");
}

void TimeSlotItem::setTimeStart(const QTime &time)
{
    if (QTime::fromString(m_editStart->text()) != time) {
        m_editStart->setText(time.toString("h:mm"));
        Q_EMIT timeStartChanged(time);
    }
}

QTime TimeSlotItem::getTimeEnd() const
{
    return QTime::fromString(m_editEnd->text(), "h:mm");
}

void TimeSlotItem::setTimeEnd(const QTime &time)
{
    if (QTime::fromString(m_editEnd->text()) != time) {
        m_editEnd->setText(time.toString("h:mm"));
        Q_EMIT timeEndChanged(time);
    }
}
