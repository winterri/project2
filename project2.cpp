/*
 * Project Title:
 * - Conway's Game of Life
 *
 * Description:
 * - Conway's Game of Life works based on a seed of intial conditions (given to the program from a user-input
 * - text file) that will seed the position of the initial alive cells.  Our initializeBoard member function of our
 * - classes takes the coordinates from a vector as an input and iterates through the entire board to specify where each
 * - alive cell is to start the game by using an array of boolean values where true values represent alive cells and
 * - false values represent dead cells.  Then, based on the initial coordinates, we count the adjacent number of cells in our
 * - board in our isAlive member function of our classes to determine what cells will be alive in the next turn.  Then, we
 * - use two nested for loops to iterate through the entire board and copy it to a different board, which we called compareBoard.
 * - This is how the game was able to run continuously off of the original parameters, as the gameBoard would be compared to the
 * - compareBoard to determine what cells should live or die in the next iteration.  Then using compareBoard as the reference,
 * - we iterated through our gameBoard array and labeled each one as true or false depending on whether that cell was alive or
 * - dead, hence the name of the function isAlive.  Next, since our gameBoard was set with all of its boolean values, we used
 * - the displayBoard member function of our classes to iterate through the entire gameBoard (which is the private variable in
 * - our classes) and output a zero for all of the true values in gameBoard and a period for all of the false values in gameBoard.
 * - Then, so that the screen would not get clustered, we had to figure out how to clear the screen after each turn.  So, using
 * - the help of MathBits.com, we figured out how to use system("CLS") to clear the screen, which we made as a member function
 * - of our classes.  Then, we had to figure out how to let the display of our gameBoard pause for a brief moment before clearing
 * - the screen, as we wanted the user to be able to see what the board looked like before it cleared.  Again, using the help of
 * - the internet, we used StackOverflow.com and learned how to use the _sleep() function of the "chrono" library to make the
 * - screen pause for a specified amount of time (which we also used to pause the display of the rules before the game started).
 * - Then we made a display rules member function to display the exact rules of the game, which basically was a description for
 * - the user of how the game would operate.  To allow the user to change the rules (and to incorporate object-oriented
 * - programming in the form of multiple classes), we made one class (standardRules) to represent the standard rules of Conway's
 * - Game of Life and another class (alternateRules) for the alternate rules that the user could choose themselves based on
 * - input statements in the main function.
 *
 * Developers:
 * - Mason Douglas - Douglamc@mail.uc.edu
 * - Ryan Winterhalter - Winterri@mail.uc.edu
 *
 * Help Received:
 * - Used StackOverflow.com to learn about the sleep command
 * - Used MathBits.com to learn how to clear the screen
 *
 * Special Instructions:
 * - The grid ends at (20,20) -> DO NOT enter any points with an X or Y greater than 20.
 * - The grid starts at (1,1) -> DO NOT enter any points with an X or Y lower than 1.
 * - The grid starts from the top left corner at (1,1) and ends at the bottom right corner (20, 20).  The x-coordinate represents what
 * - column (1-20) the alive cell falls in and the y-coordinate represents what row (1-20) the alive cell falls in.  Additionally,
 * - the y-axis is inverted.  For instance, if you are trying to locate the point (3,7), you would go to the third column and then count down
 * - from the top row 7 rows until you are at that point.
 * - Make sure that when you input the filename, you use the exact file path
 * - Make sure that you only input a number for the ruleType variable, as any input other than a number will result in an infinite loop
 * - Make sure that each line in your text file only contains two numbers separated by a space to represent one coordinate (an example text file
 * - will be uploaded to GitHub with the code)
 * - Make sure that there are no blank lines in your text document, even at the very end of the file
 * - Make sure that there are no spaces at the end of any line in the text file
 *
 * SIDE NOTE:
 * - using our coordinate text file with standard rules creates an ocillating pattern
 * - using these as the inputs for alternate rules creates a nice pattern when used along with our coordinates text file
 * - input1 = 1
 * - input2 = 5
 * - input3 = 4
 *
 * Developer comments:
 * Mason Douglas:
 * - My partner and I used the pair programming approach where we split the time of who was coding and who was watching for errors
 * - into roughly a 50/50 ratio for each of us. My biggest take away from this project, is that I feel it really helped me to
 * - strengthen my skills in object oriented programming and has allowed me to feel more confident in my ability to work with classes.
 * Ryan Winterhalter:
 * - My partner and I used the pair programming approach where we split the time of who was coding and who was watching for errors
 * - into roughly a 50/50 ratio for each of us.  We both worked together to write all of our member functions for all of our classes
 * - and to come up with all of the tasks we were required to do for this game: displaying the board, inputting initial conditions
 * - from a text file, determining which cells were alive and dead for the next turn, incorporating object oriented programming, and more.
 * - From this project, I learned a lot about how to use file i/o processes to take input from a text file.  I also learned a lot about how
 * - to use different member functions of classes, which made me feel a lot more comfortable with object-oriented programming.
 */

#include <iostream>
#include <math.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cctype>
#include <stdlib.h>
#include <chrono>

using namespace std;

const int BOARDSIZE = 21;

class standardRules{ // The class for the traditional rules of Conway's Game of Life
    public:

    /* Function Name: initializeBoard
     *
     * Function Description:
     * This member function takes the coordinates input by the user via text file and initializes them as live cells on the game board.
     * This is done by collecting all of the coordinates into one 1D vector and then placing the first two values as one coordinate on
     * the game board, then erasing the first two numbers in the vector, until no numbers remain. This allows us to be sure that we do not
     * miss any coordinates that are input.
     *
     * Parameters:
     * vector<int> coordinates is the only parameter passed through this member function.
     * This parameter contains all of the coordinates of the living cells gathered from the text file.
     *
     * Return Value:
     * The function is type void, therefore it has no return value.
     */

    void initializeBoard(vector<int> coordinates){
        while(coordinates.size() != 0) {
            gameBoard[coordinates.at(1)][coordinates.at(0)] = true;
            coordinates.erase(coordinates.begin() + 0);
            coordinates.erase(coordinates.begin() + 0);
        }
    }

    /* Function Name: isAlive
     *
     * Function Description:
     * This member function will first store the gameBoard in the comparingBoard so that we have a reference for what cells will be alive or
     * dead in the next turn on the gameBoard.  This is done with nested for loops and a boolean array that we define within the
     * member function itself.  Then, after we do that, we will iterate through the entire board and count the number of
     * living adjacent cells, which we will do using nested for loops.  Then, we will iterate through our boolean array gameBoard
     * using nested for loops and using the number of living adjacent cells to figure out whether or not that cell should be alive (true)
     * or dead (false) in the next turn of the game.
     *
     * Parameters:
     * There are no parameters passed through this function
     *
     * Return Value:
     * The function is type void, therefore it has no return value.
     */

    void isAlive(){
        bool comparingBoard[BOARDSIZE+1][BOARDSIZE+1] = {};

        for(int i = 0; i < BOARDSIZE; i++){
            for(int j = 0; j < BOARDSIZE; j++){
                comparingBoard[i][j] = gameBoard[i][j];
            }
        }

        for(int i = 1; i < BOARDSIZE; i++){
            for(int j = 1; j < BOARDSIZE; j++){
                int living = 0;
                for(int a = -1; a <= 1; a++){
                    for(int b = -1; b <= 1; b++){
                        if(!(a == 0 && b == 0)){
                            if(comparingBoard[i+a][j+b]){
                                living = living + 1;
                            }
                        }
                    }
                }
                if(living < 2){
                    gameBoard[i][j] = false;
                }
                else if(living > 3){
                    gameBoard[i][j] = false;
                }
                else if(living == 3){
                    gameBoard[i][j] = true;
                }
            }
        }
    }

    /* Function Name: displayBoard
     *
     * Function Description:
     * This member function will use nested for loops to iterate through our gameBoard and, based on the boolean values in the gameBoard array,
     * output a zero for the living (true) cells and a period for the dead (false) cells.  Then, once we reach the end of the row on the board
     * (which should be of length 20), we will go to a new line.
     *
     * Parameters:
     * There are no parameters passed through this function
     *
     * Return Value:
     * The function is type void, therefore it has no return value
     */

    void displayBoard(){
        for(int i = 1; i < BOARDSIZE; i++){
            for(int j = 1; j < BOARDSIZE; j++){
                if(gameBoard[i][j] == true){
                    cout << " 0 " << flush;
                }
                else{
                    cout << " . " << flush;
                }
                if(j == BOARDSIZE-1){
                    cout << endl << flush;
                }
            }
        }
    }

    /* Function Name: clearBoard
     *
     * Function Description:
     * This member function will use the system("CLS") command to clear the board from the previous turn from the screen so that
     * it is clear for the next turn's board to be displayed.
     *
     * Parameters:
     * There are no parameters passed through this function
     *
     * Return Value:
     * The function is type void, therefore it has no return value
     */

    void clearBoard(){
        system("CLS");
    }

    /* Function Name: displayRules
     *
     * Function Description:
     * This member function uses a series of cout statements to display the rules and description of the game to the user
     * before the game starts.
     *
     * Parameters:
     * There are no parameters passed through this function
     *
     * Return Value:
     * This function is type void, therefore it has no return value
     */

    void displayRules() {
        cout << "Welcome to Conway's Game of Life!" << endl;
        cout << endl;
        cout << "The rules of the game are fairly simple:" << endl;
        cout << "We will ask you for a text file that has a list of coordinates that should represent" << endl;
        cout << "the initial position of the 'living' cells." << endl;
        cout << endl;
        cout << "For your coordinates, make sure there aren't any spaces at the ends of your line." << endl;
        cout << "Also make sure that the last line of your text file containst coordinates and isn't blank." << endl;
        cout << "Make sure you only have two numbers per line, the first being the x-coordinate and the second" << endl;
        cout << "being the y-coordinate, separating the two with a space." << endl;
        cout << "Otherwise, your coordinates will not be read for that line." << endl;
        cout << "Additionally, make sure that the coordinates in your text file will fit into the grid you specify." << endl;
        cout << endl;
        cout << "After the text file has been read, those coordinates will be set as living cells in the grid." << endl;
        cout << "Every other cell will be initialized as a dead cell." << endl;
        cout << endl;
        cout << "Each turn will modify the number of living and dead cells in the program in the following manner:" << endl;
        cout << "1) Any living cell with fewer than 2 living adjacent cells will die from underpopulation" << endl;
        cout << "2) Any living cell with 2 or 3 living adjacent cells will live on to the next turn" << endl;
        cout << "3) Any living cell with more than 3 living adjacent cells will die from overpopulation" << endl;
        cout << "4) Any dead cell with exactly 3 live neighbors becomes a live cell from reproduction" << endl;
        cout << endl;
    }

    private:
    bool gameBoard[BOARDSIZE+1][BOARDSIZE+1] = {}; // This is the 2D boolean array that represents our board
};

// END OF STANDARD RULES CLASS

class alternateRules{
    public:

    /* Function Name: initializeBoard
     *
     * Function Description:
     * This member function takes the coordinates input by the user via text file and initializes them as live cells on the game board.
     * This is done by collecting all of the coordinates into one 1D vector and then placing the first two values as one coordinate on
     * the game board, then erasing the first two numbers in the vector, until no numbers remain. This allows us to be sure that we do not
     * miss any coordinates that are input.
     *
     * Parameters:
     * vector<int> coordinates is the only parameter passed through this member function.
     * This parameter contains all of the coordinates of the living cells gathered from the text file.
     *
     * Return Value:
     * The function is type void, therefore it has no return value.
     */

    void initializeBoard(vector<int> coordinates){
        while(coordinates.size() != 0) {
            gameBoard[coordinates.at(1)][coordinates.at(0)] = true;
            coordinates.erase(coordinates.begin() + 0);
            coordinates.erase(coordinates.begin() + 0);
        }
    }

    /* Function Name: isAlive
     *
     * Function Description:
     * This member function will first store the gameBoard in the comparingBoard so that we have a reference for what cells will be alive or
     * dead in the next turn on the gameBoard.  This is done with nested for loops and a boolean array that we define within the
     * member function itself.  Then, after we do that, we will iterate through the entire board and count the number of
     * living adjacent cells, which we will do using nested for loops.  Then, we will iterate through our boolean array gameBoard
     * using nested for loops and using the number of living adjacent cells to figure out whether or not that cell should be alive (true)
     * or dead (false) in the next turn of the game.
     *
     * Parameters:
     * int input1 used for adjusting the underpopulation limit to match user inputs
     * int input2 used for adjusting the overpopulation limit to match user inputs
     * int input3 used for adjusting number of cells required for reproduction to match user inputs
     *
     * Return Value:
     * The function is type void, therefore it has no return value.
     */

    void isAlive(int input1, int input2, int input3){
        bool comparingBoard[BOARDSIZE+1][BOARDSIZE+1] = {};

        for(int i = 0; i < BOARDSIZE; i++){
            for(int j = 0; j < BOARDSIZE; j++){
                comparingBoard[i][j] = gameBoard[i][j];
            }
        }

        for(int i = 1; i < BOARDSIZE; i++){
            for(int j = 1; j < BOARDSIZE; j++){
                int living = 0;
                for(int a = -1; a <= 1; a++){
                    for(int b = -1; b <= 1; b++){
                        if(!(a == 0 && b == 0)){
                            if(comparingBoard[i+a][j+b]){
                                living = living + 1;
                            }
                        }
                    }
                }
                if(living < input1){
                    gameBoard[i][j] = false;
                }
                else if(living > input2){
                    gameBoard[i][j] = false;
                }
                else if(living == input3){
                    gameBoard[i][j] = true;
                }
            }
        }
    }

    /* Function Name: displayBoard
     *
     * Function Description:
     * This member function will use nested for loops to iterate through our gameBoard and, based on the boolean values in the gameBoard array,
     * output a zero for the living (true) cells and a period for the dead (false) cells.  Then, once we reach the end of the row on the board
     * (which should be of length 20), we will go to a new line.
     *
     * Parameters:
     * There are no parameters passed through this function
     *
     * Return Value:
     * The function is type void, therefore it has no return value
     */

    void displayBoard(){
        for(int i = 1; i < BOARDSIZE; i++){
            for(int j = 1; j < BOARDSIZE; j++){
                if(gameBoard[i][j] == true){
                    cout << " 0 " << flush;
                }
                else{
                    cout << " . " << flush;
                }
                if(j == BOARDSIZE-1){
                    cout << endl << flush;
                }
            }
        }
    }

    /* Function Name: clearBoard
     *
     * Function Description:
     * This member function will use the system("CLS") command to clear the board from the previous turn from the screen so that
     * it is clear for the next turn's board to be displayed.
     *
     * Parameters:
     * There are no parameters passed through this function
     *
     * Return Value:
     * The function is type void, therefore it has no return value
     */

    void clearBoard(){
        system("CLS");
    }

    /* Function Name: displayRules
     *
     * Function Description:
     * This member function uses a series of cout statements to display the rules and description of the game to the user
     * before the game starts.
     *
     * Parameters:
     * int input1 used for displaying the underpopulation limit to match user inputs
     * int input2 used for displaying the overpopulation limit to match user inputs
     * int input3 used for displaying number of cells required for reproduction to match user inputs
     *
     * Return Value:
     * This function is type void, therefore it has no return value
     */

    void displayRules(int input1, int input2, int input3) {
        cout << "Welcome to Conway's Game of Life!" << endl;
        cout << endl;
        cout << "The rules of the game are fairly simple:" << endl;
        cout << "We will ask you for a text file that has a list of coordinates that should represent" << endl;
        cout << "the initial position of the 'living' cells." << endl;
        cout << endl;
        cout << "For your coordinates, make sure there aren't any spaces at the ends of your line." << endl;
        cout << "Also make sure that the last line of your text file containst coordinates and isn't blank." << endl;
        cout << "Make sure you only have two numbers per line, the first being the x-coordinate and the second" << endl;
        cout << "being the y-coordinate, separating the two with a space." << endl;
        cout << "Otherwise, your coordinates will not be read for that line." << endl;
        cout << "Additionally, make sure that the coordinates in your text file will fit into the grid you specify." << endl;
        cout << endl;
        cout << "After the text file has been read, those coordinates will be set as living cells in the grid." << endl;
        cout << "Every other cell will be initialized as a dead cell." << endl;
        cout << endl;
        cout << "Each turn will modify the number of living and dead cells in the program in the following manner:" << endl;
        cout << "1) Any living cell with fewer than " << input1 << " living adjacent cells will die from underpopulation" << endl;
        cout << "2) Any living cell with more than " << input2 << " living adjacent cells will die from overpopulation" << endl;
        cout << "3) Any dead cell with exactly " << input3 << " live neighbors becomes a live cell from reproduction" << endl;
        cout << endl;
    }

    private:
    bool gameBoard[BOARDSIZE+1][BOARDSIZE+1] = {}; // This is the 2D boolean array that represents our board
};

//END OF ALTERNATE RULES CLASS

/* Function Name: breakupstring
 *
 * Function Description:
 * This function breaks up the string recieved from the file using the getline command, into seperate coordinates and places them
 * into a vector
 *
 * Parameters:
 * string str - the string recieved from the getline command, containing the coordinates
 *
 * Return Value:
 * A vector of type int called numdata that contains all the coordinates from the line passed into the function
 */


vector<int> breakupstring(string str){
    vector<int> numdata;
    stringstream ss;
    ss << str;

    while(!ss.eof()){
        int temp;
        ss >> temp;
        numdata.push_back(temp);
    }

    return numdata;
}

// END OF BREAK UP STRING FUNCTION

int main() {
    string filename; // used for opening and closing the file input by the user
    int ruleType; // integer value used for selecting a game mode
    bool validRuleTypeEntered; // boolean value used in our while statement to determine if the value enetered for the rule type is acceptable
    int input1, input2, input3; // used for passsing the users new rules to the alternate rules Class

    cout << "What is the exact filename of your text file with the coordinates: ";
    cin >> filename; // Must use exact file path
    cout << endl;

    string string1; // string used to hold each individual line from the text file that is input by the user
    vector<int> coordinates; //vector of type int that will temporarily hold coordinates until they are added into the finalCoordinates vector
    vector<int> finalCoordinates; // vector of type int used to pass all of the coordinates into the classes to initialize the boards.

    ifstream infile;
    infile.open(filename); // Must use the exact file path

    while(!infile.eof()){ // seperates the lines of the file into seperet coordinates
        getline(infile, string1);
        coordinates = breakupstring(string1);
        finalCoordinates.push_back(coordinates.at(0)); //adds coordinates to the finalCoordinates Vector
        finalCoordinates.push_back(coordinates.at(1)); //adds coordinates to the finalCoordinates Vector
    }

    infile.close(); //closes the input file

    ENTERRULE: // goto statement send user back to here if invalid game mode is entered
    cout << "What type of rules would you like?" << endl;
    cout << "1) Standard Rules" << endl;
    cout << "2) Alternative Rules" << endl;
    cin >> ruleType; // enters game mode

    validRuleTypeEntered = 1;

    while(validRuleTypeEntered == 1){ //loop used to prevent invalid inputs
        if(ruleType == 1) { //runs standard rules class
            validRuleTypeEntered = 0; //closes while loop
            standardRules game;
            game.displayRules(); //shows rules
            _sleep(30000); // pauses screen for 30 seconds
            game.initializeBoard(finalCoordinates); // initializes board
            game.displayBoard(); // displays initial coordinates input by user on the board
            _sleep(2000); // pauses screen for 2 seconds
            game.clearBoard(); // clears screen
            while(validRuleTypeEntered == 0){ //allow infinite display
              game.isAlive(); //finds which cells should be alive or dead
              game.displayBoard(); // shows board
              _sleep(1000); // pauses screen for 1 second
              game.clearBoard(); // clears board
            }
        }
        else if(ruleType == 2) { //uses alternate rule type
            cout << "Enter the minimum number of cells around before death due to underpopulation: " << endl;
            cin >> input1;
            cout << "Enter the maximum number of cells around before one must die due to overpopulation: " << endl;
            cin >> input2;
            cout << "Enter the number of cells that must be around for a cell to come to life as if reproduction: " << endl;
            cin >> input3;
            cout << endl;

            validRuleTypeEntered = 0; //closes while loop
            alternateRules game;
            game.displayRules(input1, input2, input3); //shows rules
            _sleep(30000); // pauses screen for 30 seconds
            game.initializeBoard(finalCoordinates); // initializes board
            game.displayBoard(); // displays initial coordinates input by user on the board
            _sleep(2000); // pauses screen for 2 seconds
            game.clearBoard(); // clears screen
            while(validRuleTypeEntered == 0){ //allow infinite display
              game.isAlive(input1, input2, input3); //finds which cells should be alive or dead
              game.displayBoard(); // shows board
              _sleep(1000); // pauses screen for 1 second
              game.clearBoard(); // clears board
            }
         }
        else { // used if invalid game mode is entered
            validRuleTypeEntered = 1;
            cout << "Please enter a valid rule type (1 or 2)" << endl;
            goto ENTERRULE;
        }
    }

        return 0;
}
