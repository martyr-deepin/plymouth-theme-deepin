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
#include "numericalsettingwidget.h"
#include "window/utils.h"
#include "widgets/settingsgroup.h"
#include "widgets/settingshead.h"
#include "widgets/comboxwidget.h"
#include "modules/keyboard/checkitem.h"
#include "modules/keyboard/keylabel.h"
#include "modules/keyboard/keyboardmodel.h"
#include <DSuggestButton>
#include <QVBoxLayout>

using namespace DCC_NAMESPACE::keyboard;
using namespace dcc;
using namespace dcc::keyboard;
using namespace dcc::widgets;

NumericalSettingWidget::NumericalSettingWidget(KeyboardModel *model, QWidget *parent)
    : QWidget(parent)
    , m_model(model)
    , m_dccSettings(new QGSettings("com.deepin.dde.control-center", QByteArray(), this))
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(20);
    layout->setMargin(0);

    QHBoxLayout *headLayout = new QHBoxLayout();
    headLayout->setMargin(0);
    TitleLabel *headTitle = new TitleLabel(tr("Number and Currency Formats"));   //数值显示设置
    headLayout->addWidget(headTitle);
    //headLayout->addStretch();

    layout->addLayout(headLayout);


    layout->setContentsMargins(ThirdPageContentsMargins);
    //layout->addStretch();


    m_numericalSettingsGrp = new SettingsGroup();



    SettingsItem *timeItem = new SettingsItem;
    QVBoxLayout *numlayout = new  QVBoxLayout;
    QLabel *label = new QLabel(tr("Separator"));  //数位分割符
    numlayout->addWidget(label);
    QGridLayout *timeLayout = new QGridLayout;
    /* if (label) {
         label->setFixedWidth(75);
     }
     label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);*/
    //timeLayout->addWidget(label);
    QLabel *label2 = new QLabel(tr("Grouping")); //分位
    /*label2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    label2->setFixedWidth(45);*/
    timeLayout->addWidget(label2, 0, 0, 1, 1, Qt::AlignHCenter);
    m_interCbx = new QComboBox();
    m_interCbx->addItem(",");
    m_interCbx->addItem(".");
    m_interCbx->addItem(" ");
    timeLayout->addWidget(m_interCbx, 0, 1, 1, 2);

    QLabel *label3 = new QLabel(tr("Decimal"));  //小数
    /* label3->setFixedWidth(45);
     label3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);*/
    timeLayout->addWidget(label3, 0, 3, 1, 1, Qt::AlignHCenter);
    m_decimalsCbx = new QComboBox();

    m_decimalsCbx->addItem(".");
    m_decimalsCbx->addItem(",");
    timeLayout->addWidget(m_decimalsCbx, 0, 4, 1, 2);


    QLabel *label4 = new QLabel(tr("Currency")); //货币
    timeLayout->addWidget(label4, 1, 0, 1, 1, Qt::AlignHCenter);
    m_currencyCbx = new QComboBox();
    m_currencyCbx->addItem(tr("RMB"));     //人民币
    m_currencyCbx->addItem(tr("Dollars"));     //美元
    m_currencyCbx->addItem(tr("Pound"));    //英镑
    m_currencyCbx->addItem(tr("Hong Kong dollar"));     //港元
    m_currencyCbx->addItem(tr("Euro"));     //欧元
    m_currencyCbx->addItem(tr("Yen"));     //日元
    m_currencyCbx->addItem(tr("AUD"));    //澳元
    m_currencyCbx->addItem(tr("Canadian dollar"));     //加元
    timeLayout->addWidget(m_currencyCbx, 1, 1, 1, 5);
    numlayout->addLayout(timeLayout);
    timeItem->setLayout(numlayout);
    m_numericalSettingsGrp->appendItem(timeItem);
    // m_numericalSettingsGrp->appendItem(percentile);

    layout->addWidget(m_numericalSettingsGrp);

    QHBoxLayout *hLayout2 = new QHBoxLayout();
    hLayout2->setMargin(0);
    m_label = new QLabel();
    hLayout2->addWidget(m_label, 0, Qt::AlignRight);


    layout->addLayout(hLayout2);
    layout->addStretch();
    QHBoxLayout *hLayout3 = new QHBoxLayout();
    QPushButton *btn = new QPushButton(tr("Cancel"), this);
    hLayout3->addWidget(btn);
    //connect(btn, &QPushButton::clicked, this, &NumericalSettingWidget::reject);
    QPushButton *btn2 = new DSuggestButton(tr("Save"), this);
    connect(btn2, &QPushButton::clicked, this, &NumericalSettingWidget::saveSetting);
    hLayout3->addWidget(btn2);

    layout->addLayout(hLayout3);
    QWidget *widget = new QWidget(this);
    widget->setLayout(layout);
    ContentWidget *contentWidget = new ContentWidget(this);
    contentWidget->setContent(widget);


    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setMargin(0);
    vLayout->addWidget(contentWidget);
    contentWidget->setAttribute(Qt::WA_TranslucentBackground);
    setLayout(vLayout);
    initLabel();
    connect(m_interCbx, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &NumericalSettingWidget::numericalSettingChanged);
    connect(m_decimalsCbx, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &NumericalSettingWidget::numericalSettingChanged);
    connect(m_currencyCbx, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &NumericalSettingWidget::numericalSettingChanged);

}

void NumericalSettingWidget::numericalSettingChanged(int index)
{
    QString text{""};
    switch (m_currencyCbx->currentIndex()) {
    case 0:
        text = "￥";
        break;
    case 1:
        text = "$";
        break;
    case 2:
        text = "￡";
        break;
    case 3:
        text = "HK$";
        break;
    case 4:
        text = "€";
        break;
    case 5:
        text = "￥";
        break;
    case 6:
        text = "$";
        break;
    case 7:
        text = "C$";
        break;
    default:
        break;
    }
    switch (m_interCbx->currentIndex()) {
    case 0:
        text += "99,999";
        break;
    case 1:
        text += "99.999";
        break;
    case 2:
        text += "99999";
        break;
    default:
        break;
    }
    switch (m_decimalsCbx->currentIndex()) {
    case 0:
        text += ".90";
        break;
    case 1:
        text += ",90";
        break;
    default:
        break;
    }
    m_label->setText(text);
}

void NumericalSettingWidget::saveSetting()
{
    int cbxtype = m_currencyCbx->currentIndex();
    int ietertype = m_interCbx->currentIndex();
    int decimalsCbxtype = m_decimalsCbx->currentIndex();
    m_dccSettings->set("currency-format", 2 * ietertype + decimalsCbxtype);
    m_dccSettings->set("currency-type", cbxtype);
}

void NumericalSettingWidget::initLabel()
{
    int currencytype = m_dccSettings->get("currency-type").toInt();
    int currencyformat = m_dccSettings->get("currency-format").toInt();
    int interCbxindex = currencyformat / 2;
    int decimalsCbx = currencyformat % 2 ? 1 : 0;
    this->blockSignals(true);
    m_currencyCbx->setCurrentIndex(currencytype);
    m_interCbx->setCurrentIndex(interCbxindex);
    m_decimalsCbx->setCurrentIndex(decimalsCbx);
    this->blockSignals(false);
    numericalSettingChanged(0);
}
