#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
using namespace std;

struct packet
{
    int data;
};

struct frame
{						
    packet pdata;
    int seq;
};

void network_to_data(int data)
{
    cout<<"Data "<<data<<"is now Converted to packet...\n";
}

void network_to_dataA(int data)
{
    cout<<"Acknowledgement "<<data<<"is now Converted to packet...\n";
}

void data_to_physicalA(int ack)
{
    cout<<"Packet is now Converted to Frame(ACK).. \tSequence number: "<<ack<<"\n";
    cout<<"Acknowledgement is sent to Sender...."; 
}

void data_to_physical(frame f1)
{
    packet pack=f1.pdata;
    cout<<"Packet is now Converted to Frame..with information "<<pack.data<<" and Sequence number "<<f1.seq<<"\n";
    cout<<"Frame is sent to receiver...."; 
}

void physical_to_data(frame f)
{
    packet p=f.pdata;
    int no=f.seq;
    cout<<"Frame is received from Physical Layer of receiver\n";
    cout<<"info :"<<p.data<<"\tsequence no. :"<<no<<endl;
}

void data_to_network()
{
    cout<<"Frame is now Converted back to Packet \n";
}

int receiver(frame f,int st)
{
    packet p;
    int  d;
    int s;
    cout<<"\n\n\nReceiver End:\n\n";

	if(st==5)
        cout<<"!!!! Frame Discarded.";
    else
    {		
        physical_to_data(f);
        p=f.pdata;
        s=f.seq;
        d=p.data;
        data_to_network();
    }

	if(s==0)
		s=1;
	else
		s=0;

	cout<<"\nACKNOWLEDGEMENT TRANSMISSION\n";
	network_to_dataA(s);
	data_to_physicalA(s);
    return s;
}

int sender(int data,int s,int cases)
{
    int var=-1;
    int check;
    packet pack;
    pack.data=data;
    cout<<"\n\nSender End:\n\n";
    network_to_data(data);
    frame f1;
    f1.pdata=pack;
    f1.seq=s;
    data_to_physical(f1);

	if(cases==1||cases==2||cases==3)
    {
		for(int i=0;i<500000000;i++);
		cout<<"\nAcknowledgement doesn't Received";
        return var;
    }
    
    else if(cases==5)
    {
        check=receiver(f1,5);
        cout<<"\n\nSender End:\n\n";

		if(check>1)
            cout<<"Acknowledge is failed \n\n";
        else if(check==0)
            cout<<"Acknowledge is Recieved by sender to send Data frame with seq.number \n\n"<<check;
        else
            cout<<"Acknowledge is Recieved by sender to send Data frame with seq.number \n\n"<<check;		
    }
    else
    {
        check=receiver(f1,0);
        cout<<"\n\nSender End:\n\n";

		if(check>1)
            cout<<"Acknowledge is failed \n\n";
        else if(check==0)
            cout<<"Acknowledge is Recieved by sender to send Data frame with seq.number \n\n"<<check;
        else
            cout<<"Acknowledge is Recieved by sender to send Data frame with seq.number \n\n"<<check;
    }
    return 0;
}

int main()
{
    int trigger;
    int n,i;
    cout<<"Enter no.of Data you want to send ";
    cin>>n;
    int data[n];

	for(i=0;i<n;i++)
    {
        cout<<"Enter data "<<i+1<<endl;
        cin>>data[i];
    }

	cout<<endl;
    for(i=0;i<n;i++)
    {
        int ch;
        srand(time(NULL));
        trigger=rand()%4;
        switch(trigger)
        {
            case 3:
				cout<<"\nCase :"<<endl;
				cout<<"\nAcknowledgement is lost\n";
				ch=sender(data[i],(i+1)%2,trigger);
				if(ch==-1)
				{
					cout<<"\n**Frame is Sent Again....**\n ";
					ch=sender(data[i],(i+1)%2,5);
				}
				break;
            case 2:
				cout<<"\nCase :"<<endl;
				cout<<"\nFrame losts\n";
				ch=sender(data[i],(i+1)%2,trigger);
				if(ch==-1)
				{
					cout<<"\n**Frame is Sent Again....**\n ";
					ch=sender(data[i],(i+1)%2,0);
				}
				break;
            case 1:
				cout<<"\nCase :"<<endl;

				cout<<"\nFrame gets Damage\n";
				ch=sender(data[i],(i+1)%2,trigger);
				if(ch==-1)
				{
					cout<<"\n**Frame is Sent Again....**\n ";
					ch=sender(data[i],(i+1)%2,0);
				}
				break;
            default:
				cout<<"\nCase :"<<endl;
				cout<<"Normal frame";
				ch=sender(data[i],(i+1)%2,trigger);
				break;
        }
    }
    cout<<"\nStop and wait completes ";
    return 0;
}
