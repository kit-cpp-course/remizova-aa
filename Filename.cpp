#include "Filename.h"

Filename::Filename(int argc, const char * argv[])
	: m_argc(argc), m_argv(argv)
{}

std::string Filename::GetFilenameToEncode() const
{
	if (m_argc < 2) return DefaultFileName;
	return { m_argv[1] };
}

std::string Filename:: GetFilenameToDecode() const
{
	std::string temp = (m_argc < 2) ? DefaultFileName : m_argv[1];
	temp = temp.substr(0, temp.find('.'));
	return temp + ".bin";
}