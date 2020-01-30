#include "udpserver.h"
#include <boost/bind.hpp>
#include <memory>

using namespace boost::asio::ip;
using namespace boost::asio;
using namespace std;

UdpServer::UdpServer(int port, int maxDataSize)
{
    m_port = port;
    m_maxDataSize = maxDataSize;
}

void UdpServer::start(function<void(vector<char>)> callback)
{
   if (m_running) return;
   m_callback = callback;
   m_socket_ptr =  make_unique<udp::socket>(
               udp::socket(m_ioService, udp::endpoint(udp::v4(), static_cast<unsigned short>(m_port))));
   startReceive();
   //start io Service on other thread
   m_runThread = thread(boost::bind(&boost::asio::io_service::run, boost::ref(m_ioService)));
   m_running = true;

}

void UdpServer::startaWithReply(std::function<std::vector<char> (std::vector<char>)> callback)
{
    if (m_running) return;
    m_callbackWithReply = callback;
    m_socket_ptr =  make_unique<udp::socket>(
                udp::socket(m_ioService, udp::endpoint(udp::v4(), static_cast<unsigned short>(m_port))));
    startReceive();
    //start io Service on other thread
    m_runThread = thread(boost::bind(&boost::asio::io_service::run, boost::ref(m_ioService)));
    m_running = true;
}

void UdpServer::handleReceive(const boost::system::error_code &error,
                              size_t bytesReceived,  std::shared_ptr<EndPointData> endPointData)
{
    if (!error || error == error::message_size)
    {
        vector<char> dataOut;
        dataOut.insert(dataOut.begin(), endPointData.get()->data.begin(),
                        endPointData.get()->data.begin() + static_cast<int>(bytesReceived));

        if (!m_withReply)
        {
            //handel received data
            m_callback(dataOut);
        }
        else
        {
             //handel received data and get response data
            std::vector<char> data2Send = m_callbackWithReply(dataOut);
            if (data2Send.empty())
            {
                startReceive();
                return;
            }
            //send response data to client
            //here we don't need async. just send it and hope it will get it
            m_socket_ptr->send_to(buffer(data2Send, data2Send.size()), endPointData.get()->remoteEndpoint);
        }
    }
    //start start receiving data
    startReceive();
}

void UdpServer::startReceive()
{
    auto endPointData = make_shared<EndPointData>(
                EndPointData(vector<char>(static_cast<size_t>(m_maxDataSize))));

    m_socket_ptr.get()->async_receive_from(
                buffer(endPointData.get()->data, static_cast<size_t>(m_maxDataSize)),
                endPointData.get()->remoteEndpoint,
                boost::bind(&UdpServer::handleReceive, this,
                     boost::asio::placeholders::error,
                     boost::asio::placeholders::bytes_transferred, endPointData));

}
