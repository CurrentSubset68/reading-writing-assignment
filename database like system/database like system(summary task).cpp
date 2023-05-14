#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;


class teamMembers
{
	private:// attributes
		string name;
		string team;
		int goals;
		int ycards;
		int rcards;


	public://constructor
		teamMembers(string inName,string inTeam,int inGoals,int inYCards,int inRCards)
		{
			name = inName;
			team = inTeam;
			goals = inGoals;
			ycards = inYCards;
			rcards = inRCards;
		}

		void displayRecord();



        string &GetName();
        string &GetTeam();
        int& GetGoals();
		int& GetYcards();
        int &GetRcards();

        void SetName(string setName);
        void SetTeam(string setTeam);
		void SetGoals(int setGoals);
		void SetYcards(int setYcards);
        void SetRcards(int setRcards);


};

void teamMembers::displayRecord()// displays all attributes in a record
{
	cout << name << " " << team << " " << goals << " " << ycards << " " << rcards << endl;

}

//getters and setters

string& teamMembers::GetName()
{
	return name;
}

void teamMembers::SetName(string setName)
{
	name = setName;
}

string &teamMembers::GetTeam()
{
    return team;
}

void teamMembers::SetTeam(string setTeam)
{
    team = setTeam;
}

int& teamMembers::GetGoals()
{
	return goals;
}

void teamMembers::SetGoals(int setGoals)
{
	goals = setGoals;
}

int& teamMembers::GetYcards()
{
	return ycards;
}

void teamMembers::SetYcards(int setYcards)
{
	ycards = setYcards;
}

int& teamMembers::GetRcards()
{
	return rcards;
}

void teamMembers::SetRcards(int setRcards)
{
	rcards = setRcards;
}


bool validRecord(vector <teamMembers> input, int index, string twoChoice)// validates a record
{
  if(twoChoice == input[index].GetName()) //compares the input to the vector element
  {
      return true;
  }
    return false;

    
}


vector<teamMembers> FileRead(vector<teamMembers> &input) // reads from a file into the vector of classes
{
    ifstream inFile("Records.txt"); // input stream for this specific file
    string store = ""; // stores the file line read
    
    
    if (!inFile)
    {
        cout << "cannot open file" << endl; // validation
        exit(1);
    }
    else
    {
        ifstream inFile("Records.txt"); // input stream for this specific file
        string store = "";
        string stringStore = "";
        
        string::size_type startpos = 0;
        int index = 0;
        while (!inFile.eof()) // while not end of file
        {
            input.push_back({" ", " ", 0, 0, 0});
            inFile >> store;
            stringstream ss(store); // string stream to read each word
            string line;
            getline(ss, line, ','); /* get line reads up to a delimeter
            (i ended up nearly coding this myself) found it trying to fix a bug in my implementation:
            https://www.geeksforgeeks.org/getline-string-c/ */
            input[index].SetName(line); // sets the value of each attribute
            getline(ss, line, ',');
            input[index].SetTeam(line);
            getline(ss, line, ',');
            input[index].SetGoals(stoi(line)); /* found stoi when looking for converting string to integer:
                                               https://cplusplus.com/reference/string/stoi/*/
            getline(ss, line, ',');
            input[index].SetYcards(stoi(line));
            getline(ss, line, ',');
            input[index].SetRcards(stoi(line));
            index++; // index for getting the class position in the vector
        }
    }
    return input;
}

void fileWrite(vector <teamMembers> &vectorclass) // writes to file
{
    ofstream outfile("Records.txt");
    outfile.clear(); // clears the file for overwriting
    outfile.close();
    int index = 0;
    string output = ""; // appended word to output to file

    while ( index != vectorclass.size()) // while not end of vector
    {
        outfile.open("Records.txt", std::ios::app); /* moves line in a file :
                                              https://stackoverflow.com/questions/10359702/c-filehandling-difference-between-iosapp-and-iosate */
        if (!outfile)
        {
            cout << "cannot open file" << endl;
            exit(1);
        }
        else
        {
            output = "";
            output.append(vectorclass[index].GetName()); // appends to the end of the file
            output.append(",");
            output.append(vectorclass[index].GetTeam());
            output.append(",");
            output.append(to_string(vectorclass[index].GetGoals()));
            output.append(",");
            output.append(to_string(vectorclass[index].GetYcards()));
            output.append(",");
            output.append(to_string(vectorclass[index].GetRcards()));
            /* ^found to_string() when looking for making a int into a string: https://www.geeksforgeeks.org/stdto_string-in-cpp/ */
            output.append(",");
            outfile << output << endl;
            index++; // increments size vector
        }
        outfile.close();
    }
    outfile.open("Records.txt", std::ios::app); // opens it on next line
   
    
}

void insertAttribute(vector<teamMembers> input, string inName, string inteam, int inGoal, int inYcards, int inRcards)// inserts attributes
{
    input.back().SetName(inName);
    input.back().SetTeam(inteam);
    input.back().SetGoals(inGoal);
    input.back().SetYcards(inYcards);
    input.back().SetRcards(inRcards);
}

int menuValidation(int input) // validates input
{
    cout << "press 1 to list all" << endl;
    cout << "press 2 to search" << endl;
    cout << "press 3 to update a record" << endl;
    cout << "press 4 to input a record" << endl;
    cout << "press 5 to display all goals, yellow cards and red cards" << endl;
    cout << "press 6 to exit" << endl;
    cin >> input;
    while (cin.fail()) // while not integer
    {
        cin.clear();
        cin.ignore(80, '\n');
        cout << "invalid input enter again" << endl; // reset and ask for correct input
        cin >> input;
    }
    while ((input != 1) && (input != 2) && (input != 3) && (input != 4) && (input != 5) && (input != 6)) // while not correct number
    {
        cout << "invalid input enter again" << endl; // ask for correct input
        cin >> input;
    }
    return input; // return once corect
}

int main()
{
	vector <teamMembers> classArray = {};
	string insertName;
	string insertTeam;
	int insertGoals;
	int insertYcards;
	int insertRcards;
	int menuinput = 0;
	string twoChoice; // input
	int index= 0;
	bool validResponse = false;
    int menuCheck = 0; // checks if the menu is zero or more

    FileRead(classArray); // initialises the vector
    menuinput = menuValidation(menuinput); // validates input

	while(menuinput != 6) // while not quitting
	{
        if (menuCheck != 0) // if second input and onwards
        {
           menuinput = menuValidation(menuinput); // validate
        }
	    if (menuinput == 1) // if displaying records
	    {   
	    	for (int i = 0; i < classArray.size(); i++) // for all vector elements
            {   
                classArray[i].displayRecord(); // display
            }
	    }
        else if (menuinput == 2) // if displaying a certain record
	    {
	    	cout << "enter the name that you want to search for" << endl;
	    	cin >> twoChoice;
            while ((index < classArray.size()) && validRecord(classArray, index, twoChoice) == false)
                // ^while not end of the vector, and input not found
            {

                index++; // increment
            }
            if (validRecord(classArray, index, twoChoice)) // once found
	    	{
	    		classArray[index].displayRecord(); //display
	    	}
            else
            {
                cout << "could not find entry" << endl;
                index = 0;
                validResponse = false; //resets
            }
	    	index = 0;
	    	validResponse = false; // resets

	    }
        else if (menuinput == 3) // if updating
        {
            cout << "enter the name that you want to update" << endl;
            cin >> twoChoice;
            while ((index < classArray.size()) && validRecord(classArray, index, twoChoice) == false)
                // ^while not end of vector and not found item
            {

                index++; // increment
            }
            if (validRecord(classArray, index, twoChoice)) // if found
            {
                //append to vector
                classArray[index].SetName(twoChoice);
                cout << "enter a team for entry" << endl;
                cin >> insertTeam;
                classArray[index].SetTeam(insertTeam);
                cout << "enter the number of goals scored" << endl;
                cin >> insertGoals;
                classArray[index].SetGoals(insertGoals);
                cout << "enter the number of yellow cards received" << endl;
                cin >> insertYcards;
                classArray[index].SetYcards(insertYcards);
                cout << "enter the number of red cards received" << endl;
                cin >> insertRcards;
                classArray[index].SetRcards(insertRcards);
                fileWrite(classArray);// overwrite file
            }
            else
            {
                cout << "could not find entry" << endl;
                index = 0;
                validResponse = false; // resets
            }
            index = 0;
            validResponse = false; // resets
        }
	    else if(menuinput == 4) // if adding new record
	    {
            //capture input
	    	cout << "enter a name for entry" << endl;
	    	cin >> insertName;
	    	cout << "enter a team for entry" << endl;
	    	cin >> insertTeam;
	    	cout << "enter the number of goals scored" << endl;
	    	cin >> insertGoals;
	    	cout << "enter the number of yellow cards received" << endl;
	    	cin >> insertYcards;
	    	cout << "enter the number of red cards received" << endl;
	    	cin >> insertRcards;
	    	// create vector and then update the class attributes
            classArray.push_back({" ", " ", 0, 0, 0});
            classArray.back().SetName(insertName);
            classArray.back().SetTeam(insertTeam);
            classArray.back().SetGoals(insertGoals);
            classArray.back().SetYcards(insertYcards);
            classArray.back().SetRcards(insertRcards);
	    }
        else if (menuinput == 5) // if displaying total stats
        {
            int displayGoals = 0;
            int displayYcards = 0;
            int displayRcards = 0;

            for (int i = 0; i < classArray.size(); i++) // for size of the vector
            {
                //add the scores of each class to the respective integers
                displayGoals += classArray[i].GetGoals();
                displayRcards += classArray[i].GetRcards();
                displayYcards += classArray[i].GetYcards();

            }
            //display the integers
            cout << "total goals are " << displayGoals << endl;
            cout << "total Yellow cards are " << displayYcards << endl;
            cout << "total Red cards are " << displayRcards << endl;
        }
        menuCheck++; // index for keeping track of the current menu loop. it needs to offer validation again if it is the second loop onwards
	}
	return 0; // exits
}
