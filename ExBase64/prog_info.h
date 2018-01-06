#pragma once

#include <iostream>
#include <string>

namespace prog_about
{
	const std::string prog_name = "ExBase64";
	const std::string prog_full_name = "Base64 De/En/coding Utility";
	const std::string prog_version = "1.0";
	const std::string prog_edition = "Melting Spectre";
	const std::string prog_release_date = "January 06, 2018";

#ifdef _M_IX86
	const std::string arch = "32-bit";
#else
	const std::string arch = "64-bit";
#endif

	const std::string author_name = "Mohamad Mokbel";
	const std::string author_email = "mfmokbel@live.com";
	const std::string website = "http://www.mfmokbel.com";
}