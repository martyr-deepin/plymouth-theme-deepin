/*
 * Copyright (C) 2019 ~ 2020 Deepin Technology Co., Ltd.
 *
 * Author:     liuxueming <liuxueming@uniontech.com>
 *
 * Maintainer: liuxueming <liuxueming@uniontech.com>
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
#include "formatsetting.h"
#include "modules/datetime/datetimemodel.h"
#include "modules/datetime/timezoneitem.h"
#include "widgets/titlelabel.h"
#include "widgets/comboxwidget.h"
#include "widgets/settingsgroup.h"
#include <QVBoxLayout>
#include <QComboBox>
using namespace dcc::datetime;
using namespace DCC_NAMESPACE::datetime;
using namespace dcc::widgets;
/*格式说明
weekdayFormat   0 星期一 (默认项），1周一
shortDateFormat 0  2020/4/5（默认项）/ 1; 2020-4-5;2   2020.4.5;3  2020/04/05;4  2020-04-05
;5 2020.04.05;6  20/4/5;7  20-4-5;8 20.4.5
longDateFormat  0 2020年4月5日（默认项）;1 2020年4月5日 星期三,2  星期三 020年4月5日
shortTimeFormat 0 9:40（默认项)1, 09:40
longTimeFormat  0 9:40:07（默认项）;1  09:40:07
*/

FormatSetting::FormatSetting(DatetimeModel *mdoel, QWidget *parent)
    : QWidget(parent)
    , m_layout(new QVBoxLayout)
    , mModel(mdoel)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    TitleLabel *headTitle = new TitleLabel(tr("TIME Format Setting"));     //时间格式设置
    QLabel *txtLbael = new QLabel("Format the date  you see in the system bar"); //设置您在系统栏中看到的日期格式
    m_layout->setSpacing(10);
    m_layout->setMargin(0);
    m_layout->addWidget(headTitle, 0, Qt::AlignLeft);
    m_layout->addWidget(txtLbael, 0, Qt::AlignLeft);
    m_layout->setSpacing(2);

    QVBoxLayout *vbox = new QVBoxLayout;
    m_weekCbx = new ComboxWidget();

    m_weekCbx->setTitle(tr("Weeks"));   //星期


    m_shortDateCbx = new ComboxWidget();
    m_shortDateCbx->setTitle(tr("short data"));  //短日期

    m_longdateCbx = new ComboxWidget();
    m_longdateCbx->setTitle(tr("longdata"));  //长日期


    m_shortimeCbx = new ComboxWidget();
    m_shortimeCbx->setTitle(tr("short time"));  //短时间

    m_longtimeCbx = new ComboxWidget();
    m_longtimeCbx->setTitle(tr("long time"));  //长时间


    vbox->addWidget(m_weekCbx);
    vbox->addWidget(m_longdateCbx);
    vbox->addWidget(m_shortDateCbx);
    vbox->addWidget(m_longtimeCbx);
    vbox->addWidget(m_shortimeCbx);
    SettingsItem *timeItem = new SettingsItem;
    timeItem->setLayout(vbox);
    m_layout->addWidget(timeItem);

    m_layout->addStretch(0);
    initComboxWidgetList();
    setLayout(m_layout);
}

void FormatSetting::initComboxWidgetList()
{
    int formatcount = 2;
    for (int i = 0; i < formatcount; i++) {
        m_weekCbx->comboBox()->addItem(fotmatWeek(i));
    }
    m_weekCbx->comboBox()->setCurrentIndex(mModel->weekdayFormatType());
    connect(m_weekCbx->comboBox(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &FormatSetting::weekdayFormatChanged);
    int shortdatecount = 9;
    for (int i = 0; i < shortdatecount; i++) {
        m_shortDateCbx->comboBox()->addItem(fotmatShortDate(i));
    }
    m_shortDateCbx->comboBox()->setCurrentIndex(mModel->shortDateFormat());
    connect(m_shortDateCbx->comboBox(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &FormatSetting::shortDateFormatChanged);
    int longdatecount = 3;
    for (int i = 0; i < longdatecount; i++) {
        m_longdateCbx->comboBox()->addItem(fotmatLongDate(i));
    }
    m_longdateCbx->comboBox()->setCurrentIndex(mModel->longDateFormat());
    connect(m_longdateCbx->comboBox(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &FormatSetting::longDateFormatChanged);
    int longtimecount = 2;
    for (int i = 0; i < longtimecount; i++) {
        m_longtimeCbx->comboBox()->addItem(fotmatLongTime(i));
    }
    m_longtimeCbx->comboBox()->setCurrentIndex(mModel->longTimeFormat());
    connect(m_longtimeCbx->comboBox(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &FormatSetting::longTimeFormatChanged);
    int shorttimecount = 2;
    for (int i = 0; i < shorttimecount; i++) {
        m_shortimeCbx->comboBox()->addItem(fotmatShortTime(i));
    }
    m_shortimeCbx->comboBox()->setCurrentIndex(mModel->shorTimeFormat());
    connect(m_shortimeCbx->comboBox(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &FormatSetting::shortTimeFormatChanged);
}

QString FormatSetting::fotmatWeek(int type)
{
    QString day("");
    switch (type) {
    case 0:
        day = tr("Sunday"); //星期天
        break;
    case 1:
        day = tr("sunday"); //周天
        break;
    default:
        break;
    }
    return day;
}

QString FormatSetting::fotmatLongDate(int type)
{
    QString date("");
    switch (type) {
    case 0:
        date = tr("2020year4month5day");
        break;
    case 1:
        date = tr("2020year4month5day Sunday");
        break;
    case 2:
        date = tr("Sunday 2020year4month5day");
        break;
    default:
        break;
    }

    return date;
}

QString FormatSetting::fotmatShortDate(int type)
{
    QString date("");
    switch (type) {
    case 0:
        date = tr("2020/4/5");
        break;
    case 1:
        date = tr("2020-4-5");
        break;
    case 2:
        date = tr("2020.4.5");
        break;
    case 3:
        date = tr("2020/04/05");
        break;
    case 4:
        date = tr("2020-04-05");
        break;
    case 5:
        date = tr("2020.04.05");
        break;
    case 6:
        date = tr("20/4/5");
        break;
    case 7:
        date = tr("20-4-5");
        break;
    case 8:
        date = tr("20.4.5");
        break;
    default:
        break;
    }
    return date;
}

QString FormatSetting::fotmatLongTime(int type)
{
    QString time("");
    switch (type) {
    case 0: {
        if (mModel->get24HourFormat()) {
            time = tr("9:40:07");
        } else
            time = tr("AM 9:40:07");
        break;
    }
    case 1: {
        if (mModel->get24HourFormat()) {
            time = tr("09:40:07");
        } else
            time = tr("AM 09:40:07");
        break;
    }
    default:
        break;
    }
    return time;
}

QString FormatSetting::fotmatShortTime(int type)
{
    QString time("");
    switch (type) {;
    case 0: {
        if (mModel->get24HourFormat()) {
            time = tr("9:40");
        } else {
            time = tr("AM 9:40");
        }
        break;
    }
    case 1: {
        if (mModel->get24HourFormat()) {
            time = tr("09:40");
        } else {
            time = tr("AM 09:40");
        }
        break;
    }
    default:
        break;
    }
    return time;

}
void FormatSetting::setCururentWeekdayFormat(int type)
{
    if (m_weekCbx && m_weekCbx->comboBox()->count() > type) {
        m_weekCbx->blockSignals(true);
        m_weekCbx->comboBox()->setCurrentIndex(type);
        m_weekCbx->blockSignals(false);
    }
}
void FormatSetting::setCururentShortDateFormat(int type)
{
    if (m_shortDateCbx && m_shortDateCbx->comboBox()->count() > type) {
        m_shortDateCbx->blockSignals(true);
        m_shortDateCbx->comboBox()->setCurrentIndex(type);
        m_shortDateCbx->blockSignals(false);
    }
}
void FormatSetting::setCururentLongDateFormat(int type)
{
    if (m_longdateCbx && m_longdateCbx->comboBox()->count() > type) {
        m_longdateCbx->blockSignals(true);
        m_longdateCbx->comboBox()->setCurrentIndex(type);
        m_longdateCbx->blockSignals(false);
    }
}
void FormatSetting::setCururentLongTimeFormat(int type)
{
    if (m_longtimeCbx && m_longtimeCbx->comboBox()->count() > type) {
        m_longtimeCbx->blockSignals(true);
        m_longtimeCbx->comboBox()->setCurrentIndex(type);
        m_longtimeCbx->blockSignals(false);
    }
}
void FormatSetting::setCururentShortTimeFormat(int type)
{
    if (m_shortimeCbx && m_shortimeCbx->comboBox()->count() > type) {
        m_shortimeCbx->blockSignals(true);
        m_shortimeCbx->comboBox()->setCurrentIndex(type);
        m_shortimeCbx->blockSignals(false);
    }
}

void FormatSetting::resetUi()
{
    if(m_weekCbx)
    {
        disconnect(m_weekCbx->comboBox(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this, &FormatSetting::weekdayFormatChanged);
        m_weekCbx->comboBox()->clear();
    }
    if(m_shortDateCbx){
        disconnect(m_shortDateCbx->comboBox(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this, &FormatSetting::shortDateFormatChanged);
        m_shortDateCbx->comboBox()->clear();
    }
    if(m_longdateCbx){
        disconnect(m_longdateCbx->comboBox(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this, &FormatSetting::longDateFormatChanged);
        m_longdateCbx->comboBox()->clear();
    }
    if(m_longtimeCbx){
        disconnect(m_longtimeCbx->comboBox(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this, &FormatSetting::longTimeFormatChanged);
        m_longtimeCbx->comboBox()->clear();
    }
    if(m_shortimeCbx){
        disconnect(m_shortimeCbx->comboBox(), static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                this, &FormatSetting::shortTimeFormatChanged);
        m_shortimeCbx->comboBox()->clear();
    }
    initComboxWidgetList();
}


