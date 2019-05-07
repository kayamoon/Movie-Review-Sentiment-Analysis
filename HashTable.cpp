#include "HashTable.h"
#include "WordEntry.h"
#include <iterator>


/* HashTable constructor
*  input s is the size of the array
*  set s to be size
*  initialize array of lists of WordEntry
*/
HashTable::HashTable (int s) {
    this->size = s;
    //list<WordEntry> arr = new array<WordEntry>();
    hashTable = new list<WordEntry>[size];
}


/* computeHash
*  return an integer based on the input string
*  used for index into the array in hash table
*  be sure to use the size of the array to 
*  ensure array index doesn't go out of bounds
*/
int HashTable::computeHash(string s) {
    int value = 0;
    for (int i = 0; i < s.length(); i++) {
        value += int(s[i]);
    }
    return value % size; 
}


/* put
*  input: string word and int score to be inserted
*  First, look to see if word already exists in hash table
*   if so, addNewAppearence with the score to the WordEntry
*   if not, create a new Entry and push it on the list at the
*   appropriate array index
*/
void HashTable::put(string s, int score) {
    int index = computeHash(s);
        
    //if hashtable does contain word, add new appearance and score
    
    list<WordEntry>::iterator i; 
    for (i = hashTable[index].begin(); i != hashTable[index].end(); i++) { 
        if (i->getWord() == s) {
            break;
        }
    }
     //if key is found in hash table add new appearance 
     while (i != hashTable[index].end()) { 
            if (i->getWord() == s) {
                i->addNewAppearance(score);
                return;
            }
            i++;
     }
     
    //if hashtable does not contain word, add new word entry
    WordEntry we(s, score);
    hashTable[index].push_back(we);
 

}


/* displayHash
*  displays sample of hashtable for testing purposes
*  visually shows hashtable's separate chaining to avoid   
*  collision
*/
void HashTable::displayHash() { 
  for (int i = 420; i < 440; i++) { 
    cout << i; 
    for (auto x : hashTable[i])
    {
      cout << " --> " << "[" << x.getWord() << " " << x.getAverage() << "]" << endl;
    }
    cout << endl; 
  } 
} 


/* getAverage
*  input: string word 
*  output: the result of a call to getAverage()
*          from the WordEntry
*  Must first find the WordEntry in the hash table
*  then return the average
*  If not found, return the value 2.0 (neutral result)
*/

double HashTable::getAverage(string s) {
    int index = computeHash(s);

    list<WordEntry>::iterator i; 

    for (i = hashTable[index].begin(); i != hashTable[index].end(); i++) { 
        if (i->getWord() == s) {
            break;
        }
    }
      // if key is found in hash table return average
     if (i != hashTable[index].end()) { 
            if (i->getWord() == s) {
                return i->getAverage();
            }
            i++;
     }
    
     return 1.5;
}

/* contains
* input: string word
* output: true if word is in the hash table
*         false if word is not in the hash table
*/
bool HashTable::contains(string s) {
     int index = computeHash(s);
     
     //loop through list, find the key
    list<WordEntry>::iterator i; 
    for (i = hashTable[index].begin(); i != hashTable[index].end(); i++) { 
        if (i->getWord() == s) {
            break; 
        }
    } 
      //if list contains key, return true
      if (i != hashTable[index].end()) { 
            if (i->getWord() == s) {
                return true;
            }
            i++;
      } 
       return false;
}



