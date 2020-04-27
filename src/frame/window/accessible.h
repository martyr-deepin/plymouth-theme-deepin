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
#include "accessibledefine.h"

#include "./mainwindow.h"
#include "./modules/personalization/personalizationlist.h"
#include "./modules/personalization/personalizationgeneral.h"
#include "./modules/personalization/personalizationthemelist.h"
#include "./modules/personalization/personalizationfontswidget.h"
#include "./modules/personalization/themeitem.h"
#include "./modules/personalization/themeitempic.h"
#include "./modules/personalization/roundcolorwidget.h"
#include "./modules/personalization/perssonalizationthemewidget.h"

#include "./widgets/multiselectlistview.h"
#include "./widgets/settingsitem.h"
#include "./widgets/dccslider.h"

#include <DSwitchButton>

#include <QWidget>
#include <QList>

DWIDGET_USE_NAMESPACE
using namespace DCC_NAMESPACE;
using namespace DCC_NAMESPACE::personalization;
using namespace dcc::widgets;

SET_FORM_ACCESSIBLE(MainWindow,"mainwindow")
SET_FORM_ACCESSIBLE(PersonalizationList,"personalizationlist")
SET_FORM_ACCESSIBLE(PersonalizationGeneral,"personalizationgeneral")
SET_FORM_ACCESSIBLE(PerssonalizationThemeWidget,"perssonalizationthemewidget")
SET_SLIDER_ACCESSIBLE(DCCSlider,"dccslider")
SET_FORM_ACCESSIBLE(ThemeItem,"themeitem")
SET_BUTTON_ACCESSIBLE(ThemeItemPic,"themeitempic")
SET_BUTTON_ACCESSIBLE(RoundColorWidget,"roundcolorwidget")
SET_FORM_ACCESSIBLE(SettingsItem,"settingsitem")
SET_FORM_ACCESSIBLE(DBackgroundGroup,m_w->objectName())
SET_BUTTON_ACCESSIBLE(QWidget,m_w->objectName())
SET_BUTTON_ACCESSIBLE(DSwitchButton,m_w->text())

QAccessibleInterface *accessibleFactory(const QString &classname, QObject *object)
{
    QAccessibleInterface *interface = nullptr;
    USE_ACCESSIBLE(classname, QWidget);
    USE_ACCESSIBLE(QString(classname).replace("dccV20::", ""), MainWindow);
    USE_ACCESSIBLE(QString(classname).replace("Dtk::Widget::", ""), DBackgroundGroup);
    USE_ACCESSIBLE(QString(classname).replace("dccV20::personalization::", ""), PersonalizationList);
    //个性化模块
    USE_ACCESSIBLE(QString(classname).replace("dccV20::personalization::", ""), PersonalizationGeneral);
    USE_ACCESSIBLE(QString(classname).replace("dccV20::personalization::", ""), PerssonalizationThemeWidget);
    USE_ACCESSIBLE(QString(classname).replace("dccV20::personalization::", ""), ThemeItem);
    USE_ACCESSIBLE(QString(classname).replace("dccV20::personalization::", ""), ThemeItemPic);
    USE_ACCESSIBLE(QString(classname).replace("dccV20::personalization::", ""), RoundColorWidget);
    USE_ACCESSIBLE(QString(classname).replace("dcc::widgets::", ""), SettingsItem);
    USE_ACCESSIBLE(QString(classname).replace("dcc::widgets::", ""), DCCSlider);
    USE_ACCESSIBLE_BY_OBJECTNAME(QString(classname).replace("Dtk::Widget::", ""), DSwitchButton, "");
    return interface;
}
