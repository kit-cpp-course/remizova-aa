#ifndef DECODER_H
#define DECODER_H
#include"Coder.h"

/*
* ���������� �������� ���� ������� � ��������
*/
class Decoder: public Coder
{
public:	
	Decoder(const char* filepath);
	virtual ~Decoder() = default;
	/*
	* ������������ ������� ������������� �����
	*/
	virtual void process();
};

#endif // DECODER_H