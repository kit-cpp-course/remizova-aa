#ifndef CODER_H
#define CODER_H
#include <vector>
#include "huffman.h"
class Coder abstract
{
public:	
	virtual void process() = 0;
protected:
	/*Структура, содержащая параметры изображения */
	struct
	{
		int width;
		int height;
		int channels;
		std::vector<unsigned char> pixels;
	}m_imageData;	
	/* Объект, реализующий метод кодировки*/
	HuffmanTree m_huffmanTree;
	/*Пути к входному и выходному файлам*/
	std::string m_inPath, m_outPath;
	/*Поток данных для записи входных и выходных файлов*/
	std::fstream m_stream;
};

#endif //CODER_H