// APSC 143 Engineering Programming Project Starter Code
// Feel free to change anything about this file, but do not remove "#include "colours.h".

// Make sure to include all relevant libraries
#include <stdio.h>
#include <string.h>
#include "colours.h"
#include <stdlib.h>
#include <time.h>


#define PACMAN 'P'
#define GHOST 'G'
#define DOT '.'
#define WALL 'W'
#define EMPTY ' '
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'

void printMap(char map[11][32]){ // Function to scan and print the map from filed
    map[1][0] ='W';
    for (int n = 0; n < 12; n++) { // for loop checks all rows
        for (int f = 0; f < 32; f++) { // for loop checks all columns
            if (map[n][f] == 'G') {
                colourChange(13);
                printf("%c", map[n][f]);
            }
            else if (map[n][f] == 'P'){
                colourChange(6);
                printf("%c", map[n][f]);
            }else if (map[n][f] == 'W'){
                colourChange(1);
                printf("%c", map[n][f]);
            }
            //if (n == 1 && f == 0) {
              //  printf("W");
            //}
            else {
                colourChange(15);
                printf("%c", map[n][f]);
            }
        }
        printf("\n");
    }
}

int winCheck(char map [11][32]){ // Function ends the game when pacman has collected all the dots
    int dotcounter = 0;
    int x = 0;
    while (dotcounter == 0 && x<32){ // counts how many dots are left on map
        for (int y =1;y<11;y++){
            if (map[y][x]=='.'){
                dotcounter++;
            }
        }x++;
    }
    if (dotcounter == 0){
        char youWin;
        printf("Congratulations! You win! Press any key to exit the\n"
               "game\n");
        scanf("%c", youWin);
        int endgame = 2;
        return endgame;
    }else{
        int endgame = 0;
        return endgame;
    }

}
int loseCheck(int pacH, int pacV, int gH, int gV, int g2H, int g2V) { // Function ends the game if a ghost catches pacman
    if ((pacH == gH && pacV == gV) || (pacH == g2H && pacV == g2V)) {
        char youLost;
        printf("Sorry, you lose. Press any key to exit the game\n");
        scanf("%c", youLost);
        int endgame = 1;
        return endgame;
    } else {
        int endgame = 0;
        return endgame;
    }
}


int isWall (char path, int pacLocV, int pacLocH,char map[11][32]){ // Function checks for walls around pacman
    int check=0;
    // Checks one space above or below for vertical movement
    if (path=='w' ) {
        if (map[pacLocV-1][pacLocH] == 'W') {
            check = 1;
        }else {
            check = 0;
        }
    }
    if (path == 's') {
        if (map[pacLocV + 1][pacLocH] == 'W') {
            check = 1;
        }else {
            check = 0;
        }
    }
    // Checks 3 spaces to right and left for horizontal movement
    if(path == 'a'){
        if(map[pacLocV][pacLocH-3]== 'W'){
            check = 1;
        }else {
            check = 0;
        }
    }
    if(path =='d') {
        if (map[pacLocV][pacLocH + 3] == 'W') {
            check = 1;
        } else {
            check = 0;
        }
    }
    return check; // Check=1 means there is a wall, check=0 means there is no wall
}


int ghostwall (int randomInt, int ghostLocV, int ghostLocH, char map[11][32]) { // Function checks for walls around ghosts
    map[1][0]='W';
    int check = 0;
    // Random number between 0 and 3 is generated
    if(randomInt == 0){ // If random number is zero, check above ghost
        if(map[ghostLocV-1][ghostLocH] == 'W') {
            check = 1;
        }
    }if(randomInt == 1){ // If random number is one, check below ghost
        if(map[ghostLocV+1][ghostLocH] == 'W'){
            check = 1;
        }
    }if(randomInt == 2){ // If random number is 2, check left of ghost
        if(map[ghostLocV][ghostLocH-3] == 'W'){
            check = 1;
        }
    }if(randomInt == 3){ // If random number is 3, check right of ghost
        if(map[ghostLocV][ghostLocH+3] == 'W'){
            check = 1;
        }
    }
    return check;
    }



int movement (char direction){ // Funciton for movement of pacman and ghosts
    // Vertical movement is one up or one down
    if (direction == 'w'){
        int changeM = -1;
        return changeM;
    }if (direction == 's'){
        int changeM = 1;
        return changeM;
    }
    // Horizontal movement is 3 right or 3 left
    if (direction == 'd'){
        int changeM = 3;
        return changeM;
    }if (direction == 'a'){
        int changeM = -3;
        return changeM;
    }

}
int chasepac(char map[11][32], int gLocH, int glocV) {//Checks to see if pac man is in the line of sight of the ghost
    int seePac = 0;
    int checkdir = 0;//Variable to check each direction
    while (seePac == 0 && checkdir < 4) {// Goes through all four directions until all 4 are checked or pacman is seen
        int wallview = 0;
        int x = 0;
        while (seePac == 0 && wallview == 0) {
            if (checkdir == 0) {// Checks the up direction
                if (map[glocV - x][gLocH] == 'W') { // This if statement checks to see if there is a wall above the ghost
                    wallview = 1;
                }
                if (map[glocV - x][gLocH] == 'P'){// Check to see if Pac man is above
                    seePac = 1;
                checkdir = -1;
            }
                else{
                    x++;
                }
            }
            if (checkdir == 1) {//Checks the down direction
                if (map[glocV + x][gLocH] == 'W') {// Checks for a wall below the ghost
                    wallview = 1;
                }
                if (map[glocV + x][gLocH] == 'P') {// Checks for pac man below the ghost
                    seePac = 1;
                    checkdir=0;
                } else {
                    x++;
                }
            }
            if (checkdir == 2) {// Checks the left direction
                if (map[glocV][gLocH - x] == 'W') {//Check if their a wall to the left of ghost
                    wallview = 1;
                }
                if (map[glocV + x][gLocH - x] == 'P') {//Checks if pac man is to the left of the ghost
                    seePac = 1;
                    checkdir = 1;
                } else {
                    x = x + 3;
                }
            }
            if (checkdir == 3) {//Checks the right direction
                if (map[glocV][gLocH + x] == 'W') {// Checks for a wall to the right of the ghost
                    wallview = 1;
                }
                if (map[glocV][gLocH + x] == 'P') {// Checks for pacman to the right of the ghost
                    seePac = 1;
                    checkdir = 2;
                } else {
                    x = x + 3;
                }
            }
        }checkdir ++;
    }return checkdir;// Returns a number between 0-3 if it sees pacman or 4 if it does not see pacman
}



int main() {
    char mapArray[11][32];
    FILE *fp = fopen("/Users/jordanvick/Desktop/Queen's University/APSC 143/PACMAN/apsc143project 2/cmake-build-debug/map.txt","r");
    if (fp == NULL) {
        printf("File not found\n");
    }
    for (int x = 0; x < 33; x++) {// All characters in array should be spaces before copying file
        for (int y = 0; y < 12; y++) {
            mapArray[y][x] = ' ';
        }
    }

    for (int x = 0; x < 11; x++) {// Adds left wall
        mapArray[x][0] = 'W';
        mapArray[x][1] = ' ';
        mapArray[x][2] = ' ';
    }

    for (int x = 0; x < 11; x++) {// Adds right wall
        mapArray[x][30] = 'W';
        mapArray[x][29] = ' ';
    }

    for (int y = 0; y < 32; y = y + 3) {// Adds bottom wall
        mapArray[10][y] = 'W';
        mapArray[10][y + 1] = ' ';
        mapArray[10][y + 2] = ' ';
    }

    for (int x = 1; x < 10; x = x + 1) { // Copys map from file into the array
        for (int y = 3; y < 29; y = y + 3) {
            fscanf(fp, "%s", &mapArray[x][y]);
        }
    }

    for (int x = 0; x < 33; x++) {
        for (int y = 0; y < 12; y++) {
            if (mapArray[y][x] == NULL || mapArray[y][x] == '\n') {// Replaces null and \n characters with spaces
                mapArray[y][x] = ' ';
            }
        }
    }

    fclose(fp);
    mapArray[10][3] = 'W';
    char dotArray[11][32]; // Identical array that keeps track of dot locations
    for (int x = 0; x < 33; x++) {
        for (int y = 0; y < 12; y++) {
            dotArray[y][x] = ' ';
        }
    }

    for (int x = 0; x < 33; x++) {
        for (int y = 0; y < 12; y++) {
            dotArray[y][x] = mapArray[y][x];
        }
    }

    // Make both ghosts starting locations dots
    dotArray[1][3] = '.';
    dotArray[9][27] = '.';


    for (int y = 0; y < 32; y = y + 3) {// Adds top wall
        mapArray[0][y] = 'W';
        mapArray[0][y + 1] = ' ';
        mapArray[0][y + 2] = ' ';
    }

    // Initialize variables for both ghosts and pacmans locations, pacmans last location and the win and lose check
    int randomNumbertwo = 2; //Ghost ones starting direction is right
    int randomNumber = 3;  //Ghost twos starting direction is left
    int pacLocV = 5;
    int pacLocH = 15;
    int gOneLocV = 1;
    int gOneLocH = 3;
    int gTwoLocV = 9;
    int gTwoLocH = 27;
    int pacoldLocV;
    int pacoldLocH;
    int wincounter = 0;
    int losecounter = 0;
    printMap(mapArray);
    while (wincounter == 0 && losecounter == 0) {
        wincounter = winCheck(mapArray); //Calls wincheck function
        losecounter = loseCheck(pacLocH, pacLocV, gOneLocH, gOneLocV, gTwoLocH, gTwoLocV);//Calls lose check function
        char direction;
        direction = getchar();
        fflush(stdin);//removes buffer from user input

        // GHOST ONE CODE
        int seePac;
        int checkValue;
        seePac = chasepac(mapArray, gOneLocH, gOneLocV);//Call chasepac function for ghost1
        if (seePac == 4) {//If ghost doesent see pacman
            checkValue = ghostwall(randomNumber, gOneLocV, gOneLocH, mapArray);//Calls function to check for walls around ghost
            if (checkValue == 1) {
                while (checkValue == 1) {//Each random number checks a new direction until the ghost finds a direction without a wall
                    srand(time(NULL));
                    randomNumber = rand() % 4;
                    checkValue = ghostwall(int(randomNumber), gOneLocV, gOneLocH, mapArray);
                }
            }
        } else {
            randomNumber = seePac;//If ghost see's pacman
        }
        char gdirection;
        //Assigns a "w", "a", "s", or "d" direction to each possible random number
        if (randomNumber == 0) {
            gdirection = 'w';
        }
        if (randomNumber == 1) {
            gdirection = 's';
        }
        if (randomNumber == 2) {
            gdirection = 'a';
        }
        if (randomNumber == 3) {
            gdirection = 'd';
        }
        if (gdirection == 'w' || gdirection == 's') { //If ghost direction is up or down
            int gmovement = movement(gdirection); //Calls movement function
            gOneLocV = gOneLocV + gmovement;
        }
        if (gdirection == 'd' || gdirection == 'a') { //If ghost direction is left or right
            int gmovement = movement(gdirection); //Calls movement funciton
            gOneLocH = gOneLocH + gmovement;
        }


        // GHOST 2 CODE
        int checkValuetwo;
        int seePactwo;
        seePactwo = chasepac(mapArray, gTwoLocH, gTwoLocV);//Checks to see if ghost 2 sees pacman
        if (seePactwo == 4) {//Ghost does not see pac man
            checkValuetwo = ghostwall(int(randomNumbertwo), gTwoLocV, gTwoLocH, mapArray);//Checks to see if the ghost needs to change direction
            if (checkValuetwo == 1) {//Ghost needs a new direction
                while (checkValuetwo == 1) {
                    srand(time(NULL));
                    randomNumbertwo = rand() % 4;//Picks a random direction
                    checkValuetwo = ghostwall(int(randomNumbertwo), gTwoLocV, gTwoLocH, mapArray);//Checks to see if there is a wall in that direction
                }
            }
        } else {
            randomNumbertwo = seePactwo;
        }//Depending on the random number found will result in which direction the ghost moves
        char gdirectiontwo;
        if (randomNumbertwo == 0) {
            gdirectiontwo = 'w';
        }
        if (randomNumbertwo == 1) {
            gdirectiontwo = 's';
        }
        if (randomNumbertwo == 2) {
            gdirectiontwo = 'a';
        }
        if (randomNumbertwo == 3) {
            gdirectiontwo = 'd';
        }
        //Changes the coordinate of the ghost depending on the direction it is going in
        if (gdirectiontwo == 'w' || gdirectiontwo == 's') {
            int gmovement = movement(gdirectiontwo);
            gTwoLocV = gTwoLocV + gmovement;
            }
        if (gdirectiontwo == 'd' || gdirectiontwo == 'a') {
            int gmovement = movement(gdirectiontwo);
            gTwoLocH = gTwoLocH + gmovement;
        }

        //Keeps track of pacmans last location
        pacoldLocH = pacLocH;
        pacoldLocV = pacLocV;
        int wallcheck = isWall(direction, pacLocV, pacLocH, mapArray);//Call function to check for walls around pacman
        if (wallcheck == 0) {
            if (direction == 'w' || direction == 's') {
                int movementChange = movement(direction);//Calls movement function for pacman (vertical movement)
                pacLocV = pacLocV + movementChange;
            }
            if (direction == 'd' || direction == 'a') {
                int movementChange = movement(direction);// Calls movement funciton for pacman (horiontal movement)
                pacLocH = pacLocH + movementChange;
            }
        }
        dotArray[pacoldLocV][pacoldLocH] = ' ';
        mapArray[pacoldLocV][pacoldLocH] = ' ';//Turns dots into spaces based on pacmans old location
        mapArray[pacLocV][pacLocH] = 'P';

        for (int y = 1; y < 12; y++) {//Copies any remaining '.' to the array temporarily removing the ghost
            for (int x = 3; x < 29; x++) {
                if (mapArray[y][x] == '.' || mapArray[y][x] == 'G') {
                    if (mapArray[y][x] != dotArray[y][x]) {
                        mapArray[y][x] = dotArray[y][x];
                    }
                }
            }
        }
        mapArray[gOneLocV][gOneLocH] = 'G';//Reimplements the first ghost back into the array
        mapArray[gTwoLocV][gTwoLocH] = 'G';//Reimplemeents the second ghost back into the array
        printMap(mapArray);//Prints the map to the user
    }

}


