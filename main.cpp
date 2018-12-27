#include"ifcpch.h"
#include"Coder.h"
#include "Encoder.h"
#include "Decoder.h"
#include "Filename.h"

int main(int argc, const char* argv[])
{	
	Filename filename(argc, argv);

	Coder* encoder = new Encoder(filename.GetFilenameToEncode().data());
	Coder* decoder = new Decoder(filename.GetFilenameToDecode().data());
	
	encoder->process();
	decoder->process();
	
	delete encoder;
	delete decoder;
	
	return 0;
}