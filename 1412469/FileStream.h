#ifndef __FILESTREAM_H__
#define __FILESTREAM_H__
#include <string>
#include <vector>
#include <fstream>
#include "Category.h"

using namespace std;

class FileStream
{
private:
	string filename;
public:
	FileStream();
	FileStream(string _filename);
	~FileStream();

	vector<Category> ReadFile();
	void SaveFile(vector<Category> vCat);
};

#endif