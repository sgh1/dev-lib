    
//
// Logger adapted from Dr. Dobbs article, "A Lightweight Logger for C++",
// By Filip Janiszewski, January 31, 2013
//

#ifndef LOGGING_H_
#define LOGGING_H_

#include <memory>
#include <mutex>
#include <string>


namespace devlib
{

namespace logging
{
 
// Interface for logging policies.
class log_policy_interface
{
public:
    virtual void		open_ostream(const std::string& name) = 0;
    virtual void		close_ostream() = 0;
    virtual void		write(const std::string& msg) = 0;
};

// Implementation which allow to write into a file.
class file_log_policy : public log_policy_interface
{
    std::unique_ptr< std::ofstream > out_stream;
public:
    file_log_policy() : out_stream( new std::ofstream ) {}
    void open_ostream(const std::string& name);
    void close_ostream();
    void write(const std::string& msg);
    ~file_log_policy();
};

// Implementation which allow to write to stdout.
class console_log_policy : public log_policy_interface
{
public:
    void open_ostream(const std::string& name);
    void close_ostream();
    void write(const std::string& msg);
};
    
// Severity level.    
enum severity_type
{
    debug = 1,
    message,
    error,
    warning
};


// Main logger template.    	
template< typename log_policy >
class logger
{
    unsigned log_line_number;
    
    // Creates timestamp string.
	std::string get_time()
	{
		std::string time_str;
		time_t raw_time;
		
		time( & raw_time );
		time_str = ctime( &raw_time );

		//without the newline character
		return time_str.substr( 0 , time_str.size() - 1 );
    }

    // Build the first part of the log entry (line no. + timestamp).
	std::string get_logline_header()
	{
		std::stringstream header;

		header.str("");
		header.fill('0');
		header.width(7);
		header << log_line_number++ <<" < "<<get_time()<<" - ";

		header.fill('0');
		header.width(7);
		header <<clock()<<" > ~ ";

		return header.str();
	}

    std::stringstream log_stream;
    log_policy* policy;
    std::mutex write_mutex;
    
    //Core printing functionality
	void print_impl()
	{
		policy->write( get_logline_header() + log_stream.str() );
		log_stream.str("");
	}

	template<typename First, typename...Rest >
	void print_impl(First parm1, Rest...parm)
	{
		log_stream<<parm1;
		print_impl(parm...);	
    }
    
public:
    
    logger( const std::string& name );

    template< typename...Args >
    void print( Args...args )
    {
        write_mutex.lock();
		switch( severity )
		{
			case severity_type::debug:
				log_stream<<"<DEBUG> :";
                break;
			case severity_type::message:
				log_stream<<"<MESSAGE> :";
                break;                
			case severity_type::warning:
				log_stream<<"<WARNING> :";
				break;
			case severity_type::error:
				log_stream<<"<ERROR> :";
				break;
		};
		print_impl( args... );
		write_mutex.unlock();
    }

    ~logger();
};


}
}

// ?? We might need to use a scheme like boost::logger.
//static logging::logger< logging::file_log_policy > log_inst( "execution.log" );
static logging::logger< logging::console_log_policy > log_inst( "" );


#define LOG log_inst.print< logging::severity_type::debug >
#define LOG_ERR log_inst.print< logging::severity_type::error >
#define LOG_WARN log_inst.print< logging::severity_type::warning >

#endif