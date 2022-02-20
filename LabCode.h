#include<iostream>
using namespace std;
const int buf = 400;
const int Letters = 33;
struct A{
	wchar_t value;
	unsigned char pos;
	wchar_t next;
}
Alphabet[Letters] = { { L'\x401',6,L'\x416'}, {L'\x410',0,L'\x411'}, {L'\x411',1,L'\x412'}, {L'\x412',2,L'\x413'},
	{L'\x413',3,L'\x414'},{ L'\x414',4,L'\x415'}, {L'\x415',5,L'\x401'},{ L'\x416',7,L'\x417'}, {L'\x417',8,L'\x418'},
	{L'\x418',9,L'\x419'}, {L'\x419',10,L'\x41A'},{L'\x41A',11,L'\x41B'},{L'\x41B',12,L'\x41C'}, {L'\x41C',13,L'\x41D'},
	{L'\x41D',14,L'\x41E'},{L'\x41E',15,L'\x41F'},{ L'\x41F',16,L'\x420'}, {L'\x420',17,L'\x421'},{L'\x421',18,L'\x422'},
	{L'\x422',19,L'\x423'},{L'\x423',20,L'\x424'},{L'\x424',21,L'\x425'},{ L'\x425',22,L'\x426'},{L'\x426',23,L'\x427'},
	{L'\x427',24,L'\x428'},{L'\x428',25,L'\x429'},{L'\x429',26,L'\x42A'}, {L'\x42A',27,L'\x42B'},{L'\x42B',28,L'\x42C'},
	{L'\x42C',29,L'\x42D'},{L'\x42D',30,L'\x42E'},{L'\x42E',31,L'\x42F'}, {L'\x42F',32,L'\x410'} };

const unsigned char Column[16] = { 0,3,2,1,3,0,1,2,2,1,0,3,1,2,3,0 }; 



int find(wchar_t val)
{
	int razn = val - L'\x410';
	if (razn < 0)
		return 0;
	return razn + 1;
}

wstring CheckCollisionRus(wstring& key) {  

	wstring newkey;
	for (int i = 0; i < key.length(); i++) {
		if ((key[i] >= L'\x410' && key[i] <= L'\x42F') || (key[i] == L'\x401'))//A..Я Ё
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
		if ((key[i] >= L'\x30' && key[i] <= L'\x39')) // 0..9
		{
			newkey.push_back(key[i]);
		}
	}
	if (newkey.length() == 0)
		throw gcnew System::String(L"Invalid key. Key must contain figures");
	return newkey;
}
wchar_t findNewPos(int val)
{
	for (int i = 0; i < Letters; i++)
		if (Alphabet[i].pos == val)
			return Alphabet[i].value;
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
	key=CheckCollisionRus(key); //проверка ключа
	
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
				int indK = find(key[j]);
				int indM = find(mas[i]);
				int newPos=(Alphabet[indM].pos + Alphabet[indK].pos) % Letters;
				mas[i] = findNewPos(newPos);
				key[j] = Alphabet[indK].next;

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
				int indK = find(key[j]);
				int indM = find(mas[i]);
				int newPos = (Alphabet[indM].pos + Letters - Alphabet[indK].pos) % Letters;//a=(c+n-k) mod n
				mas[i] = findNewPos(newPos);  

				key[j] = Alphabet[indK].next;

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
	key = CheckCollisionFigures(key); //проверка ключа
	unsigned long klen = ::wcstoul(key.c_str(), L'\0', 10); //перевод в число
	if (klen == 0) // если ключ 0 , то нельзя построить изгородь т к высота = 0
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

			if ((mas[i] >= L'\x410' && mas[i] <= L'\x42F') || (mas[i] == L'\x401')) //А..Я Ё
			{
				src.push_back(mas[i]);
			}
		}
	}
		res.resize(src.size());
		if (!(klen == 1 || klen > src.size())) // если ключ=1 или >числа обрабатываемых символов - сразу записываем в файл
		{
			int maxdist = 2 * klen - 2;  //max расстояние между 2мя эл-тами в строке изгороди
			int ind = maxdist; // расстояние 
			int curr = maxdist;  //начальное расстояние между эл-тами строки изгороди для каждой строки (после прохода каждой строки, уменьшается на 2)
			int pos; //позиция шифруемого индекса в рез массиве
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
	key = CheckCollisionFigures(key); //проверка ключа
	unsigned long klen = ::wcstoul(key.c_str(), L'\0', 10); //перевод в число
	if (klen == 0) //если ключ=0, нельзя построить изгородь, высота = 0
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

			if ((mas[i] >= L'\x410' && mas[i] <= L'\x42F') || (mas[i] == L'\x401')) // A..Я Ё
			{
				src.push_back(mas[i]);
			}
		}
	}
	int vsize = src.size();

		if (!(klen == 1 || klen >vsize))
		{
			int maxdist = 2 * klen - 2; //max расстояние между 2мя символами в строке изгородии
			int ind = maxdist; //расстояние между эл-тами
			int curr = maxdist; //начальное расстояние между эл-тами изгороди в текущей строке
			int pos; //позиция эл-та в зашифрованном массиве
			for (int i = 0; i < klen; i++)
			{

				pos = i;
				while (pos < vsize)
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
	wchar_t grid[size][size]; //сетка
	
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

			if (mas[i] >= L'\x41' && mas[i] <= L'\x5A') //A..Z
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
						grid[row][Column[k]] = src[counter];  //вставляем в нужную позицию исходные данные
					else
						grid[row][Column[k]] = L'\x61'; //добавляем 'a' в сетку, полностью заполняя ее
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
						grid[i][j] = L'\x61'; // если число символов в массиве не кратно размеру решетки - дополняем решетку символом 'a'
					else
					grid[i][j] = src[counter++];
				}


			k = -1;
			for (int col = 0; col < size; col++) //вывод в файл
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
