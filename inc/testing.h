#ifndef MACROLESS_H
#define MACROLESS_H

#include "logger.h"

#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <vector>


namespace devlib
{
namespace testing
{

    // Test class.  Also serves as the base class for fixtures.
    class test
    {
    public:

        test(   std::string name,
                std::function<bool(test*)> r,
                std::function<void(test*)> su = [](test*){},
                std::function<void(test*)> td = [](test*){} );

        virtual ~test();

        virtual void setup();
        virtual bool run();
        virtual void teardown();

        std::string test_name_;

        std::function<bool(test*)> run_;
        std::function<void(test*)> setup_, teardown_;
    };

    // Typedefs.
    typedef std::unique_ptr<test> test_ptr;
    typedef std::vector<std::unique_ptr<test>> test_vector;
    typedef std::vector< std::function<void()> > collector_vector;

    // Exception to throw when a test fails.
    class test_fail: std::exception {};

    // Function to run a std::vector of tests collected by a std::vector of functions. 
    bool run(int argc, char** argv, const collector_vector& collectors, const test_vector& tests);

    

    // Fail message.
    template<typename... Args>
    void fail_test(const Args&... args)
    {
        // Build the message.
        std::stringstream ss;
        ss << "TEST ERROR: ";
        strstr_append(ss,args...);

        // Write the message to the global output.
        get_output() << "\t\t" << ss.str() << "\n";

        // Throw failure exception.
        throw test_fail();
    };

}
}

#endif //UNTITLED2_MACROLESS_H
