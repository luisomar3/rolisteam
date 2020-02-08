/***************************************************************************
 *	Copyright (C) 2019 by Renaud Guezennec                               *
 *   http://www.rolisteam.org/contact                                      *
 *                                                                         *
 *   This software is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef MEDIACONTROLLERINTERFACE_H
#define MEDIACONTROLLERINTERFACE_H

#include <QObject>

#include "data/cleveruri.h"
#include "network/networkreceiver.h"
class QUndoStack;
class MediaControllerInterface : public QObject, public NetWorkReceiver
{
    Q_OBJECT
public:
    MediaControllerInterface(QObject* parent= nullptr) : QObject(parent) {}
    virtual CleverURI::ContentType type() const= 0;
    virtual bool openMedia(CleverURI*, const std::map<QString, QVariant>& args)= 0;
    virtual void closeMedia(const QString& id)= 0;
    virtual void registerNetworkReceiver()= 0;
    virtual void setUndoStack(QUndoStack* stack)= 0;
};

#endif // MEDIACONTROLLERINTERFACE_H
