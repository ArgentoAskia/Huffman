#include <windows.h>
void Debug_ArrayCount(int *array, int size, const char *file)
{
	int i= 0;
	printf("-------- 统计文件字节 --------\n");
	printf("在文件（%s）中：\n", file);
	for(i; i<size; i++)
	{
		if(array[i]!=0)
			printf("字节为 %d 的数据出现的次数为：%d\n", i-128, array[i]);
	}
	printf("------------------------------\n");
}
void SetDebugMode(const char *file,int mode)
{
	if(mode==1)
	{
		printf("*************** Compress debug mode ***************\n");
		printf("In file:%s\n", file);
	}
	else if(mode==0)
	{
		printf("*************** Decompress debug mode ***************\n");
		printf("In file:%s\n", file);
	}
}
void EndDebugMode()
{
	printf("******************************************\n\n");
}
void Debug_HuffmanCode(HuffmanCode *_code, int size)
{
	int i = 0;
	printf("-------- 查看哈夫曼编码 --------\n");
	printf("在HuffmanCode blank中：\n");
	for(i; i<size-1; i++)
	{
		if(_code[i]!=NULL)
		{
			printf("字节为 %d 的数据：编码为：%s 编码长度：%d\n", i-128, _code[i],strlen(_code[i]));
		}
	}
	printf("--------------------------------\n");
}
void PrevOrderTraveler(PHuffmanTree Tree, int i)
{


	printf("树深度为 %d 的节点的地址为: %d, 所携带的数据为：%d\n", i, Tree, Tree->byte);
	if(IsLeaves(Tree))
	{
		return;
	}
	else
	{
		i++;
		PrevOrderTraveler(Tree->lchild, i);
		PrevOrderTraveler(Tree->rchild, i);

	}
}
void Debug_HuffmanTree(PHuffmanTree Tree)
{
	printf("-------- 查看哈夫曼树结构 --------\n");
	printf("出现数据为-2或者其他不在哈夫曼编码表中出现的数据均为正常现象\n");
	printf("huffman tree数据存储如下:\n");
	int i = 1;
	PrevOrderTraveler(Tree, i);
	printf("----------------------------------\n");
}
void TestFile(const char *file, const char *DecompressFile)
{
	printf("-------- 检查源文件和解压文件是否相同 --------\n");
	FILE *fp = NULL;
	FILE *defp = NULL;
	fp = fopen(file,"r");
	defp = fopen(DecompressFile, "r");
	char cmp1 = 0;
	char cmp2 = 0;
	int i = 0;
	cmp1 = fgetc(fp);
	cmp2 = fgetc(defp);
	while(!feof(fp) && !feof(defp))
	{
		i++;
		if(cmp1==cmp2)
		{
			cmp1 = fgetc(fp);
			cmp2 = fgetc(defp);
			
		}
		else
		{
			
			printf("源文件和解压文件不相同\n");
			return;
		}
	}
	printf("源文件和解压文件相同\n");
	fclose(fp);
	fclose(defp);
}
// test function
/*
void setlasterror(void (*DEfunc)(void *,...), const char *fomat, ...)
{

}
*/


