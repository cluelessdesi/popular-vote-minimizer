#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

/********************************************************************************
Name: Sufiyan Shariff                                                           |
Course: CS 211 Spring '24                                                       |
Environment project developed in: Zybooks, Advanced Zylabs IDE                  |
Description: Project 4 - Popular Vote Minimizer ~ The program uses recursion    |
to determine a possible combination of states with the least possible popular   |
votes with enough electoral votes to still win the US Presidential election     |
*********************************************************************************/


bool setSettings(int argc, char** argv, int* year, bool* fastMode, bool* quietMode) {
    //------------------------------------------------   
    // TODO: Task 1 - write the setSettings() function
    //------------------------------------------------
    *year = 0; 
    *quietMode = false; 
    *fastMode = false; 
    
    // //sample processing of command-line arg...
    // *fastMode = true; //modify or replace this
    // return true; //modify or replace this

    int i = 1;
    while(i < argc) {
        if(strcmp(argv[i], "-f") == 0) {*fastMode = true;} // if f is seen set fastmode to true
        else if(strcmp(argv[i], "-q") == 0){*quietMode = true;} //  if q is seen set quietmode to true
        else if(strcmp(argv[i], "-y") == 0) { // if y is seen, chec for a number afterwards and handle accordingly
            if (i+1 < argc) { //
                if (atoi(argv[i+1]) >= 1828 && atoi(argv[i+1]) <= 2020 && atoi(argv[i+1]) % 4 == 0) {*year = atoi(argv[i+1]);} // if number after -y meets all this conditions, we set year to that number
                i += 1; // we skip an index (skip an argument) as its the year passed and thats already been handled
            }
            else {
                // -y was passed but no year was passed so invalid argument
                return false;
            }
        }
        else { return false; } // an argument apart from -y -q -f was passed
        i += 1;
    }
    return true;
}

void inFilename(char* filename, int year) {
    //------------------------------------------------   
    // TODO: Task 2 - write the inFilename() function
    //------------------------------------------------
    sprintf(filename, "data/%d.csv", year); // sets filename to data/year.csv
}

void outFilename(char* filename, int year) {
    //------------------------------------------------   
    // TODO: Task 2 - write the outFilename() function
    //------------------------------------------------
    sprintf(filename, "toWin/%d_win.csv", year); // sets filename to toWin/year_win.csv
}

bool parseLine(char* line, State* myState) {
    //------------------------------------------------   
    // TODO: Task 4 - write the parseLine() function
    //------------------------------------------------
    // return false; //modify or replace this 
    int i = 0, commaCounter = 0;
    while(line[i] != '\0') {
        if(line[i] == ',') {
            commaCounter += 1; // commacounter increments whenever comma is seen
        }
        i += 1;
    }
    if (commaCounter != 3) { return false; } // if less than 3 or more than 3 commas then we have invalid data format (does '\0' come after every word or at the end of the string?)

    char* sName;
    char* pCode;
    int eVotes = 0;
    int pVotes = 0;

    sName = strtok(line, ","); // reads from starting of line to first comma (handled edge case if nothing was read) & set data member 
    if(sName == NULL) { return false; }
    strcpy(myState->name, sName); 

    pCode = strtok('\0', ",");
    if(pCode == NULL) { return false; }
    strcpy(myState->postalCode, pCode); // reads from ending of first token to second comma (handled edge case if nothing was read) && set data member 
    
    eVotes = atoi(strtok('\0', ","));  // reads from ending of second token to third comma && set data member 
    myState->electoralVotes = eVotes;

    pVotes = atoi(strtok('\0', ","));  // reads from ending of third token to fourth comma && set data member 
    myState->popularVotes = pVotes;

    return true;
        
}

bool readElectionData(char* filename, State* allStates, int* nStates) {
    *nStates = 0; //required initialization prior to incrementing. 
    //-----------------------------------------------------   
    // TODO: Task 5 - write the readElectionData() function
    //-----------------------------------------------------
    // return true; //modify or replace this

    FILE* file1 = fopen(filename, "r"); // opening file for reading
    if(file1 == NULL) { return false; } // if file not found / not opened

    char cLine[50]; // i'm assuming max length of string is 12 (longest state name) + 2 (state id) + 9 digit possible number (331.9 mil people) + 9 digit possible number (331.9 mil people) + some extra characters idk
    while(fgets(cLine, 50, file1) != NULL) {
        // while data can be read in 
        State cState;        
        bool worked = parseLine(cLine, &cState); // passing current state for its data memebers to be filled
        if (worked == false) { continue; } // if there was any error in filling states data, skip that state
        else {
            // if states data was correctly filled, add state to arrays of states, increment nStates
            allStates[*nStates] = cState;
            (*nStates) += 1;
            if( (*nStates) >= 51) { break; } // max nStates possible is 51
        }
    }

    fclose(file1); // clsoing file stream
    return true;

}

int totalEVs(State* states, int szStates) {
    //----------------------------------------------   
    // TODO: Task 6 - write the totalEVs() function;
    //                note test_totalEVs() is 
    //                provided in test.c to test
    //                the functionality of totalEVs()
    //                   >> make build_test
    //                   >> make run_test 
    //----------------------------------------------
    // return 0; // modify or replace this line 
    int i = 0, totEVotes = 0;
    while(i < szStates) {
        totEVotes += states[i].electoralVotes; // go through all states adding up their EVs
        i += 1;
    }
    return totEVotes;
}

int totalPVs(State* states, int szStates) {
    //--------------------------------------------------   
    // TODO: Task 6 - write the totalPVs() function;
    //                then, write your own test function 
    //                test_totalPVs() in test.c
    //                   >> make build_test
    //                   >> make run_test 
    //--------------------------------------------------
    // return 0; // modify or replace this line 
    int i = 0, totPVotes = 0;
    while(i < szStates) {
        totPVotes += states[i].popularVotes; // go through all states adding up their PVs
        i += 1;
    }
    return totPVotes;
}

MinInfo minPopVoteAtLeast(State* states, int szStates, int start, int EVs) {
    //----------------------------------------------   
    // TODO: Task 7 - write minPopVoteAtLeast();
    //                a recursive helper function;
    //                returns MinInfo for the subset
    //                of [states] from index [start]
    //                to the end with the minimum
    //                popular vote total that has 
    //                sufficient [EVs] to win
    //---------------------------------------------- 
    MinInfo result;
    
    // base case (the subset is complete when [start] equals [szStates]) OR when EVs hits 0 or below
    if (start == szStates || EVs <= 0) {
        result.szSomeStates = 0; 
        result.subsetPVs = 0; 
        result.sufficientEVs = (EVs <= 0) ? true : false; // chec if EVs reached 0 before start hit szStates
        return result;
    }

    // recursive cases

    // create a subset of states with current state
    MinInfo withCurrState = minPopVoteAtLeast(states, szStates, start + 1, EVs - states[start].electoralVotes); // start + 1 (to get next state and so on), EVs - states[start].electoralVotes to lower EVS (eventually to <= 0)
    
    withCurrState.subsetPVs += ((states[start].popularVotes / 2) + 1); // add PVs to sum so far
    withCurrState.someStates[withCurrState.szSomeStates] = states[start]; // add current state (in current subset) to array of states that contribute to our result
    withCurrState.szSomeStates++; // increment szSomeStates as we added a element

    // create a subset of states without current state
    MinInfo withoutCurrState = minPopVoteAtLeast(states, szStates, start + 1, EVs); // start + 1 (to get next state and so on), lack of EVs - states[start].electoralVotes as we want to exclude the current state so we dont subtract

    // check which one has sufficient EVs, then check for min PVs
    if(withCurrState.sufficientEVs == true && withoutCurrState.sufficientEVs == false) {
        return withCurrState;
    }
    else if(withCurrState.sufficientEVs == false && withoutCurrState.sufficientEVs == true) {
        return withoutCurrState;
    }
    else {
        if (withCurrState.subsetPVs < withoutCurrState.subsetPVs) { return withCurrState; }
        else { return withoutCurrState; }
    }
}

MinInfo minPopVoteToWin(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election
    return minPopVoteAtLeast(states, szStates, 0, reqEVs);
}

MinInfo minPopVoteAtLeastFast(State* states, int szStates, int start, int EVs, MinInfo** memo) {
    //----------------------------------------------   
    // TODO: Task 8 - write minPopVoteAtLeastFast();
    //                start by copying in fully
    //                functioning code from 
    //                minPopVoteAtLeast() and make
    //                additions for memoization
    //---------------------------------------------- 
    // MinInfo res; // modify or replace this line
    // res.szSomeStates = 0; // modify or replace this line
    // return res; // modify or replace this line

    if(EVs >= 0 && memo[start][EVs].subsetPVs != -1) { return memo[start][EVs];} // base case, given array index (EVs) is valid, we chec if subsetPVs for that has changed from initialization, if yes, we return it

    MinInfo result;

    // base case (the subset is complete when [start] equals [szStates]) OR when EVs hits 0 or below
    if (start == szStates || EVs <= 0) {
        result.szSomeStates = 0; 
        result.subsetPVs = 0; 
        result.sufficientEVs = (EVs <= 0) ? true : false; // chec if EVs reached 0 before start hit szStates
        return result;
    }

    // recursive cases

    // create a subset of states with current state and store in memo
    MinInfo withCurrState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs - states[start].electoralVotes, memo); // start + 1 (to get next state and so on), EVs - states[start].electoralVotes to lower EVS (eventually to <= 0)
    
    withCurrState.subsetPVs += ((states[start].popularVotes / 2) + 1); // add PVs to sum so far
    withCurrState.someStates[withCurrState.szSomeStates] = states[start]; // add current state (in current subset) to array of states that contribute to our result
    withCurrState.szSomeStates++; // increment szSomeStates as we added a element

    // create a subset of states without current state and store in memo
    MinInfo withoutCurrState = minPopVoteAtLeastFast(states, szStates, start + 1, EVs, memo); // start + 1 (to get next state and so on), lack of EVs - states[start].electoralVotes as we want to exclude the current state so we dont subtract

    // check which one has sufficient EVs, then check for min pop vote and store in memo
    if(withCurrState.sufficientEVs == true && withoutCurrState.sufficientEVs == false) {
        memo[start][EVs] = withCurrState; // store the current state set in memo 
        return withCurrState;
    }
    else if(withCurrState.sufficientEVs == false && withoutCurrState.sufficientEVs == true) {
        memo[start][EVs] = withoutCurrState; // store the without current state set in memo
        return withoutCurrState;
    }
    else {
        // chec which set has lesser PVs, store that in memo and return withCurrState/withoutCurrState
        if (withCurrState.subsetPVs < withoutCurrState.subsetPVs) { memo[start][EVs] = withCurrState; return withCurrState; }
        else { memo[start][EVs] = withoutCurrState; return withoutCurrState; }
    }
}

MinInfo minPopVoteToWinFast(State* states, int szStates) {
    int totEVs = totalEVs(states,szStates);
    int reqEVs = totEVs/2 + 1; // required EVs to win election

    MinInfo** memo = (MinInfo**)malloc((szStates+1)*sizeof(MinInfo*));
    for (int i = 0; i < szStates+1; ++i) {
        memo[i] = (MinInfo*)malloc((reqEVs+1)*sizeof(MinInfo));
        for (int j = 0; j < reqEVs+1; ++j) {
            memo[i][j].subsetPVs = -1;
        }
    }
    MinInfo res = minPopVoteAtLeastFast(states, szStates, 0, reqEVs, memo);
    
    //----------------------------------------------   
    // TODO: Task 8 - [memo] will go out of scope 
    //                upon return, so free all
    //                heap-allocated memory for 
    //                [memo] before return 
    //---------------------------------------------- 
    int p = 0;
    for (p = 0; p <= szStates; ++p) {
        free(memo[p]); // reheck
    }
    free(memo);

    return res;
}

bool writeSubsetData(char* filenameW, int totEVs, int totPVs, int wonEVs, MinInfo toWin) {
    //-----------------------------------------------------   
    // TODO: Task 9 - write the writeSubsetData() function
    //-----------------------------------------------------
    // return false; //modify or replace this 

    FILE* output = fopen(filenameW, "w"); // open file to write output to
    if (output == NULL) { return false; } // if file not there / not opened

    fprintf(output, "%d,%d,%d,%d\n", totEVs, totPVs, wonEVs, toWin.subsetPVs); // writing first line to file manually
    int i = 0; // we start for loop at i = maxIndex as the information was stored in the reverse order when we recursively climbed out of the function
    for (i = toWin.szSomeStates -1; i >= 0; --i) {
        fprintf(output, "%s,%s,%d,%d\n", (toWin.someStates[i]).name, (toWin.someStates[i]).postalCode, (toWin.someStates[i]).electoralVotes, ( ( (toWin.someStates[i]).popularVotes / 2 ) + 1 ) ); // print state information line by line to file
    }

    fclose(output); // close file

    return true;
    
}

// project 4 end -- yay -- :)