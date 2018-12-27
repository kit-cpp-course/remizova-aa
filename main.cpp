#include"ifcpch.h"
#include"Coder.h"
#include "Encoder.h"
#include "Decoder.h"
int main(int argc, char* argv[])
{	
	Coder* coder = new Encoder("WOLF1.bmp");	
	coder->process();
	return 0;
}