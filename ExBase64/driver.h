#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <memory>
#include "base64.h"

namespace driver
{
	class args
	{
	public:

		// -------------------------------------

		void parse_args(int argc, char* argv[]) noexcept(false);
		void execute_args_code(std::unique_ptr<driver::args> &arg_opts) noexcept(false);
		
		void file_write_status_msg(const std::string& file_name, const std::string& mode, bool is_success) noexcept(true);
		std::string author_about(void) noexcept(true);
		void help(void) noexcept(true);

		// --------------------------------------

		std::pair<bool, std::string> encode_hex;        // -e:h
		std::pair<bool, std::string> encode_str;        // -e:s

		std::pair<bool, std::string> decode_str;        // -d:s
		std::pair<bool, std::string> decode_hex;        // -d:h

		std::pair<bool, std::string> delimiter_in;      // -dl:i
		std::pair<bool, std::string> delimiter_out;     // -dl:o

		std::pair<bool, std::string> subst_table;       // -s
		std::pair<bool, std::string> padding_char;      // -p

		std::pair<bool, std::string> encode_file_in;    // -ef
		std::pair<bool, std::string> decode_file_in;    // -df

		std::pair<bool, std::string> file_out;          // -o

		bool return_ascii    = false;    // -r:a
		bool return_hex      = false;    // -r:h
		
		bool print_help      = false;    // -h
		bool program_info    = false;    // -v

		int32_t nb_of_rounds = 1;        // -t
	};

} // driver namespace