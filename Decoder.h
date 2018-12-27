#ifndef DECODER_H
#define DECODER_H
#include"Coder.h"

/*
* Возвращает бинарный файл обратно в картинку
*/
class Decoder: public Coder
{
public:	
	Decoder(const char* filepath);
	virtual ~Decoder() = default;
	/*
	* Осуществляет процесс декодирования файла
	*/
	virtual void process();
};

#endif // DECODER_H