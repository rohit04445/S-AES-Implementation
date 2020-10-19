#include<bits/stdc++.h>
using namespace std;
string k1="",k2="",k3="";//keys 
//lookup table It is for a*b mod (2^4) r0->2*b r1->4*b r2->9*b 
int lookup[3][16]={{0,2,4,6,8,10,12,14,3,1,7,5,11,9,15,13},
                    {0,4,8,12,3,7,11,15,6,2,14,10,5,1,13,9},
                    {0,9,1,8,2,11,3,10,4,13,5,12,6,15,7,14}};
//converts string of binary to numerical(base10) 	
int to_numeric(string x)
{         int ans=0;
	for(int i=0;i<x.length();i++)
	{	ans+=(x[i]-'0')*pow(2,x.length()-i-1);  }
	return ans;		
}
//converts character to binary string
string conv_to_bits(char ch)
{
    int i=0,bit;
    string x="";
     int a=ch;
     if(a<0)
     {	a+=256 ;  }
    while(a>0||i<8)
    {    bit=a%2;
	a=a/2;
	char k=bit+'0';
             x=k+x;
             i++;  }
    return x;
}
//converts given binary string to character of strings
string getValue(string x)
{         int k=0,k1=0;
	int l=x.length()/2;
	for(int i=0;i<l;i++)
	{         k*=2;
		if(x[i]=='1')   k+=1;  }
	for(int i=l;i<x.length();i++)
	{          k1*=2;
		if(x[i]=='1')   k1+=1;
	}
	char z=k;
	char z1=k1;
	string ans="";
	ans=ans+z+z1;
	return ans;
}
//converts integer to string_binary
string to_binary(int x)
{        string ans="";
	while(x>0||ans.length()<4)
	{         int k=x%2;
		ans+=(k+'0');
		x/=2;  }
	reverse(ans.begin(),ans.end());
	return ans;
}
//xor binary string 
string xorr(string x1,string x2)
{  string ans="";
    for(int i=0;i<x1.length();i++)
	{        if(x1[i]==x2[i])
		ans+="0";
		else
		ans+="1";  }
	return ans;	
}
//rotate nibble
string rotNib(string x)
{         string ans1="",ans2="";
	int k=x.length()/2;
	for(int i=0;i<k;i++)
	{         ans2+=x[i];
		ans1+=x[i+k];  }
	return ans1+ans2;
}
//S-Box for the given string
string sbox_4(string x)
{   int s_box[4][4]={ {9,4,10,11},
                                 {13,1,8,5},
                                 {6,2,0,3},
                                 {12,14,15,7} };
    string a="";
    a+=x[0];  a+=x[1];				       
    int ro1=to_numeric(a);
    a="";
    a+=x[2];  a+=x[3];
    int co1=to_numeric(a);
    return to_binary(s_box[ro1][co1]);
}
//Nibble Substitution
string subNib(string x)
{  string a="";
   string ans="";
   int k=x.length()/4;
   for(int i=0;i<k;i++)
    {
    	a="";
  	    a=a+x[4*i]+x[4*i+1]+x[4*i+2]+x[4*i+3];
 	    ans+=sbox_4(a); }
  return ans;
}
//Generates the 3 keys
void generateKeys(string key)
{       string w0="",w1="",w2="",w3="",w4="",w5="";
	for(int i=0;i<=7;i++)
	{         w0+=key[i];
		w1+=key[i+8];  }
	w2=xorr(xorr(w0,"10000000"),subNib(rotNib(w1)));
	w3=xorr(w2,w1);
	w4=xorr(w2,xorr("00110000",subNib(rotNib(w3))));
	w5=xorr(w4,w3);
	k1=w0+w1;
	k2=w2+w3;
	k3=w4+w5;
}
//Shift row
string shift_row(string text)
{
	for(int i=4;i<8;i++)
    	swap(text[i],text[i+8]);
	return text;
	
}
//Mixes Column
string mix_col(string text)
{  string s1="",s2="",s3="",s4="",s11="",s22="",s33="",s44="";
	for(int i=0;i<4;i++)
    { s1+=text[i];  s2+=text[i+4];
     s3+=text[i+8]; s4+=text[i+12];}
    s11=xorr(s1,to_binary(lookup[1][to_numeric(s3)]));
    s22=xorr(s2,to_binary(lookup[1][to_numeric(s4)]));
    s33=xorr(s3,to_binary(lookup[1][to_numeric(s1)]));
    s44=xorr(s4,to_binary(lookup[1][to_numeric(s2)]));
return s11+s22+s33+s44;
}
//Inverse SBox
string inverse_sbox_4(string x)
{
  int s_box[4][4]={     {10,5,9,11},
                    	{1,7,8,15},
                    	{6,0,2,3},
                    	{12,4,13,14}};
  string a="";
  a+=x[0];
  a+=x[1];				       
  int ro1=to_numeric(a); 

  a="";
  a+=x[2];
  a+=x[3];
  int co1=to_numeric(a);
  return to_binary(s_box[ro1][co1]);			  	
}
//Inverse Nibble Substitution
string inverse_subNib(string x)
{
  string a="";
  string ans="";
  int k=x.length()/4;
  for(int i=0;i<k;i++)
   {
    	a="";
 	    a=a+x[4*i]+x[4*i+1]+x[4*i+2]+x[4*i+3];
     	ans+=inverse_sbox_4(a);
   }
  return ans;
}
//Inverse Mix column
string inverse_mix_col(string text)
{       string s1="",s2="",s3="",s4="",s11="",s22="",s33="",s44="";
	for(int i=0;i<4;i++)
          {  s1+=text[i];  s2+=text[i+4];
               s3+=text[i+8];  s4+=text[i+12]; }
    s11=xorr(to_binary(lookup[2][to_numeric(s1)]),to_binary(lookup[0][to_numeric(s3)]));
    s22=xorr(to_binary(lookup[2][to_numeric(s2)]),to_binary(lookup[0][to_numeric(s4)]));
    s33=xorr(to_binary(lookup[2][to_numeric(s3)]),to_binary(lookup[0][to_numeric(s1)]));
    s44=xorr(to_binary(lookup[2][to_numeric(s4)]),to_binary(lookup[0][to_numeric(s2)]));
    return s11+s22+s33+s44;
}
//Encrypts 16 bit text
string encrypt(string text)
{         //round 0 xor
	string r0=xorr(text,k1);
	//round 1
	//Substitution Nibble round 1
	string r1=subNib(r0);
	//Shift Row of round 1
	r1=shift_row(r1);
	//Mix Columns round 1 
	r1=mix_col(r1);
	//Xor round 1
	r1=xorr(r1,k2);
	//Substitution Nibble round 2
	string r2=subNib(r1);
	//Shift Row of round 2	
	r2=shift_row(r2);
	//Xor round 2
	r2=xorr(r2,k3);
	return r2;
}
//Decrypts 16 bit text
string decrypt(string text)
{   string r2=xorr(text,k3);
    // Inverse Shift Row of round 2 {Shift Row == Inverse Shift Row}
	r2=shift_row(r2);
	//Inverse Substitution Nibble round 2
	r2=inverse_subNib(r2);
	//Xor round 1
	string r1=xorr(r2,k2);
	//Mix Columns round 1
	r1=inverse_mix_col(r1);
	//Inverse Shift Row of round 1
	r1=shift_row(r1);
	//Inverse Substitution Nibble round 1	
	r1=inverse_subNib(r1);
	//Xor round 0
	string r0=xorr(r1,k1);;
	return r0;
}
//Encrypts the data
string encryption(string s)
{      if(s.length()%2!=0)
	s+=" ";
	int i=0;
	string ans="";
    for(i=0;i<s.length();i++)
	{ //convert the s[i] and s[i+1] to 16 bit data
		string temp=conv_to_bits(s[i++]);
		temp+=conv_to_bits(s[i]);
		//encrypts the 16 bit data
		temp=encrypt(temp);
		//convert to characters back
		string k=getValue(temp);;
		ans+=k;
	}
	return ans;	
}
//Decrypts the data
string decryption(string s)
{
	int i=0;
	string ans="";
         for(i=0; i<s.length(); i++)
	{
		//convert the s[i] and s[i+1] to 16 bit data
		string temp=conv_to_bits(s[i++]);
		temp+=conv_to_bits(s[i]);
		//decrypts the 16 bit data
		temp=decrypt(temp);
		//convert to characters back		
		string k=getValue(temp);
		ans+=k;	}
	return ans;
}
int main()
{	
	cout<<"Enter the 16 bit key (having only 0s and 1s) for encryption"<<endl;
	string key;
	//inputs 16 bit key
	cin>>key;
	string s;
	while(key.length()>16||key.length()<16)
	{        cout<<"Invalid Key "<<endl;
		cin>>key;  }
	//generates the 3 keys
	generateKeys(key);
	cout<<"Enter the text to be encrypted"<<endl;
	getline(cin,s);
	getline(cin,s);
	//encrypts the data
	string en=encryption(s);
	cout<<"Encrypted text is "<<endl<<en<<endl<<endl;
	//decrypts the data
	string de=decryption(en);
	cout<<"Decrypted text is "<<endl<<de<<endl;
}
