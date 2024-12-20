#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED




#include <iostream>
#include <string.h>
#include <algorithm>
#include <vector>
#include <assert.h>
#include <math.h>


using namespace std;


class bigInt
{
    //--------------------------By- Prince Pratap------------------------------//


private:
    //-----------------------------DATA MEMBERS-------------------------------//


    string num = "0";
    bool isNeg = false;


    //-----------------------------------------------------------------------//


    //-------------------------VALIDITY CHECK AND CONVERSION-----------------------//


    bool isDigit(char ch)
    {
        return '0' <= ch and ch <= '9';
    }


    bool isValid(string num)
    {
        switch (num[0])
        {
        case '+':
            break;
        case '-':
            break;
        default:
            if (!isDigit(num[0]))
                return false;
        }
        int i = 1;
        while (i < num.length())
        {
            if (!isDigit(num[i]))
                return false;
            i++;
        }
        return true;
    }


    bigInt convert(string num)
    {


        bigInt b;
        b.isNeg = (num[0] == '-');


        int i = num[0] == '-' or num[0] == '+';


        while (i < num.length() and num[i] == '0')
            i++;


        b.num = num.substr(i);


        if (b.num == "")
            b.num += '0';


        return b;
    }
    //-----------------------------------------------------------------------//


public:
    //-----------------------------CONSTRUCTORS-------------------------------//
    bigInt()
    {
        this->num = "";
        this->isNeg = false;
    }
    bigInt(string num)
    {
        assert(isValid(num));


        *this = convert(num);
    }
    bigInt(int num)
    {
        *this = to_string(num);
    }
    //------------------------------------------------------------------------//


    //-------------------------INPUT/OUTPUT OPERATORS-------------------------//
    friend istream &operator>>(istream &input, bigInt &b)
    {
        string s;
        input >> s;
        assert(b.isValid(s));
        b = b.convert(s);
        return input;
    }
    friend ostream &operator<<(ostream &output, const bigInt &b)
    {
        if (b.isNeg)
            output << "-" << b.num;
        else
            output << b.num;
        return output;
    }
    //------------------------------------------------------------------------//


    //-------------------------ASSIGNMENT OPERATORS--------------------------//
    void operator=(const bigInt &b)
    {
        this->num = b.num;
        this->isNeg = b.isNeg;
    }
    void operator=(const string &num)
    {
        assert(isValid(num));
        *this = convert(num);
    }
    void operator=(const int &num)
    {
        string x = to_string(num);
        *this = x;
    }
    //------------------------------------------------------------------------//


    //-------------------------COMPARISON OPERATORS--------------------------//
    bool operator>(const bigInt &b)
    {


        if (this->num.length() > b.num.length())
            return true;
        else if (this->num.length() < b.num.length())
            return false;


        return this->num > b.num;
    }
    bool operator>=(const bigInt &b)
    {
        return *(this) > b or this->num >= b.num;
    }
    bool operator<(const bigInt &b)
    {
        return !(*this >= b);
    }
    bool operator<=(const bigInt &b)
    {
        return !(*this > b);
    }
    bool operator==(const bigInt &b)
    {
        return this->num == b.num and this->isNeg == b.isNeg;
    }
    bool operator!=(const bigInt &b)
    {
        return !((*this) == b);
    }
    //----------------------------------------------------------------------//
    //-------------------------ARITHMETIC OPERATORS--------------------------//
    bigInt operator+(const bigInt &b)
    {
        bool differentSigns = (b.isNeg ^ this->isNeg);
        bigInt result;


        if (differentSigns)
        {
            if (b.isNeg)
                result = convert(subtract(this->num, b.num));
            else
                result = convert(subtract(b.num, this->num));
        }
        else
        {
            result = convert(add(this->num, b.num));
            result.isNeg = (this->isNeg and b.isNeg);
        }
        return result;
    }
    bigInt operator-(const bigInt &b)
    {
        bool differentSigns = (b.isNeg ^ this->isNeg);
        bigInt result;


        if (differentSigns)
        {
            if (b.isNeg)
                result = convert(add(this->num, b.num));
            else
            {
                result = convert(add(b.num, this->num));
                result.isNeg = true;
            }
        }
        else
        {
            if (!this->isNeg and !b.isNeg)
                result = convert(subtract(this->num, b.num));
            else
                result = convert(subtract(b.num, this->num));
        }
        return result;
    }
    bigInt operator*(const bigInt &b)
    {
        bigInt result;
        result = convert(multiply(this->num, b.num));
        result.isNeg = this->isNeg ^ b.isNeg;
        return result;
    }
    bigInt operator/(const bigInt &b)
    {
        assert(b.num != "0");
        bigInt result;
        result = convert(divide(this->num, b.num));
        result.isNeg = (result.num != "0" and (this->isNeg ^ b.isNeg));
        return result;
    }
    bigInt operator%(const bigInt &b)
    {
        bigInt result;
        result = convert(modulo(this->num, b.num));
        result.isNeg = this->isNeg;
        return result;
    }
    //------------------------------------------------------------------------//


private:
    //-----------------------------STRING / 2--------------------------------//
    string divideBy2(bigInt x)
    {
        int current = 0;
        string res = "";
        for (int i = 0; i < x.num.length(); i++)
        {
            current = current * 10 + (x.num[i] - '0');


            if (current < 2)
            {
                if (i > 0)
                {
                    res += '0';
                }
            }
            else
            {
                res += ((current / 2) + '0');
                current = current % 2;
            }
        }
        if (res.size() == 0)
            return "0";
        return res;
    }
    //-----------------------------------------------------------------------//


    //-----------------------------ADDITION-----------------------------------//
    string add(const string &a, const string &b)
    {
        string res = "";
        int length1 = a.length();
        int length2 = b.length();
        int carry = 0;


        while (length1 > 0 or length2 > 0 or carry > 0)
        {
            int currentDigit1 = (length1 > 0) ? a[length1 - 1] - '0' : 0;
            int currentDigit2 = (length2 > 0) ? b[length2 - 1] - '0' : 0;


            int currentDigit = currentDigit1 + currentDigit2 + carry;


            carry = currentDigit / 10;
            currentDigit %= 10;


            res += (char)(currentDigit + '0');


            length1--;
            length2--;
        }
        reverse(res.begin(), res.end());


        return res;
    }
    //-----------------------------------------------------------------------//


    //-----------------------------SUBTRACTION--------------------------------//
    string subtract(string a, string b)
    {
        if (a.length() < b.length() or (a.length() == b.length() and a < b))
        {
            return '-' + subtract(b, a);
        }


        string res = "";


        int length1 = a.length();
        int length2 = b.length();


        while (length1 > 0 or length2 > 0)
        {
            int currentDigit1 = a[length1 - 1] - '0';
            int currentDigit2 = (length2 > 0) ? b[length2 - 1] - '0' : 0;


            if (currentDigit2 > currentDigit1)
            {
                int i = length1 - 2;
                while (i >= 0 and a[i] == '0')
                {
                    a[i] = '9';
                    i--;
                }
                if (i >= 0)
                    a[i]--;
                currentDigit1 += 10;
            }


            int currentDigit = currentDigit1 - currentDigit2;
            res += (char)(currentDigit + '0');


            length1--;
            length2--;
        }
        reverse(res.begin(), res.end());
        return res;
    }
    //-----------------------------------------------------------------------//


    //-----------------------------MULTIPLICATION----------------------------//






    string multiply(const string &a, const string &b)
    {
         string n1=a;
         string n2=b;
        if(n1.length() > n2.length())
		n1.swap(n2);


	    string res = "0";
	     for(int i=n1.length()-1; i>=0; --i)
	    {
	     	string temp = n2;
	     	int currentDigit = n1[i]-'0';
	    	int carry = 0;


		    for(int j=temp.length()-1; j>=0; --j)
		    {
			temp[j] = ((temp[j]-'0') * currentDigit) + carry;


			if(temp[j] > 9)
			{
				carry = (temp[j]/10);
				temp[j] -= (carry*10);
			}
			else
				carry = 0;


			temp[j] += '0'; // back to string mood
		    }


		  if(carry > 0)
			temp.insert(0, 1, (carry+'0'));


		  temp.append((n1.length()-i-1), '0'); // as like mult by 10, 100, 1000, 10000 and so on


		  res = add(res, temp); // O(n)
	   }


	 while(res[0] == '0' && res.length()!=1)    // erase leading zeros
		res.erase(0,1);


	 return res;
    }


    //----------------------------------------------------------------------//


    //-----------------------------DIVISION----------------------------//
    string divide(const string &a, const string &b)
    {
        if (b == "1")
            return a;
        bigInt l;
        bigInt r = (bigInt)(a);
        bigInt one = (bigInt) "1";
        while (r - l > one)
        {
            bigInt m = divideBy2(l + r);


            if (m * b <= (bigInt)a)
                l = m;
            else
                r = m;
        }
        return l.num;
    }
    //----------------------------------------------------------------------//


    string modulo(const string &a, const string &b)
    {


        bigInt a_ = (bigInt)(a);
        bigInt b_ = (bigInt)(b);


        return (a_ - ((a_ / b_) * b_)).num;
    }
};


//----------------------MATH FUNCTIONS-----------------------------------//
namespace MathFunctions
{




    bigInt factorial(int n)
    {


        bigInt res("1");
        for (int i = 2; i <= n; i++)
        {
            res = res * (bigInt)(to_string(i));
        }
        return res;
    }


    bigInt gcd(bigInt a, bigInt b)
    {
        if (b == (bigInt) "0")
            return a;


        return gcd(b, a % b);
    }


    bigInt lcm(bigInt a, bigInt b)
    {
        return a * (b / gcd(a, b));
    }


    bigInt pow(bigInt x, bigInt n)
    {
        bigInt ans;
        ans = "1";
        while (n > (bigInt)("0"))
        {
            bool setBit = (n % (bigInt)("2") == (bigInt) "1");
            if (setBit)
                ans = ans * x;
            x = x * x;


            n = n / (bigInt)("2");
        }
        return ans;
    }


}




//-----------------------------------------------------------------------//


#endif
