module;

#include <string>

#if UNIX_LIKE
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#else
// TO DO Windows
#endif

export module core_rtsp;

namespace core_rtsp
{
    export class rtspReceiver
    {
        sockaddr_in socketAddress;
        std::string rtspHost;

    public:
        // valid uri: rtsp:
        explicit rtspReceiver(const sockaddr_in socketAddress, const std::string& rtspHost)
            : socketAddress(socketAddress) {

        }

        bool establishConnection() {
            // check if port is open
#if UNIX_LIKE
            // populate sin_addr with IP4 or IP6 in binary form
            inet_pton(socketAddress.sin_family, rtspHost.c_str(), &socketAddress.sin_addr);

            const int socket_endpoint = socket(socketAddress.sin_family, SOCK_STREAM, 0);

            if (socket_endpoint == -1)
            {
                // throw
            }

            // connect to server
            const struct sockaddr_in rtspSocketAddress =
            {
                .sin_family = socketAddress.sin_family,
                .sin_port = socketAddress.sin_port
            };

            auto result =
                connect(socket_endpoint, reinterpret_cast<const sockaddr *>(&rtspSocketAddress), sizeof(rtspSocketAddress));
            if (result != 0)
            {
                // throw
            }
#else
            // TO DO
#endif
            return false;
        }

        // don't allow copying
        rtspReceiver(const rtspReceiver&) = delete;
        rtspReceiver operator=(const rtspReceiver&) = delete;
    };
}
