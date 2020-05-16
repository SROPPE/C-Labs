#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;
struct  Word
{
	string str;
	int count = 0;
	int CompareTo(Word word)
	{
		if (count > word.count)
			return 1;
		else if (count < word.count)
			return -1;
		else
			return 0;
	}
	void CountWord()
	{
		count++;	
	}
};

struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	Word data;
	TreeNode(const Word& item, TreeNode* lptr = NULL,
		TreeNode* rptr = NULL) :data(item), left(lptr), right(rptr)
	{
	}
	void Add(Word word)
	{
		TreeNode* node = new TreeNode(word);
		if (node->data.CompareTo(word) == -1)
		{
			if (left == NULL)
			{

				left = node;
			}
			else
			{
				left->Add(data);
			}
		}
		else
		{
			if (right == NULL)
			{
				right = node;
			}
			else
			{
				right->Add(data);
			}
		}
		
	}
};
struct Tree
{
	TreeNode* current;
	TreeNode* root;
	int count;
	bool isNull = true;
	void Add(Word word)
	{
		TreeNode* node = new TreeNode(word);
		if (isNull)
		{
			root = node;
			count = 1;	
			isNull = false;
			return;
		}
		root->Add(word);
		count++;
	}
	
	void Insert(Word x)
	{
		TreeNode** cur = &root;
		while (*cur) {
			TreeNode& node = **cur;
			if (x.count < node.data.count) {
				cur = &node.left;
			}
			else if (x.count >= node.data.count) {
				cur = &node.right;
			}
			else {
				return;
			}
		}
		*cur = new TreeNode(x);
	}

};

void Inorder(TreeNode* t)
{
	if (t != NULL)
	{
		Inorder(t->right);
		cout << t->data.str<< ' ';
		Inorder(t->left);
	}
}
ifstream fin;
const int MAX_WORD_SIZE = 30;
bool IsDevide(char a);
void PrintWord(Word& w)
{
	cout << w.str;
}
int IsExists(char **strs, char *str, int count)
{
	int length = 0;
	bool exit = false;
	for (int i = 0; i < count; i++)
	{
	
		if (strlen(strs[i]) < strlen(str))
			length = strlen(str);
		else
			length = strlen(strs[i]);
		for (int j = 0,k = 0; j < length; j++, k++)
		{
			if (strs[i][j] != str[j])
				exit = true;
			if (j + 1 == length && !exit)
				return i;
		}
		exit = false;
	}
	return -1;
}
void SetWords(char **strs, int *wordFreq, int &count)
{
	if(!fin) fin.open("Text.txt");
	char str[MAX_WORD_SIZE];
	int i = 0;
	count = 0;
	while (!fin.eof())
	{
		
		char a= fin.get();
		while(!IsDevide(a) && !fin.eof())
		{
			
			a = toupper(a);
			str[i] = a;
			i++;
			a = fin.get();
		}
			str[i] = '\0';
			int pos = IsExists(strs, str, count);
			if (pos != -1)
			{
				wordFreq[pos]++;
			}
			else
			{
				for (int i = 0; i <= strlen(str); i++)
				{
					strs[count][i] = str[i];
				}
				count++;
			}
			i = 0;
			for (int i = strlen(str); i >= 0; i--)
			{
				str[i] = '\0';
			}
	}
	fin.close();
}
bool IsDevide(char a)
{
	char strDevide[10] = { ' ','.',',','-','\n','!','?','\0' };
	for (int i = 0; i < strlen(strDevide); i++)
	{
		if (a == strDevide[i])
			return true;
	}
	return false;
}
int GetTextWordSize()
{
	fin.open("Text.txt");
	int count = 0;
	while (!fin.eof())
	{
		char a = fin.get();
		if (IsDevide(a))
		{
			count++;
		}
	}
	fin.close();
	return count;
}
void main(void)
{
	setlocale(LC_ALL, "ru");
	Tree wordTree;
	int count = GetTextWordSize();
	char** strs = new char* [count];
	for (int i = 0; i < count; i++)
	{
		strs[i] = new char[MAX_WORD_SIZE];
	}
	int* wordFrequency = new int[count] {0};
	SetWords(strs,wordFrequency,count);
	fin.open("Text.txt");
	if (!fin)
	{
		cerr << "Не могу открыть Text.txt" << endl;
		exit(1);
	}
	Word word;
	word.str = strs[0];
	word.count = wordFrequency[0];
	TreeNode* root = new TreeNode(word);
	wordTree.root = root;
	for (int i = 1; i < count; i++)
	{
		Word word;
		word.str = strs[i];
		word.count = wordFrequency[i];
		wordTree.Insert(word);
	}
	Inorder(wordTree.root);
}