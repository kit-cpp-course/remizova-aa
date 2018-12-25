#ifndef ENCODER_H
#define ENCODER_H
#include "Coder.h"

class Encoder: public Coder
{
public:	
	Encoder(const char* filepath);
	virtual ~Encoder();
	virtual void process();
};

#endif // ENCODER_H