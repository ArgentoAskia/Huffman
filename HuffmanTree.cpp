#include <stack>
typedef struct HuffmanNode HuffmanNode,*PHuffmanNode;
struct HuffmanNode
{
	int byte;
	PHuffmanNode lchild;
	PHuffmanNode rchild;
};

bool FillHuffmanCode(std::stack<HuffmanCode> _codestack, HuffmanCode *code);
bool IsLeaves(PHuffmanNode HN);
bool ChooseNode(int *WeightArray, int Arrayzise, int &minbyte1, int &minbyte2);



bool ChooseNode(int *WeightArray, int Arrayzise, int &minbyte1, int &minbyte2)		// 选择两个出现次数最小的成员
{
	int i = 0;
	int exit = 0;
	int j;
	for(j=0; j<Arrayzise; j++)
	{
		if(WeightArray[j]==0)	// 如果数组只剩一个非零的权，说明树已经建立完成
		{
			exit++;
		}
		if(WeightArray[i]==0)		//寻找第一个可用元素作为最小权
		{
			i++;
		}
	}
	if(exit >= Arrayzise-1)
	{
		return false;
	}
	minbyte1 = i;                // 指定第一个元素为最小权元素
	// 指定第一个元素为最小权元素
	int temp;
	int beginplace = i;
	for(i=beginplace; i<Arrayzise; i++)      // 寻找第一小权
	{
		if(WeightArray[i]<WeightArray[minbyte1] && WeightArray[i]!=0)           //找到更加小的权的下标
			minbyte1 = i;
	}
	temp = WeightArray[minbyte1];
	WeightArray[minbyte1] = 0;

	for(j=beginplace; j<Arrayzise; j++)
	{
		if(WeightArray[j]!=0)
		{
			minbyte2 = j;
			break;
		}
	}
	for(i=beginplace; i<Arrayzise; i++)      // 寻找第二小权
	{
		if(WeightArray[i]<WeightArray[minbyte2] && WeightArray[i]!=0)           //找到更加小的权的下标
			minbyte2 = i;
	}
	WeightArray[minbyte1] = temp;
	return true;
}

PHuffmanTree CreateHuffmanTree(int *WeightArray, int Arrayzise)			// 根据统计数组生成哈夫曼树
{
	PHuffmanTree *TreeManager = (PHuffmanTree *)malloc(sizeof(PHuffmanTree)*Arrayzise);
	if(TreeManager==NULL)
	{
		// setlasterror
		return NULL;
	}
	PHuffmanTree ret;
	int i;
	int valid = 0;
	PHuffmanTree NewHfTree;
	// 1. Create
	for(i = 0; i<Arrayzise; i++)
	{
		*(TreeManager+i) = NULL;
		if(WeightArray[i]!=0)
		{
			NewHfTree = (PHuffmanTree) malloc(sizeof(HuffmanTree));
			if(NewHfTree==NULL)
			{
				// setlasterror
				return NULL;
			}
			NewHfTree ->byte = i-128;
			NewHfTree->lchild = NULL;
			NewHfTree->rchild = NULL;
			valid++;
			*(TreeManager+i) = NewHfTree;

		}
	}

	for(i = 1; i<=valid-1; i++)		//
	{
		int min1, min2;
		if(ChooseNode(WeightArray,Arrayzise,min1, min2))
		{
			// 选择两个最小权节点
			NewHfTree = (PHuffmanTree) malloc(sizeof(HuffmanTree));	//  PHuffmanTree->PHuffmanNode
			NewHfTree ->byte = -2; // visit flag
			NewHfTree->lchild = *(TreeManager+min1);

			NewHfTree->rchild = *(TreeManager+min2);
			*(TreeManager+min1) = NULL;
			*(TreeManager+min2) = NewHfTree;

			// 合并Huffman树
			WeightArray[min2] = WeightArray[min1] + WeightArray[min2];
			WeightArray[min1] = 0;

			// 合并权，构成新WeightArray。
		}
	}

	i = 0; // 返回huffmantree首地址
	while(*(TreeManager+i)==NULL)
	{
		i++;
	}
	// set tree size;
	(*(TreeManager+i))->byte = valid;
	ret = *(TreeManager+i);
	free(TreeManager);			// bug_2 Dev 5.11 无法释放管理器内存
	return ret;
}

bool CreateHuffmanCode(PHuffmanTree HT, const char *keyfile, HuffmanCode *&_code, int Arrayzise) // 根据哈夫曼树生成哈夫曼编码
{
	_code = (HuffmanCode *)malloc(sizeof(HuffmanCode) * Arrayzise);
	int i;
	FILE *fp = fopen(keyfile, "w");
	if(fp==NULL)
	{
		return false;
	}
		
	for(i=0; i<Arrayzise; i++)
	{
		*(_code+i) = NULL;
	}			// 初始化

	std::stack<PHuffmanNode> address;
	std::stack<HuffmanCode> codestack;
	// Stack address;
	// Stack code;

	int bytecount = 0;
	int TotalByte = HT->byte;
	// 记录已经获取编码的字节的数量
	// 获取编码的方式是遍历到叶子节点

	PHuffmanNode traveler = HT;
	while(true)
	{
		// Push(code,ToElemPoint("0"));
		// Push(address, ToElemPoint(traveler->lchild));
		if(IsLeaves(traveler))
		{
			if(codestack.size()!=0)	// 判断可去除
			{
				FillHuffmanCode(codestack, _code + traveler->byte + 128); // 将code填充进_code
				bytecount++;		// interface
				fprintf(fp,"%d %s\n", traveler->byte, *(_code + traveler->byte + 128));
				if(bytecount==TotalByte)
					break;
			}
			codestack.pop();
			traveler = address.top();
			while(traveler->byte == -4)
			{
				address.pop();
				codestack.pop();
				traveler = address.top();
			}
			traveler->byte = -4;
			codestack.push("1");
			traveler = traveler->rchild;
		}
		else
		{
			address.push(traveler);
			codestack.push("0");
			traveler->byte = -3;
			traveler = traveler->lchild;
		}
	}
	fclose(fp);
	return true;
}
bool IsLeaves(PHuffmanNode HN)
{
	if(HN->lchild==NULL && HN->rchild==NULL)
	{
		return true;
	}
	else
		return false;
}

bool FillHuffmanCode(std::stack<HuffmanCode> _codestack, HuffmanCode *code)
{
	int stacksize = _codestack.size();
	int i;
	*code = (HuffmanCode)malloc(sizeof(char) * (stacksize+1));
	*(*code+stacksize) = '\0';
	std::stack<HuffmanCode> tmpstack;
	for(i=stacksize-1; i>=0; i--)           // 生成编码
	{

		memcpy(*code + i, _codestack.top(),sizeof(char));
		tmpstack.push(_codestack.top());
		_codestack.pop();
	}
	for(i=0; i<stacksize; i++)              // 还原栈
	{
		_codestack.push(tmpstack.top());
		tmpstack.pop();
	}
	return true;
}
/*
 Test attention:
      VS VC6.0 codeblock去掉函数参数的&
      Dev 5.11+ 增加参数的&
*/
void DeleteHuffmanTree(PHuffmanTree &HT)
{
	if(IsLeaves(HT))
	{
		free(HT);
	}
	else
	{
		DeleteHuffmanTree(HT->lchild);
		HT->lchild=NULL;
		DeleteHuffmanTree(HT->rchild);
		HT->rchild=NULL;
		DeleteHuffmanTree(HT);
	}
}
void DeleteHuffmanCode(HuffmanCode *&_code, int Arraysize)
{
	int i;
	for(i=0; i<Arraysize; i++)
	{
		if(*(_code+i)!=NULL)
		{
			free(*(_code+i));
			*(_code+i) =NULL;
		}
	}
	free(_code);
}

