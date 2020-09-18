#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

bool isPowerOfTwo(unsigned x)
{
    return (x != 0) && ((x & (x - 1)) == 0);
}

int ham_check(vector<bool> &en)
{
	unsigned x = 0, i;
	for( i=0; i < en.size(); i++)
	{
        if( en[i]) x = x ^ i;
	}
	return x;
}

void setParity(vector<bool> &en)
{
	unsigned x = 0, i;
	for( i=0; i < en.size(); i++)
	{
		if( en[i]) x = x ^ i;
	}
	for( i=0; i < en.size(); i++)
	{
		if( isPowerOfTwo(i))
		{
			en[i] = (x & 1);
			x >>= 1;
		}
	}
}

void ham_en(vector<bool> &b, vector<bool> &en)
{
    unsigned i, j = 0;

    en.push_back(0);
   
    for( i = 1; j < b.size(); i++)
    {
        if( !isPowerOfTwo(i))
            en.push_back(b[j++]);
        else 
            en.push_back(0);
    }

    setParity(en);
}

int main() 
{
    unsigned i;
    vector<bool> b, en;
    string s;

    cout << "Enter input data bits to transfer (any char other than 0 will be considered as 1) : ";
    cin >> s;

    for(i = 0 ; i < s.size(); i++) b.push_back(bool(int(s[i])-48));

    ham_en(b, en);

    cout << "encoded data bits = ";
    for(i = 1; i < en.size(); i++) cout << en[i];
    cout << endl;

    cout << "Enter received data bits : ";
    cin >> s;

    b.clear();
    b.push_back(0);

    for(i = 0 ; i < s.size(); i++)
    b.push_back(bool(int(s[i])-48));

    int c = ham_check(b);
    if(c)
    {
        cout << "correction needed at bit " << c << endl;
        b[c] = !b[c];
    }
    else
    {
        cout << "no correction needed" << endl;
    }

    cout << "corrected data bits = " ;
    for(i = 1; i < b.size(); i++) cout << b[i];

    cout << endl;

    return 0;
}