module;

#include <string>

#if UNIX_LIKE
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#else
// TO DO Windows
#endif


export module coreRtsp;
import coreException;

namespace core_rtsp
{
    export union protocol
    {

    };

    export struct rtspUrl
    {
        std::string_view url;
        std::string_view username;
        std::string_view password;
        std::string_view ipAddress;
        uint16_t port;
        std::string_view channel;
    };

    export class rtspReceiver
    {
        sockaddr_in socketAddress;
        std::string rtspHost;

    public:
        //! Host example: rtsp://user:pass@192.168.1.1:554/Streaming/Channels/101
        //! rtsp://<user>:<pass>@IPv4:<port>/<channel>
        explicit rtspReceiver(std::string_view host) {

        }

        bool establishConnection() {
            // connectToServer
#if UNIX_LIKE
           connectToServer();

#else
            // TO DO
#endif
            return false;
        }

        // don't allow copying
        rtspReceiver(const rtspReceiver&) = delete;
        rtspReceiver operator=(const rtspReceiver&) = delete;

    private:
        void connectToServer() {
            // https://man7.org/linux/man-pages/man2/socket.2.html
            // int domain, int type, int protocol);
            // AF_INET - IPv4, SOCK_STREAM - socket,
            // 0 protocol,
            // The protocol specifies a particular protocol to be used with the
            // socket.  Normally only a single protocol exists to support a
            // particular socket type within a given protocol family, in which
            // case protocol can be specified as 0.  However, it is possible that
            // many protocols may exist, in which case a particular protocol must
            // be specified in this manner.
            int clientSocket = socket(AF_INET, SOCK_STREAM, 0);

            sockaddr_in serverAddress {};
            serverAddress.sin_family = AF_INET;
            serverAddress.sin_port = htons(8080);
            // to be validated
            auto result = inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

            result = connect(clientSocket, reinterpret_cast<sockaddr *>(&serverAddress), sizeof(serverAddress));
        }
    };
}
