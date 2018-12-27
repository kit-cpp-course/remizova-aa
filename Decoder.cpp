#include"ifcpch.h"
#include "Decoder.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include"libs/stb_image_write.h"

Decoder::Decoder(const char* filepath)
{
	m_inPath = std::string(filepath);
	std::string outFile(filepath);
	outFile = outFile.substr(0, outFile.find('.'));
	outFile += "[converted].bmp";
	m_outPath = outFile;
}

Decoder::~Decoder()
{
}

void Decoder::process()
{	
	m_stream.open(m_inPath, std::ios::in | std::ios::binary);
	m_stream.read((char*)&m_imageData.width, sizeof(int));
	m_stream.read((char*)&m_imageData.height, sizeof(int));
	m_stream.read((char*)&m_imageData.channels, sizeof(int));	
	m_imageData.pixels = m_huffmanTree.decode(m_stream);
	m_stream.close();
	stbi_write_bmp(m_outPath.c_str(), m_imageData.width, m_imageData.height, m_imageData.channels, m_imageData.pixels.data());
}