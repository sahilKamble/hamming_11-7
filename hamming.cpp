#include<iostream>
#include <stdio.h>
using namespace std;
 
bitset<12> hencode(bitset<8> b);
bitset<8> hdecode(bitset<12> b);

bitset<12> setParity(bitset<12> b);
bitset<12> hcorrect(bitset<12> b);
bool isPowerOfTwo(unsigned x);

int main() {
	char inp;
	string rec,s;

	std::cout << "enter a character to encode (if multiple chars are enterd only first char will be considered): ";
	std::cin >> s;
	inp = s[0];
	bitset<8> bs = bitset<8>(inp) << 1;
	std::cout << "entered character in ASCII is " << bs.to_string().substr(0,bs.size()-1) << std::endl;
	bitset<12> en = hencode(bs);
	std::cout << "encoded message is " << en.to_string().substr(0,en.size()-1) << std::endl;

	std::cout << "enter received message in binary ";
	cin >> rec;
	bitset<12> brec = bitset<12>(rec) << 1;
	std::cout << "received message is " << brec.to_string().substr(0,brec.size()-1) << std::endl << std::endl;
	brec = hcorrect(brec);
	std::cout << "corrected message is " << brec.to_string().substr(0,brec.size()-1) << std::endl << std::endl;
	bitset<8> de = hdecode(brec) >> 1;
	char op = de.to_ulong();
	std::cout << "decoded message is " << de.to_string().substr(1,de.size()) << std::endl;
	std::cout << "decoded message in ASCII : " << op << std::endl;

}

bitset<12> hencode(bitset<8> b){
	std::bitset<12> en; 
	unsigned i, j=0;
	
	for( i=0; i < en.size(); i++)
	{
		if( !isPowerOfTwo(i)) 
		en[i] = b[j++];
	}
	
	return setParity(en);
}

bitset<8> hdecode(bitset<12> b){
	std::bitset<8> de; 
	unsigned i, j=0;
	for( i=0; i < b.size(); i++)
	{
		if( !isPowerOfTwo(i)) 
		de[j++] = b[i];
	}
	return de;
}

bitset<12> setParity(bitset<12> en)
{
	unsigned x = 0, i;
	for( i=0; i < en.size(); i++)
	{
		if( en[i]) 
		{
			x = x ^ i;
		}
	}
	for( i=0; i < en.size(); i++)
	{
		if( isPowerOfTwo(i))
		{
			en[i] = (x & 1);
			x >>= 1;
		}
	}
	return en;
}

bitset<12> hcorrect(bitset<12> en)
{
	unsigned x = 0, i;
	for( i=0; i < en.size(); i++)
	{
		if( en[i]) 
		{
			x = x ^ i;
		}
		
	}
	if ( x != 0)
	{
		std::cout << "correction needed in bit " << x << std::endl;
		en[x] = !en[x];
	}
	else 
	std::cout << "no correction needed" << std::endl;

	return en;
}

bool isPowerOfTwo(unsigned x)
{
    return (x != 0) && ((x & (x - 1)) == 0);
}