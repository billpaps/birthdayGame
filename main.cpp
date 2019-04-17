#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

void outputFromat();
void choices(int answer, string* birthdayInputs);
void writeDateToFile(string* birthdayInputs);
void showBirthdays();
void wishHappyBirthday();
vector<string> stringToVector(string theString, char separator);
void saveToFile(string* inputString);


//---------------MAIN------------

int main(){
    int userInput;
    string birthdayInputs = "";
    while(true){

        do{
            outputFromat();
            cin >> userInput;
        }while (userInput <0 || userInput > 5);
        if (userInput == 0){
            break;
        }else{
            choices(userInput, &birthdayInputs);
        }
        cout << "\n";
    }
    return 0;

}

//--------------END MAIN----------------


//-------------GUI INSTRUCTIONS-------------

void outputFromat(){
    cout << "1. Insert BirthDate\n";
    cout << "2. Show BirthDates\n";
    cout << "3. Wish Happy Birthday\n";
    cout << "4. Save to file\n";
    cout << "5. Load from file\n";
    cout << "0. Quit\n\n";
    cout << "Your choice (1-5,0): ";
}

//----------CHOICES----------

void choices(int answer, string* birthdayInputs){
    
    if(answer == 1){
        writeDateToFile(birthdayInputs);
    }else if(answer == 2){
        showBirthdays();
    }else if(answer == 3){
        wishHappyBirthday();
    }else if(answer == 4){
        saveToFile(&birthdayInputs);
    }else if(answer == 5){

    }
}

//-----------INSERT NEW NAME/DATE------------

void writeDateToFile(string& birthdayInputs){
    string line;
    cout << "What do you want to write?";
    cin.ignore();
    getline(cin, line);
    birthdayInputs += line;
    cout << birthdayInputs;
}

//------------SHOW BIRTHDAYS---------------

void showBirthdays(){
    ifstream readFromFile;
    string textFromFile = "";
    readFromFile.open("date.txt", ios_base::in);
    if (readFromFile.is_open()){
        while(readFromFile.good()){
            cin.ignore();
            getline(readFromFile, textFromFile);
            cout << textFromFile;
        }
        readFromFile.close();
    }
}

//--------------STRING TO VECTOR--------------

vector<string> stringToVector(string theString, char separator){
    vector<string> vecWords;
    stringstream ss(theString);
    string indvString;

    while(getline(ss, indvString, separator)){
        vecWords.push_back(indvString);
    }
    return vecWords;
}

//------------WISH HAPPY BIRTHDAY-----------------

void wishHappyBirthday(){

    time_t now = time(0);
    tm *ltm = localtime(&now);
    int month = 1 + ltm -> tm_mon;
    int day = ltm -> tm_mday;
    int year = 1900 + ltm -> tm_year;
    
    char separator = ' ';
    vector<string> theVec;
    ifstream readFromFile;
    string textFromFile = "";
    readFromFile.open("date.txt", ios_base::out);
    
    if (readFromFile.is_open()){
        while(readFromFile.good()){
            getline(readFromFile, textFromFile);
            theVec = stringToVector(textFromFile, separator);
            if ((stoi(theVec[1]) == day) && (stoi(theVec[2]) == month)){
                cout << theVec[0] << " happy birthday";
            }
        }
    }

}

//-----------------SAVE TO FILE-------------------

void saveToFile(string* inputString){
    string folder;
    ofstream writeToFile;
    cout << "Give filename (no spaces): ";
    cin >> folder;
    writeToFile.open(folder, ios_base::out);
    stringstream ss(*inputString);
    string indvString;
    if (writeToFile.is_open()){
        while(getline(ss, indvString, '\n')){
            
            writeToFile << indvString;
        }
        writeToFile.close();
    }

}

