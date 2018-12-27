#pragma once
#include <string>

/*¬ыполн€ет работу с аргументами командной строки*/
class Filename
{
private:
	const int m_argc;
	const char ** m_argv;
	const char * DefaultFileName = "WOLF1.bmp";
public:
	Filename(int argc, const char * argv[]);
	std::string GetFilenameToEncode() const;
	std::string GetFilenameToDecode() const;
};