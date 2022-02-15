#include<iostream>
#include<string.h>
#include<cstdlib>                               
#include<time.h> 
using namespace std;

class CRC{
 
     string input , divisor , divident , result;
     int len_divident , len_gen , len_inp;

public:


    string fun_xor(string a , string b){
     
    string result="";
    if(a[0] =='0'){
        return a.substr(1);
    }

    else{
        for(int i=0 ;i<len_gen; i++)
        {
          result = result + (a[i]==b[i] ? '0': '1');  
        }
        return result.substr(1);
    }


    }

    void getdata()
    {

    cout<<"\nEnter Input:  ";
    cin>>input;
    divisor ="1101";
    
    len_gen =divisor.length();
    len_inp=input.length();
     
    divident=input;
    for(int i=0 ; i<len_gen-1;i++){
        divident = divident+'0';
    }

    len_divident=divident.length();

    modulo_div();

}

void modulo_div(){

    string temp_div = divisor;
    string temp_divident = divident.substr(0 , len_gen);
    int j =len_gen;
    while(j<len_divident)
    {
    temp_divident =fun_xor(temp_divident , temp_div);
    temp_divident = temp_divident+divident[j];
    j++;
    }

result =input + fun_xor(temp_divident , temp_div);

}

void sender_side(){
    

  cout<<"\nSender's Side:\n\n";
  cout<<"Input : "<<input<<endl;
  cout<<"Generator Function : "<<divisor<<endl;
  cout<<"Checksum: "<<result.substr(input.length() , result.length())<<endl;
  cout<<"Data to send : "<<result<<endl;
}

void receiver_side(){
   
	cout<<"\nReceiver side:\n"<<endl;
	string data_rec = result;

    srand(time(0));
    int ran = rand()%2;
    int SRan = rand()%(result.length());
    data_rec.replace(SRan , 1 , to_string(ran));
    cout<<"Data Received : "<<data_rec<<endl;

    string temp_div = divisor;
    string temp_divident=data_rec.substr(0 ,len_gen);
    int j=len_gen;
    
    while(j<data_rec.length()){
        temp_divident=fun_xor(temp_divident , temp_div);
        temp_divident=temp_divident + data_rec[j] ;
        j++;
    }

string error = fun_xor(temp_divident, temp_div);
cout<<"Remainder is: "<<error<<endl;

bool flag=0; 
for(int i=0 ; i<len_gen-1 ; i++)
{
    if(error[i]=='1'){
        flag=1;
        break;
    }

}

if(flag==0)
    cout<<"Correct data received without any error\n\n"<<endl;
else
    cout<<"Data received have some errors\n\n"<<endl;

}

};

int main(){

    CRC crc ;
    crc.getdata();
    crc.sender_side();
    crc.receiver_side();
    return 1;
}
