#ifndef UDPSERVER_H
#define UDPSERVER_H
#include <boost/asio.hpp>
#include <vector>
#include <boost/array.hpp>
#include <thread>

class UdpServer
{
public:

    //maxDataSize is max request data size
    UdpServer(int port, int maxDataSize);
    //start server with call back function
    // this will call callback with raw data
    void start(std::function<void(std::vector<char>)> callback);

    //start server with call back fucntion what will return response data
    // all data is raw data
    // this can be used for hosting multiple clients
    void startaWithReply(std::function<std::vector<char>(std::vector<char>)> callback);
private:

    //this will keep client data and endpoint
    struct EndPointData
    {
        boost::asio::ip::udp::endpoint remoteEndpoint;
        std::vector<char> data;
        EndPointData( std::vector<char> data)
        {
            this->data = data;
        }
    };

    bool m_withReply = false;
    bool m_running = false;
    int m_port;
    int m_maxDataSize;
    boost::asio::io_service m_ioService;
    std::unique_ptr<boost::asio::ip::udp::socket> m_socket_ptr;
    std::thread m_runThread;

    std::function<void(std::vector<char>)> m_callback;
    std::function<std::vector<char>(std::vector<char>)> m_callbackWithReply;

    void handleReceive(const boost::system::error_code &error, size_t bytesReceived,
                       std::shared_ptr<EndPointData> endPointData);
    void startReceive();
};

#endif // UDPSERVER_H
