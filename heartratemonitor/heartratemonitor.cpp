#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <dos.h>
#include <math.h>

using namespace std;

// Color handler
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// IO variables
ifstream in;
ofstream out;

// Global variables
vector<int> rates;
string input;

// Functions prototypes
void splash();
void hr();
void upperFrame();
void bottomFrame();
void leftBorder();
vector<double> calculatemean(vector<int> rates);
void displayData();
void inputData();
void deleteLastEntry();
void additionalInfo(vector<double> means);
void rightBorder(int length);

template <class T>
void graphicBar(vector<T> rates, bool mean = false);

// Main function
int main() {
    // Print splash screen
	splash();

	// Variables
	int option;

	// Welcoming messages
	SetConsoleTextAttribute(hConsole, 160);
	cout << setw(86) << setfill(' ') << left;
	cout << "Welcome to the Heart Rate Progression Monitor" << endl;
	SetConsoleTextAttribute(hConsole, 32);
	cout << setw(86) << setfill(' ') << left;
	cout << "Select an option (0 - Display data; 1 - Insert data; 2 - Delete last entry; 3 - exit):" << endl;
	SetConsoleTextAttribute(hConsole, 15);
	
	// Get option
	do {
		cin >> option;

		if (option < 0 || option > 3) {
			cout << "Invalid option. Try again!";
		}
		else {
			break;
		}
	} while (true);

	hr();

	// Route to selected function
	switch (option) {
	case 0:
		displayData();
		break;
	case 1:
		inputData();
		break;
	case 2:
		deleteLastEntry();
		break;
	case 3:
		exit(0);
		break;
	}

	system("pause");
	return 0;
}

// Splash screen
void splash() {
	SetConsoleTextAttribute(hConsole, 12);
	cout << "                                                         " << endl;
	cout << "                                                         " << endl;
	cout << "  ooooo   ooooo ooooooooo.   ooooooooo.   ooo        ooooo " << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << endl;
	Sleep(200);
	cout << "  `888'   `888' `888   `Y88. `888   `Y88. `88.       .888' " << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << endl;
	Sleep(200);
	cout << "   888     888   888   .d88'  888   .d88'  888b     d'888  " << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << endl;
	Sleep(200);
	cout << "   888ooooo888   888ooo88P'   888ooo88P'   8 Y88. .P  888  " << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << endl;
	Sleep(200);
	cout << "   888     888   888`88b.     888          8  `888'   888  " << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << endl;
	Sleep(200);
	cout << "   888     888   888  `88b.   888          8    Y     888  " << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << endl;
	Sleep(200);
	cout << "  o888o   o888o o888o  o888o o888o        o8o        o888o " << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(177) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << char(176) << endl;
	Sleep(200);
	cout << "                                                         " << endl;
	cout << "                                                         " << endl;
	SetConsoleTextAttribute(hConsole, 6);
	cout << "         ___   _    __  ____    __    _  ____  ___                                                   " << endl;
	cout << "   )__/ (_    /_|  /__)  /     /__)  /_|  /   (_                                                     " << endl;
	cout << "  / _/  /___ (  |_/ ( __(   __/ (___(  |_(  __/__   __                 __           ____   __    __  " << endl;
	cout << "   /__)  /__)  /  )  / _   /__) (_    (    (    /  /  )  /| )   /|/|  /  )  /| )  /  /    /  )  /__) " << endl;
	cout << "  /     / (   (__/  (__)  / (   /__  __)  __)  (  (__/  / |/   /   | (__/  / |/  (  (    (__/  / (   " << endl;
	cout << "                                                         " << endl;
	cout << "                                                         " << endl;
	Sleep(2000);
	system("cls");
	cout << "\a" << flush;
}

// Draw horizontal line
void hr() {
	for (int i = 0; i < 84; i++) {
		cout << (char)196;	// ──
	}
	cout << endl;
}

// Draw upper frame in results
void upperFrame() {
	SetConsoleTextAttribute(hConsole, 10);
	cout << ' ' << (char)201;			// ╔

	for (int i = 0; i < 84; i++) {
		cout << (char)205;				// ══
	}

	cout << (char)187 << endl;			// ╗
}

// Draw bottom frame in results
void bottomFrame() {
	cout << ' ' << (char)200;			// ╚

	for (int i = 0; i < 84; i++) {
		cout << (char)205;				// ══
	}

	cout << (char)188 << endl;			// ╝
}

// Calculate Heart Rate mean
vector<double> calculatemean(vector<int> rates) {
	int total = 0;
	int counter = 0;
	int size = rates.size();
	vector<double> means;

	// Populate means array
	for (int i = 0; i < size; i++) {
		total += rates[i];

		if ((i + 1) % 7 == 0) {						
			means.push_back(total / 7);				// If a whole week is complete, calculate mean
			total = 0;
		} else if (i == size - 1) {
			means.push_back(total / (size % 7));	// Calculate the mean of the remaining rates
		}
	}

	return means;
}

// Display data stored in horizontal bars format
void displayData() {
	string rate;

	// Process gathered information
	in.open("input.txt");
	in >> input;
	in.close();

	for (int i = 0; i < input.length(); i += 4) {
		rate = input.substr(i, input.find(','));
		rates.push_back(stoi(rate));
	}

	system("cls");

	upperFrame();

	graphicBar(rates);

	bottomFrame();

	// Display current heart rate mean
	vector<double> means = calculatemean(rates);

	SetConsoleTextAttribute(hConsole, 15);			// Red/Black
	cout << "  Current mean: " << endl;

	upperFrame();
	graphicBar(means, true);
	bottomFrame();

	// Display additional information
	additionalInfo(means);
}

// Receive input
void inputData() {
	int heartRate;
	struct tm initialDate = { 0, 0, 0, 28, 8, 119 };

	cout << "Insert today's heart rate: " << endl;

	// Assure correct input
	do {
		cin >> heartRate;
		cout << endl;

		if (heartRate > 200 || heartRate < 100) {
			cout << "Informed value. It must be between 100 and 200. Try again!" << endl;
		}
		else {
			break;
		}
	} while (true);

	// Input new information into the storage file
	out.open("input.txt", ios::app);
	out << heartRate;
	out << ',';
	out.close();

	// Change color and display bars
	displayData();
}

// Delete last entry from database
void deleteLastEntry() {
	in.open("input.txt");
	in >> input;
	in.close();

	string newInput;

	// Creates new string
	for (int i = 0; i < input.length() - 4; i++) {
		newInput += input[i];
	}

	// Rewrites the data file
	out.open("input.txt");
	out << newInput;
	out.close();

	displayData();

	SetConsoleTextAttribute(hConsole, 207);
	cout << "\n  Last registry succesfully removed!" << endl;
	SetConsoleTextAttribute(hConsole, 0);
}

// Display graphic bar based on input
template <class T>
void graphicBar(vector<T> rates, bool mean) {
	int temp = 0;

	for (T rate : rates) {
		SetConsoleTextAttribute(hConsole, 10);		// Green/Black

		temp = (int)rate / 3;

		leftBorder();								// Display left border

		for (int i = 0; i < temp; i++) {
			mean ? SetConsoleTextAttribute(hConsole, 12) : SetConsoleTextAttribute(hConsole, 2);
			cout << (char)254;						// ■■
		}

		SetConsoleTextAttribute(hConsole, 12);		// Red/Black
		cout << ' ' << rate;

		for (int i = 0; i < 79 - temp; i++) {		// Fill the remaining space
			cout << ' ';
		}

		SetConsoleTextAttribute(hConsole, 10);		// Green/Black
		cout << (char)186;							// ║
		cout << endl;
	}
}

// Display additional information regarding variation in the heart rate means
void additionalInfo(vector<double> means) {
	int size = means.size();
	double varLastWeek;
	double varFirstWeek;

	// If user has been running for more than one week
	if (size > 1) {
		varLastWeek = ((means[size - 1] - means[size - 2]) / means[size - 1]) * 100; // Calculate the variation compared to last week

		varFirstWeek = ((means[size - 1] - means[0]) / means[size - 1]) * 100;  // Calculate the variation compared to fist week

		//Reducing amount of decimal houses
		varLastWeek = (int)(varLastWeek / 0.01) * 0.01;
		varFirstWeek = (int)(varFirstWeek / 0.01) * 0.01;

		SetConsoleTextAttribute(hConsole, 15);										// White/Black
		cout << "  The mean variation between last week and now is: ";

		// Changes result's color to green, if variation negative, or red, if positive
		(varLastWeek < 0) ? SetConsoleTextAttribute(hConsole, 160) : SetConsoleTextAttribute(hConsole, 207);
		cout << varLastWeek << '%' << endl;

		upperFrame();
		leftBorder();
		
		// Inform if variation has been negative or positive
		SetConsoleTextAttribute(hConsole, 15);										// White/Black
		if (varLastWeek < 0) {
			cout << "Good news! Your mean heart rate has decreased comparted to last week!";
			rightBorder(3 + 69);
		}
		else {
			cout << "Bad news! Your mean heart rate has INCREASED compared to last week!";
			rightBorder(3 + 67);
		}

		bottomFrame();

		// Inform how the mean rate has varied since user started running
		SetConsoleTextAttribute(hConsole, 15);
		cout << "  Since you started running, the mean variation has been: " 
			 << varFirstWeek << '%' << endl;
	}
	else {
		upperFrame();
		leftBorder();
		SetConsoleTextAttribute(hConsole, 12);
		cout << "That's still your first week running!";
		rightBorder(3 + 37);
		bottomFrame();
	}
}

void leftBorder() {
	SetConsoleTextAttribute(hConsole, 10);
	cout << ' ' << (char)186 << ' ';											// ║
}

// Display right border, given the length of the text printed before it
void rightBorder(int length) {
	for (int i = 0; i < 86 - length; i++) {							// Fill the remaining space
		cout << ' ';
	}
	SetConsoleTextAttribute(hConsole, 10);							// Green/Black
	cout << (char)186;												// ║
	cout << endl;
}