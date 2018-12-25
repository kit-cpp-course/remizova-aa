#include"ifcpch.h"
#include "huffman.h"

//Рекурсивная функция для построения дерева и генерации кодов Хаффмана
void traverse(node_ptr node, std::string code);

HuffmanTree::HuffmanTree()
{
	//Инициализация таблицы частот
	for (int i = 0; i < 256; i++)
	{
		m_freqTable[i] = new HuffmanNode;
		m_freqTable[i]->color = i;
		m_freqTable[i]->freq = 0;
	}
}


std::string HuffmanTree::encode(std::vector<unsigned char> buffer)
{
	{
		//Заполнение таблицы частот
		for (auto id = buffer.begin(); id != buffer.end(); id++)
			m_freqTable[*id]->freq++;

		//Заполнение приоритетной очереди цветами, которые встречаются 1 или больше раз
		for (int i = 0; i < 256; i++)
			if (m_freqTable[i]->freq)
				pq.push(m_freqTable[i]);

		//Создание дерева Хаффмана
		auto temp(pq);
		while (temp.size() > 1)
		{
			m_root = new HuffmanNode;
			m_root->freq = 0;
			m_root->left = temp.top();
			m_root->freq += temp.top()->freq;
			temp.pop();
			m_root->right = temp.top();
			m_root->freq += temp.top()->freq;
			temp.pop();
			temp.push(m_root);
		}
		traverse(m_root, "");
	}
	std::string in = "", s = "";	
	{
		//Первый байт будет содержать количество узлов дерева
		in += (char)pq.size();
		auto temp(pq);
		//Запись всех цветов с их кодами
		while (!temp.empty())
		{
			node_ptr current = temp.top();
			in += current->color;

			//Заполнение 128 битной строки 0
			s.assign(127 - current->code.size(), '0');

			//'1' сигнализирует о начале кода Хаффмана
			s += '1';
			s.append(current->code);
			
			//Конвертирование 128 0 и 1 в 8 битные числа для записи в файл			
			for (int i = 0; i < 16; i++)
			{
				in += (char)std::bitset<8>(s.substr(0, 8)).to_ulong();
				s = s.substr(8);
			}
			temp.pop();
		}
		s.clear();

		//Замена пикселей кодами Хаффмана 
		for (auto id = buffer.begin(); id != buffer.end(); id++)
		{
			s += m_freqTable[*id]->code;
			while (s.size() > 8)
			{				
				in += (char)std::bitset<8>(s.substr(0, 8)).to_ulong();
				s = s.substr(8);
			}
		}

		int count = 8 - s.size();
		
		//Дополнение до целого байта
		if (s.size() < 8)
		{
			s.append(count, '0');
		}
		in += (char)std::bitset<8>(s).to_ulong();		
		in += (char)count;
	}
	return in;
}

std::vector<unsigned char> HuffmanTree::decode(std::fstream& stream)
{	
	//Количество узлов в дереве Хаффмана
	unsigned char size;
	stream.read((char*)&size, 1);
	m_root = new HuffmanNode;
	for (int i = 0; i < size; i++)
	{
		unsigned char a_code;
		stream.read((char*)&a_code, 1);

		//Чтение 128 битной строки
		unsigned char h_code_c[16];
		stream.read((char*)h_code_c, 16);

		//Перевод в двоичный вид
		std::string h_code_s = "";
		for (int i = 0; i < 16; i++)
			h_code_s += std::bitset<8>(h_code_c[i]).to_string();

		//Получение кода Хаффмана
		int j = 0;
		while (h_code_s[j] == '0') j++;
		h_code_s = h_code_s.substr(j + 1);
		build_tree(h_code_s, a_code);
	}	

	stream.seekg(-1, std::ios::end);
	char count;
	stream.read(&count, 1);

	//Переход к началу закодированного изображение
	stream.seekg(1 + 17 * size, std::ios::beg);

	std::vector<unsigned char> text;

	//Чтение байт за байтом
	unsigned char textseg;
	stream.read((char*)&textseg, 1);
	while (!stream.eof())
	{
		text.push_back(textseg);
		stream.read((char*)&textseg, 1);
	}

	node_ptr current = m_root;
	std::string path;
	std::vector<unsigned char> buffer;
	//Расшифровка кодов Хаффмана
	for (int i = 0; i < text.size() - 1; i++)
	{
		path = std::bitset<8>((text[i])).to_string();
		if (i == text.size() - 2)
			path = path.substr(0, 8 - count);
		for (int j = 0; j < path.size(); j++)
		{
			if (path[j] == '0')
				current = current->left;
			else
				current = current->right;

			if (current->left == nullptr && current->right == nullptr)
			{
				buffer.push_back(current->color);
				current = m_root;
			}
		}
	}	
	return buffer;
}

inline void HuffmanTree::build_tree(std::string& path, unsigned char a_code)
{
	node_ptr current = m_root;
	for (int i = 0; i < path.size(); i++)
	{
		if (path[i] == '0')
		{
			if (current->left == nullptr)
				current->left = new HuffmanNode;
			current = current->left;
		}
		else if (path[i] == '1')
		{
			if (current->right == nullptr)
				current->right = new HuffmanNode;
			current = current->right;
		}
	}	
	current->color = a_code;
}

//Рекурсивная функция для построения дерева и генерации кодов Хаффмана
void traverse(node_ptr node, std::string code)
{
	if (node->left == nullptr && node->right == nullptr)
	{
		node->code = code;
	}
	else
	{
		traverse(node->left, code + '0');
		traverse(node->right, code + '1');
	}
}
