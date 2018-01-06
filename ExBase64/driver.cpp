#include "driver.h"
#include "prog_info.h"

namespace driver
{
	// parses command line argument and sets each args variable accordingly
	// throw exceptions of the types, std::string and std::exception
	void
	args::parse_args(int argc, char* argv[]) noexcept(false)
	{
		if (argc > 1)
		{
			std::vector<std::string> args_list(argv, argv + argc);
			
			// search vector args_list for argument options
			auto find_vstr = [&](const std::string& arg_o)-> auto const
			{
				return std::find(args_list.begin(), args_list.end(), arg_o);
			};

			// check if std::next index is valid
			auto chk_nxt_arg = [&](const auto& f_arg) -> bool const
			{
				auto nxt = std::next(f_arg);

				return (nxt != args_list.end()) ? true : false;
			};

			// throw exception for missing argument option
			auto throw_exc = [](const std::string &msg) -> void const
			{
				throw msg + " argument option is missing its value";
			};

			auto found_arg = find_vstr("-v");

			if (found_arg != args_list.end() && argc == 2)
			{
				std::cout << author_about();
				std::exit(0);
			}

			found_arg = find_vstr("-e:s");

			if (found_arg != args_list.end())
			{
				chk_nxt_arg(found_arg) ? (encode_str = std::make_pair(true, *std::next(found_arg))) : throw_exc("-e:s");
			}

			found_arg = find_vstr("-e:h");

			if (found_arg != args_list.end())
			{

				chk_nxt_arg(found_arg) ? (encode_hex = std::make_pair(true, *std::next(found_arg))) : throw_exc("-e:h");
			}

			found_arg = find_vstr("-d:s");

			if (found_arg != args_list.end())
			{
				chk_nxt_arg(found_arg) ? (decode_str = std::make_pair(true, *std::next(found_arg))) : throw_exc("-d:s");
			}

			found_arg = find_vstr("-d:h");

			if (found_arg != args_list.end())
			{
				chk_nxt_arg(found_arg) ? (decode_hex = std::make_pair(true, *std::next(found_arg))) : throw_exc("-d:h");
			}

			found_arg = find_vstr("-r:a");

			if (found_arg != args_list.end())
			{
				return_ascii = true;
			}

			found_arg = find_vstr("-r:h");

			if (found_arg != args_list.end())
			{
				return_hex = true;
			}

			found_arg = find_vstr("-t");

			if (found_arg != args_list.end())
			{
				chk_nxt_arg(found_arg) ? (nb_of_rounds = std::stoi(*std::next(found_arg))) : throw_exc("-t");

				if (nb_of_rounds <= 1)
				{
					throw std::exception("number of rounds cannot be less than 1");
				}
			}

			found_arg = find_vstr("-dl:i");

			if (found_arg != args_list.end())
			{
				chk_nxt_arg(found_arg) ? (delimiter_in = std::make_pair(true, *std::next(found_arg))) : throw_exc("-dl:i");
			}

			found_arg = find_vstr("-dl:o");

			if (found_arg != args_list.end())
			{
				chk_nxt_arg(found_arg) ? (delimiter_out = std::make_pair(true, *std::next(found_arg))) : throw_exc("-dl:o");
			}

			found_arg = find_vstr("-ef");

			if (found_arg != args_list.end())
			{
				chk_nxt_arg(found_arg) ? (encode_file_in = std::make_pair(true, *std::next(found_arg))) : throw_exc("-ef");
			}

			found_arg = find_vstr("-o");

			if (found_arg != args_list.end())
			{
				chk_nxt_arg(found_arg) ? (file_out = std::make_pair(true, *std::next(found_arg))) : throw_exc("-o");
			}

			found_arg = find_vstr("-df");

			if (found_arg != args_list.end())
			{
				chk_nxt_arg(found_arg) ? (decode_file_in = std::make_pair(true, *std::next(found_arg))) : throw_exc("-df");
			}

			found_arg = find_vstr("-p");

			if (found_arg != args_list.end())
			{
				chk_nxt_arg(found_arg) ? (padding_char = std::make_pair(true, *std::next(found_arg))) : throw_exc("-p");
			}

			found_arg = find_vstr("-s");

			if (found_arg != args_list.end() )
			{
				chk_nxt_arg(found_arg) ? (subst_table = std::make_pair(true, *std::next(found_arg))) : throw_exc("-s");
			}

			found_arg = find_vstr("-h");

			if (found_arg != args_list.end() && argc == 2)
			{
				help();
				std::exit(0);
			}
		} // if argc > 1
		else
		{
			throw std::exception("no argument was passed. Please pass argument -h for more information");
		}
	} // parse_args function

	// based on a given list of input args as set by the function "parse_args", 
	// this function is responsible for executing them accordingly by calling 
	// relevant methods from the base64 class
	// _in_ (arg_opts) : an object of type std::unique_ptr<driver::args> which
	//					 has all input args information
	void 
	args::execute_args_code(std::unique_ptr<driver::args>& arg_opts) noexcept(false)
	{
		std::unique_ptr<Base64> b64_obj = std::make_unique<Base64>();

		using namespace driver;
		// -p
		if (arg_opts->padding_char.first)
		{
			b64_obj->set_p_char(arg_opts->padding_char.second);
		}
		// -s
		if (arg_opts->subst_table.first)
		{
			b64_obj->set_s_table(arg_opts->subst_table.second);
		}
		// -e:s
		if (arg_opts->encode_str.first)
		{	// -r:h		
			if (!arg_opts->return_hex)
			{
				std::cout << std::endl << b64_obj->encode_str(arg_opts->encode_str.second, arg_opts->nb_of_rounds) << std::endl;
				std::exit(0);
			}
			// -r:h and takes dl:o <delimiter>
			if (arg_opts->return_hex)
			{
				std::cout << 
				std::endl << b64_obj->string_to_hex(
							 b64_obj->encode_str(arg_opts->encode_str.second, arg_opts->nb_of_rounds),
							 arg_opts->delimiter_out.second) << std::endl;
				std::exit(0);
			}
		}
		// -e:h
		if (arg_opts->encode_hex.first)
		{	// -r:h and takes dl:i <delimiter>
			if (!arg_opts->return_hex)
			{
				std::cout << std::endl << b64_obj->encode_hex(arg_opts->encode_hex.second, arg_opts->nb_of_rounds, arg_opts->delimiter_in.second) << std::endl;
				std::exit(0);
			}
			// r:h
			if (arg_opts->return_hex)
			{
				std::cout << 
				std::endl << b64_obj->string_to_hex(
							 b64_obj->encode_hex(arg_opts->encode_hex.second, arg_opts->nb_of_rounds, arg_opts->delimiter_in.second),
													arg_opts->delimiter_out.second) << std::endl;
				std::exit(0);
			}
		}
		// -d:s
		if (arg_opts->decode_str.first)
		{	// -r:h
			if (!arg_opts->return_hex)
			{
				std::cout << std::endl << b64_obj->decode_str(arg_opts->decode_str.second, arg_opts->nb_of_rounds) << std::endl;
				std::exit(0);
			}
			// -r:h
			if (arg_opts->return_hex)
			{
				std::cout << std::endl << b64_obj->decode_hex(arg_opts->decode_str.second, arg_opts->nb_of_rounds, arg_opts->delimiter_out.second) << std::endl;
				std::exit(0);
			}
		}
		// -d:h
		if (arg_opts->decode_hex.first)
		{	// -r:h
			if (!arg_opts->return_hex)
			{
				std::cout << 
				std::endl << b64_obj->decode_str(
							 b64_obj->hex_to_string(arg_opts->decode_hex.second, arg_opts->delimiter_in.second),
												 arg_opts->nb_of_rounds) << std::endl;
				std::exit(0);
			}
			// -r:h
			if (arg_opts->return_hex)
			{
				std::cout << 
				std::endl << b64_obj->decode_hex(
							 b64_obj->hex_to_string(arg_opts->decode_hex.second, arg_opts->delimiter_in.second),
												 arg_opts->nb_of_rounds, arg_opts->delimiter_out.second) << std::endl;
				std::exit(0);
			}
		}

		// -ef
		if (arg_opts->encode_file_in.first)
		{	// -r:h
			if (!arg_opts->return_hex)
			{	// -o
				if (arg_opts->file_out.first)
				{
					if (b64_obj->save_file_text(arg_opts->file_out.second,
						b64_obj->encode_hex(
							b64_obj->open_file_binay(
								arg_opts->encode_file_in.second),
							arg_opts->nb_of_rounds)))
					{
						arg_opts->file_write_status_msg(arg_opts->file_out.second, "encoded", false);
						std::exit(0);
					}
					else
					{
						arg_opts->file_write_status_msg(arg_opts->file_out.second, "encoded", true);
						std::exit(0);
					}
				}
				else
				{
					std::cout << 
					std::endl << b64_obj->encode_hex(
								 b64_obj->open_file_binay(arg_opts->encode_file_in.second),
													 arg_opts->nb_of_rounds) << std::endl;
					std::exit(0);
				}
			}
			// -r:h
			if (arg_opts->return_hex)
			{	// -o
				if (arg_opts->file_out.first)
				{
					if (b64_obj->save_file_text(arg_opts->file_out.second,
						b64_obj->string_to_hex(
						b64_obj->encode_str(
						b64_obj->open_file_binay(arg_opts->encode_file_in.second),
								arg_opts->nb_of_rounds),
							arg_opts->delimiter_out.second)))
					{
						arg_opts->file_write_status_msg(arg_opts->file_out.second, "encoded", false);
						std::exit(0);
					}
					else
					{
						arg_opts->file_write_status_msg(arg_opts->file_out.second, "encoded", true);
						std::exit(0);
					}
				}
				else
				{
					std::cout << 
					std::endl << b64_obj->string_to_hex(
								 b64_obj->encode_str(
								 b64_obj->open_file_binay(arg_opts->encode_file_in.second),
														  arg_opts->nb_of_rounds),
														arg_opts->delimiter_out.second) << std::endl;
					std::exit(0);
				}
			}
		}
		// -df
		if (arg_opts->decode_file_in.first)
		{	// -r:h
			if (!arg_opts->return_hex)
			{		// -o
				if (arg_opts->file_out.first)
				{
					if (b64_obj->save_file_text(arg_opts->file_out.second,
						b64_obj->decode_str(
						b64_obj->open_file_text(arg_opts->decode_file_in.second),
							arg_opts->nb_of_rounds)))
					{
						arg_opts->file_write_status_msg(arg_opts->file_out.second, "decoded", false);
						std::exit(0);
					}
					else
					{
						arg_opts->file_write_status_msg(arg_opts->file_out.second, "decoded", true);
						std::exit(0);
					}
				}
				else
				{
					std::cout << 
					std::endl << b64_obj->decode_str(
								 b64_obj->open_file_text(arg_opts->decode_file_in.second),
													 arg_opts->nb_of_rounds) << std::endl;
					std::exit(0);
				}

			}
			// -r:h
			if (arg_opts->return_hex)
			{	// -o
				if (arg_opts->file_out.first)
				{
					if (b64_obj->save_file_text(arg_opts->file_out.second,
						b64_obj->string_to_hex(
						b64_obj->decode_str(
						b64_obj->open_file_text(arg_opts->decode_file_in.second),
												arg_opts->nb_of_rounds),
												arg_opts->delimiter_out.second)))
					{
						arg_opts->file_write_status_msg(arg_opts->file_out.second, "decoded", false);
						std::exit(0);
					}
					else
					{
						arg_opts->file_write_status_msg(arg_opts->file_out.second, "decoded", true);
						std::exit(0);
					}
				}
				else
				{
					std::cout << 
					std::endl << b64_obj->string_to_hex(
								 b64_obj->decode_str(
								 b64_obj->open_file_text(arg_opts->decode_file_in.second),
													 arg_opts->nb_of_rounds),
														arg_opts->delimiter_out.second) << std::endl;
					std::exit(0);
				}
			}

		}
		else
		{
			throw std::exception("argument option is not valid");
		}
	}

	// it tells whether the decoded/encoded file has been written to disk successfully or not
	// _in_ (file_name)  : file name
	// _in_ (mode)       : takes either of the strings, "decoded" or "encoded"
	// _in_ (is_success) : true = successfull; false = failed
	void
	args::file_write_status_msg(const std::string& file_name, const std::string& mode, bool is_success) noexcept(true)
	{
		if (is_success)
		{
			std::cout << std::endl << "message: " << mode << " file \"" << file_name << "\" has been written successfully" << std::endl;
		}
		else
		{
			std::cerr << std::endl << "message: failed to write to file \"" << file_name << "\"" << std::endl;
		}
	}

	// author and version info
	std::string
	args::author_about(void)  noexcept(true)
	{
		using namespace prog_about;

		std::stringstream about_str;

		about_str << std::endl

			<< "  " << prog_name + " (" + prog_full_name + ") " + "v" + prog_version + " (" + arch + ") " << std::endl
			<< "  " << "Release Date: [" + prog_release_date + "]" << std::endl
			<< "  " << "Edition: " << prog_edition << std::endl << std::endl
			<< "  " << author_name << std::endl
			<< "  " << author_email << std::endl
			<< "  " << website

			<< std::endl;

		return about_str.str();
	}

	void
	args::help(void) noexcept(true)
	{
		auto p_spaces = [](const int8_t& w) -> std::string { return std::string(w, ' '); };

		std::cout << std::endl << prog_about::prog_name + " is a Base64 encoding and decoding tool." << std::endl << std::endl;

		std::cout << "Usage: " + prog_about::prog_name + " ";
						std::cout << "[-e:s <string>] [-e:h <hex stream>] [-d:s <string>] [-d:h <hex stream>]" << std::endl
				  << p_spaces(16) << "[-ef <filename>] [-o <out_filename>] [-df <filename>] [-o <out_filename>]" << std::endl
				  << p_spaces(16) << "[-p <padding char>] [-s <substitution table>] [-r:h] [-t <nb of rounds>]" << std::endl
				  << p_spaces(16) << "[-dl:o <delimiter output>] [-dl:i <delimiter input>] [-h] [-v]" << std::endl << std::endl;

		auto p_option = [&](const std::string& opt, const std::string& info) -> void 
		{
			std::cout << p_spaces(4) << std::setw(25) << std::left << opt << info << std::endl;
		};

		std::cout << "Options:" << std::endl;

		p_option("-e:s <string>", "encode a string.");
		p_option("-e:h <hex stream>", "encode a hex stream. could be used with [-dl:i] and [-dl:o] options");
		p_option("-d:s <string>", "decode encoded string.");
		p_option("-d:h <hex stream>", "decode encoded hex stream.");
		p_option("-ef <filename>", "encode a file.");
		p_option("-df <filename>", "decode encoded file.");
		p_option("-o <filename>", "save output of options [-ef] and [-df] to a file.");
		p_option("-p <padding char>", "custom padding character.");
		p_option("-s <substitution table>", "custom substitution table.");
		p_option("-r:h", "returns a hex stream. By default it returns ascii (-r:a).");
		p_option("-t <nb of rounds>", "number of rounds/times to encode or decode.");

		p_option("-dl:o <delimiter output>", "delimit hex stream output (options -r:h) with a specific string.");
		p_option("-dl:i <delimiter input>", "erase hex stream input delimiter (options -e:h and -d:h)");
		p_option("-h", "print this help message.");
		p_option("-v", "print tool's version and author information.");

		std::cout << std::endl << "Examples:" << std::endl << std::endl;
		std::cout << "    - To encode a string, ExBase64.exe -e:s \"Hello World\"" << std::endl;
		std::cout << "    - To decode a string, ExBase64.exe -d:s aGVsbG8gd29ybGQ=" << std::endl << std::endl;

		std::cout << "Note: please check the readme file for more information about how to use the tool." << std::endl;
	}
} // driver namespace