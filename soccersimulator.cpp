///
// Student name: Sydney LeBlanc
// Student number: 20880112
//
// SYDE 121 assignment: 3
// file name: a3-q1.cpp
//
// I hereby declare that this code, submitted for credit for the course
// SYDE121, is a product of my own efforts.  This coded solution has
// not been plagiarized from other sources and has not been knowingly
// plagiarized by others.
//
// Project: Soccer Simulation
// Purpose: to stimulate a game of soccer between two teams,Team A and Team B
//
// Due date: October 30, 2020
//***************************************************

/*
 Testing Scenerios:
 
 - While running through, I placed a breakpoint on each function to track each
    randomly generated integers and updated stats, to verify the correct statement is
    outputted and the correct stat is updated
 - Ran through the program twice, vertifying the stats and number of event
    types by manually counting and visible inspection
 - Confirmed that each run had a different outcome and the correct stats
 - After 2 run-thoughs, every event type combination had been outputted, in different orders
 Limitations: not all events are guaranteed to occur in one game, some games may have more
    repeats than others
 
 OUTPUTS: (final stats only)
 First run-through:
 Team A and Team B tied with final scores of 1

 Final game stats:
                Team A:      Team B:
 Shots on goal:     1            2
 Shots off goal:    4            2
 Shots blocked:     3            2
 Fouls:             1            6
 Yellow Cards:      1            1
 Red Cards:         0            3
 
 Second run-through:
 Team A won with a final score of 5, compared to Team B with 3

 Final game stats:
                Team A:      Team B:
 Shots on goal:     3            1
 Shots off goal:    2            2
 Shots blocked:     1            4
 Fouls:             6            4
 Yellow Cards:      1            1
 Red Cards:         3            1
 */

#include <iostream>
#include <ctime>
#include <iomanip>

using namespace std;

void is_goal_scored(int& goal_scored);
//PURPOSE: to determine if a goal is scored, blocked or missed
//INPUT: goal_scored – integer value to be randomized
//OUTPUT: nothing, value gets passed by reference

void is_foul_given(int& foul_given);
//PURPOSE: to determine if a foul is given
//INPUT: foul_given – integer value to be randomized
//OUTPUT: nothing; value gets passed by reference

void update_score(int goal_scored, int& score, int& shots,
                  int& block, int& shot_off, int event_type);
//PURPOSE: Computes and updates stats after an attempt to score a goal
//INPUT: goal_scored – integer to determine which stats are computed
//      score, shots, blocks, shot_off – corresponding integer values
//OUTPUT: nothing; values gets passed by reference

void update_fouls(int foul_given, int& fouls, int& yellow_card, int& red_card);
//PURPOSE: Computes stats after a team commits a foul
//INPUT: foul_given – integer to determine which stats are computed
//       fouls, yellow_card, red_card – corresponding integer values
//OUTPUT: nothing; values gets passed by reference

void halftime_stats(int a_score, int b_score);
//PURPOSE: to output current winner at halftime and the correpsonding statement
//INPUT: a_score, b_score – integers values as the scores
//OUTPUT: nothing; output is the the console

void final_stats(int a_score, int b_score);
//PURPOSE: to output final winner at the end and the correpsonding statement
//INPUT: a_score, b_score – integers values as the scores
//OUTPUT: nothing; output is the the console

void output_stats(int a_shots, int b_shots, int a_shot_off, int b_shot_off, int a_block,
                  int b_block, int a_fouls, int b_fouls, int a_yellow, int b_yellow,
                  int a_red, int b_red);
//PURPOSE: to output all computed stats
//INPUT: all corresponding integer values
//OUTPUT: nothing; output is to the console

void is_goal_scored(int& goal_scored, int event_type){
    // Step1. Generate a random number to determine the condition of the shot
    if (event_type >= 5) {
        goal_scored = rand() % 3;
    }
    else {
        goal_scored = rand() % 4;
    }
    // Step2. Output the corresponding statement
    switch (goal_scored) {
        case 0:
            cout << "scored a goal! Fantastic shot!\n";
            break;
        case 1:
            cout << "shot, but the goalkeeper blocked it!\n"
                    << "Wow, The crowd went insane!\n";
            break;
         case 2:
            cout << "shot, but it was made off goal. So close!\n";
            break;
        case 3:
            cout << "shot, but it was blocked by a player who is not the"
           << " last defender!\nAmazing play by the other team!\n";
            break;
    }
}

void is_foul_given(int& foul_given) {
    // Step1. Generate a random number to determine foul
    foul_given = rand() % 3;
    // Step2. Output the corresponding statement
    switch (foul_given) {
        case 0:
            cout << "Luckily, no foul card was given.\n";
            break;
        case 1:
            cout << "Yikes! A yellow card was given for that foul!\n";
            break;
        case 2:
            cout << "Oh no! They received a red card for that foul!\n";
            break;
    }
}

void update_score(int goal_scored, int& score, int& shots,
                  int& block, int& shot_off, int event_type){
    // Step1. Update the number of shots and additional stats depending
    // on shot
    // If they shot on target, update number of shots; if it is a penality
    // or free kick, it does not classify as a shot on goal
    if (event_type <= 2) {
        switch (goal_scored) {
            case 0:
                ++shots;
                ++score;
                break;
            case 1:
                ++shots;
                ++block;
                break;
            case 2:
                ++shot_off;
                break;
            case 3:
                ++block;
                break;
        }
    }
    else {
        switch (goal_scored) {
            case 0:
                ++score;
                break;
            case 1:
                ++block;
                break;
            case 2:
                ++shot_off;
                break;
            case 3:
                ++block;
                break;
        }
    }
}

void update_fouls(int foul_given, int& fouls, int& yellow_card, int& red_card){
    // Step1. Update number of fouls for the corresponding team
    ++fouls;
    // Step2. Update additional stats depending on condition of foul
    switch (foul_given) {
         case 1:
            ++yellow_card;
            break;
        case 2:
            ++red_card;
            break;
    }
}

void halftime_stats(int a_score, int b_score){
    // Step1. Determine which team has the higher score and output
    // corresponding statement
    cout << "\nWe've rearched halftime, the game has been intense so far!\n";
    if (a_score > b_score) {
        cout << "Team A is currently winning with a score of " << a_score
            << ", compared to Team B with " << b_score << endl;
    }
    else if(a_score < b_score){
        cout << "Team B is currently winning with a score of " << b_score
        << ", compared to Team A with " << a_score << endl;
    }
    else {
        cout << "Team A and Team B are currently tied with scores of " << a_score << endl;
    }
    cout << "\nHalftime Stats:\n";
}

void final_stats(int a_score, int b_score){
    // Step1. Determine which team has the higher score and output
    // corresponding statement
    cout << "\nWow what a game!\n";
    if (a_score > b_score) {
        cout << "Team A won with a final score of " << a_score
            << ", compared to Team B with " << b_score << endl;
    }
    else if (a_score < b_score) {
        cout << "Team B won with a final score of " << b_score
            << ", compared to Team A with " << a_score << endl;
    }
    else {
        cout << "Team A and Team B tied with final scores of " << a_score << endl;
    }
    cout << "\nFinal game stats:\n";
}

void output_stats(int a_shots, int b_shots, int a_shot_off, int b_shot_off, int a_block,
                  int b_block, int a_fouls, int b_fouls, int a_yellow, int b_yellow,
                  int a_red, int b_red){
    // Step1. Output all stats in a chart format
    cout << " \t\t\t   Team A: \t Team B:\n";
    cout << "Shots on goal: \t" << a_shots << "\t\t\t" << b_shots << endl;
    cout << "Shots off goal: " << a_shot_off << "\t\t\t" << b_shot_off << endl;
    cout << "Shots blocked: \t" << a_block << "\t\t\t" << b_block << endl;
    cout << "Fouls: \t\t\t" << a_fouls << "\t\t\t" << b_fouls << endl;
    cout << "Yellow Cards: \t" << a_yellow << "\t\t\t" << b_yellow << endl;
    cout << "Red Cards: \t\t" << a_red << "\t\t\t" << b_red << endl;
}

void start_soccer_simulation(){
    // [Setup] Call srand() to randomize game outcome
    srand(static_cast<unsigned int>(time(0)));
    // [Setup] Declare and intialize variables
    int goal_scored = 0, foul_given = 0;
    int a_shots = 0,a_shot_off = 0, a_fouls = 0, a_yellow = 0, a_red = 0;
    int b_shots = 0, b_shot_off = 0, b_fouls = 0, b_yellow = 0, b_red = 0;
    int a_block = 0, b_block = 0, a_score = 0, b_score = 0;
   
    // Step1. Let user know the game has begun
    cout << "Good evening!\n"
        << "It's time for the soccer game to begin!\n";
    
    // Step2. Randomize number of events between 1 and 20
    int number_of_events = (rand() % 20) + 1;
    
    // Step3. For every event, generate a random type of event between 1 and 6
    //      and output the corresponding statement
    for (int count = 0; count < number_of_events; count++) {
       int event_type = (rand() % 6) + 1;
        switch (event_type) {
            case 1:
                cout << "\nTeam A ";
                break;
            case 2:
                cout << "\nTeam B ";
                break;
            case 3:
                cout << "\nTeam B commited a foul, so Team A gets a free kick.\n"
                    << "Team A ";
                break;
            case 4:
                cout << "\nTeam A commited a foul, so Team B gets a free kick.\n"
                    << "Team B ";
                break;
            case 5:
                cout << "\nTeam B commited a foul close to the goal, so Team A gets"
                    << " a penalty kick.\nTeam A ";
                break;
            case 6:
                cout << "\nTeam A commited a foul close to the goal, so Team B gets"
                    << " a penalty kick.\nTeam B ";
                break;
        }
        // Step3.1 Determine the circumstance around a goal and/or a foul
        is_goal_scored(goal_scored, event_type);
        if (event_type >= 3) {
            is_foul_given(foul_given);
        }
        // Step3.2 Update corresponding stats depending on event type
        if (event_type == 1) {
            update_score(goal_scored, a_score, a_shots, a_block, a_shot_off, event_type);
        }
        else if (event_type == 2) {
            update_score(goal_scored, b_score, b_shots, b_block, b_shot_off, event_type);
        }
        else if (event_type == 3 || event_type == 5) {
            update_score(goal_scored, a_score, a_shots, a_block, a_shot_off, event_type);
            update_fouls(foul_given, b_fouls, b_yellow, b_red);
        }
        else {
            update_score(goal_scored, b_score, b_shots, b_block, b_shot_off, event_type);
            update_fouls(foul_given, a_fouls, a_yellow, a_red);
        }
        // Step3.3 After half the events have occured, output current winner and stats
        if (count == ((number_of_events - 1) - number_of_events / 2)) {
            halftime_stats(a_score, b_score);
            output_stats(a_shots, b_shots, a_shot_off, b_shot_off, a_block, b_block,
                         a_fouls, b_fouls, a_yellow, b_yellow, a_red, b_red);
            cout << "\nHalftime is over, time to begin the second half!\n";
        }
    }
    // Step4. After all events have occured, output winner and final stats
    final_stats(a_score, b_score);
    output_stats(a_shots, b_shots, a_shot_off, b_shot_off, a_block, b_block,
                        a_fouls, b_fouls, a_yellow, b_yellow, a_red, b_red);
    cout << "\nThat's all folks, have a good night!\n";
}

int main(){
    // Envoke the soccer simulation
    start_soccer_simulation();
}
