#include <restinio/all.hpp>
#include <iostream>

using namespace restinio;

// For fmt::format to be able to use the optional_t< > param
template<typename T>
std::ostream & operator<<(std::ostream & to, const optional_t<T> & v) {
    if(v) to << *v;
    return to;
}


// Create the Router for the REST server.
//
// after the server is set up and is running, you can
// execute the following curl command from bash to get
// a response:
//
// curl 'localhost:8080/data/meter/3215?year=2020&mon=05&day=31'
//
std::unique_ptr<router::express_router_t<> > setupRouter()
{
    auto RESTrouter = std::make_unique<router::express_router_t<>>();

    //Handle a path that looks like
    //
    //  URL/data/meter/37283?year=2020&mon=05&day=31
    RESTrouter->http_get(
            R"(/data/meter/:meter_id(\d+))",
            [](request_handle_t req, auto params)
            {
                const auto qp = parse_query(req->header().query());

                auto meter_id = cast_to<int>(params["meter_id"]);

                auto year     = opt_value<int>(qp, "year");
                auto mon      = opt_value<int>(qp, "mon");
                auto day      = opt_value<int>(qp, "day");

                auto outString = fmt::format("meter_id={} (year={}/mon={}/day={})\n", meter_id, year, mon, day);
                std::cout << "Sending: " << outString << std::endl;

                return req->create_response()
                        .set_body(
                                    outString
                                 )
                        .done();
            });

    RESTrouter->http_post(
            R"(/new)",
            [](request_handle_t req, auto params)
            {
                (void)params;
                const auto qp = parse_query(req->header().query());
                return req->create_response()
                        .set_body(  "new created" )
                        .done();
            });

    RESTrouter->non_matched_request_handler(
            [](request_handle_t req)
            {
                std::cout << "unmatched" << std::endl;
                return req->create_response(restinio::status_not_found()).connection_close().done();
            });

    return RESTrouter;
}



// Run the REST server with the built-in sigterm catrcher
//
//  restinio::run() will block until ctrl-C is pressed
//  after which it will continue
int runWithSigTerm()
{
    auto RESTrouter = setupRouter();


    // run the server on this thread until the user presses Ctrl-C
    // after which shutdown
    restinio::run(
                      restinio::on_thread_pool(4) // Thread pool size is 4 threads.
                                .port(8080)
                                .address("localhost")
                                .request_handler([&](auto req)
                                                 {
                                                     return (*RESTrouter)(req);
                                                 }
                                                )
                );

    std::cout << "Server Shutting Down" << std::endl;
    return 0;
}



// Run the REST server without the sigterm catcher.
// this will run for 5 seconds and then manually shutdown
// the server and clean up resources.
int runWithoutSigTerm()
{
    using my_server_t = restinio::http_server_t<  >;

    auto RESTrouter = setupRouter();

    my_server_t server
    {
       restinio::own_io_context(),
       [&](auto & settings)
       {
          settings.port(8080);
          settings.address("localhost");
          settings.request_handler( [&](request_handle_t req)
                                    {
                                        return (*RESTrouter)(req);
                                        //return req->create_response().set_body("hello!").done();
                                    }
                                  );
       }
    };


    // Create a separate thread to control execution of RESTinio's server.
    std::thread restinio_control_thread{ [&server] {
          // Use restinio::run to launch RESTinio's server.
          // This run() will return only if server stopped from
          // some other thread.
          restinio::run( restinio::on_thread_pool(
                4, // Count of worker threads for RESTinio.
                restinio::skip_break_signal_handling(), // Don't react to Ctrl+C.
                server) // Server to be run.
             );
       }
    };

    // Some application-dependent logic there. Maybe creation of
    // some GUI windows.
    std::cout << "waiting...." << std::endl;
    std::this_thread::sleep_for( std::chrono::seconds(5) );

    // Now RESTinio can be stopped.
    std::cout << "initiate_shutdown...." << std::endl;
    restinio::initiate_shutdown(server);

    // Wait for completeness of RESTinio's shutdown.
    std::cout << "join...." << std::endl;
    restinio_control_thread.join();

    std::cout << "exiting" << std::endl;
    return 0;
}



int main()
{
    std::cout << "Running server for 5 seconds. Pressing Ctrl-C now will immediately exit the program" << std::endl;
    runWithoutSigTerm();


    std::cout << "Running server indefinitely. Pressing Ctrl-C now will catch the signal and exit approprately" << std::endl;
    return runWithSigTerm();

    return 0;
}
