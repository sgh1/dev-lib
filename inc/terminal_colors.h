
//
// Source: https://stackoverflow.com/questions/2616906/how-do-i-output-coloured-text-to-a-linux-terminal
// Author: Daniel Langr
//

#ifndef TERMINAL_COLORS_H_
#define TERMINAL_COLORS_H_

#include <string>

namespace minisoup
{	
namespace termcolor
{
	
	const std::string red("\033[0;31m");
	const std::string green("\033[1;32m");
	const std::string yellow("\033[1;33m");
	const std::string cyan("\033[0;36m");
	const std::string magenta("\033[0;35m");	
	const std::string reset("\033[0m");

}
}

#endif