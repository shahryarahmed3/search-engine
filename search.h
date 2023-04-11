// System: Mac using XCode
// Author: Shahryar Ahmed
// Date: September 23, 2022
//
// CREATIVE COMPONENT: UNCOMMENT IN SEARCH ENGINE.
//
// ------------------------------------------------

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <set>
#include <map>

#include <vector> //creative component


using namespace std;


// Function: cleanToken cleans a provided token w/out blank spaces.
// The function returns a token free of any leading or trailing
// puctuation as determined by the function ispunct(). If the
// function is given a token without a single alphabet, the
// function returns an empty string. The function also performs
// lowercase conversion on each alpha character, using
// the tolower() library function.
string cleanToken(string s) {
    
    bool containsAlpha = false;
    
    for(int i=0; i < s.size(); i++)     //loop checks if the string contains atleast one alphabet
    {
        if(isalpha(s.at(i)))
        {
            s.at(i) = tolower(s.at(i)); //converts uppercase letters to lowercase
            containsAlpha = true;
        }
    }
    
    if(!containsAlpha)                  //returns an empty string if token doesn't contain alpha
    {
        return "";
    }
    
    int j = 0;
    
    while(j < s.size()+2)               //loop performs cleaning on token
    {
        for(int i = 0; i < s.size(); i++)
        {
            if( (i == 0) && (ispunct(s.at(i)) ) )
            {
                s.erase(i,1);
            }
            else if( (i == s.size()-1) && ispunct(s.at(i))  )
            {
                s.erase(i,1);
            }
        }
        j++;
    }
    
    return s;
}

// Function: gatherTokens takes input of a string, parses strings
// by whitespace seperation. To ensure unique storage of entries,
// the function uses a set of strings. With the help of sstream
// library functions using the arrow operator, the tokens are
// seperated by whitespaces. To ignore, a token of empty string
// an if statement condition is used to only insert non-empty
// strings.
set<string> gatherTokens(string text) {
    set<string> tokens;
    
    stringstream ss(text);              //string stream
    
    string token;                       //store single token
    
    while(ss >> token)
    {
        token = cleanToken(token);
        if (token != "")                //ignoring empty string.
        {
            tokens.insert(token);
        }
    }
    
    return tokens;
}

// Function: buildIndex takes argument of filename, and a map. This
// function opens the file, reads the file line by line using the
// getline() function. If line is at an odd number the function
// saves the string at line in a copy variable. If line is at an
// odd number the function calls gatherTokens() and saves the set
// of tokens in a temporary set. A for auto loop is implemented
// to iterate through each token, save the token as key, and the
// URL as the value.
int buildIndex(string filename, map<string, set<string>>& index) {
    
    ifstream inFS;
    string line;
    set<string> tokens;
    
    inFS.open(filename);
    
    if(!inFS.is_open())
    {
        cout << "Could not open file: " << filename << endl;
        return 0;
    }
    
    int lineNum = 1;
    string copyLine = "";
    int mapCount = 0;
    
    while(getline(inFS, line))
    {
        
        if(lineNum % 2 == 1) //lineNum isOdd (URL is at location)
        {
            copyLine = line;
            mapCount++;
        }
        else if (lineNum % 2 == 0) //lineNum isEven (Text is at location)
        {
            tokens = gatherTokens(line);
            
            for (auto itr : tokens)
            {
                index[itr].insert(copyLine);
            
            }
        }
        lineNum++;
    }
    
    return mapCount;
}

// Function: printSet recieves an argument of a set. The purpose
// of the function is to print how many pages matched the searched
// phrase and to print each element of the set and end the line. The
// function uses a for constant auto loop to iterate through
// the set.
void printSet(const set<string> set){
    
    cout << "Found " << set.size() << " matching pages" << endl;
    
    for (const auto &itr : set){
        cout << itr << endl;
    }
    
    cout << endl;
    
}

// Function: tokenSet recieves argument of map and a string. The
// map consists of the index, and the string contains the token.
// The function populates a set of string with ALL matching URLs.
// A nested const auto for loop is implemented, if map key is equal
// to the token, then the value (URLs) at the key are inserted in
// to the set of strings (temp). Set (temp) is returned.
set<string> tokenSet(const map<string, set<string>> index, const string token){
    set<string> temp;
    
    for (const auto &mapElement : index) {
        if(mapElement.first == token){      //if token matches the key of the map
            for (const auto &setElement : mapElement.second){
                temp.insert(setElement);    //URL is inserted in to the set to be returned.
            }
        }
    }
    
    return temp;
}

// Function: setUnion recieves two arguments, two sets. The
// function performs set operation AND (finds the union
// of two sets). Returns the union of set A and set B. A
// for auto loop is implemented which iterates through setB
// and inserts all elements of set A into set B. Set A is
// returned as an equivalent to the union of Set A and Set B.
set<string> setUnion(set<string> setA, set<string> setB){
    
    for (auto itr : setB){
        setA.insert(itr);
    }

    return setA; //returns set equivalent to the union of set A & B.

}

// Function: setIntersect recieves two arguments, two sets. The
// function performs set operation OR (finds the intersection
// of two sets). Returns the intersection of set A and set B. A
// nested for auto loop is implemented which iterates through setA
// and setB, and inserts all elements that are common in set A and
// setB into another setAAndB. setAAndB is returned.
set<string> setIntersect(set<string> setA, set<string> setB){
    set<string> setAAndB;
    
    for (auto itr : setA){
        for (auto itr1 : setB){
            if (itr == itr1){
                setAAndB.insert(itr);
            }
        }
    }
    return setAAndB; //returns the intersection of set A & B
}

// Function: setDifference recieves two arguments, two sets. The
// function performs set operation NOT (finds the difference
// of two sets). Returns the difference, ex: set A NOT set B. A
// for auto loop is implemented which iterates through setA
// if an element does not exist in setB then it is inserted into
// setANotB. The setANotB is returned.
set<string> setDifference(set<string> setA, set<string> setB){
    set<string> setANotB;
    
    for (auto &itr : setA){
        if(!setB.count(itr)){
            setANotB.insert(itr);
        }
    }
    return setANotB; //returns set A not B
}

// Function: findQueryMatches recieves two arguments, a map, and
// a string. The map is the inverted index. The sentence is the
// user's search phrase. The purpose of this function is to find
// all the URLs that match a given token, and/or a search phrase;
// following conditions as determined by the user input. The function
// has two sets declared, result is an empty set that is modified
// throughout the loop iteration. Set operations are performed in
// between the result and next token in the search phrase (if there
// are any).
set<string> findQueryMatches(map<string, set<string>>& index, string sentence) {
    string token;
    set<string> result;
    set<string> temp;
    
    stringstream ss(sentence);
    string word = "";
    
    while (ss >> word){ //gets word from the sentence
        
        temp = tokenSet(index, cleanToken(word));
        
        if(isalpha(word.at(0))){ //no preceding character
            result = setUnion(result, temp);
        }
        if (word.at(0) == '+'){ // + preceding character
            result = setIntersect(result, temp);
        }
        if (word.at(0) == '-'){ // - preceding character
            result = setDifference(result, temp);
        }
        temp.clear();
    }
    return result;
}


// ------------------------[CREATIVE COMPONENT]------------------------
// CREATIVE COMPONENT: UNCOMMENT IN SEARCH ENGINE. NOTE in searchEngine.
// Creative Component: showExcerpt recieves an argument of a set,
// and the filename. The purpose of the function is to print how many
// pages matched the searched phrase and to print each element of the
// set and end the line. This function has added feature to the original
// output, of showing an excerpt of the content/text at the URL. The
// excerpt portion following the URL is helpful to the searcher to determing
// if the link is relevant to what he/she is seeking. Function uses a
// for constant auto loop to iterate through the set.
int showExcerptWithURL(const set<string> set, string filename){
    
    ifstream inFS;
    string line;
    string copyLine;
    
    vector<string> excerpt;
    
    inFS.open(filename);
    
    if(!inFS.is_open())
    {
        cout << "Could not open file: " << filename << endl;
        return 0;
    }
    
    
    cout
    << "\n\n             ███████ ██   ██  █████  ██   ██ ██████  ██    ██  █████  ██████" << endl
    <<"             ██      ██   ██ ██   ██ ██   ██ ██   ██  ██  ██  ██   ██ ██   ██" << endl
    <<"             ███████ ███████ ███████ ███████ ██████    ████   ███████ ██████" << endl
    <<"                  ██ ██   ██ ██   ██ ██   ██ ██   ██    ██    ██   ██ ██   ██" << endl
    <<"             ███████ ██   ██ ██   ██ ██   ██ ██   ██    ██    ██   ██ ██   ██" << endl;
                                                                     
                                                                     
    cout << "\n\n                     [ All ] [ Books ] [ Videos ] [ Images ] [ More ]" << endl;
    cout << " ___________________________________________________________________________________________" << endl;
    cout << "\nAbout " << set.size() << " results" << endl << endl;

    
    while(getline(inFS, line))
    {
        excerpt.push_back(line);
    }
    string word;
    for (const auto &itr : set){
        
        cout << itr << endl << endl; //
        
        for(int i = 0; i< excerpt.size(); i++){
            
            if(itr == excerpt.at(i)){
                
                stringstream ss(excerpt.at(i+1));
                
                int i = 1;
                while (ss >> word) {
                    
                    cout << word << " ";
                    if(i%11 ==0){ // 11 words per line before line is ended.
                        cout << endl;
                    }
                    if(i == 28){
                        cout << "..." << endl; // if word count is at 28 "..." is added to the excerpt.
                        break;
                    }
                    i++;
                }
                
                cout << " __________________________________________________________";
                cout << "_________________________________" << endl << endl;
                
            }
        }
        
    }
    
    cout << endl;
    return 1;
}

// Function: searchEngine, this function creates an abstraction
// for the user. The function recieves an argument of filename.
// Using the single parameter, it calls all necessary function
// to conduct the search. Declared variables are a map, and
// set, and string. The map stores the inverted index, the set
// contains all the URLS that are relevant to the search. The
// string contains the user's search phrase.
void searchEngine(string filename) {

    map<string, set<string>> index; //stores the inverted index
    set<string> set; //stores the set of URLs
    string sentence; //stores user input
    bool showCreativeC = false;


    cout << "Stand by while building index..." << endl;
    cout << "Indexed " << buildIndex(filename, index)
         << " pages containing " << index.size()
         << " unique terms" << endl << endl;

    while (true) {

        cout << "Enter query sentence (press enter to quit): ";
        getline(cin, sentence);

        if(sentence == ""){
            cout << "Thank you for searching!" << endl;
            break;
        }
        
        // *********************[CREATIVE COMPONENT]***************************
        //
        // Uncomment the following line and re-run to show CREATIVE COMPONENT:
        // showCreativeC = true;
        //
        // ********************************************************************
        
        if(showCreativeC){
            showExcerptWithURL(findQueryMatches(index, sentence), filename);
        }
        else{
            printSet(findQueryMatches(index, sentence));
        }
        
        
        set.clear();
    }
}
