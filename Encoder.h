#ifndef ENCODER_H
#define ENCODER_H
#include "Coder.h"
/*Переводит картинку в бинарный файл*/
class Encoder: public Coder
{
public:	
	Encoder(const char* filepath);
	virtual ~Encoder();
	/*Осуществляет процесс кодирования файлов*/
	virtual void process();
};

#endif // ENCODER_H