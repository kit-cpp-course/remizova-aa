#include"ifcpch.h"
#include "Encoder.h"

#define STB_IMAGE_IMPLEMENTATION
#include"libs/stb_image.h"

Encoder::Encoder(const char* filepath)
{
	m_inPath = std::string(filepath);
	std::string outFile(filepath);
	outFile = outFile.substr(0, outFile.find('.'));
	outFile += ".bin";
	m_outPath = outFile;
}

Encoder::~Encoder()
{}

void Encoder::process()
{
	unsigned char* data = stbi_load(m_inPath.c_str(), &m_imageData.width, &m_imageData.height, &m_imageData.channels, STBI_grey);
	m_imageData.channels = 1;
	int size = m_imageData.width * m_imageData.height;
	for (int i = 0; i < size; i++)
		m_imageData.pixels.push_back(data[i]);
	std::string huffmanCode = m_huffmanTree.encode(m_imageData.pixels);

	m_stream.open(m_outPath, std::ios::out | std::ios::binary);
	m_stream.write((char*)&m_imageData.width, sizeof(int));
	m_stream.write((char*)&m_imageData.height, sizeof(int));
	m_stream.write((char*)&m_imageData.channels, sizeof(int));
	m_stream.write(huffmanCode.c_str(), huffmanCode.size());
	m_stream.close();
}