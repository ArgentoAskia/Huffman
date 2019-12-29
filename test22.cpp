#define _DEBUG_
#include "HuffmanCompressor.hpp"
#include "ExtraHuffmanCompressor.hpp"
int main() 
{
	printf("********** 基于哈夫曼树算法的文件压缩演示 **********\n");
	printf("Target: TestFile\\test.txt\n");
	printf("Size of File: %d\n",CountFileByte("TestFile\\ReserveMe.dat"));
	printf("Compressed target: TestFile\\CompressFile1.dat\n");
	printf("Compressing...\n");
	CompressBinaryFile("TestFile\\test.txt", "TestFile\\Key.key", "TestFile\\CompressFile1.dat");
	printf("Size of Compressed File: %d\n",CountFileByte("TestFile\\CompressFile1.dat"));
	// CompressBinaryFile(要加压的文件, 秘钥存储位置, 加压后文件存储位置);
	printf("Decompressed target: TestFile\\DecompressFile2.dat\n");
	printf("Decompressing...\n");
	DecompressBinaryFile("TestFile\\CompressFile1.dat", "TestFile\\Key.key","TestFile\\DecompressFile2.dat","TestFile\\ReserveMe.dat");
	// DecompressBinaryFile(加压文件所在位置, 秘钥存储位置, 解压文件后文件存储位置);
	return 0;
}
