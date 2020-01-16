/*
 * Copyright (C) 2011 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     sbw <sbw@sbw.so>
 *             kirigaya <kirigaya@mkacg.com>
 *             Hualet <mr.asianwang@gmail.com>
 *             Chris Xiong <chirs241097@gmail.com>
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

#include "scalingpage.h"
#include "displaymodel.h"
#include "monitor.h"
#include "displaywidget.h"
#include "widgets/dccslider.h"
#include "widgets/settingsheaderitem.h"
#include "widgets/settingsgroup.h"

const float MinScreenWidth = 1024.0f;
const float MinScreenHeight = 768.0f;

using namespace dcc::widgets;

namespace dcc {

namespace display {

ScalingPage::ScalingPage(QWidget *parent)
    : ContentWidget(parent),
      m_centralLayout(new QVBoxLayout)
{
    m_centralLayout->setMargin(0);
    m_centralLayout->setSpacing(10);
    m_centralLayout->addSpacing(10);

    QWidget *w = new TranslucentFrame;
    w->setLayout(m_centralLayout);

    m_slidersgrp = new SettingsGroup;
    m_centralLayout->addWidget(m_slidersgrp);

    tip = new TipsLabel(tr("Some applications in multi-screens may not scale as the settings."), this);
    tip->setWordWrap(true);
    tip->setContentsMargins(16, 5, 10, 5);
    tip->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    m_centralLayout->addWidget(tip, 0, Qt::AlignTop);

    setTitle(tr("Display Scaling"));
    setContent(w);
}

void ScalingPage::setModel(DisplayModel *model)
{
    m_displayModel = model;

    setupSliders();
}

void ScalingPage::setupSliders()
{
    for(auto& s : m_sliders)
        delete s;
    m_sliders.clear();
    for(int i = 0; i < m_displayModel->monitorList().size(); ++i)
        addSlider(i);
}

void ScalingPage::addSlider(int monitorID)
{
    Q_UNUSED(monitorID)
    if (m_displayModel->monitorList().size() == 0)
        return;
    m_slider = new TitledSliderItem("");
    const QStringList maxList = {"1.0", "1.25", "1.5", "1.75", "2.0", "2.25", "2.5", "2.75", "3.0"};;
    QStringList fscaleList = maxList;
    for (auto moni : m_displayModel->monitorList()) {
        auto tmode = moni->currentMode();
        auto ts = getScaleList(tmode);
        fscaleList = ts.size() < fscaleList.size() ? ts :fscaleList;
    }
    //如果仅一个缩放值可用，则不显示
    auto scale = m_displayModel->uiScale();
    if (fscaleList.size() == 1 && fabs(scale - 1.0) < 0.000001) {
        tip->setText(tr("The monitor only supports 100% display scaling"));
        return;
    }
    tip->setText(tr("Some applications cannot be scaled with the specified settings in multi-display environment."));
    //如果当前缩放大于可用缩放，则显示至当前缩放
    while(scale > fscaleList.last().toDouble() && fscaleList.size() < maxList.size()) {
        fscaleList.append(maxList.at(fscaleList.size()));
    }
    DCCSlider *slider = m_slider->slider();
    slider->setRange(1, fscaleList.size());
    slider->setType(DCCSlider::Vernier);
    slider->setTickPosition(QSlider::TicksBelow);
    slider->setTickInterval(1);
    slider->setPageStep(1);
    m_slider->setAnnotations(fscaleList);
    m_centralLayout->addWidget(m_slider);
    m_centralLayout->addStretch();

    double scaling = m_displayModel->uiScale();
    if (scaling < 1.0)
        scaling = 1.0;
    slider->setValue(convertToSlider(scaling));

    connect(slider, &DCCSlider::valueChanged, this, [ = ](const int value) {
        Q_EMIT requestUiScaleChange(convertToScale(value));
    });
    connect(m_displayModel, &DisplayModel::uiScaleChanged, this, [ = ](const double scale) {
        slider->blockSignals(true);
        qDebug() << "monitor scaleCahnged ,scale :" << convertToSlider(scale);
        slider->setValue(convertToSlider(scale));
        slider->blockSignals(false);
    });

    for (auto moni : m_displayModel->monitorList()) {
        connect(moni, &Monitor::currentModeChanged, this, &ScalingPage::onResolutionChanged);
    }
}

QStringList dcc::display::ScalingPage::getScaleList(const Resolution &r)
{
    QStringList tvstring;
    tvstring << "1.0"
             << "1.25"
             << "1.5"
             << "1.75"
             << "2.0"
             << "2.25"
             << "2.5"
             << "2.75"
             << "3.0";

    QStringList fscaleList;
    auto maxWScale = r.width() / MinScreenWidth;
    auto maxHScale = r.height() / MinScreenHeight;
    auto maxScale = maxWScale < maxHScale ? maxWScale : maxHScale;
    maxScale = maxScale < 3.0f ? maxScale : 3.0f;
    for (int idx = 0; idx * 0.25f + 1.0f <= maxScale; ++idx) {
        fscaleList << tvstring[idx];
    }
    return  fscaleList;
}

int ScalingPage::convertToSlider(const double value)
{
    //remove base scale (100), then convert to 1-based value
    //with a stepping of 25
    return int(round(double(value * 100 - 100) / 25)) + 1;
}

double ScalingPage::convertToScale(const int value)
{
    return 1.0 + (value - 1) * 0.25;
}

void ScalingPage::onResolutionChanged()
{
    auto pmoni = m_displayModel->monitorList()[0];
    QStringList fscaleList = getScaleList(pmoni->currentMode());
    for (auto moni : m_displayModel->monitorList()) {
        auto ts = getScaleList(moni->currentMode());
        fscaleList = ts.size() < fscaleList.size() ? ts :fscaleList;
    }

    DCCSlider *tslider = m_slider->slider();
    if (fscaleList.size() < tslider->value()) {
        qWarning() << "分辨率被设置，当前缩放会使屏幕过小，大部分窗口将无法被完整显示！";
    } else {
        auto tv = tslider->value();
        tslider->blockSignals(true);
        tslider->setRange(1, fscaleList.size());
        tslider->setValue(tv);
        tslider->blockSignals(false);
        m_slider->setAnnotations(fscaleList);
    }
}

}
}
