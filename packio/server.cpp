#include <packio/packio.h>
#include <iostream>
#include <thread>

int main(int, char**)
{
    //=============================================================================
    // If defined will use message pack protocol otherwise, will use JSON
    #define USE_MSG_PACK

    // If defined will use unix domain sockets, otherwise will use TCP
    //#define USE_UNIX_DOMAIN

    #define END_POINT_ADDRESS "mysocket"        // socket name to use for unix domains
    #define END_POINT_PORT 43845                // port to use for TCP
    //=============================================================================

    namespace pio = packio;
#if defined USE_MSG_PACK
    namespace protocol = pio::msgpack_rpc;
#else
    namespace protocol = pio::nl_json_rpc;
#endif

#if defined USE_UNIX_DOMAIN
    using transport_t   = packio::net::local::stream_protocol;
#else
    using transport_t = packio::net::ip::tcp;
#endif

    // Declare a server and a client, sharing the same io_context
    pio::net::io_context io;

    transport_t::endpoint bind_ep{
                #if defined USE_UNIX_DOMAIN
        END_POINT_ADDRESS
                #else
                    pio::net::ip::make_address("127.0.0.1"), END_POINT_PORT
                #endif

        };

    //============ Everything below here is the same for protocol/transport types ==============


    //========================================================================
    // Initialize the server
    //========================================================================
    #if defined USE_UNIX_DOMAIN
        // unlink the domain socket in case it still exists
        unlink(END_POINT_ADDRESS);
    #endif
    auto server = protocol::make_server(transport_t::acceptor{io, bind_ep});

    // Declare a synchronous callback with named arguments
    server->dispatcher()->add("add", {"a", "b"},
    [](int a, int b)
    {
        return a + b;
    });

    // Declare an asynchronous callback with named arguments
    server->dispatcher()->add_async(
        "multiply", {"a", "b"},
        [&io](protocol::completion_handler complete, int a, int b)
        {
            // Call the completion handler later
            packio::net::post(
                io, [a, b, complete = std::move(complete)]() mutable {
                    std::this_thread::sleep_for( std::chrono::seconds(4));
                    complete(a * b);
                });
        });

    // Accept connections
    server->async_serve_forever();
    // Run the io_context
    std::thread thread{[&] {
                io.run();
                #if defined USE_UNIX_DOMAIN
                    // unlink the domain socket in case it still exists
                    unlink(END_POINT_ADDRESS);
                #endif
                }};

    //========================================================================
    // Initialize the Client and make some calls to the server
    //========================================================================
    // Make an asynchronous call with named arguments
    auto client = protocol::make_client(transport_t::socket{io});

    // Connect the client
    client->socket().connect(server->acceptor().local_endpoint());

    std::promise<int> add1_result;

    std::cout << "Result retrieved: " << std::this_thread::get_id() << std::endl;
    client->async_call(
        "add",
        #if defined USE_MSG_PACK
        std::tuple{42, 24},
        #else
        std::tuple{pio::arg("a") = 42, pio::arg("b") = 24},
        #endif
        [&](pio::error_code, const protocol::rpc::response_type& r)
        {
            std::cout << "Result retrieved: " << std::this_thread::get_id() << std::endl;
            #if defined USE_MSG_PACK
                add1_result.set_value(r.result.as<int>());
            #else
                add1_result.set_value(r.result.get<int>());
            #endif
        });
    std::cout << "42 + 24 = " << add1_result.get_future().get() << std::endl;




    // Perform the RPC call in a background thread and get the future
    // the future can be used to check the RPC function on the server has
    // completed and a value returned
    auto add_future = client->async_call( "multiply",
                                          #if defined USE_MSG_PACK
                                          std::tuple{12, 23},
                                          #else
                                          std::tuple{ pio::arg("a") = 12, pio::arg("b")= 23},
                                          #endif
                                          packio::net::use_future);

    while( add_future.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "Waiting for RPC call to return" << std::endl;
    }
#if defined USE_MSG_PACK
    std::cout << "12 * 23 = " << add_future.get().result.as<int>() << std::endl;
#else
    std::cout << "12 * 23 = " << add_future.get().result.get<int>() << std::endl;
#endif


    std::this_thread::sleep_for( std::chrono::seconds(10));
    io.stop();
    thread.join();

    return 0;
}
