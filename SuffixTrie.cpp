#include <iostream>
using namespace std;


class SuffixTrie
{
private:

	struct LNode
	{
		char data;
		int code = -1;
		LNode* next = nullptr;
		LNode* child = nullptr;
	};
	void add(char* data, int size, LNode*& node)
	{
		if (size < 1)return;
		if (node == nullptr)
		{
			node = new LNode;
			node->data = data[0];
			for (int i = 0; i < size; i++)
			{
				data[i] = data[i + 1];
			}
			data[size - 1] = 0;
			add(data, size - 1, (node->child));
		}
		else
		{
			if (node->data == data[0])
			{
				for (int i = 0; i < size; i++)
				{
					data[i] = data[i + 1];
				}
				data[size] = 0;

				add(data, size - 1, (node->child));
			}
			else
			{
				add(data, size, (node->next));
			}
		}
	}
	LNode* list;
	int length;
	void indexPrinter(LNode*& node)
	{
		if (node == nullptr)return;
		if (node->next != nullptr)
		{
			indexPrinter(node->next);
		}
		if (node->data == '$')
		{
			cout << node->code << " ";
		}
		else
		{
			indexPrinter(node->child);
		}
	}
	LNode* search(char* word, int wordSize, LNode* node, int index = 0)
	{
		if (wordSize -index==0)return node;
		if (node == nullptr)
		{
			cout << "not found\n";
			return 0;
		}
		if (node->data == word[index])
		{
			if (node->data == '$')
				return node;
			node = search(word, wordSize, node->child, ++index);
		}
		else if (node->data == '$')
		{
			cout << "not found\n";
			return 0;
		}
		
		else if (node->next != nullptr)
		{
			node=search(word, wordSize, node->next, index);
		}
		
	}
public:
	SuffixTrie(const char* mainWord)
	{
		int wordSize = 0;
		while (mainWord[wordSize] != NULL)
		{
			wordSize += 1;
		}
		char* word;
		word = new char[wordSize];
		for (int i = 0; i < wordSize; i++)
		{
			word[i]=mainWord[i];
		}
		length = wordSize;
		char* tempArr;
		for (int i = 0; i < wordSize; i++)
		{
			tempArr = new char[(int)(wordSize - i)];
			for (int j = 0; j < wordSize -i;j++)
			{
				tempArr[j] = word[j];
			}
			add(tempArr, wordSize - i, list);
			for (int k = 0; k < wordSize-i; k++)
			{
				word[k] = word[k + 1];
			}
			word[wordSize - i] = 0;
		}
		indexer(0, list);
	}
	void indexer(int code,LNode*& node)
	{
		if (node->next != nullptr)
		{
			indexer(code , node->next);
		}
		if (node->child != nullptr)
		{
			indexer(code + 1, node->child);
		}
		else
		{
			node->code = length - code-1;
		}
	}
	void Search(const char* word)
	{
		int wordSize = 0;
		while (word[wordSize] != NULL)
		{
			wordSize += 1;
		}
		char* wordTemp;
		wordTemp= new char[wordSize];
		for (int i = 0; i < wordSize; i++)
		{
			wordTemp[i] = word[i];
		}
		LNode* temp = list;
		temp=search(wordTemp, wordSize, temp,0);
		indexPrinter(temp);
		cout << "\n";
	}
};

int main()
{
	// Construct a suffix trie containing all suffixes of "bananabanaba$"
	//            0123456789012
	SuffixTrie t("bananabanaba$");
	t.Search("ana"); // Prints: 1 3 7
	t.Search("naba"); // Prints: 4 8
	return 0;
}
