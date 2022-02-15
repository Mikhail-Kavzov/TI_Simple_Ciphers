#include<iostream>
using namespace std;
const int buf = 400;
const wchar_t Letters = 33;
vector<wchar_t> Alphabet = {L'\x410',L'\x411',L'\x412',L'\x413',L'\x414', L'\x415',L'\x401',L'\x416', L'\x417',L'\x418', L'\x419',
L'\x41A',L'\x41B', L'\x41C',L'\x41D',L'\x41E', L'\x41F', L'\x420',L'\x421',L'\x422',L'\x423',L'\x424', L'\x425',L'\x426',L'\x427',
L'\x428',L'\x429', L'\x42A',L'\x42B',L'\x42C',L'\x42D',L'\x42E', L'\x42F'};

const unsigned char Column[16] = { 0,3,2,1,3,0,1,2,2,1,0,3,1,2,3,0 };
int find(wchar_t value)
{
	for (int i = 0; i < Alphabet.size(); i++)
	{
		if (Alphabet[i] == value)
			return i;
	}
	return 255;
}

wstring CheckCollisionRus(wstring& key) {

	wstring newkey;
	for (int i = 0; i < key.length(); i++) {
		if ((key[i] >= L'\x410' && key[i] <= L'\x42F') || (key[i] == L'\x401'))
		{
			newkey.push_back(key[i]);
		}
	}
	if (newkey.length() == 0)
		throw gcnew System::String(L"Invalid key. Key must contain russian symbols");
	return newkey;
}
wstring CheckCollisionFigures(wstring& key) {
	wstring newkey;
	for (int i = 0; i < key.length(); i++) {
		if ((key[i] >= L'\x30' && key[i] <= L'\x39'))
		{
			newkey.push_back(key[i]);
		}
	}
	if (newkey.length() == 0)
		throw gcnew System::String(L"Invalid key. Key must contain figures");
	return newkey;
}

void  UpperWstr(std::wstring &str)
{   
	
	int len = str.length();
	for (int i = 0; i < len; i++)
	{
		if ((((str[i] >= L'\x430') && (str[i] <= L'\x44f')) || (str[i] == L'\x451')))  //430= a 44f=я 
		{
			if (str[i] == L'\x451') // ё
			{
				str[i] = L'\x401'; //Ё
			}
			else str[i] = str[i] - (L'\x430' - L'\x410'); //a-A
		}
	}

}

wchar_t UpCaseRus(wchar_t& value)
{
	if ((value >= L'\x430' && value <= L'\x44F') || (value == L'\x451'))
	{
		if (value == L'\x451')
			return L'\x401';
			return value - (L'\x430' - L'\x410');
	}
	return value;
}
wchar_t UpCaseEng(wchar_t value)
{
	if (value >= L'\x61' && value <= L'\x7A')  // a till z
	{
		return  value - (L'\x61' - L'\x41'); //a-A
	}
	return value;
}
void VizhenerEncrypt( std::wstring&key,std::wifstream&in,std::wofstream&out)
{


	UpperWstr(key);
	key=CheckCollisionRus(key);
	
	unsigned long ksize = key.length();
	wchar_t mas[buf / 2];
	while (in)
	{   //progressive key
		in.read(reinterpret_cast<wchar_t*>(mas), buf);

		int count = in.gcount();

		int j = 0;

		for (int i = 0; i < count; i++)
		{


			mas[i]=UpCaseRus(mas[i]);

			if ((mas[i] >= L'\x410' && mas[i] <= L'\x42F') || (mas[i] == L'\x401'))
			{
				int Kpos = find(key[j]);
				mas[i] = Alphabet[(find(mas[i]) + Kpos) % Letters];

				key[j] = Alphabet[(Kpos + 1) % Letters];

				if (j + 1 < ksize)
					j++;
				else j = 0;


			}

		}
		out.write(reinterpret_cast<wchar_t*>(mas), count);
	}

}
void VizhenerDecrypt(std::wstring& key, std::wifstream& in, std::wofstream& out)
{

	UpperWstr(key);
	key = CheckCollisionRus(key);
	int ksize = key.length();
	wchar_t mas[buf / 2];
	while (in)
	{  
		in.read(reinterpret_cast<wchar_t*>(mas), buf);
		int count = in.gcount();
		int j = 0;

		for (int i = 0; i < count; i++)
		{


			mas[i] = UpCaseRus(mas[i]);

			if ((mas[i] >= L'\x410' && mas[i] <= L'\x42F') || (mas[i] == L'\x401'))
			{
				int Kpos = find(key[j]);
				int del = find(mas[i]) - Kpos;

				mas[i] = (del < 0) ? Alphabet[Letters + del] : Alphabet[del % Letters];

				key[j] = Alphabet[(Kpos + 1) % Letters];

				if (j + 1 < ksize)
					j++;
				else j = 0;
			}

		}
		out.write(reinterpret_cast<wchar_t*>(mas), count);
	}

}

void RailwayDecrypt(std::wstring& key, std::wifstream& in, std::wofstream& out)
{
	key = CheckCollisionFigures(key);
	unsigned long klen = ::wcstoul(key.c_str(), L'\0', 10);
	if (klen == 0)
		throw gcnew System::String(L"Key value should be more than 0");
	std::vector<wchar_t> src;
	std::vector<wchar_t> res;
	wchar_t mas[buf / 2];
	while (in)
	{
		in.read(reinterpret_cast<wchar_t*>(mas), buf);

		int count = in.gcount();
		int j = 0;
		for (int i = 0; i < count; i++)
		{
			mas[i] = UpCaseRus(mas[i]);

			if ((mas[i] >= L'\x410' && mas[i] <= L'\x42F') || (mas[i] == L'\x401'))
			{
				src.push_back(mas[i]);
			}
		}
	}
		res.resize(src.size());
		if (!(klen == 1 || klen > src.size()))
		{
			int maxdist = 2 * klen - 2;
			int ind = maxdist;
			int curr = maxdist;
			int pos;
			int m = 0;
			for (int i = 0; i < klen; i++)
			{

				pos = i;
				while (pos < src.size())
				{
					res[pos] = src[m];
					if (ind != maxdist)
						ind = maxdist - ind;
					pos += ind;
					++m;
				}
				curr -= 2;
				ind = maxdist - curr;
			}
		}
		else res = src;
		for (auto& ptr : res)
			out << ptr;

		res.clear();
		src.clear();
}
void RailwayEncrypt(std::wstring& key, std::wifstream& in, std::wofstream& out)
{
	key = CheckCollisionFigures(key);
	unsigned long klen = ::wcstoul(key.c_str(), L'\0', 10);
	if (klen == 0)
		throw gcnew System::String(L"Key value should be more than 0");
	std::vector<wchar_t> src;
	std::vector<wchar_t> res;
	wchar_t mas[buf / 2];
	while (in)
	{
		in.read(reinterpret_cast<wchar_t*>(mas), buf);
		int count = in.gcount();
		int j = 0;
		for (int i = 0; i < count; i++)
		{
			mas[i] = UpCaseRus(mas[i]);

			if ((mas[i] >= L'\x410' && mas[i] <= L'\x42F') || (mas[i] == L'\x401'))
			{
				src.push_back(mas[i]);
			}
		}
	}

		if (!(klen == 1 || klen > src.size()))
		{
			int maxdist = 2 * klen - 2;
			int ind = maxdist;
			int curr = maxdist;
			int pos;
			for (int i = 0; i < klen; i++)
			{

				pos = i;
				while (pos < src.size())
				{
					res.push_back(src[pos]);
					if (ind != maxdist)
						ind = maxdist - ind;
					pos += ind;
				}
				curr -= 2;
				ind = maxdist - curr;
			}
		}
		else res = src;
		for (auto& ptr : res)
			out << ptr;
		
		res.clear();
		src.clear();
}


void GridEncrypt(std::wifstream& in, std::wofstream& out)
{
	

	const int size = 4;
	wchar_t grid[size][size];
	
	std::vector<wchar_t> src;
	wchar_t mas[buf / 2];
	while (in)
	{
		in.read(reinterpret_cast<wchar_t*>(mas), buf);

		int count = in.gcount();

		int j = 0;

		for (int i = 0; i < count; i++)
		{
			mas[i] = UpCaseEng(mas[i]);

			if (mas[i] >= L'\x41' && mas[i] <= L'\x5A')
			{

				src.push_back(mas[i]);

			}

		}
	}
		int k = -1;
		int vsize = src.size();
		int counter = 0;
		while (counter < vsize)
		{
			k = -1;
			for (int col = 0; col < size; col++)
			{
				for (int row = 0; row < size; row++)
				{
					++k;
					if (counter < vsize)
						grid[row][Column[k]] = src[counter];
					else
						grid[row][Column[k]] = L'\x61'; //*
					++counter;
				}
			}

			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					out << grid[i][j];
		}
		src.clear();
}


void GridDecrypt(std::wifstream& in, std::wofstream& out)
{
	const int size = 4;
	const int gridcount = size * size;
	wchar_t grid[size][size];

	std::vector<wchar_t> src;
	wchar_t mas[buf / 2];
	while (in)
	{
		in.read(reinterpret_cast<wchar_t*>(mas), buf);

		int count = in.gcount();

		int j = 0;

		for (int i = 0; i < count; i++)
		{
			mas[i] = UpCaseEng(mas[i]);
			if (mas[i] >= L'\x41' && mas[i] <= L'\x5A')
			{

				src.push_back(mas[i]);

			}

		}
	}
	
	
	int vsize = src.size();
	

		int counter = 0;
		int k = -1;
		while (counter < vsize)
		{
			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
				{
					if (counter >= vsize)
						grid[i][j] = L'\x61'; // если число символов в массиве не кратно размеру решетки - добавляем в конец произвольный
					else
					grid[i][j] = src[counter++];
				}


			k = -1;
			for (int col = 0; col < size; col++)
			{
				for (int row = 0; row < size; row++)
				{
					++k;
					
						out << grid[row][Column[k]];
				}
			}

		}



	src.clear();

}
