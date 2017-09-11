// test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;
class elem_even
{
public:
	bool operator()(int i)
	{
		return i%2? true:false;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	ifstream in_file("C:\\Users\\Mach\\Desktop\\inputfile.txt");
	ofstream even_file("C:\\Users\\Mach\\Desktop\\even.txt");
	ofstream odd_file("C:\\Users\\Mach\\Desktop\\odd.txt");
	ofstream out_file("C:\\Users\\Mach\\Desktop\\out.txt");

	istream_iterator<int> initer(in_file);
	ostream_iterator<int> eveniter(even_file," ");
	ostream_iterator<int> odditer(odd_file," \n");
	ostream_iterator<int> outiter(out_file," ");

	vector<int> numbers;
	istream_iterator<int> eof;
	copy(initer,eof,back_inserter(numbers));
	copy(numbers.begin(),numbers.end(),outiter);

	vector<int>::iterator division=partition(numbers.begin(),numbers.end(),elem_even());

	copy(numbers.begin(),division,odditer);
	copy(division,numbers.end(),eveniter);




	return 0;
}

