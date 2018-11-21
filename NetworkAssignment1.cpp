
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/*******************************************************************************
 *                          Functions Prototybes                               *
 *******************************************************************************/

string xor2 (string str1, string str2);
string generator (string message, string polynomial); // used at sender
void verify (string message, string polynomial);  //used at reciever
string alter(int index,string transmitted_message);

/*******************************************************************************
 *                             main function                                   *
 *******************************************************************************/

int main ()
{
	/*read message and polynomial generator*/
	int index;
	ifstream input("input.txt");
	string message, polynomial, result;
	input>>message;
	input>>polynomial;
	/*generator(input file)-> verifier case*/
	ofstream correct("correct_output.txt");
	result = generator(message, polynomial);  /* get the result of CRC */
	correct << message+result;
	verify(message + result, polynomial);
	cout << endl << "transmitted message ---> " << message + result<<"\n";
	/*generator(input file)-> alter -> verifier case*/
	ofstream error("error_output.txt");
	//The index >=0 && index < length of the message
	cout << "The index of the element to alter is: ";
	cin>>index;
	result = alter(index,generator(message, polynomial));  /* get the result of CRC */
	error << message+result;
	verify(message+result,polynomial);
	cout << endl << "transmitted message ---> " << message + result<<"\n";
		 
	system("pause");
	return 0;
}

/*******************************************************************************
 *                          Functions Definitions                              *
 *******************************************************************************/

/*  this function is to calcualte the result of the CRC algorithm */
string generator (string message, string polynomial)
{
	int length = polynomial.length();      /* the length of the generator */
	string str;

	for(int i=0; i <polynomial.length()-1;i++)  /* add number of zeros = the polynomial degree after the message*/
	{
		message+='0';
	}

	str = message.substr(0,length);     /* get the first number of bits = polynomial length to make them xor with the polynomial */ 

	for(int i = length; i< message.length(); i++)
	{
		if(str[0] != '0')    /* if the first bit is zero, the str will be XORed with zeros so the output will be the same */
		{                    /* if the first bit is 1, the str will be XORed with the polynomial */
			str = xor2(str,polynomial);
		}
		str.erase(0,1);     /* delete the first bit as it will be always zero */
		str+=message[i];    /* get the next bit of message */
	}
	/* finally there will be another XOR */
	if(str[0] !='0')   /* if the first bit isn't zero */
	{                  /* if it zero the str will be the same */
		str = xor2(str,polynomial);
	}
	str.erase(0,1);  /* delete the first bit as it will be always zero */

	return str;
}

/* XOR tow strings and get the result,    both strings should be same size */
string xor2 (string str1, string str2)
{
	string result;
	for(int i=0; i <str1.length(); i++)
	{
		if(str1[i] == str2[i])
			result += '0';
		else
			result += '1';
	}

	return result;
}

/* print whether the received message is correct or not */ 
void verify (string message, string polynomial)
{
	if(stoi(generator(message, polynomial))==0)  /* if the result of the CRC is zero, the received message is correct */
		cout<<endl<<"	message is correct";
	else
		cout<<endl<<"	message is not correct";
}
/*change 1 bit from transmitted message (output from generator at sender)*/
string alter(int index,string transmitted_message)
{
	string str= transmitted_message;
	if (transmitted_message[index] == '0')
	{
		str[index] = '1';
	}
	else
	{
		str[index] == '0';
	}
	return str;
}
