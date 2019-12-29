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



bool ChooseNode(int *WeightArray, int Arrayzise, int &minbyte1, int &minbyte2)		// ѡ���������ִ�����С�ĳ�Ա
{
	int i = 0;
	int exit = 0;
	int j;
	for(j=0; j<Arrayzise; j++)
	{
		if(WeightArray[j]==0)	// �������ֻʣһ�������Ȩ��˵�����Ѿ��������
		{
			exit++;
		}
		if(WeightArray[i]==0)		//Ѱ�ҵ�һ������Ԫ����Ϊ��СȨ
		{
			i++;
		}
	}
	if(exit >= Arrayzise-1)
	{
		return false;
	}
	minbyte1 = i;                // ָ����һ��Ԫ��Ϊ��СȨԪ��
	// ָ����һ��Ԫ��Ϊ��СȨԪ��
	int temp;
	int beginplace = i;
	for(i=beginplace; i<Arrayzise; i++)      // Ѱ�ҵ�һСȨ
	{
		if(WeightArray[i]<WeightArray[minbyte1] && WeightArray[i]!=0)           //�ҵ�����С��Ȩ���±�
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
	for(i=beginplace; i<Arrayzise; i++)      // Ѱ�ҵڶ�СȨ
	{
		if(WeightArray[i]<WeightArray[minbyte2] && WeightArray[i]!=0)           //�ҵ�����С��Ȩ���±�
			minbyte2 = i;
	}
	WeightArray[minbyte1] = temp;
	return true;
}

PHuffmanTree CreateHuffmanTree(int *WeightArray, int Arrayzise)			// ����ͳ���������ɹ�������
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
			// ѡ��������СȨ�ڵ�
			NewHfTree = (PHuffmanTree) malloc(sizeof(HuffmanTree));	//  PHuffmanTree->PHuffmanNode
			NewHfTree ->byte = -2; // visit flag
			NewHfTree->lchild = *(TreeManager+min1);

			NewHfTree->rchild = *(TreeManager+min2);
			*(TreeManager+min1) = NULL;
			*(TreeManager+min2) = NewHfTree;

			// �ϲ�Huffman��
			WeightArray[min2] = WeightArray[min1] + WeightArray[min2];
			WeightArray[min1] = 0;

			// �ϲ�Ȩ��������WeightArray��
		}
	}

	i = 0; // ����huffmantree�׵�ַ
	while(*(TreeManager+i)==NULL)
	{
		i++;
	}
	// set tree size;
	(*(TreeManager+i))->byte = valid;
	ret = *(TreeManager+i);
	free(TreeManager);			// bug_2 Dev 5.11 �޷��ͷŹ������ڴ�
	return ret;
}

bool CreateHuffmanCode(PHuffmanTree HT, const char *keyfile, HuffmanCode *&_code, int Arrayzise) // ���ݹ����������ɹ���������
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
	}			// ��ʼ��

	std::stack<PHuffmanNode> address;
	std::stack<HuffmanCode> codestack;
	// Stack address;
	// Stack code;

	int bytecount = 0;
	int TotalByte = HT->byte;
	// ��¼�Ѿ���ȡ������ֽڵ�����
	// ��ȡ����ķ�ʽ�Ǳ�����Ҷ�ӽڵ�

	PHuffmanNode traveler = HT;
	while(true)
	{
		// Push(code,ToElemPoint("0"));
		// Push(address, ToElemPoint(traveler->lchild));
		if(IsLeaves(traveler))
		{
			if(codestack.size()!=0)	// �жϿ�ȥ��
			{
				FillHuffmanCode(codestack, _code + traveler->byte + 128); // ��code����_code
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
	for(i=stacksize-1; i>=0; i--)           // ���ɱ���
	{

		memcpy(*code + i, _codestack.top(),sizeof(char));
		tmpstack.push(_codestack.top());
		_codestack.pop();
	}
	for(i=0; i<stacksize; i++)              // ��ԭջ
	{
		_codestack.push(tmpstack.top());
		tmpstack.pop();
	}
	return true;
}
/*
 Test attention:
      VS VC6.0 codeblockȥ������������&
      Dev 5.11+ ���Ӳ�����&
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

