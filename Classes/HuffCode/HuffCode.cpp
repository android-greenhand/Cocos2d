#include "HuffCode.h"
#include <algorithm>
#include <bitset>
#include <assert.h>
#include <stack>
#include<time.h>
HuffCode::HuffCode()
{
	root = NULL;
}
void HuffCode::Process()
{
	vector<char> a=ReadFile();
	BuildHuffTree();
	
	HuffDecompress(a, mcount);

	
	time_t t = time(0);
	char tmp[64] = {0};
	strftime(tmp, sizeof(tmp), "%Y-%m-%d %X", localtime(&t));
	for (int i = 0; tmp[i] != '\0'; i++)
	{
		resstr += tmp[i];
		char c = tmp[i];
		if (mmap.find(c) == mmap.end())
		{
			mmap[c] = 0;
		}
		mmap[c]++;
	}
	
	

	for (int i = 0; i < resstr.size(); i++)
	{
		if (i%19==0)
		{
			stxet.push_back('\n');
		}
		stxet.push_back(resstr[i]);
	}

	//cout << resstr << endl;


	BuildHuffTree();
	

	PreOrder(root, 0, 0); //先序遍历 计算每个字符在哈夫曼树中的值和位数

	int numchar = GetCountChar(unmap);//要传输的字符个数
	Compress(numchar, resstr); //转换成二进制 01 

	WriteFile();
}
vector<char>  HuffCode::ReadFile()
{
	
	string s = "F:\\cocos\\ChineseChess\\proj.win32\\Debug.win32\\LoginHistory\\loginhistory.txt";

	ifstream file;
	file.open(s, ios::binary);
	if (!file.is_open())
	{
		cout << "打开文件失败！" << endl;
		assert(!"打开文件失败");

	}

	int n = 0;
	if (!file.eof())
	{
		file >> n;
	}

	int flag = 0;

	while (!file.eof())
	{
		if (flag >= n)
		{
			break;

		}
		char c = file.get();
		if (c == '\n')
		{
			continue;
		}
		int num;
		file >> num;

		mmap[c] = num;
		mcount += num;
		flag++;

	}
	vector<char> a;
	char c = file.get();


	while (file.peek() != EOF)
	{
		char c = file.get();
		a.push_back(c);
	}
	
	file.close();
	return  a;
}
void HuffCode::WriteFile()
{
	string s = "F:\\cocos\\ChineseChess\\proj.win32\\Debug.win32\\LoginHistory\\loginhistory.txt";

	ofstream file;
	file.open(s, ios::binary);
	if (!file.is_open())
	{
		cout << "打开文件失败！" << endl;
		assert(!"打开文件失败");
		return;
	}


	file << mmap.size() << endl;

	map<char, int>::iterator it = mmap.begin();
	for (; it != mmap.end(); it++)
	{
		char c = it->first;
		file << c << '\t' << it->second << endl;

	}


	for (int i = 0; i < mres.size(); i++)
	{
		file << mres[i];
		//file.write(&mres[i], sizeof(mres[i]));
	}
	file.close();

}
struct compare
{
	bool operator ()(const TreeNode *a, const TreeNode *b)
	{
		return a->weight> b->weight;
	}
};
void HuffCode::BuildHuffTree()
{
	priority_queue<TreeNode *, vector<TreeNode *>, compare> pq;

	map<char, int>::iterator it=mmap.begin();
	for (; it != mmap.end(); it++)
	{
		TreeNode *temp = new TreeNode(it->first,it->second);
		pq.push(temp);
		
	}
	while (!pq.empty())
	{
		TreeNode *left = pq.top();
		pq.pop();
		if (pq.empty())
		{
			root = left;
			return;
		}
		TreeNode *right = pq.top();
		pq.pop();
		TreeNode *parent = new TreeNode('0', left->weight + right->weight, left, right);
		left->pparent = parent;
		right->pparent = parent;
		pq.push(parent);
	}
	int a = 0;
}

void HuffCode::PreOrder(TreeNode *root, int num, int level)
{
	if (root->pleft == NULL&&root->pright == NULL)
	{
		unmap[root->key] = Leaf(num, level);
		return;
	}
	PreOrder(root->pleft, num * 2, level + 1);
	PreOrder(root->pright, num * 2 + 1, level + 1);
}
int HuffCode::GetCountChar(unordered_map<char, Leaf> unmap)
{
	int countbit = 0; // 计算总共的位数
	for (auto i : unmap)
	{
		countbit += mmap[i.first] * i.second.bitnum; //buffer里是每个元素的个数
	}
	int numchar = countbit / 8; //所需要传输的字符个数
	if (countbit % 8 != 0)  //8.3==》9 不能整除则加1 确保都能存下，多余的后几位补0
	{
		numchar++;
	}
	return numchar;
}
void HuffCode::Compress(int numchar,string s)
{
	int m = 8; //剩余的位数
	int highbit = numchar * 8 - 1;  //最高位
	mres.assign(numchar, 0);
	for (int i = 0; i < s.size(); i++)
	{
		int k_val = unmap[s[i]].value;
		int k_bit = unmap[s[i]].bitnum;
		while (1)
		{
			int i = highbit / 8;
			int m = highbit % 8 + 1;
			if (k_bit <= m)
			{
				k_val = k_val << (m - k_bit);
				mres[i] ^= k_val;
				highbit -= k_bit;
				m -= k_bit;
				break;
			}
			int ktemp = k_val >> (k_bit - m);
			mres[i] ^= ktemp;
			ktemp = ktemp << (k_bit - m);
			k_val ^= ktemp;
			k_bit = k_bit - m;
			highbit -= m;
		}
	}
}
char HuffCode::Decompress(int &highbit, vector<char> &a)
{
	TreeNode *temp = root;
	while (1)
	{
		if (temp->pleft == NULL&&temp->pright == NULL)
		{
			return temp->key;
		}
		int i = highbit / 8;
		int m = highbit % 8 ;
		if (a[i]&(1<<m)) //判断a[i]（8位）的每一位是0还是1 ，0为左结点，1为右结点
		{
			temp=temp->pright;
		}
		else
		{
			temp=temp->pleft;
		}
		highbit--;
	}
}
void HuffCode::HuffDecompress(vector<char>a, int count)
{
	int highbit = a.size() * 8 - 1;
	while (count)
	{
		resstr += Decompress(highbit, a);
		count--;
	}
	return;
}
HuffCode::~HuffCode()
{
	stack<TreeNode *> stemp1;
	stack<TreeNode *> stemp2;
	stemp1.push(root);
	while (!stemp1.empty())
	{
		TreeNode * cur = stemp1.top();
		stemp1.pop();
		if (cur->pleft)
		{
			stemp1.push(cur->pleft);
		}
		if (cur->pright)
		{
			stemp1.push(cur->pright);
		}
		stemp2.push(cur);
	}
	while(!stemp2.empty())
	{
		TreeNode * cur = stemp2.top();
		stemp2.pop();
		delete cur;
	}
}