
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;
// consts for the last word in each tweet file
const string TweetEnd1 = "back";
const string TweetEnd2 = "pigeon.";
const string TweetEnd3 = "waddle.";
const string TweetEnd4 = ":-)";
// these constants are for the filenames, so that they can be read into the vector
const string tweetFiltered1 = "tweets1Filtered.txt";
const string tweetFiltered2 = "tweets2Filtered.txt";
const string tweetFiltered3 = "tweets3Filtered.txt";  
const string tweetFiltered4 = "tweets4Filtered.txt";
// for custom incrementing on the positive/ negative sentiment analysis
const int checksNextElement = 1;
const int checksNextLoop = 2;

class tweets // class for tweet names, and popularity
{
	private:
		string name; // attributes
		int index;

	public: // constructors
		tweets(string inName, int inindex)
		{
			name = inName;
			index = inindex;
		}

		string& GetName();
		int& GetIndex();

		void setName(string setname);
		void setIndex(int setindex);
};
// definitions
string& tweets::GetName()
{
	return name;
}

int& tweets::GetIndex()
{
	return index;
}

void tweets::setIndex(int setindex)
{
	index = setindex;
}

void tweets::setName(string setName)
{
	name = setName;
}

void fileWrite1(int& startIndex, vector <tweets>& filteredInput, vector <tweets>& rawInput, int& i, const string& fileName) 
{
	ofstream outFile(fileName);
	outFile.clear(); // resets the file
	outFile.close();

	while (startIndex == -1) // if it is not at the last word in the tweet
	{
		outFile.open(fileName, std::ios::app); /* opens onto the next line.found this here while looking for "move to next line in file c++":
		https://stackoverflow.com/questions/10359702/c-filehandling-difference-between-iosapp-and-iosate*/

		if (!outFile)
		{
			cout << "cannot open file" << endl;
			exit(1);
		}
		else
		{
			cout << "writing to file..." << endl;
			outFile << filteredInput[i].GetName() << endl; // writes the name of the class element
			cout << "Successfull" << endl;

			i++;
			startIndex = rawInput[i].GetName().find(TweetEnd1); // increments
		}
		outFile.close();
	}
	outFile.open(fileName, std::ios::app);
	outFile << TweetEnd1 << endl;  // opens on the next line
	outFile.close();
}

void fileWritenext(int& startIndex, vector <tweets>& filteredInput, vector <tweets>& rawInput,
	int& i, const string& fileName, const string &constEndl)
{
	startIndex = rawInput[i].GetName().find(constEndl); // finds the end of the tweet
	ofstream outFile2(fileName);
	outFile2.clear(); // resets the file
	outFile2.close();

	while (startIndex == -1) { // while not the end of the tweet
		outFile2.open(fileName, std::ios::app); // opens on the next line
		if (!outFile2)
		{
			cout << "cannot open file" << endl;
			exit(1);
		}
		else
		{
			cout << "writing to file..." << endl;
			outFile2 << filteredInput[i].GetName() << endl; // writes to file
			cout << "Successfull" << endl;

			i++; // increments the for loop
			startIndex = rawInput[i].GetName().find(constEndl);  // startIndex is next tweet end
		}
		outFile2.close();
	}
	outFile2.open(fileName, std::ios::app);
	outFile2 << constEndl << endl; // writes the end of the tweet to the file
	outFile2.close();
}

void filewrite(vector <tweets>& filteredInput, vector <tweets>& rawInput)
{
	int startIndex = -1;
	
	for (int i = 0; i < filteredInput.size(); i++) // for loop for getting the position of the class element in the vector
	{
		fileWrite1(startIndex, filteredInput, rawInput, i, tweetFiltered1);
		fileWritenext(startIndex, filteredInput, rawInput, i, tweetFiltered2, TweetEnd2);
		fileWritenext(startIndex, filteredInput, rawInput, i, tweetFiltered3, TweetEnd3);  // writes each tweet to a seperate file
		fileWritenext(startIndex, filteredInput, rawInput, i, tweetFiltered4, TweetEnd4);
	}
}

void initialiseVectorTweets(vector <tweets>& vectorInput)
{
	string fileWord;
	int index = 0;
	vector <string> tweetFile  // vector of file names
	{
		"tweets1.txt",
		"tweets2.txt",
		"tweets3.txt",
		"tweets4.txt",
	};

	for (int i = 0; i < tweetFile.size(); i++) // for the size of the file name array
	{
		ifstream inFile(tweetFile[i]); // input stream each file name
		if (!inFile) // called if file can't be opened
		{
			cout << "cannot open file" << endl;
			exit(1); // exits with an error code if this fails
		}
		else
		{
			while (!inFile.eof()) // checks for end of line
			{
				inFile >> fileWord; // reads file

				vectorInput.push_back({ fileWord, index }); // adds line from file to vector
			}
			inFile.close(); // closes file
		}
	}
}

void initaliseVectorNegativePositive(vector <string>& vectorInput, string fileName)
{
	ifstream inFile(fileName);// opens the file
	// validation
	if (!inFile)
	{
		cout << "cannot open file" << endl;  
		exit(1);
	}
	else
	{
		string fileWord;
		while (!inFile.eof())
		{
			inFile >> fileWord; // reads the line into the variable
			if (!inFile.eof())
			{
				vectorInput.push_back(fileWord); // pushes onto the end of the vector
			}
		}
		inFile.close();
	}
}

int positiveNegativeCheck(vector <string>& vectorInput, vector <tweets>& vectorRaw, const string &constEndl, int &startIndex)
{
	int index = 0;

	for (int i = 0; i < vectorRaw.size(); i++)
	{ // for each word in the tweet
		for (int j = 0; j < vectorInput.size(); j++)
		{//for each word in the positive/ negative vector
			startIndex = vectorRaw[i].GetName().find(constEndl);
			if (startIndex == -1)
			{
				string::size_type findindex = vectorRaw[i].GetName().find(vectorInput[j]); /* finds the occurrence.
				string::size_type is a counter used to store the result of.find() because using an integer results in data loss.
				it can be processed like an integer*/
				if (findindex != -1)
				{ // if it occurrs increments
					index++;
				}
			}
			else
			{
				return index;
			}
		} // for each positive/negative word
	}
	return index;
}

void initialiseVectorBanned(vector <string> &vectorinput)
{
	ifstream infile("banned.txt"); // input stream for this specific file
	if (!infile)
	{
		cout << "cannot open file" << endl;  // validation
		exit(1);
	}
	else
	{
		string fileWord;

		while (!infile.eof()) // while not end of line
		{
			infile >> fileWord;  // reads line from file
			if (!infile.eof())
			{
				vectorinput.push_back(fileWord); // adds line to banned words vector
			}
		}
		infile.close(); // closes file
	}

}

string ToLower(string input) // from the powerpoint provided by uclan
{
  string lowerstring;
  for(auto c:input) lowerstring += tolower(c); // applies toLower to each character in a string
  return lowerstring;
}

vector <tweets> Filter(vector <tweets> tweets, vector <string> &bannedWords)
{
	int startIndex = 0;
	for (int b = 0; b < tweets.size(); b++) // processes one word from the input
	{
	  for (int i = 0; i < bannedWords.size(); i++) // processes one word from the banned words
	  {
	    startIndex = ToLower(tweets[b].GetName()).find(bannedWords[i], startIndex); // looks at one word and compares it to banned words
	    if (startIndex != -1) // checks to see if word is found
	    {
		int midpoint = (bannedWords[i].size() / 2); // creates a value for the midpoint
		    for (int j = 0; j < bannedWords[i].size(); j++) // for the length of the word
		    {
			if(j == midpoint ) // filters if midpoint of the word
			{
			    tweets[b].GetName()[startIndex] = '*'; // replace string at startIndex with *
			}
			startIndex++; // increment to repeat
		    }
	    }
	    startIndex = 0; // reset for next
	  }
	}
	return tweets; // return vector
}

int noOfOccurences(vector <tweets> &input)
{
    int index = 0;
    for(int i = 0; i < input.size(); i++) // for the size of the vector
    {
		for(string::size_type j = 0; j < input[i].GetName().length(); j++) // for the size of the word
		{
			if(input[i].GetName()[j] == '*') // check for * in word
			{
			index++; // increment if true
			}
		}
    }
  return index;
}

void specialFilter(vector <string> banned, vector <int> index, vector <tweets> tweets)
{
	for (int j = 0; j < (banned.size()); j++)  // for size of the banned vector
	{
		for (int i = 0; i < tweets.size(); i++)  // for the size of the tweet vector
		{
			int startIndex = 0;
			startIndex = ToLower(tweets[i].GetName()).find(banned[j]); // startIndex equals the vaulue of the location of the banned word

			if (!(startIndex == -1)) // checks if .find() failed
			{
				index[j]++; // increments
			}
		}
		cout << banned[j] << " was banned " << index[j] << " times." << endl; // outputs
	}
	int maxsize = index[0];
	for (int i = 0; i < index.size(); i++) // for size of the index
	{
		if (maxsize < index[i])
		{
			maxsize = index[i];  // compares
		}
	}

	cout << "biggest item is " << maxsize << endl;
	cout << "biggest items are  ";
	for (int j = 0; j < index.size(); j++) // for size of the index
	{
		if (index[j] == maxsize)  // if the item is the biggest one it is outputted
		{
			cout << banned[j] << "  ";
		}
	}
	cout << endl;
}

void mostCommonWord(vector <tweets> &input)
{
	for (int i = 0; i < input.size(); i++) // for size of input
	{
		input[i].GetIndex();


		//needs class to work. needs name + value for tweet words. will simplyfiy some other points as well.
	}
	int startIndex = 0;

	for (int i = 0; i < input.size(); i++) // for each tweet
	{
		for (int j = 0; j < input.size(); j++) // compares against each tweet: one word will trip up if it appears twice
		{
			if (ToLower(input[i].GetName()) == ToLower(input[j].GetName())) //  comapares the contents of tweets to another instance of it.
			{
				input[j].setIndex(startIndex); // sets the value
				startIndex++; // increments
			}
		}
		startIndex = 0; // resets
	}

	int maxsize = input[0].GetIndex();
		
	// sorts for max size (linear)
	for (int i = 0; i < input.size(); i++) 
	{
		if (maxsize < input[i].GetIndex()) 
		{
			maxsize = input[i].GetIndex();
		}


	}

	cout << "biggest item is ";
	for (int j = 0; j < input.size(); j++)
	{
		if (input[j].GetIndex() == maxsize) // output
		{
			cout << "!!" << input[j].GetName() << "!! which appears " << input[j].GetIndex() << " times!"; // outputs name and index

		}
	}
	cout << endl;
}

int main()
{
	//variables
	string positiveName = "positive.txt";
	string negativeName = "negative.txt";
	vector <string> bannedWords;
	vector <tweets> Tweets{};
	string input;
	vector <tweets> filterStorage;
	vector <string> negative;
	vector <string> positive;
	vector <int> bannedIndex  // index for banned words
	{
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	};

	initialiseVectorBanned(bannedWords); // initialises the banned words vector
	initialiseVectorTweets(Tweets); // initialises the tweets vector

	initaliseVectorNegativePositive(negative, negativeName); // initialises the negative tweets vector
	initaliseVectorNegativePositive(positive, positiveName); // initialises the positive tweets vector

	int checkIndex = 0;
	
	vector <int> checks // vector of functions that return an integer
	{
		positiveNegativeCheck(positive, Tweets, TweetEnd1, checkIndex),
		positiveNegativeCheck(negative, Tweets, TweetEnd1, checkIndex),
		positiveNegativeCheck(positive, Tweets, TweetEnd2, checkIndex),
		positiveNegativeCheck(negative, Tweets, TweetEnd2, checkIndex),
		positiveNegativeCheck(positive, Tweets, TweetEnd3, checkIndex),
		positiveNegativeCheck(negative, Tweets, TweetEnd3, checkIndex),
		positiveNegativeCheck(positive, Tweets, TweetEnd4, checkIndex),
		positiveNegativeCheck(negative, Tweets, TweetEnd4, checkIndex)

	};

	filterStorage = Filter(Tweets, bannedWords);
	for (int i = 0; i < Tweets.size(); i++) // for size of tweets
	{
		cout << filterStorage[i].GetName() << endl; // outputs filtered words
	}

	specialFilter(bannedWords, bannedIndex, Tweets);
	int index = noOfOccurences(filterStorage);
	
	cout << "number of banned words = " << index << endl;
	mostCommonWord(Tweets);
	
	/*the message warnings are about potential overflow that would result from not including the if not checks.back().
	this checks to see if the last element has been reached.*/
	for (int j = 0; j < checks.size(); j += checksNextLoop)// for the size of the function vector
	{
		if (checks[j] != checks.back()) // if it is not the end of the vector
		{
			if (checks[j] > checks[j + checksNextElement]) // if positive is larger than  negative
			{
				cout << "positive tweet" << endl;
			}
			else if (checks[j + checksNextElement] > checks[j]) // if negative is larger than positive
			{
				cout << "negative tweet" << endl;
			}
			else 
			{
				cout << "neutral tweet" << endl;
			}
		}

	}
	
	cout << "press enter to write results to file" << endl;
	system("pause");
	filewrite(filterStorage, Tweets); // writes to file
}
