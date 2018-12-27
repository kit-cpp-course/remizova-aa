#ifndef HUFFMAN_H
#define HUFFMAN_H

//Элемент дерева Хаффмана, содержащий цвет, частоту появления, сгенерируемый код и указатели на предыдущий и следующий элементы 
struct HuffmanNode
{
	unsigned char color;
	int freq;
	std::string code;
	HuffmanNode* left = nullptr;
	HuffmanNode* right = nullptr;
};
typedef HuffmanNode* node_ptr;

class HuffmanTree
{										
public:	
	HuffmanTree();
	~HuffmanTree();
	HuffmanTree(const HuffmanTree& other);

	//Функция кодировки, принимающая массив пикселей и возвращающая строку, состоящую из кодов Хаффмана 
	std::string encode(std::vector<unsigned char> buffer);

	//Функция раскодировки, принимающая поток с открытым бинарным файлом и возвращающая массив пикселей
	std::vector<unsigned char> decode(std::fstream& stream);
private:
	//Вспомогательная функция для заполнения дерева
	inline void build_tree(std::string&, unsigned char);
private:
	//Класс сравнения для приорететной очереди
	class NodeComparator
	{
	public:
		bool operator()(const node_ptr& c1, const node_ptr& c2) const
		{
			return c1->freq > c2->freq;
		}
	};
	
	//Приоритетная очередь, содержащая все цвета в изображенни, отсортированные по частоте появления
	std::priority_queue<node_ptr, std::vector<node_ptr>, NodeComparator> pq;
	
	//Таблица частот
	node_ptr m_freqTable[256];

	//Начальный элемент дерева
	node_ptr m_root;	
};
#endif