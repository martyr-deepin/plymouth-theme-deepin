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
#ifndef ACCESSIBLE_H
#define ACCESSIBLE_H

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

#include <QAccessible>
#include <QAccessibleWidget>
#include <QEvent>
#include <QMouseEvent>
#include <QApplication>
#include <QListView>
#include <DSwitchButton>
#include <DBackgroundGroup>

DWIDGET_USE_NAMESPACE

/**************************************************************************************/
// 构造函数
#define FUNC_CREATE(classname,accessibletype,accessdescription)    Accessible##classname(classname *w) \
        : QAccessibleWidget(w,accessibletype,#classname)\
        , m_w(w)\
        , m_description(accessdescription)\
    {}\
    private:\
    classname *m_w;\
    QString m_description;\

// 左键点击
#define FUNC_PRESS(classobj)     QStringList actionNames() const override{\
        if(!classobj->isEnabled())\
            return QStringList();\
        return QStringList() << pressAction();}\
    void doAction(const QString &actionName) override{\
        if(actionName == pressAction())\
        {\
            QPointF localPos = classobj->geometry().center();\
            QMouseEvent event(QEvent::MouseButtonPress,localPos,Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);\
            QMouseEvent event2(QEvent::MouseButtonRelease,localPos,Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);\
            qApp->sendEvent(classobj,&event);\
            qApp->sendEvent(classobj,&event2);\
        }\
    }\

// 右键点击
#define FUNC_SHOWMENU(classobj)     QStringList actionNames() const override{\
        if(!classobj->isEnabled())\
            return QStringList();\
        return QStringList() << showMenuAction();}\
    void doAction(const QString &actionName) override{\
        if(actionName == showMenuAction())\
        {\
            QPointF localPos = classobj->geometry().center();\
            QMouseEvent event(QEvent::MouseButtonPress,localPos,Qt::RightButton,Qt::RightButton,Qt::NoModifier);\
            QMouseEvent event2(QEvent::MouseButtonRelease,localPos,Qt::RightButton,Qt::RightButton,Qt::NoModifier);\
            qApp->sendEvent(classobj,&event);\
            qApp->sendEvent(classobj,&event2);\
        }\
    }\

// 左键和右键点击
#define FUNC_PRESS_SHOWMENU(classobj)     QStringList actionNames() const override{\
        if(!classobj->isEnabled())\
            return QStringList();\
        return QStringList() << pressAction() << showMenuAction();}\
    void doAction(const QString &actionName) override{\
        if(actionName == pressAction())\
        {\
            QPointF localPos = classobj->geometry().center();\
            QMouseEvent event(QEvent::MouseButtonPress,localPos,Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);\
            QMouseEvent event2(QEvent::MouseButtonRelease,localPos,Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);\
            qApp->sendEvent(classobj,&event);\
            qApp->sendEvent(classobj,&event2);\
        }\
        else if(actionName == showMenuAction())\
        {\
            QPointF localPos = classobj->geometry().center();\
            QMouseEvent event(QEvent::MouseButtonPress,localPos,Qt::RightButton,Qt::RightButton,Qt::NoModifier);\
            QMouseEvent event2(QEvent::MouseButtonRelease,localPos,Qt::RightButton,Qt::RightButton,Qt::NoModifier);\
            qApp->sendEvent(classobj,&event);\
            qApp->sendEvent(classobj,&event2);\
        }\
    }\

// 实现rect接口
#define FUNC_RECT(classobj) QRect rect() const override{\
        if (!classobj->isVisible())\
            return QRect();\
        return classobj->geometry();\
    }

// 启用accessible
#define GET_ACCESSIBLE(classnamestring,classname)    if (classnamestring == QLatin1String(#classname) && object && object->isWidgetType())\
    {\
        interface = new Accessible##classname(static_cast<classname *>(object));\
    }\

// 启用accessible[指定objectname]---适用同一个类，但objectname不同的情况
#define GET_ACCESSIBLE_BY_OBJECTNAME(classnamestring,classname,objectname)    if (classnamestring == QLatin1String(#classname) && object && (object->objectName() == objectname) && object->isWidgetType())\
    {\
        interface = new Accessible##classname(static_cast<classname *>(object));\
    }\

// 按钮类型的控件[仅有左键点击]
#define SET_BUTTON_ACCESSIBLE_PRESS_DESCRIPTION(classname,accessdescription)  class Accessible##classname : public QAccessibleWidget\
    {\
    public:\
        FUNC_CREATE(classname,QAccessible::Button,accessdescription)\
        QString text(QAccessible::Text t) const override;/*需要单独实现*/\
        FUNC_PRESS(m_w)\
    };\

// 按钮类型的控件[仅有右键点击]
#define SET_BUTTON_ACCESSIBLE_SHOWMENU_DESCRIPTION(classname,accessdescription)  class Accessible##classname : public QAccessibleWidget\
    {\
    public:\
        FUNC_CREATE(classname,QAccessible::Button,accessdescription)\
        QString text(QAccessible::Text t) const override;/*需要单独实现*/\
        FUNC_SHOWMENU(m_w)\
    };\

// 按钮类型的控件[有左键点击和右键点击]
#define SET_BUTTON_ACCESSIBLE_PRESS_SHOEMENU_DESCRIPTION(classname,accessdescription)  class Accessible##classname : public QAccessibleWidget\
    {\
    public:\
        FUNC_CREATE(classname,QAccessible::Button,accessdescription)\
        QString text(QAccessible::Text t) const override;/*需要单独实现*/\
        FUNC_PRESS_SHOWMENU(m_w)\
    };\

// 标签类型的控件
#define SET_LABEL_ACCESSIBLE_WITH_DESCRIPTION(classname,aaccessibletype,accessdescription)  class Accessible##classname : public QAccessibleWidget\
    {\
    public:\
        FUNC_CREATE(classname,aaccessibletype,accessdescription)\
        QString text(QAccessible::Text t) const override;/*需要单独实现*/\
        FUNC_RECT(m_w)\
    };\

// 简化使用
#define SET_BUTTON_ACCESSIBLE_PRESS_SHOWMENU(classname)         SET_BUTTON_ACCESSIBLE_PRESS_SHOEMENU_DESCRIPTION(classname,"")
#define SET_BUTTON_ACCESSIBLE_SHOWMENU(classname)               SET_BUTTON_ACCESSIBLE_SHOWMENU_DESCRIPTION(classname,"")
#define SET_BUTTON_ACCESSIBLE(classname)                        SET_BUTTON_ACCESSIBLE_PRESS_DESCRIPTION(classname,"")

#define SET_LABEL_ACCESSIBLE(classname)                         SET_LABEL_ACCESSIBLE_WITH_DESCRIPTION(classname,QAccessible::StaticText,"")
#define SET_FORM_ACCESSIBLE(classname)                          SET_LABEL_ACCESSIBLE_WITH_DESCRIPTION(classname,QAccessible::Form,"")
#define SET_SLIDER_ACCESSIBLE(classname)                        SET_LABEL_ACCESSIBLE_WITH_DESCRIPTION(classname,QAccessible::Slider,"")
#define SET_SEPARATOR_ACCESSIBLE(classname)                     SET_LABEL_ACCESSIBLE_WITH_DESCRIPTION(classname,QAccessible::Separator,"")
/**************************************************************************************/
using MainWindow = DCC_NAMESPACE::MainWindow;
using MultiSelectListView = dcc::widgets::MultiSelectListView;
using PersonalizationList = DCC_NAMESPACE::personalization::PersonalizationList;
using PersonalizationGeneral = DCC_NAMESPACE::personalization::PersonalizationGeneral;
using PerssonalizationThemeWidget = DCC_NAMESPACE::personalization::PerssonalizationThemeWidget;
using ThemeItem = DCC_NAMESPACE::personalization::ThemeItem;
using ThemeItemPic = DCC_NAMESPACE::personalization::ThemeItemPic;
using RoundColorWidget = DCC_NAMESPACE::personalization::RoundColorWidget;
using SettingsItem = dcc::widgets::SettingsItem;
using DCCSlider = dcc::widgets::DCCSlider;

// 添加accessible
SET_FORM_ACCESSIBLE(MainWindow)
SET_FORM_ACCESSIBLE(PersonalizationList)
SET_FORM_ACCESSIBLE(PersonalizationGeneral)
SET_FORM_ACCESSIBLE(PerssonalizationThemeWidget)
SET_SLIDER_ACCESSIBLE(DCCSlider)
SET_FORM_ACCESSIBLE(ThemeItem)
SET_BUTTON_ACCESSIBLE(ThemeItemPic)
SET_BUTTON_ACCESSIBLE(RoundColorWidget)
SET_FORM_ACCESSIBLE(SettingsItem)

SET_FORM_ACCESSIBLE(DBackgroundGroup)
SET_BUTTON_ACCESSIBLE(QWidget)
SET_BUTTON_ACCESSIBLE(DSwitchButton)

#endif // ACCESSIBLE_H
