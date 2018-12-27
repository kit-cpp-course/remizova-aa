#ifndef HUFFMAN_H
#define HUFFMAN_H

//������� ������ ��������, ���������� ����, ������� ���������, ������������� ��� � ��������� �� ���������� � ��������� �������� 
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

	//������� ���������, ����������� ������ �������� � ������������ ������, ��������� �� ����� �������� 
	std::string encode(std::vector<unsigned char> buffer);

	//������� ������������, ����������� ����� � �������� �������� ������ � ������������ ������ ��������
	std::vector<unsigned char> decode(std::fstream& stream);
private:
	//��������������� ������� ��� ���������� ������
	inline void build_tree(std::string&, unsigned char);
private:
	//����� ��������� ��� ������������ �������
	class NodeComparator
	{
	public:
		bool operator()(const node_ptr& c1, const node_ptr& c2) const
		{
			return c1->freq > c2->freq;
		}
	};
	
	//������������ �������, ���������� ��� ����� � �����������, ��������������� �� ������� ���������
	std::priority_queue<node_ptr, std::vector<node_ptr>, NodeComparator> pq;
	
	//������� ������
	node_ptr m_freqTable[256];

	//��������� ������� ������
	node_ptr m_root;	
};
#endif