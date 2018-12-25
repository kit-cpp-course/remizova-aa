#ifndef CODER_H
#define CODER_H
#include "huffman.h"
class Coder abstract
{
public:	
	Coder();
	~Coder();
	virtual void process() = 0;
protected:
	struct
	{
		int width;
		int height;
		int channels;
		std::vector<unsigned char> pixels;
	}m_imageData;	
	HuffmanTree m_huffmanTree;
	std::string m_inPath, m_outPath;
	std::fstream m_stream;
};

#endif //CODER_H