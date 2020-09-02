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

#ifndef NETWORKDETAILPAGE_H
#define NETWORKDETAILPAGE_H

#include "widgets/contentwidget.h"
#include "interface/namespace.h"

namespace dde {
namespace network {
class NetworkModel;
}
}

namespace DCC_NAMESPACE {
namespace network {



class NetworkDetailPage : public dcc::ContentWidget
{
    Q_OBJECT

    enum InterfaceFlags {
        NM_DEVICE_INTERFACE_FLAG_NONE       = 0,       //an alias for numeric zero, no flags set.
        NM_DEVICE_INTERFACE_FLAG_UP         = 0x1,     //the interface is enabled from the administrative point of view. Corresponds to kernel IFF_UP.
        NM_DEVICE_INTERFACE_FLAG_LOWER_UP   = 0x2,     //the physical link is up. Corresponds to kernel IFF_LOWER_UP.
        NM_DEVICE_INTERFACE_FLAG_CARRIER    = 0x10000, //the interface has carrier. In most cases this is equal to the value of @NM_DEVICE_INTERFACE_FLAG_LOWER_UP
    };

public:
    explicit NetworkDetailPage(QWidget *parent = nullptr);

    void setModel(dde::network::NetworkModel *model);

private Q_SLOTS:
    void onActiveInfoChanged(const QList<QJsonObject> &infos);

private:
    QVBoxLayout *m_groupsLayout;
};
}
}
#endif // NETWORKDETAILPAGE_H
