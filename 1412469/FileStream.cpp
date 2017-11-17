#include "stdafx.h"
#include "FileStream.h"
#include <locale>
#include <codecvt>
#include <sstream>


FileStream::FileStream()
{
}

FileStream::FileStream(string _filename)
{
	this->filename = _filename;
}

FileStream::~FileStream()
{
}

vector<Category> FileStream::ReadFile()
{
	vector<Category> vCat;
	locale loc(locale(), new codecvt_utf8<wchar_t>);
	wifstream ifs(this->filename);
	ifs.imbue(loc);

	if (ifs.is_open())
	{
		while (!ifs.eof())
		{
			wstring buffer, item;
			getline(ifs, buffer);

			if (!buffer.empty())
			{
				wstringstream ss(buffer);
				vector<wstring> items;

				while (getline(ss, item, L';')) items.push_back(item);
				Category cat(items[0], items[1], stoi(items[2]));
				vCat.push_back(cat);
			}
			else break;
		}
	}

	ifs.close();

	return vCat;
}

void FileStream::SaveFile(vector<Category> vCat)
{
	locale loc(locale(), new codecvt_utf8<wchar_t>);
	wofstream ofs(this->filename);
	ofs.imbue(loc);

	for (int i = 0; i < vCat.size(); ++i)
	{
		wstring buffer = vCat[i].GetCategoryType() + L';' +
			vCat[i].GetCategoryInformation() + L';' +
			to_wstring(vCat[i].GetCategoryAmount());
		
		ofs << buffer;
		if (i < vCat.size() - 1) ofs << endl;
	}
	ofs.close();
}
