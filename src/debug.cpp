/*

#include <iostream>
#include <typeinfo>
#include <vector>

// For rudimentary backtrace.
#include <execinfo.h>

using namespace std;

namespace debug_tools
{
//    // By default, we can't print.
//    template<typename T>
//    struct has_output_op{       static bool value = false;  };
//
//    template<> struct has_output_op<int>            { static bool value = true; };
//    template<> struct has_output_op<double>         { static bool value = true; };
//    template<> struct has_output_op<float>          { static bool value = true; };
//    template<> struct has_output_op<std::string>    { static bool value = true; };
//    template<> struct has_output_op<unsigned>       { static bool value = true; };
//
//    template<T> struct has_output_op<std::complex<T> >  { static bool value = true; };

    template<typename T>
    struct get_typename
    {

    };


    template<typename T>
    struct p
    {
        static void print(const T&                v,
                          std::ostream&           os =    cout,
                          const std::string&      name =  "")
        {
            std::cout << "printing nothing\n";
        }
    };

//    template<typename T>
//    struct p<T,true>
//    {
//        static void print(const T&                v,
//                          std::ostream&           os =    cout,
//                          const std::string&      name =  "")
//        {
//            std::cout << "printing nothing\n";
//        }
//    };

    template<typename T>
    struct p<std::vector<T> >
    {
        static void print(const std::vector<T>&   v,
                          std::ostream&           os =    cout,
                          const std::string&      name =  "")
        {
            os << "Printing std::vector " << name << ":\n";
            os << "==================================\n";
            os << "Type: " << typeid(T()).name() << "\n";
            os << "Size: " << v.size() << "\n";
            os << "Mem: " << v.capacity()*sizeof(T) << " bytes\n";
            os << "Vals:\n";

            for(size_t i = 0; i < v.size(); i++){
                os << "\t" << i << ":\t" << v[i] << "\n";
            }
        }
    };

    void brk(const std::string& name = "")
    {
        // Print indicator.
        std::cout << "<breaking: " << name << ">\n";

        // Print the backtrace.
        print_backtrace();

        std::string nothing;
        cin >> nothing;
    }

    template<typename T>
    void print( const T&                x,
                std::ostream&           os =    cout,
                const std::string&      name =  "")
    {
        p<T>::print(x,os,name);
    }

//    template<typename T, typename U>
//    void print( const T& x,
//                const std::string&      namex,
//                const U& y,
//                const std::string&      namey,
//                std::ostream&           os =    cout)
//    {
//        p::print(x,os,namex);
//        p::print(y,os,namey);
//    }



   void print_backtrace(void)
   {
       void *tracePtrs[10];
       size_t count;

       count = backtrace(tracePtrs, 10);

       char** funcNames = backtrace_symbols(tracePtrs, count);

       for (int i = 0; i < count; i++)
           std::cout << funcNames[i] << "\n";

       free(funcNames);
}


}



int main()
{
    cout << "Hello world!" << endl;

    std::vector<double> dv;

    dv.push_back(1.03343);
    dv.push_back(4.03343);
    dv.push_back(5.34343);
    dv.push_back(1.6343);

    debug_tools::print(dv,cout,"dv");

    debug_tools::brk();

    return 0;
}

*/
