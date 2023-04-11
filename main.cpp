// System: Mac using Xcode
// Author: Shahryar Ahmed
//-----------------------------------

#include <iostream>
#include "search.h"
using namespace std;


int main() {

//    // ****************************[TESTING cleanToken]****************************
//
//    string token = "#$@shanon@uic.edu!@!!!@!@";
//    string tokenANSWER = "shanon@uic.edu";
//
//    cout << "1. " << (cleanToken(token) == tokenANSWER) << endl;
//
//    // ****************************[TESTING gatherTokens]****************************
//
//    set<string> tokens = gatherTokens("EGGS! milk, fish,      @  bread cheese");
//    set<string> tokensANS;
//    tokensANS.insert("eggs");
//    tokensANS.insert("milk");
//    tokensANS.insert("fish");
//    tokensANS.insert("bread");
//    tokensANS.insert("cheese");
//    cout << "1. " << (tokens.size() == 5) << endl;
//    cout << "2. " << (tokens == tokensANS) << endl;
//
//    // ****************************[TESTING setIntersect]****************************
//
//    set<string> setA;
//    set<string> setB;
//    set<string> setAOrB;
//    setA.insert("A");
//    setA.insert("B");
//    setA.insert("C");
//    setA.insert("D");
//    setA.insert("E");
//
//    setB.insert("A");
//    setB.insert("B");
//    setB.insert("C");
//    setB.insert("D");
//    setB.insert("E");
//
//    setAOrB = setIntersect(setA, setB);
//    cout << "1. " << (setAOrB.size() == 5) << endl;
//
//    // ****************************[TESTING setUnion]****************************
//
//    set<string> setA1;
//    set<string> setB1;
//    set<string> setAAndB;
//    setA1.insert("A");
//    setA1.insert("B");
//    setA1.insert("C");
//    setA1.insert("D");
//    setA1.insert("E");
//
//    setB1.insert("C");
//    setB1.insert("F");
//
//
//    setAAndB = setUnion(setA1, setB1);
//    cout << "1. " << (setAAndB.size() == 6) << endl;
//
//    // ****************************[TESTING setDifference]****************************
//
//    set<string> setA2;
//    set<string> setB2;
//    set<string> setANotB;
//    setA2.insert("A");
//    setA2.insert("B");
//    setA2.insert("C");
//    setA2.insert("D");
//    setA2.insert("E");
//
//    setB2.insert("C");
//    setB2.insert("F");
//
//
//    setANotB = setDifference(setA2, setB2);
//    cout << "1. " << (setANotB.size() == 4) << endl;
//
//    // ****************************[END of Tests]****************************
    
    searchEngine("cplusplus.txt");
    
    return 0;
}


