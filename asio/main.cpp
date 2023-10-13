#include <asio.hpp>
#include <iostream>

int main(int argc, char ** argv)
{
    //====================================================
    // Asio's works by having a context run
    // "tasks", you can think of it like
    // a queue of functional objects that get called
    //
    //
    asio::io_context io;

    // calling asio::post will
    // add a functional object onto the
    // queue to be called.
    asio::post(io,[]()
    {
        std::cout << "Posted" << std::endl;
    });

    // when we call run
    // it will execute what's on the queue
    // until there are no more tasks left
    io.run();
    //====================================================

    //====================================================
    // since io.run() returned
    // it is no longer usable until
    // you call restart()
    io.restart();
    //====================================================


    // asio provides a Handler which can call
    // another function after a timer has elapsed
    for(size_t i=0;i<50;i++)
    {
        // we are going to create the timer as a shared object
        // and give it an expiry time of 5 seconds
        auto t = std::make_shared<asio::steady_timer>(io, asio::chrono::seconds(5));

        // we will then tell the timer to execute this lambda
        // when the timer expires.
        // We are also going to pass the timer object into the
        // lambda so that it can free the memory
        // when it it finished
        t->async_wait( [t](auto & ec)
        {
            std::cout << "Lambda called on Thread: " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        });
    }
    std::cout << "Multiple Timers primed" << std::endl;

    // the io_context can be be called from
    // mulitple threads. each thread will execute
    // a task object on the queue
    std::thread t1([&io](){io.run();});
    std::thread t2([&io](){io.run();});
    t1.join();
    t2.join();

    return 0;
}

