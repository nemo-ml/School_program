#include <iostream>
#include <string>
#include <fstream>

using namespace std;

/////Declarations////////////////////////////////////////////////
const int MAX_STUDENT = 500;
const char FILE_PATH[] = "C:\\entry_file.txt";
typedef int INDEX;

typedef double MARK;
typedef string NAME;
int entryCount = -1;	//-1 means the list is empty
fstream entryFile;

class StudentEntry
{
public:
	StudentEntry(NAME name, MARK mark) : name(name), mark(mark) {}
	StrudentEntry& operator = (StudentEntry& entry)
	{
		name = entry.name;
		mark = entry.mark;
		return *this;
	}
	NAME name;
	MARK mark;
}*entryList[MAX_STUDENT];

/////Function prototypes////////////////////////////////////////
INDEX GetStudentIdx();	//Gets number of index from user
MARK GetStudentMark();	//Gets number of maerk from user
NAME GetStudentName();	//Gets string of name from user
void DeleteFromTheList(INDEX idx);	//Deletes an item with index of idx
void Delete();	//Called by DeleteFromTheList(INDEX)
void ChangeMark();	//Changes the mark field of a record
void SetNewMark(INDEX idx, MARK mark);	//Called by ChangeMark()
void AddEntry();	//Adds new item to list
void AddToList(NAME name, MARK mark);	//Called by AddEntry()
void SortList();	//Does a buble sort on list
void ShowMark();	//Shows all marks with the same name
void ShowName();	//Shows all names with the same mark
void ShowList();	//Shows all the items in the list
int GetUserChoice();	//Gets numbet of option from user
void LoadDataFromFile();	//Loads data from a file
void SaveDataToFile();	//Saves data to a file

/////////////////////////////////////////////////////////////
INDEX GetStudentIdx()
{
	cout << "Enter index: ";
	INDEX idx;
	cin >> idx;
	return idx;
}

MARK GetStudentMark()
{
	cout << "Enter mark: ";
	MARK mark;
	cin >> mark;
	return mark;
}

NAME GetStudentName()
{
	cout << "Enter name: ";
	NAME name;
	cin >> name;
	return name;
}

void DeleteFromTheList(INDEX idx)
{
	if (entryCount != idx)
		for (int i = idx; i < entryCount; i++) {
			entryList<i>->name = entryList[i + 1]->name;
			entryList<i>->mark = entryList[i + 1]->mark;
		}
	delete entryList[entryCount];
}
void Delete()
{
	if (entryCount != -1) {
		DeleteFromTheList(GetStudentIdx());
		entryCount--;
	}
}

void SetNewMark(INDEX idx, MARK mark)
{
	entryList[idx]->mark = mark;
}

void ChangeMark()
{
	SetNewMark(GetStudentIdx(), GetStudentMark());
}

void AddToList(NAME name, MARK mark)
{
	entryList[entryCount] = new StudentEntry(name, mark);
}

void SortList()
{
	for (int i = 0; i < entryCount; i++) {
		for (int j = 0; j < entryCount; j++)
		{
			if (entryList[j]->name.compare(entryList[j + 1]->name) == 1)
			{
				StudentEntry temp = *entryList[j + 1];
				*entryList[j + 1] = entryList[j];
				*entryList[j] = temp;

			}
		}
	}
}

void AddEntry()
{
	entryCount++;
	NAME name = GetStudentName();
	AddToList(name, GetStudentMark());
	SortList();
}

void ShowMark()
{
	NAME name = GetStudentName();
	for (int i = 0; i <= entryCount; ++i) if (entryList<i>->name == name) cout << i << "\t" << entryList<i>->mark << endl;
}

void ShowName()
{
	MARK mark = GetStudentMark();
	for (int i = 0; i <= entryCount; ++i) if (entryList<i>->mark == mark) cout << i << "\t" << entryList<i>->name << endl;
}

void ShowList()
{
	for (int i = 0; i <= entryCount; ++i) cout << i << "\t" << entryList<i>->name << "\t" << entryList<i>->mark << endl;
}


int GetUserChoice()
{
	int choice;
	cout << "Enter the option's number and press enter: ";
	cin >> choice;
	return choice;
}

void LoadDataFromFile()
{
	entryFile.open(FILE_PATH, ios_base::in);
	if (entryFile.is_open()) {
		cout << "File opened." << endl;
		char temp[100];
		for (entryCount = 0; entryFile >> temp; entryCount++)
		{
			entryList[entryCount] = new StudentEntry(temp, 0);
			entryFile >> entryList[entryCount]->mark;


		}
		entryCount--;
		entryFile.close();
		entryFile.clear();
	}
	else {
		entryFile.clear();
		cout << "File not found in " << FILE_PATH << endl;
	}
}

void SaveDataToFile()
{
	entryFile.open(FILE_PATH, ios_base::out);
	if (entryFile.is_open()) {
		if (!entryFile.good())
		{
			cout << "Error writing file." << endl;
		}
		else
			for (int i = 0; i <= entryCount; i++)
			{
				entryFile << entryList<i>->name << endl;
				entryFile << entryList<i>->mark << endl;
			}
		entryFile.close();
	}


}

int main()
{
	LoadDataFromFile();
	int userChoice;
	do {
		cout << "1: Show List\n2: Add Entry\n3: Change Mark\n4: Delete\n5: Search Name\n6: Search Mark\n7: Save and Exit\n";
		cout << "Current number of records: " << entryCount + 1 << endl;
		userChoice = GetUserChoice();
		switch (userChoice) {
		case 1: ShowList(); break;
		case 2: AddEntry(); break;
		case 3: ChangeMark(); break;
		case 4: Delete(); break;
		case 5: ShowMark(); break;
		case 6: ShowName(); break;
		}
	} while (userChoice != 7);
	SaveDataToFile();
	return 0;
}