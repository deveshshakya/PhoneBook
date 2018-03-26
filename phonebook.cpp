// Created by Devesh Shakya on 21/11/2017

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <fstream>
using namespace std;

class Phonebook
{
        char name[80];
        char ph_number[15];
public:
        char* getname() { return name; }
        char* getnumber() { return ph_number;}
        void get_input();
        void output();
        void update(char*, char*);
};

void Phonebook::get_input()
{
        cout<<"\nEnter name: ";
        cin>>name;
        cout<<"Enter number: ";
        cin>>ph_number;
        for (int i=0;name[i];i++)
            name[i] = toupper(name[i]);
}

void Phonebook::output()
{
        cout<<name<<" - "<<ph_number;
        cout<<endl;
}

void Phonebook::update(char *nm, char* num)
{
        strcpy(name,nm);
        strcpy(ph_number,num);
        for (int i=0;name[i];i++)
            name[i] = toupper(name[i]);
}

Phonebook pb;

void insert_data()
{
    	ofstream File("phonebook", ios::app | ios::binary);
    	if (!File.is_open())
    	{
    		cout<<"File opening error. Try again."<<endl;
        	return;
    	}
	pb.get_input();
	File.write( (char *) &pb, sizeof(Phonebook));
    	cout<<"Entry successful\n";
	cout<<endl;
    	File.close();
}

void search_entry()
{
    	char name[80];
    	int found = 0;
    	ifstream File("phonebook", ios::in | ios::binary);
    	if (!File.is_open())
    	{
    		cout<<"File opening error. Try again."<<endl;
        	return;
    	}
	File.seekg(0,ios::beg);
    	cout<<"\nEnter name: ";
    	cin>>name;
    	while (File.read( (char *) &pb, sizeof(Phonebook)))
    	{
    		if ( strcasecmp(name, pb.getname()) == 0 )
        	{
        		found++;
        		cout<<"\nDetail is:\t";
            		pb.output();
            		break;
        	}
    	}
    	if ( found == 0 )
    	{
    		cout<<"Entry not found\n";
    	}
    	File.clear();
    	File.close();
}

void update_entry()
{
    	char name[80];
    	char ph_number[15];
    	int temp = 0, found = 0;
    	cout<<"\nEnter name: ";
    	cin>>name;
    	ifstream File("phonebook", ios::in | ios::binary);
    	if (!File.is_open())
    	{
    		cout<<"File opening error. Try again."<<endl;
        	return;
    	}
    	File.seekg(0,ios::beg);
    	while (File.read( (char *) &pb, sizeof(Phonebook)))
    	{
        	temp++;
        	if ((strcasecmp(name, pb.getname()) == 0))
        	{
            		found++;
            		break;
        	}
    	}
    	if (found == 0)
    	{
        	cout<<"Entry not found\n";
        	File.clear();
        	File.close();
    	}
    	else
    	{
        	fstream File("phonebook", ios::in | ios::out | ios::binary);
        	if (!File.is_open())
        	{
            		cout<<"File opening error. Try again."<<endl;
            		return;
        	}
        	int location = (temp-1) * sizeof(Phonebook);
		if (File.eof())
            	File.clear();
        	cout<<"Enter Contact number: ";
        	cin>>ph_number;
        	pb.update(name, ph_number);
        	File.seekp(location,ios::beg);
        	File.write( (char *) &pb, sizeof(Phonebook));
        	File.flush();
        	cout<<"Updation successful\n";
        	File.clear();
        	File.close();
    	}
    	cout<<endl;
}

void display()
{
    	ifstream File("phonebook", ios::in | ios::binary);
    	if (!File.is_open())
    	{
    		cout<<"File opening error. Try again."<<endl;
        	return;
    	}
    	File.seekg(0,ios::beg);
    	cout<<endl;
    	cout<<"Records -\n\n";
    	while (File.read( (char *) &pb, sizeof(Phonebook)))
    	{
        	pb.output();
    	}
    	File.clear();
    	File.close();
    	cout<<endl;
}

int main()
{
        int option, found = 0;
        int location, temp = 0;
        for (;;)
        {
                cout<<"1. Insert Contact\n";
                cout<<"2. Search Contact\n";
                cout<<"3. Update Contact\n";
                cout<<"4. Display All Contacts\n";
                cout<<"5. Exit\n";
                cout<<"Choose option -\n";
                cin>>option;
                switch (option)
                {
                        case 1:
                                insert_data();
                                break;
                        case 2:
                                search_entry();
                                cout<<endl;
                                break;
                        case 3:
                                update_entry();
                                break;
                        case 4:
                                display();
                                break;
                        case 5:
                                exit(0);
                        default:
                                cout<<"\nEnter correct option.\n";
                }
        }

        return 0;
}

