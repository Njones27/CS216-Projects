/*
 * Course: CS216-003
 * Project: Lab 10 (as second part of Project 2)
 * Purpose: repeatedly ask the user to type prefix to match
 *          and generate all the prefix-matched terms 
 *          then display the prefix-matched terms in descending order by weight.
 ***** PLEASE DO NOT CHANGE THIS FILE *****
 */

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "term.h"
#include "SortingList.h"
#include "autocomplete.h"

using namespace std;

int main(int argc, char** argv) {
    const int ARGUMENTS = 2;
    
    // check the command line argument, an input file name is needed
    if (argc != ARGUMENTS+1)
    {
        cout << "Warning: need exactly 2 command line arguments." << endl;
        cout << "Usage: " << argv[0] << " <filename> number" << endl;
        return 1;
    }    
    
    // Get and validate input k
    int k = atoi(argv[2]);
    if (k <= 0)
    {
        cout << "Warning: the number of matching terms needs to be a positive number!" << endl;
        return 1;
    }

    // check if the input file can be opened successfully
    ifstream infile;
    infile.open(argv[1]);
    if (!infile.good())
    {
        cout << "Warning: cannot open the file named " << argv[1] << endl;
        return 2;
    }  
    
    // read in the terms from the input file
    // line by line and store into Autocomplete object
    Autocomplete autocomplete;
    long weight;
    string query;
    
    while (!infile.eof())
    {
        infile >> weight >> ws;
        getline(infile, query);
        if (query != "")
        {    
            Term newterm(query, weight);
            autocomplete.insert(newterm);
        }    
    } 

    // read the time clock 
    // before calling sort() function and after it
    // to measure the time spent for sorting operation
    clock_t tstart, tstop;
    tstart = clock();
    autocomplete.sort();
    tstop = clock();
    double  elapsed = (double)(tstop-tstart)/CLOCKS_PER_SEC;
    cout << "Time for sorting all terms: "<<  elapsed << " seconds." << endl;
    
    string input;
    string prefix;
    cout << "Please input the search query (type \"exit\" to quit): " << endl;
    getline(cin, input);
    prefix = input;
    while (prefix != "exit")
    {
        // measure the time spent for searching one prefix-matched term
	    /*
        clock_t tstart, tstop;
    	tstart = clock();
        */
        SortingList<Term> matchedTerms = autocomplete.allMatches(prefix);

        // Create a SortingList object to store top k matched terms
        SortingList<Term> topKMatchedTerms;
        for (int i = 0; i < k && i < matchedTerms.size(); i++)
        {
            topKMatchedTerms.insert(matchedTerms[i]);
        }

        // Finish measuring time spent for searching and output that time
        /*tstop = clock();
        double  elapsed = (double)(tstop-tstart)/CLOCKS_PER_SEC;
        cout << "Time for searching the top " << k << " matched terms: "<<  elapsed << " seconds." << endl;
        */

        if (matchedTerms.size() == 0)
        {    
            cout << "No matched query!" << endl;    // If no query, tell user
        }
        else
        {
            topKMatchedTerms.print();               // Prints all top k queries
        }

        // Output prompt
        cout << "Enjoy CS216 Auto-complete Me search engine!" << endl;
        cout << "It is written by Nathan Jones in CS216 Section 003." << endl;
        cout << "Please input the search query (type \"exit\" to quit): " << endl;
        getline(cin, input);
        prefix = input;
    }    
    cout << "Thank you for using Auto-complete feature provided by CS216!" << endl;
    return 0;
}