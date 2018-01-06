#include "driver.h"
#include <memory>

int main(int argc, char* argv[])
{
	try
	{
		std::unique_ptr<driver::args> arg_opts = std::make_unique<driver::args>();

		arg_opts->driver::args::parse_args(argc, argv);
		arg_opts->driver::args::execute_args_code(arg_opts);
	}
	catch (const std::string &es)
	{
		std::cerr << std::endl << "exception: " << es << std::endl;
	}
	catch (const std::exception &ee)
	{
		std::cerr << std::endl << "exception: " << ee.what() << std::endl;
	}
	return 0;
}
