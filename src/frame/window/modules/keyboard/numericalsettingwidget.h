/*
 * Copyright (C) 2019 Deepin Technology Co., Ltd.
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
#ifndef NUMERICALSETTING_H
#define NUMERICALSETTING_H

#include "interface/namespace.h"
#include "widgets/contentwidget.h"

#include <DCommandLinkButton>

#include <DListView>
#include<QComboBox>
#include <QWidget>
#include<QGSettings>
namespace dcc {
namespace keyboard {
class KeyboardModel;
}

namespace widgets {
class SettingsGroup;
}
}

namespace DCC_NAMESPACE {
namespace keyboard {
//NumericalSettingWidget类为数值设置界面类
class NumericalSettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NumericalSettingWidget(dcc::keyboard::KeyboardModel *model, QWidget *parent = nullptr);
Q_SIGNALS:

public Q_SLOTS:
    void  numericalSettingChanged(int index);
    void saveSetting();
private:
    void initLabel();
    dcc::keyboard::KeyboardModel *m_model;
    dcc::widgets::SettingsGroup *m_numericalSettingsGrp;
    QLabel *m_label{nullptr};
    QComboBox *m_interCbx;
    QComboBox *m_decimalsCbx;
    QComboBox *m_currencyCbx;
    QGSettings *m_dccSettings;
};
}
}
#endif // SYSTEMLANGUAGEWIDGET_H
