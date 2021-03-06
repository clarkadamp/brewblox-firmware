/*
 * Copyright 2018 BrewBlox / Elco Jacobs
 *
 * This file is part of Controlbox.
 *
 * Controlbox is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Controlbox.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "../Connections.h"
#include "spark_wiring_tcpclient.h"
#include "spark_wiring_tcpserver.h"
#include "spark_wiring_wifi.h"

namespace cbox {

class TcpConnection : public StreamConnection<TCPClient> {
public:
    explicit TcpConnection(TCPClient&& _client)
        : StreamConnection<TCPClient>(std::move(_client))
    {
    }
    ~TcpConnection()
    {
        get().flush();
        get().stop();
    }
};

class TcpConnectionSource : public ConnectionSource {
private:
    TCPServer server;
    bool server_started = false;

public:
    TcpConnectionSource(uint16_t port)
        : server(port)
    {
    }

    std::unique_ptr<Connection> newConnection() override final
    {
        if (spark::WiFi.ready() && !spark::WiFi.listening()) {
            if (!server_started) {
                server_started = server.begin();
            }

            TCPClient newClient = server.available();
            if (newClient.connected()) {
                return std::make_unique<TcpConnection>(std::move(newClient));
            }
        } else {
            server_started = false;
        }
        return nullptr;
    }

    void stop() override final
    {
        server.stop();
    }
};

} // end namespace cbox
