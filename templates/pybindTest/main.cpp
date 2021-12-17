#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <pybind11/pybind11.h>
#include <pybind11/embed.h>
#include <filesystem>
#include <stdlib.h>

namespace py = pybind11;

void runPythonScript(std::filesystem::path const & file)
{
    py::scoped_interpreter guard{};

    // The folder the python script is located in
    auto folder = file.parent_path();

    std::string abspath;

    if( folder.is_absolute() )
    {
        abspath = folder.native();
    }
    else
    {
        abspath = (std::filesystem::current_path() / folder).native();
    }


        // the name of the pyhon file without the extension
    auto module = file.filename().stem();
    
    std::cout << "Python script folder: " << abspath << std::endl;
    std::cout << "Python script module name: " << module << std::endl;

    // we have to make sure that we set the python path variable
    // so that python knows where to find our python script
    // We will add the absolute path of the folder the provided
    // script is in
    py::module sys = py::module::import("sys");
    sys.attr("path").attr("insert")(1, abspath.c_str());



    auto _script = py::module::import(module.native().c_str());


    // did the script load correctly
    if(_script)
    {
        // check if we have the method we want to call
        if(py::hasattr(_script,"helloFromPython"))
        {
            py::function helloFromPython =
                py::reinterpret_borrow<py::function>(   // cast from 'object' to 'function - use `borrow` (copy) or `steal` (move)
                  _script.attr("helloFromPython")  // import method "min_rosen" from python "module"
                );

            {
                spdlog::info("Calling: helloFromPython() from C++");
                auto result = helloFromPython();

                auto _valid = result.cast<std::string>();

                spdlog::info("Return Value: {}", _valid);
            }

            spdlog::info("Replacing python function callMe with C++ Lambda");
            // delete any old instances of callMe() function
            _script.attr("callMe") = py::none();
            // add our own callMe function
            auto callMe = _script.def("callMe",[](int x)
            {
                std::cout << "C++ Lambda function callMe: " << x << std::endl;
            });

            {
                spdlog::info("Calling: helloFromPython() from C++");
                auto result = helloFromPython();

                auto _valid = result.cast<std::string>();

                spdlog::info("Return Value: {}", _valid);
            }
        }
        else
        {
            spdlog::error("Does not have function: helloFromPython()");
        }

        if(py::hasattr(_script,"callMeToo"))
        {
            py::function callMeToo =
                py::reinterpret_borrow<py::function>(   // cast from 'object' to 'function - use `borrow` (copy) or `steal` (move)
                  _script.attr("callMeToo")  // import method "min_rosen" from python "module"
                );

            spdlog::info("Calling: callMeToo(4) from C++");
            auto result = callMeToo(4);

            auto _valid = result.cast<int>();

            spdlog::info("Return Value: {}", _valid);
        }
        else
        {
            spdlog::error("Does not have function: callMeToo()");
        }
    }
    else
    {
        spdlog::error("Script failed to load");
    }

}


int main(int argc, char ** argv)
{
    if(argc != 2)
    {
        std::cout << "./hello_world path/to/myModule.py" << std::endl;
        return 1;
    }
    runPythonScript(argv[1]);
    return 0;
}
