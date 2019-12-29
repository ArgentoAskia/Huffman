#include <windows.h>
void Debug_ArrayCount(int *array, int size, const char *file)
{
	int i= 0;
	printf("-------- ͳ���ļ��ֽ� --------\n");
	printf("���ļ���%s���У�\n", file);
	for(i; i<size; i++)
	{
		if(array[i]!=0)
			printf("�ֽ�Ϊ %d �����ݳ��ֵĴ���Ϊ��%d\n", i-128, array[i]);
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
	printf("-------- �鿴���������� --------\n");
	printf("��HuffmanCode blank�У�\n");
	for(i; i<size-1; i++)
	{
		if(_code[i]!=NULL)
		{
			printf("�ֽ�Ϊ %d �����ݣ�����Ϊ��%s ���볤�ȣ�%d\n", i-128, _code[i],strlen(_code[i]));
		}
	}
	printf("--------------------------------\n");
}
void PrevOrderTraveler(PHuffmanTree Tree, int i)
{


	printf("�����Ϊ %d �Ľڵ�ĵ�ַΪ: %d, ��Я��������Ϊ��%d\n", i, Tree, Tree->byte);
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
	printf("-------- �鿴���������ṹ --------\n");
	printf("��������Ϊ-2�����������ڹ�����������г��ֵ����ݾ�Ϊ��������\n");
	printf("huffman tree���ݴ洢����:\n");
	int i = 1;
	PrevOrderTraveler(Tree, i);
	printf("----------------------------------\n");
}
void TestFile(const char *file, const char *DecompressFile)
{
	printf("-------- ���Դ�ļ��ͽ�ѹ�ļ��Ƿ���ͬ --------\n");
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
			
			printf("Դ�ļ��ͽ�ѹ�ļ�����ͬ\n");
			return;
		}
	}
	printf("Դ�ļ��ͽ�ѹ�ļ���ͬ\n");
	fclose(fp);
	fclose(defp);
}
// test function
/*
void setlasterror(void (*DEfunc)(void *,...), const char *fomat, ...)
{

}
*/


