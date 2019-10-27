// Classes_EX2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
// #include <bits/stdc++.h>

using namespace std;

struct Date
{
	unsigned long int Year;
	unsigned long int Month;
	unsigned long int Day;
};

struct Student
{
	string firstname;
	string lastname;
	Date date;
	float grade;
	unsigned long int ID;

	void Print_Student()
	{
		cout << firstname << ' ' << lastname << ' ' << date.Year << '/' << date.Month << '/' << date.Day << ' ' << grade << ' ' << ID << endl;
	}

	string save()
	{
		return firstname + " " + lastname + " " + to_string(date.Year) + "/" + to_string(date.Month) + "/" + to_string(date.Day) + " " + to_string(grade) + " " + to_string(ID);
	}
};

struct Class
{
	string name;
	float average;
	unsigned short int capacity;
	vector<Student>data;

	void Add_Stuent(string _data)
	{
		string split_data[5];
		int index = 0;
		for (auto c : _data)
		{
			if (c != ' ')
				split_data[index] += c;
			else
				index++;
		}

		string date[3];
		index = 0;
		for (auto c : split_data[2])
		{
			if (c != '/')
				date[index] += c;
			else
				index++;
		}
		string::size_type sz;     // alias of size_t
		data.push_back({ split_data[0]  ,split_data[1] ,{stoul(date[1]) ,stoul(date[1]) ,stoul(date[2])}, stof(split_data[3], &sz) ,stoul(split_data[4]) });
	}

	void Remove_Student(unsigned long long int id)
	{
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i].ID == id)
				data.erase(data.begin() + i);
		}
	}

	void Remove_Student(string name)
	{
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i].firstname == name)
				data.erase(data.begin() + i);
		}
	}

	void Search_ID(unsigned int id)
	{
		for (int i = 0; i < data.size(); i++)
		{
			if (data[i].ID == id)
			{
				data[i].Print_Student();
				return;
			}
		}
		cout << "student is not found" << endl;
	}

	void Search_Name(string str1, string str2)
	{
		for (int i = 0; i < data.size(); i++)
		{
			if (str1 == data[i].firstname && str2 == data[i].lastname)
			{
				data[i].Print_Student();
				return;
			}
		}
		cout << "student is not found" << endl;
	}

	void  Sort_Name()
	{
		vector <Student> v;
		int j;
		v = data;
		for (auto z : v)
		{
			j = 0;
			for (auto i : v)
			{
				j++;
				if (j < v.size())
					if (i.firstname + i.lastname > v[j].firstname + v[j].lastname)
					{
						Student temp = v[j - 1];
						v[j - 1] = v[j];
						v[j] = temp;
					}
			}
		}
		for (auto s : v)
			s.Print_Student();
	}

	void Sort_Id()
	{
		vector <Student> v;
		int j;
		v = data;
		for (auto z : v)
		{
			j = 0;

			for (auto i : v)
			{
				j++;
				if (j < v.size())
					if (i.ID > v[j].ID)
					{
						Student temp = v[j - 1];
						v[j - 1] = v[j];
						v[j] = temp;
					}
			}
		}
		for (auto s : v)
			s.Print_Student();
	}

	void Basu_Rank()
	{
		//..
	}

	void Show()
	{
		cout << name << endl << average << endl << capacity << endl;
		for (auto s : data)
			s.Print_Student();
	}

	string Save()
	{
		string myfile;
		myfile = name + "\n" + to_string(data.size());
		for (auto student : data)
		{
			myfile += "\n" + student.save();
		}
		return myfile;
	}
};

struct Basu
{
	int class_slected;
	vector<Class>un;

	void addclass(string  name, unsigned short int cap, vector< string >data /* , vector<Student> s ,float avg*/)
	{
		Class c;
		c.name = name;
		c.capacity = cap;
		for (auto lineOfData : data)
		{
			c.Add_Stuent(lineOfData);
		}
		un.push_back(c);
	}

	void selectclass(string name)
	{
		int index = 0;
		for (auto i : un)
		{
			if (i.name == name)
			{
				class_slected = index;
				return;
			}
			index++;
		}
		class_slected = NULL;
	}

	void removeclass(string name)
	{
		for (int i = 0; i < un.size(); i++)
			if (un[i].name == name)
				un.erase(un.begin() + i);
	}

	void add_student(string data)
	{
		un[class_slected].Add_Stuent(data);
	}

	void remove_student(int id)
	{
		un[class_slected].Remove_Student(id);
	}

	void remove_student(string name)
	{
		un[class_slected].Remove_Student(name);
	}

	void search_id(int id)
	{
		un[class_slected].Search_ID(id);
	}


	void search_name(string stmt)
	{
		int index = 0;
		string  name[2];
		for (auto c : stmt)
		{
			if (c != ' ')
				name[index] += c;
			else
				index++;
		}
		un[class_slected].Search_Name(name[0] , name[1] );
	}

	void sort_id()
	{
		un[class_slected].Sort_Id();
	}

	void sort_name()
	{
		un[class_slected].Sort_Name();
	}

	void show()
	{
		un[class_slected].Show();
	}

	void ShowAll()
	{
		for (auto _class : un)
			_class.Show();
	}

	void get_file(string path)
	{
		ifstream infile(path);
		string name;
		string num;
		string line;
		vector <string > data;

		getline(infile, name);
		getline(infile, num);
		while (!EOF)
		{
			getline(infile, line);
			data.push_back(line);
		}
		addclass(name, stoul(num), data);
	}

	void save()
	{
		int index = 0;
		for (auto _class : un)
		{
			ofstream outfile;
			outfile.open("L" + to_string(index) + ".basu", std::ios_base::app);//std::ios_base::app
			outfile << _class.Save();
			index++;
		}
	}
};




string to_lower(string x)
{
	for (auto &i : x)
	{
		if (i < 97 && i > 55)
		{
			i = i + 32;
		}
	}
	return x;
}

string cut1(string line) // to cut the () off from a string

{
	string str, t;
	bool ok = true;
	for (int i = 0; i < line.length(); i++) // for loop for searching
	{
		if (line[i] == '\\') // if found (
		{
			str = line.substr(i + 1, line.length() - i - 2); // cut the rest of the string
			ok = false;
		}
	}
	if (str == t) // if the is nothing changed
	{
		return line; // return the same string
	}

	else
		return str; //return the cut string
}

void start()
{
	Basu basu;
	string help = "information about this programe :\n";
	help += "For adding a new class frome a file : basu add class <File Name>\n";
	help += "For adding student information to class :basu add student\n";
	help += "To remove a student from class by student number : basu remove student <ID>\n";
	help += "To select a class : basu selsect class <Class Name>";
	help += "To select nothing : basu select none";
	help += "To search for a student and show this student information by student number : basu search <ID>\n";
	help += "To search for a student and show this student information by student fullname : basu search <Full Name>\n";
	help += "To show data : basu show";
	help += "To show class information : basu show <Class Name>";
	help += "To sort the students by name : basu sort name";
	help += "To sort the students by student number : basu sort id";
	help += "To save the data : basu save";
	help += "To exit the program";
	string line;
	cout << "_>";
	while (getline(cin, line)) // till you press exit
	{
		bool correct = false;
		string arr[6];
		int i = 0;	
		int index = 0;
		for (auto c : line)
		{
			if (c != ' ')
				arr[index] += c;
			else
				index++;
		}
		string y, stmt;
		for (int i = 0; i < 6; i++)
		{
			string w = to_lower(arr[i]);
			if (w[0] != '\\')
			{
				y += w;
			}
			else
			{
				stmt = cut1(w);
			}
		}

		if (y == "basuaddclass")
		{
			basu.get_file(stmt);
		}
		else if (y == "basuremoveclass")
		{
			basu.removeclass(stmt);
		}
		else if (y == "basuaddstudent")
		{
			basu.add_student(stmt);
		}
		else if (y == "basuremovestudent")
		{
			basu.remove_student(stoi(stmt));
		}
		else if (y == "basuselectclass")
		{
			basu.selectclass(stmt);
		}
		else if (y == "basuselectnone")
		{
			basu.selectclass("non");
		}
		else if (y == "basusearch" && !isalpha(stmt[0]))
		{
			basu.search_id(stoi(stmt));
		}
		else if (y == "basusearch" && isalpha(stmt[0]))
		{		
			basu.search_name(stmt);
		}
		else if (y == "basushow" && stmt.length()>0 )
		{
			basu.show();
		}
		else if (y == "basushow")
		{
			basu.ShowAll();
		}
		else if (y == "basusortname")
		{
			basu.sort_name();
		}
		else if (y == "basusortid")
		{
			basu.sort_id();
		}
		else if (y == "basusave")
		{
			basu.save();
		}
		else if (y == "basuhelp")
		{
			cout << help;
		}
		else if (y == "exit")
		{
			break;
		}
		cout <<endl<< "_>";
	}
}

int main()
{
	start();
	return 0;
}

/*
if (isalpha(stmt[0]))
				cout << "alpha" << endl;

			else
				cout << "num" << endl;








Class myclass;
	myclass.average = 15;
	myclass.name = "sanatee";
	myclass.capacity = 60;
	myclass.Add_Stuent("ebrahem ahmad 10-10 10, 985147632");
	myclass.Add_Stuent("ahmad ebrahem 10-10 20, 123456789");
	myclass.Add_Stuent("ahmad ebrahem 10-10 9, 957851245");
	myclass.Add_Stuent("ahmad ahmad 10-10 22, 257835684");
	myclass.Add_Stuent("ebrahem ebrahem 10-10 3, 147852365");



	myclass.Show();


	myclass.Remove_Student(957851245);
	cout << "my search" << endl;
	myclass.Search_ID(147852365);

	cout << "my search" << endl;
	myclass.Search_Name("ebrahem" ,"ahmad");

	cout << "my id sort" << endl;
	myclass.Sort_Id();

	cout << "my name sort" << endl;
	myclass.Sort_Name();
	//myclass.Show_Class();

	//myclass.Add_Stuent("ahmad", "ebrahem", "10-10", 9, 957851245);
	myclass.Show();*/



	// End the buffer with a null terminating character
	



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
