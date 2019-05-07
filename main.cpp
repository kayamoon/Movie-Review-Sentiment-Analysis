/* author: Kaya Chou-Kudu
*  date: 4/3/19
*/

#include "HashTable.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm> //so can convert words to lowercase
#include <iterator>
#include <set>

using namespace std;

//declare stop word functions
set<string> createStopWords();
bool isStopWord(string s); 

//test first review: 1.64 with stop words
//second review 2.09091
int main()
{
    //declare a few needed variables for inputing the data
    string line;    
    int score;
    string message = " ";

    //open input file
    ifstream myfile ("movieReviews.txt");
    if (myfile.fail() )
    {
        cout << "could not open file" <<endl;
        exit(0);
    }

    //create hash table
    HashTable table(20000);
  
    while (! myfile.eof() )
    {
        myfile >> score;  //get score
        myfile.get();    // get blank space
        getline(myfile,line);
        int len = line.size();
        while(len >0) {  //identify all individual strings
            string sub;
            len = line.find(" ");
            if (len > 0)
            {
                sub = line.substr(0,len);
                line = line.substr(len+1,line.size());
            }
            else {
                sub = line.substr(0,line.size()-1);
            }
            //convert string to lowercase
            transform(sub.begin(), sub.end(), sub.begin(), ::tolower); 
                      
           /*
           *checks if word is equal to stop word
           *if word is not stop word, put in hashtable
           *code does not work
           */
           if(isStopWord(sub) == false) 
           {//word is not a stop word
              table.put(sub, score);
              //cout << sub << " | " << score << endl;
           }
           //else {cout << "STOP WORD RIGHT OVER HERE " << sub << endl;}
             
        }
    }
  
    /* DISPLAY HASHTABLE (for testing purposes)
    * displays sample of hashtable 
    cout << "table below: " << endl;
    table.displayHash();
    cout << "table above " << endl;
    */
  

    //after data is entered in hash function
    //prompt user for a new movie review
    while(message.length() > 0)
    {   
        cout << "enter a review -- Press return to exit: "<<endl;
        getline(cin,message);

        //used for calculating the average
        double sum = 0;
        int count = 0;
        
        int len = message.size();
        //get each individual word from the input
        while(len != std::string::npos) //npos is the maximum possible value // for strings: the end of the string
        {
            string sub;
            len = message.find(" ");
            if (len != string::npos) 
            {
                sub = message.substr(0,len);
                message = message.substr(len+1,message.size());
            }
            else {
                sub = message;
                transform(sub.begin(), sub.end(), sub.begin(), ::tolower); //convert string to lowercase
            }
            //calculate the score of each word
            sum += table.getAverage(sub);
            count++;
        }

        if (message.size() > 0)
        {
            double sentimentVal = sum/count;
            cout << "The review has an average value of " << sentimentVal << endl;
            string sentiment = "";
            
            if (sentimentVal <= .5) { sentiment = "negative"; }
            else if (sentimentVal <= 1) { sentiment = "somewhat negative"; }
            else if (sentimentVal <= 1.5) { sentiment = "neutral"; }
            else if (sentimentVal <= 2) { sentiment = "somewhat positive"; }  
            else { sentiment = "positive"; }          
            cout << sentiment << " sentiment\n" << endl;
        }
    }
    
    return 0;
}


set<string> createStopWords()
{
    string line;    

    //open input file
    ifstream myfile ("stopwords.txt");
    if (myfile.fail() )
    {
        cout << "could not open file" <<endl;
        exit(0);
    }

    //create set of stopwords
    set<string> stopWords;


    while (! myfile.eof() )
    {
        getline(myfile,line);
        int len = line.size();
        while(len >0) {  //identify all individual strings
            string sub;
            len = line.find(" ");
            if (len > 0)
            {
                sub = line.substr(0,len);
                line = line.substr(len+1,line.size());
            }
            else {
                sub = line.substr(0,line.size()-1);
            }
            stopWords.insert(sub); //insert stop word into set
        }
    }
    return stopWords;
}

bool isStopWord(string s)
{
  set<string> stopWords;
  stopWords = createStopWords();
  if (stopWords.find(s) != stopWords.end()) {
    return true;
  }
  else
  {
    return false;
  }
}

            
