#include "twitch.hpp"

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include <string>

namespace tui {

bool Twitch::auth(std::string_view oauth) const {
    // The io_context is required for all I/O
    boost::asio::io_context ioc;

    // These objects perform our I/O
    boost::asio::ip::tcp::resolver resolver(ioc);
    boost::beast::tcp_stream stream(ioc);

    const std::string host = "https://id.twitch.tv";
    const std::string target = "/oauth2/validate";
    const std::string port = "1935"; // Twitch uses port 1935

    // Look up the domain name
    auto const results = resolver.resolve(host, port);

    // Make the connection on the IP address we get from a lookup
    stream.connect(results);

    // Set up an HTTP GET request message
    boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, target, 11};
    req.set(boost::beast::http::field::host, host);
    req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

    // Send the HTTP request to the remote host
    boost::beast::http::write(stream, req);

    // This buffer is used for reading and must be persisted
    boost::beast::flat_buffer buffer;

    // Declare a container to hold the response
    boost::beast::http::response<boost::beast::http::dynamic_body> res;

    // Receive the HTTP response
    boost::beast::http::read(stream, buffer, res);

    if (res.result() != boost::beast::http::status::ok) {
        // auth did not work!
    }

    // Gracefully close the socket
    boost::beast::error_code ec;
    stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);

    // not_connected happens sometimes
    // so don't bother reporting it.
    //
    if (ec && ec != boost::beast::errc::not_connected)
        throw boost::beast::system_error{ec};

    // If we get here then the connection is closed gracefully

    return true;
}

}  // namespace tui
