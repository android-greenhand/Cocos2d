#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
#include <map>
struct TreeNode
{
	char key;
	int weight;
	TreeNode *pleft;
	TreeNode *pright;
	TreeNode *pparent;
	TreeNode(char c, int i, TreeNode* pl = NULL, TreeNode* pr = NULL, TreeNode* pa = NULL)
		:key(c), weight(i), pleft(pl), pright(pr), pparent(pa){}
};

struct Leaf
{
	int value;
	int bitnum;
	Leaf()
	{

	}
	Leaf(int v, int b) :value(v), bitnum(b){}
};
class HuffCode
{
private:
	TreeNode * root;
	int mcount = 0;
	unordered_map<char, Leaf> unmap;
	vector<char> mres;
	map<char, int> mmap;
	string resstr;
	
public:
	
	string stxet;
	HuffCode();
	//压缩过程
	vector<char>  ReadFile();
	void BuildHuffTree();
	void PreOrder(TreeNode *root,int num, int level);
	int  GetCountChar(unordered_map<char, Leaf> unmap);
	void Compress(int numchar, string s);

	//解压过程
	char Decompress(int &highbit, vector<char> &a);
	void HuffDecompress(vector<char>a, int count);
	~HuffCode();
	void WriteFile();
	void Process();
	
};