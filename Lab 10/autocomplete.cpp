/* File: autocomplete.cpp
 * Course: CS216-00x
 * Project: Project 2
 * Purpose: the implementation of member functions for the class named Autocomplete.
 *
 */
#include <iostream>
#include "autocomplete.h"

// default constructor
Autocomplete::Autocomplete()
{
    // You can leave it blank
    // since the private data member terms has been initialized through default constructor of SortingList class 
}


// inserts the newterm to the sequence
// note that a SortingList<Term> object, named terms
//          represents the sequence
void Autocomplete::insert(Term newterm)
{
    terms.insert(newterm);
}


// sort all the terms by query in the lexicographical order  
void Autocomplete::sort()
{
    terms.std_sort();
}

// binary search helper function
// as private function
// since it serves binary_search member function only
int Autocomplete::binary_searchHelper(SortingList<Term> terms, string key, int left_index, int right_index)
{
    if(right_index < left_index)
    {
        int KEY_NOT_FOUND = -1;
        return KEY_NOT_FOUND;
    }
    else
    {
        Term keyterm(key, 0);
        int r = key.length();
        int middle = (left_index + right_index) / 2;
        if(Term::compareByPrefix(keyterm,terms[middle],r) > 0) {
            return binary_searchHelper(terms, key, left_index, middle - 1);

        }
        else if(Term::compareByPrefix(keyterm,terms[middle],r)  < 0) {
            return binary_searchHelper(terms, key, middle + 1, right_index);
        }
        else {
            return middle;
        }
    }
}

// return the index number of the term whose query 
// prefix-matches the given prefix, using binary search algorithm
// Note that binary search can only be applied to sorted sequence
// Note that you may want a binary search helper function
int Autocomplete::binary_search(string prefix)
{
    int left_index = 0;
    int right_index = terms.size() - 1;
    return binary_searchHelper(terms, prefix, left_index, right_index);
}

// first: the index of the first query whose prefix matches
//          the search key, or -1 if no such key
// last: the index of the last query whose prefix matches 
//         the search key, or -1 if no such key
// key: the given prefix to match
// hints: you can call binary_search() first to find one matched index number,
//        say hit, then look up and down from hit, to find first and last respectively
void Autocomplete::search(string key, int& firstIndex, int& lastIndex)
{
    int hit = binary_search(key);
    if(hit == -1) {
        firstIndex = -1;
        lastIndex = -1;
    }
    else
    {
        int left_index = hit;
        int right_index = hit;
        while(left_index >= 0 && terms[left_index].query.compare(0, key.length(), key) == 0) {
            left_index--;
        }
        left_index++;
        while(right_index < terms.size() && terms[right_index].query.compare(0, key.length(), key) == 0) {
            right_index++;
        }
        right_index--;
        firstIndex = left_index;
        lastIndex = right_index;
    }
}

// returns all terms that start with the given prefix, in descending order of weight
SortingList<Term> Autocomplete::allMatches(string prefix)
{
    int firstIndex;
    int lastIndex;
    search(prefix, firstIndex, lastIndex);
    SortingList<Term> matches;
    if(firstIndex == -1 && lastIndex == -1) {
        return matches;
    }
    else {
        for(int i = firstIndex; i <= lastIndex; i++) {
            matches.insert(terms[i]);
        }
        
        matches.bubble_sort(Term::compareByWeight);
        
        return matches;
    }
}

void Autocomplete::print()
{
    terms.print();
}
