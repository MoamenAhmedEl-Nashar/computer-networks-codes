
#include <iostream>
#include <string>

using namespace std;

/*******************************************************************************
 *                          Functions Prototybes                               *
 *******************************************************************************/

string xor (string str1, string str2);
string generator (string message, string polynomial);
void verify (string message, string polynomial);

/*******************************************************************************
 *                             main function                                   *
 *******************************************************************************/

int main ()
{
	string message, polynomial, result, command;
	cout<<"Enter the message"<<endl<<"	";
	cin>>message;
	cout<<endl<<"Enter the generator"<<endl<<"	";
	cin>>polynomial;
	cin.ignore();
	while (1)
	{
		cout<<endl<<"Command: ";
		getline(cin,command);
		result = generator(message, polynomial);  /* get the result of CRC */
		if(command == "generator < file | verifier")  /* i think this should be changed if we will read from file */
		{
			cout<<endl<<"	transmitted message ---> "<<message+result;
			verify(message+result,polynomial);
		}
		else 
		{
			int pos;    /* the number of bit that should be toggle */
			cout<<endl<<"	transmitted message ---> "<<message+result;
			pos=stoi(command.substr( 25, 25-command.rfind("|")-1));  /* i think this should be changed if we will read from file */
			if(message[pos]=='0')      /* if the bit that we want to toggle is zero, it should be 1*/
				message.replace(pos,1,"1");
			else   /* if the bit that we want to toggle isn't zero, it should be 0 */
				message.replace(pos,1,"0");
			verify(message+result,polynomial);
		}
		cout<<endl;
	}

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
			str = xor(str,polynomial);
		}
		str.erase(0,1);     /* delete the first bit as it will be always zero */
		str+=message[i];    /* get the next bit of message */
	}
	/* finally there will be another XOR */
	if(str[0] !='0')   /* if the first bit isn't zero */
	{                  /* if it zero the str will be the same */
		str = xor(str,polynomial);
	}
	str.erase(0,1);  /* delete the first bit as it will be always zero */

	return str;
}

/* XOR tow strings and get the result,    both strings should be same size */
string xor (string str1, string str2)
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