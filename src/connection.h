/*
 * connection.h - the header file of Connection class
 *
 * Copyright (C) 2014, Symeon Huang <hzwhuang@gmail.com>
 *
 * This file is part of the libQtShadowsocks.
 *
 * libQtShadowsocks is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * libQtShadowsocks is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pdnsd; see the file COPYING. If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include "encryptor.h"

using namespace QSS;

namespace QSS {

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QTcpSocket *localTcpSocket, QObject *parent = 0);

    qintptr socketDescriptor;

public slots:
    void appendTcpSocket(QTcpSocket *);

signals:
    void disconnected();
    void info(const QString &);
    void error(const QString &);

private:
    QTcpSocket *local;
    QTcpSocket *remote;
    Encryptor *encryptor;
    static const qint64 RecvSize = 32736;//32KB, same as shadowsocks-python

private slots:
    void onRemoteTcpSocketError();
    void onRemoteTcpSocketReadyRead();
    void onLocalTcpSocketError();
    void onLocalTcpSocketReadyRead();
    void onHandshaked();
    void onHandshaked2();
};

}
#endif // CONNECTION_H