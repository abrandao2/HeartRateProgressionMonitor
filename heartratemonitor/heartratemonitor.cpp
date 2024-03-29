/**
	Heart Rate Progression Monitor
	heartratemonitor.cpp
	Purpose: Register the daily heart rates from the user who started running. After one week, it
	provides weekly mean rate comparisons, so the user knows if his heart condition has improved
	compared to last week's AND compared to the first week's. It has no scientific substantiation
	whatsover. This is just a personal experiment.

	@author André Silva
	@version  1.0 02/09/19
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <dos.h>
#include <math.h>

// Define color constants
#define GW SetConsoleTextAttribute(hConsole, 242);
#define BdG SetConsoleTextAttribute(hConsole, 32);
#define BlG SetConsoleTextAttribute(hConsole, 160);
#define WR SetConsoleTextAttribute(hConsole, 207);
#define WB SetConsoleTextAttribute(hConsole, 15);
#define RB SetConsoleTextAttribute(hConsole, 12);
#define OB SetConsoleTextAttribute(hConsole, 6);
#define lGB SetConsoleTextAttribute(hConsole, 10);
#define BB SetConsoleTextAttribute(hConsole, 0);
#define dGB SetConsoleTextAttribute(hConsole, 2);

using namespace std;

// Color handler
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// IO variables
ifstream in;
ofstream out;

// Functions prototypes
/**
	Provide additional information to the user, like if it their first week running and, if not,
	if the mean weekly heart rate has improved or degraded compared to the last and first week.

	@param means a vector with the weakly heart rate means
*/
void additionalInfo(vector<double> means);
/**
	Ask the user if they want to perform another command.
*/
bool anotherCommand();
/**
	Print a bottom frame.
*/
void bottomFrame();
/**
	Calculate every week's heart rates mean, even incomplete ones, and return a vector
	with these means.

	@param rates a vector<int> with all the daily rates from the storage file.
	@return a vector<double> with all the weekly means.
*/
vector<double> calculatemean(vector<int> rates);
/**
	Delete last entry from database txt file.
*/
void deleteLastEntry();
/**
	Display the stored data in form of daily horizontal bars.
*/
void displayData();
/**
	Print a horizontal bar.
*/
void hr();
/**
	Ask for input, certify it is correct and store it into the txt database file.
*/
void inputData();
/**
	Print a left border.
*/
void leftBorder();
/**
	Print either the full version of the menu or half of it. The half is meant for when
	the user wants to perform some action again and, thus, omits the welcome message.

	@param full a boolean that, if true, prints the full menu. If not, prints half of it.
*/
void menu(bool full);
/**
	Print a right border. This is more complex than leftBorder(), because it takes into
	consideration the length of the current line, in order to place the right border in
	the right place.

	@param length the offset for printing the right border.
*/
void rightBorder(int length);
/**
	Print the retro looking splash screen.
*/
void splash();
/**
	Print an upper frame.
*/
void upperFrame();
/**
	Print a graphic bar. It is meant to receive either a vector<int> or a vector<double>.

	@param rates represents either daily rates or mean rates.
	@param mean the aforementioned distinction is provided by this flag.
*/
template <class T>
void graphicBar(vector<T> rates, bool mean = false);

int main() {
    // Print splash screen
	splash();

	menu(true);

	system("pause");
	return 0;
}

void splash() {
	RB;
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
	OB;
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

void hr() {
	for (int i = 0; i < 84; i++) {
		cout << (char)196;	// ──
	}
	cout << endl;
}

void upperFrame() {
	lGB;
	cout << ' ' << (char)201;			// ╔

	for (int i = 0; i < 84; i++) {
		cout << (char)205;				// ══
	}

	cout << (char)187 << endl;			// ╗
}

void bottomFrame() {
	lGB;
	cout << ' ' << (char)200;			// ╚

	for (int i = 0; i < 84; i++) {
		cout << (char)205;				// ══
	}

	cout << (char)188 << endl;			// ╝
}

vector<double> calculatemean(vector<int> rates) {
	int total = 0;
	int counter = 0;
	int zeroes = 0;
	int size = rates.size();
	int weekSize = 7;
	vector<double> means;

	// Populate means array
	for (int i = 0; i < size; i++) {
		total += rates[i];

		if (rates[i] == 0) {
			weekSize--;
			zeroes++;
		}

		if ((i + 1) % 7 == 0) {						
			means.push_back(total / weekSize);				// If a whole week is complete, calculate mean discouting zeroes
			total = 0;
			weekSize = 7;
			zeroes = 0;
		} else if (i == size - 1) {							// If not, it finds the remaining amount of days and divides by the amount of days that aren't 0
			means.push_back(total / ((size % 7) - zeroes));
		}
	}

	return means;
}

void displayData() {
	string rate;
	vector<int> rates;
	string input;

	// Process gathered information
	in.open("input.txt");
	in >> input;
	in.close();

	for (int i = 0; i < input.length(); i += 4) {
		rate = input.substr(i, input.find(','));
		rates.push_back(stoi(rate));
	}

	system("cls");

	// Display rates bars
	upperFrame();
	graphicBar(rates);
	bottomFrame();

	// Display current heart rate mean
	vector<double> means = calculatemean(rates);

	WB;
	cout << "  Current mean: " << endl;

	// Display means bars
	upperFrame();
	graphicBar(means, true);
	bottomFrame();

	// Display additional information
	additionalInfo(means);

	// Clean vector<int> rates
	rates.clear();

	// Ask for another command
	(anotherCommand()) ? menu(false) : exit(0);
}

void inputData() {
	int heartRate;
	// struct tm initialDate = { 0, 0, 0, 28, 8, 119 };

	cout << "Insert today's heart rate, ";
	WR;
	cout << " 0 ";
	WB;
	cout << " if you did not run or ";
	WR;
	cout << " 999 ";
	WB;
	cout << " to cancel : " << endl;

	// Assure correct input
	do {
		cin >> heartRate;
		cout << endl << endl;

		if (heartRate == 999) {
			system("cls");
			menu(true);
		}
		else if (heartRate == 0) {
			break;
		}
		else if (heartRate > 200 || heartRate < 100) {
			cout << "Invalid value. It must be between 100 and 200. Try again!" << endl;
		}
		else {
			break;
		}
	} while (true);

	// Input new information into the storage file
	out.open("input.txt", ios::app);
	if (heartRate == 0)
		out << "000";
	else
		out << heartRate;
	out << ',';
	out.close();

	// Display bars
	displayData();

	// Ask for another command
	(anotherCommand()) ? menu(false) : exit(0);
}

void deleteLastEntry() {
	string input;

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

	WR;
	cout << "\n  Last registry succesfully removed!" << endl;
	BB;

	displayData();
}

template <class T>
void graphicBar(vector<T> rates, bool mean) {
	int temp = 0;
	int count = 1;
	int size = rates.size();

	for (int i = 0; i < size; i++) {
		lGB;

		temp = (int)rates[i] / 3;

		leftBorder();								// Display left border

		// Change color of bar if it is meant to show the weekly means
		if (mean) {
			RB;
		}
		else {
			dGB;
		}

		if (rates[i] == 0) {
			cout << "Didn't run.";
		}
		else {
			for (int i = 0; i < temp; i++) {
				cout << (char)254;						// ■■
			}
		}

		RB;
		cout << ' ' << rates[i];

		if (rates[i] == 0) {
			for (int i = 0; i < 81 - 11; i++) {			// Fill the remaining space
				cout << ' ';
			}
		}
		else {
			for (int i = 0; i < 79 - temp; i++) {		// Fill the remaining space
				cout << ' ';
			}
		}

		lGB;
		cout << (char)186;								// ║
		cout << endl;

		// Print horizontal bar to divide results by week
		if (count == 7 && i != size - 1) {
			cout << ' ' << (char)204;					// ╠

			for (int i = 0; i < 84; i++) {
				cout << (char)205;						// ══
			}

			cout << (char)185 << endl;					// ╣

			count = 1;
		}
		else {
			count++;
		}
	}
}

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

		WB;
		cout << "  The mean variation between last week and now is: ";

		// Changes result's color to green, if variation negative, or red, if positive
		if (varLastWeek < 0) {
			BlG;
		}
		else {
			WR;
		}

		cout << varLastWeek << '%' << endl;

		upperFrame();
		leftBorder();
		
		// Inform if variation has been negative or positive
		WB;
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
		WB;
		cout << "  Since you started running, the mean variation has been: "
			<< varFirstWeek << '%' << endl << endl;
	}
	else {
		upperFrame();
		leftBorder();
		RB;
		cout << "That's still your first week running!";
		rightBorder(3 + 37);
		bottomFrame();
	}
}

void leftBorder() {
	lGB;
	cout << ' ' << (char)186 << ' ';											// ║
}

void rightBorder(int length) {
	for (int i = 0; i < 86 - length; i++) {							// Fill the remaining space
		cout << ' ';
	}
	lGB;
	cout << (char)186;												// ║
	cout << endl;
}

void menu(bool full) {
	string option;
	
	if (full) {
		// Welcoming messages
		BlG;
		cout << setw(86) << setfill(' ') << left;
		cout << "Welcome to the Heart Rate Progression Monitor" << endl;
		BdG;
		cout << "Select an option (";
		GW; cout << " 1 "; BdG;
		cout << " Display data; "; 
		GW; cout << " 2 "; BdG;
		cout << " Insert data; ";
		GW; cout << " 3 "; BdG;
		cout << " Delete last entry; ";
		WR; cout << " 0 "; BdG;
		cout << " exit):" << endl;
		WB;
	}
	else {
		system("cls");
		BdG;
		cout << "Select an option (";
		GW; cout << " 1 "; BdG;
		cout << " Display data; ";
		GW; cout << " 2 "; BdG;
		cout << " Insert data; ";
		GW; cout << " 3 "; BdG;
		cout << " Delete last entry; ";
		WR; cout << " 0 "; BdG;
		cout << " exit):" << endl;
		WB;
	}

	// Get option
	do {
		cin >> option;
		cout << endl;
		
		// Certify input is correct
		try {
			switch (stoi(option)) {
			case 1:
				displayData();
				break;
			case 2:
				inputData();
				break;
			case 3:
				deleteLastEntry();
				break;
			case 0:
				exit(0);
				break;
			default:
				WR;
				cout << "Invalid option. Try again!\n";
				WB;
				break;
			}
		}
		catch (invalid_argument) {
			WR;
			cout << "Invalid argument. Try again!\n";
			WB;
		}

	} while (true);

	hr();
}

bool anotherCommand() {
	char answer;

	lGB;
	cout << "  Another command? ";
	
	do {
		if(!(cin >> answer) || answer != 'y' && answer != 'n') {
			cout << "\n  Invalid option. Try again!\n  ";
		}
		else if (answer == 'y') {
			return true;
		}
		else {
			return false;
		}
	} while (true);
}