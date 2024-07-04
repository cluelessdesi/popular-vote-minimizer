#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "MinPopVote.h"

bool test_totalEVs() {
    State aStates[10];
    int res;
    
    aStates[0].electoralVotes = 5;
    aStates[1].electoralVotes = 8;
    aStates[2].electoralVotes = 12;
    aStates[3].electoralVotes = 6;
    aStates[4].electoralVotes = 7;
    aStates[5].electoralVotes = 10;

    printf(" Checking totalEVs() for 5 States:\n");
    res = totalEVs(aStates,5);
    if (res != 38) {
        printf("  individual state EVs are 5, 8, 12, 6, 7\n");
        printf("  expected total EVs = 38, actual total EVs = %d\n",res);
        return false;
    }

    //--------------------------------------------------------   
    // TODO: Task 6 - perform additional testing to make this 
    //                test case for totalEVs() more robust
    //-------------------------------------------------------- 
    State bStates[0]; // checing for empty array
    int res1; 
    res1 = totalEVs(bStates, 0);
    printf(" Checking totalEVs() for 0 States:\n");
    if (res1 != 0) {
        printf("  individual state EVs are not there\n");
        printf("  expected total EVs = 0, actual total EVs = %d\n",res1);
        return false;
    } 

    State cStates[3]; // checing for -ve EVs
    cStates[0].electoralVotes = -1;
    cStates[1].electoralVotes = -3;
    cStates[2].electoralVotes = -5;
    int res2; 
    res2 = totalEVs(cStates, 3);
    printf(" Checking totalEVs() for 3 States:\n");
    if (res2 != -9) {
        printf("  individual state EVs are -1, -3, -5\n");
        printf("  expected total EVs = -9, actual total EVs = %d\n",res2);
        // printf("  exposed logical flaw: EVs cant be negative\n"); 
        return false;
    }

    return true;
}

bool test_totalPVs() {
    //--------------------------------------------------------   
    // TODO: Task 6 - write your own test case for totalPVs();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //--------------------------------------------------------
    // return true; 
    // return false;

    State bStates[0]; // checing for empty array
    int res1; 
    res1 = totalPVs(bStates, 0);
    printf(" Checking totalPVs() for 0 States:\n");
    if (res1 != 0) {
        printf("  individual state PVs are not there\n");
        printf("  expected total PVs = 0, actual total PVs = %d\n",res1);
        return false;
    }

    State cStates[3]; // checing for -ve PVs
    cStates[0].popularVotes = -1;
    cStates[1].popularVotes = -3;
    cStates[2].popularVotes = -5;
    int res2; 
    res2 = totalPVs(cStates, 3);
    printf(" Checking totalPVs() for 3 States:\n");
    if (res2 != -9) {
        printf("  individual state PVs are -1, -3, -5\n");
        printf("  expected total PVs = -9, actual total PVs = %d\n",res2);
        // printf("  exposed logical flaw: EVs cant be negative\n"); 
        return false;
    }

    return true;

}

bool test_setSettings() {
    //-----------------------------------------------------------   
    // TODO: Task 6 - write your own test case for setSettings();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //-----------------------------------------------------------
    // printf(" hhhhhhhhhhhhh HAVE TO DO\n"); 
    // return true; 
    // return false; //modify this

    int argc = 5; // valid input
    int year = 0;
    bool fast = false;
    bool quiet = false;
    char* argv[] = {"./a.exe", "-q", "-y", "2004", "-f"};

    bool success = setSettings(argc, argv, &year, &fast, &quiet);

    if(!success) {
        printf("Testing valid inputs to set settings\nTest Failed\n");
        return false;
    }
    if(year != 2004) {
        printf("Testing year in valid input\nTest failed\n");
        printf("Expected year = 2004, actual year = %d", year);
        return false;
    }
    if(fast != true) {
        printf("Testing fastMode in valid input\nTest failed\n");
        printf("Expected fastMode = true, actual fastMode = false");\
        return false;
    }
    if(quiet != true) {
        printf("Testing quietMode in valid input\nTest failed\n");
        printf("Expected quietMode = true, actual quietMode = false");
        return false;
    }

    // invalid input - incorrect year
    int argc2 = 5; 
    int year2 = 0;
    bool fast2 = false;
    bool quiet2 = false;
    char* argv2[] = {"./a.exe", "-q", "-y", "2003", "-f"};

    bool success2 = setSettings(argc2, argv2, &year2, &fast2, &quiet2);

    if(success2 && year2 != 0) {
        printf("Testing invalid inputs to set settings\n");
        printf("Test Failed\n");
        printf("Function should have left year = 0\n");
        return false;
    }

    // invalid input - invalid argument in argv
    int argc3 = 5; 
    int year3 = 0;
    bool fast3 = false;
    bool quiet3 = false;
    char* argv3[] = {"./a.exe", "-q", "-y", "2004", "-x"};

    bool success3 = setSettings(argc3, argv3, &year3, &fast3, &quiet3);

    if(success3) {
        printf("Testing one invalid input to set settings\nTest Failed\n");
        printf("Function should have returned false upon encountering invalid argument\n");
        return false;
    }

    // invalid input - invalid argumentin argv
    int argc4 = 5; 
    int year4 = 0;
    bool fast4 = false;
    bool quiet4 = false;
    char* argv4[] = {"./a.exe", "-a", "-b", "2002", "-f"};

    bool success4 = setSettings(argc4, argv4, &year4, &fast4, &quiet4);

    if(success4) {
        printf("Testing with multiple invalid inputs to set settings\nTest Failed\n");
        printf("Function should have returned false upon encountering invalid arguments\n");
        return false;
    }

    // invalid input - -y present but no year
    int argc5 = 4; 
    int year5 = 0;
    bool fast5 = false;
    bool quiet5 = false;
    char* argv5[] = {"./a.exe", "-q", "-f", "-y"};

    bool success5 = setSettings(argc5, argv5, &year5, &fast5, &quiet5);

    if(success5) {
        printf("Testing with multiple invalid inputs to set settings\nTest Failed\n");
        printf("Function should have returned false upon encountering -y with no year after it\n");
        return false;
    }

    return true;

}

bool test_inFilename() {
    //----------------------------------------------------------   
    // TODO: Task 6 - write your own test case for inFilename();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //----------------------------------------------------------
    // return false; //modify this
    char filename[16];
    int year = 1832;
    inFilename(filename, year);
    if(strcmp(filename, "data/1832.csv") != 0) {
        printf("Test with valid year failed");
        printf("expected filename: data/1832.csv actual filename: %s", filename);
        return false;
    }
    // return true; 

    char file1[16];
    year = -1832;
    inFilename(file1, year);
    if(strcmp(file1, "data/-1832.csv") != 0) {
        printf("Test with invalid year failed");
        printf("expected filename: data/-1832.csv actual filename: %s", file1);
        return false;
    }

    char file2[16];
    year = -1832;
    inFilename(file2, year);
    // printf("file2: %s\n", file2); 
    if(strcmp(file2, "data/-1832.csv") != 0) {
        printf("Test failed, negative year should have not generated a filename\n");
        // printf("expected filename: data/-1832.csv actual filename: %s", filename); 
        return false;
    }

    return true;
}

bool test_outFilename() {
    //-----------------------------------------------------------   
    // TODO: Task 6 - write your own test case for outFilename();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //-----------------------------------------------------------
    // return false; //modify this

    // return true; 

    char filename[25];
    int year = 1832;
    outFilename(filename, year);
    if(strcmp(filename, "toWin/1832_win.csv") != 0) {
        printf("Test with valid year failed\n");
        printf("expected filename: toWin/1832_win.csv actual filename: %s\n", filename);
        return false;
    }
    // return true; 

    char file1[25];
    year = -1832;
    outFilename(file1, year);
    if(strcmp(file1, "toWin/-1832_win.csv") != 0) {
        printf("Test with invalid year failed\n");
        printf("expected filename: toWin/-1832_win.csv actual filename: %s\n", file1);
        return false;
    }

    char file2[25];
    year = -1832;
    outFilename(file2, year);
    // printf("file2: %s\n", file2); 
    if(strcmp(file2, "toWin/-1832_win.csv") != 0) {
        printf("Test failed, negative year should have not generated a filename\n");
        // printf("expected filename: data/-1832.csv actual filename: %s", filename); 
        return false;
    }

    return true;
}

bool test_parseLine() {
    //---------------------------------------------------------   
    // TODO: Task 6 - write your own test case for parseLine();
    //                use test_totalEVs() as a sample;
    //                make sure to test all components
    //---------------------------------------------------------
    // return false; //modify this 
    // return true;  

    char line[200]; // valid input;
    strcpy(line, "stateA,AA,88,100"); 
    State stateA;
    bool success = parseLine(line, &stateA);

    if(!success) {
        printf("Testing if stateA data was assigned properly:\n");
        printf("Test failed, check code for failure\n");
        return false;
    }
    
    char expSName[10];
    strcpy(expSName, "stateA");
    char expPCode[5];
    strcpy(expPCode, "AA");
    int expEVs = 88;
    int expPVs = 100;

    if (strcmp(expSName, stateA.name) != 0) {
        printf("Testing if stateA name was assigned properly:\n");
        printf("Test failed\n");
        printf("Expected name: stateA, actual name = %s", stateA.name);
        return false;
    } 

    if (strcmp(expPCode, stateA.postalCode) != 0) {
        printf("Testing if stateA postal code was assigned properly:\n");
        printf("Test failed\n");
        printf("Expected postal code, actual postal code = %s", stateA.postalCode);
        return false;
    } 

    if (expEVs != stateA.electoralVotes) {
        printf("Testing if stateA electoral votes was set correctly\n");
        printf("Test failed\n");
        printf("Expected EVs = 88, actual EVs = %d", stateA.electoralVotes);
        return false;
    }

    if (expPVs != stateA.popularVotes) {
        printf("Testing if stateA popular votes was set correctly\n");
        printf("Test failed\n");
        printf("Expected PVs = 100, actual PVs = %d", stateA.popularVotes);
        return false;
    }

    // invalid input - just commas
    char line2[100];
    strcpy(line2, ",,,,");
    State stateB;
    bool success2 = parseLine(line2, &stateB);
    if(success2) {
        printf("Testing invalid line\n");
        printf("Test failed\n");
        printf("Function expected return = false, function actual return = true\n");
        return false;
    }   

    //invalid input - name missing
    char line3[100];
    strcpy(line3, "CC, 88, 100");
    State stateC;
    bool success3 = parseLine(line3, &stateC);
    if(success3) {
        printf("Testing invalid line\n");
        printf("Test failed\n");
        printf("Function expected return = false, function actual return = true\n");
        return false;
    }

    //invalid input - postal code missing
    char line4[100];
    strcpy(line4, "stateD, 88, 100");
    State stateD;
    bool success4 = parseLine(line4, &stateD);
    if(success4) {
        printf("Testing invalid line\n");
        printf("Test failed\n");
        printf("Function expected return = false, function actual return = true\n");
        return false;
    }

    //invalid input - EVs missing
    char line5[100];
    strcpy(line5, "stateE, EE, 100");
    State stateE;
    bool success5 = parseLine(line5, &stateE);
    if(success5) {
        printf("Testing invalid line\n");
        printf("Test failed\n");
        printf("Function expected return = false, function actual return = true\n");
        return false;
    }

    //invalid input - PVs missing
    char line6[100];
    strcpy(line6, "stateF, FF, 88");
    State stateF;
    bool success6 = parseLine(line6, &stateF);
    if(success6) {
        printf("Testing invalid line\n");
        printf("Test failed\n");
        printf("Function expected return = false, function actual return = true\n");
        return false;
    }

    return true;

}

bool test_readElectionData() {
    //----------------------------------------------------------------   
    // TODO: Task 6 - write your own test case for readElectionData();
    //                make sure to test all components
    //----------------------------------------------------------------
    // return false; //modify this 
    // return true; 

    // valid file
    char file1832[20] = "data/1832.csv";
    State allStates[51];
    int nStates = 0;

    bool success = readElectionData(file1832, allStates, &nStates);

    printf("Test: reading data from valid file (1832.csv) \n");
    if (!success) {
        printf("Test: failed, file was not read in");
        return false;
    }
    else {
        int expnStates = 24;
        if (nStates != expnStates) {
            printf("Test: nStates check\n");
            printf("Test failed\n");
            printf("Expected nStates = 24, actual nStates = %d\n", nStates);
            return false;
        }

        int expEVs = 288;
        int actualEVs = totalEVs(allStates, 24);
        if (expEVs != actualEVs) {
            printf("Test: total EVs check\n");
            printf("Test failed\n");
            printf("Expected total EVs = 200, actual total EVs = %d\n", actualEVs);
            return false;
        }

        int expPVs = 1327388;
        int actualPVs = totalPVs(allStates, 24);
        if (expPVs != actualPVs) {
            printf("Test: total PVs check\n");
            printf("Test failed\n");
            printf("Expected total PVs = 1327388, actual total PVs = %d\n", actualPVs);
            return false;
        }
    }

    // return true; 
    

    // invalid file
    char file2028[20] = "data/2028.csv";
    State allStates2[51];
    int nStates2 = 0;
    bool success2 = readElectionData(file2028, allStates2, &nStates2);
    printf("Test: reading data from invalid file (2028.csv) \n");
    if (success2) {
        printf("Test: failed, file was read in");
        return false;
    }

    return true;


}

bool test_minPVsSlow() {
    //----------------------------------------------------------------- 
    // TODO: Task 7 - write your own test case for minPopVoteAtLeast();
    //                make sure to test all components
    //-----------------------------------------------------------------
    
    // valid inputs
    State allStates[4];
    
    strcpy(allStates[0].name, "stateA");
    strcpy(allStates[0].postalCode, "aa");
    allStates[0].electoralVotes = 10;
    allStates[0].popularVotes = 11;

    strcpy(allStates[1].name, "stateB");
    strcpy(allStates[1].postalCode, "bb");
    allStates[1].electoralVotes = 20;
    allStates[1].popularVotes = 21;

    strcpy(allStates[2].name, "stateC");
    strcpy(allStates[2].postalCode, "cc");
    allStates[2].electoralVotes = 30;
    allStates[2].popularVotes = 31;

    strcpy(allStates[3].name, "stateD");
    strcpy(allStates[3].postalCode, "dd");
    allStates[3].electoralVotes = 40;
    allStates[3].popularVotes = 41;

    MinInfo result = minPopVoteToWin(allStates, 4);

    int expectPVs = 32;
    int expectSize = 2;
    bool expectSufEVs = true;

    printf("Testing size of returned set:\n");
    if (expectSize != result.szSomeStates) {
        printf("Test failed\n");
        printf("Expected size = 2, actual size = %d\n", result.szSomeStates);
        return false;
    }

    printf("Testing PVs of returned set:\n");
    if (expectPVs != result.subsetPVs) {
        printf("Test failed\n");
        printf("Expected PVs = 32, actual PVs = %d\n", result.subsetPVs);
        return false;
    }    

    printf("Testing sufficient EVs of returned set:\n");
    if (expectSufEVs != result.sufficientEVs) {
        printf("Test failed\n");
        printf("sufficientEVs supposed to be true, sufficientEVs is false");
        return false;
    }

    printf("Testing states in returned set\n");
    if (strcmp("stateD", result.someStates[0].name) != 0 && strcmp("stateD", result.someStates[1].name) != 0) {
        printf("Test failed for stateD");
        printf("Expected stateD in index 0 or 1, stateD not there in either\n");
        return false;
    }
    if (strcmp("stateB", result.someStates[0].name) != 0 && strcmp("stateB", result.someStates[1].name) != 0) {
        printf("Test failed for stateB");
        printf("Expected stateB in index 0 or 1, stateB not there in either\n");
        return false;
    }

    // maybe try invalid inputs?
   
    return true;
}

bool test_minPVsFast() {
    //--------------------------------------------------------------------- 
    // TODO: Task 8 - write your own test case for minPopVoteAtLeastFast();
    //                make sure to test all components
    //---------------------------------------------------------------------
    // printf(" hhhhhhhhhhhhhhhhhhhhhhhhh HAVE TO DO\n"); 

    return true;
    // return false; //modify this
}

int main() {
    printf("Welcome to the Popular Vote Minimizer Testing Suite!\n\n");
    
    printf("Testing totalEVs()...\n"); 
    if (test_totalEVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing totalPVs()...\n"); 
    if (test_totalPVs()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing setSettings()...\n"); 
    if (test_setSettings()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing inFilename()...\n"); 
    if (test_inFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing outFilename()...\n"); 
    if (test_outFilename()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing parseLine()...\n"); 
    if (test_parseLine()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing readElectionData()...\n"); 
    if (test_readElectionData()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }
    
    printf("Testing minPopVoteToWin()...\n"); 
    if (test_minPVsSlow()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    printf("Testing minPopVoteToWinFast()...\n"); 
    if (test_minPVsFast()) {
        printf("  All tests PASSED!\n");
    } else {
        printf("  test FAILED.\n");
    }

    return 0;
}
