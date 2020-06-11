#include<iostream>
#include<vector>
#include<string>
#include<conio.h>
#include<windows.h>
#include<chrono>
#include <fstream>
#include<algorithm>

using namespace std;

void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void wright_score(double my_time)
{
	ofstream scores;
	scores.open("Scores.txt", ios::app);
	scores << my_time << endl;
	scores.close();

}
void show_scores()
{
	color(10);

	ifstream inScores;
	vector<double> s;
	double tmp;

	inScores.open ("Scores.txt");

	while (inScores >> tmp)
	{
		s.push_back(tmp);
	}
	sort(s.begin(), s.end());

	for (int i = 0; i < (int)s.size(); ++i)
	{
		cout << i + 1 << ". " << s[i] << " seconds" << endl;
	}
	cout << "Press any key to continue";
	_getch();
	system("cls");
}

void print_towers(vector<vector<string> >& v1)
{
	int poz_y = 2;
	int poz_x = 0;

	int poz_crte = 0;

	for (int i = 0; i < (int)v1.size(); ++i)
	{
		poz_crte += (int)v1[i].size();
	}

	for (int i = 0; i < (int)v1.size(); ++i)
	{

		for (int j = 0; j < (int)v1[i].size(); ++j)
		{
			gotoxy(poz_x, poz_y);
			cout << v1[i][j];
			++poz_y;
		}
		gotoxy(poz_x, poz_crte + 2);
		cout << "__________";
		gotoxy(poz_x, poz_crte + 3);
		cout << i + 1;
		poz_x += 15;
		poz_y = 2;
	}

}

void show_rules()
{
	char key;
	color(10);
	
	gotoxy(20, 0);
	cout << "RULES";
	
	gotoxy(0, 2);
	cout << "1. Only one disk can be moved at a time.";
	
	gotoxy(0, 4);
	cout << "2. Move the upper disk to another stack or empty rod.";
	
	gotoxy(0, 6);
	cout << "3. No larger disk may be placed on top of a smaller disk.";
	
	key = _getch();
	system("cls");
}

void play_game()
{
	color(10);
	vector<vector<string> > v1;
	vector<string> v2;

	char ch = 49;
	unsigned int brojac = 0;
	string tmp = "";

	while (brojac < 3)
	{
		cout << "Choose number of disk's (3 or larger)" << endl;
		cin >> brojac;
		system("cls");
	}



	for (int i = 0; i < brojac; ++i)
	{
		for (int j = 0; j < i + 1; ++j)
		{

			tmp.push_back(ch);
		}
		++ch;
		v2.push_back(tmp);
		tmp.erase(tmp.begin(), tmp.end());
	}
	v1.push_back(v2);
	v2.erase(v2.begin(), v2.end());
	v1.push_back(v2);
	v1.push_back(v2);

	int from = -1;
	int to = -1;

	print_towers(v1);

	auto start = chrono::steady_clock::now();
	while (v1[2].size() != brojac)
	{
		tmp.erase(tmp.begin(), tmp.end());

		while (from < 0 || from > 3)
		{
			system("cls");
			print_towers(v1);
			gotoxy(50, 0);
			cout << "Pick the stack you want to take a disk from: ";
			cin >> from;
		}
		if (v1[from - 1].empty())
		{
			gotoxy(50, 1);
			cout << "Stack is empty";
			gotoxy(50, 2);
			cout << "Press any key to continue";
			_getch();
		}
		else
		{
			tmp = v1[from - 1][0];
		}


		if (!tmp.empty())
		{

			while (to < 0 || to > 3)
			{
				print_towers(v1);
				gotoxy(50, 1);
				cout << "Pick a stack on which to plce the disk: ";
				cin >> to;
				cout << string(40, '\b');

			}
			if (v1[to - 1].empty())
			{
				v1[to - 1].insert(v1[to - 1].begin(), tmp);
				v1[from - 1].erase((v1[from - 1].begin()));
			}
			else if (v1[to - 1][0].size() > tmp.size())
			{
				v1[to - 1].insert(v1[to - 1].begin(), tmp);
				v1[from - 1].erase((v1[from - 1].begin()));
			}
			else if (v1[to - 1][0].size() < tmp.size())
			{
				gotoxy(50, 2);
				cout << "Invalid move";
				gotoxy(50, 3);
				cout << "Press any key to continue";
				_getch();

			}
		}

		system("cls");
		print_towers(v1);
		from = -1;
		to = -1;
	}

	auto stop = chrono::steady_clock::now();

	double elapsed_time_ns = double(chrono::duration_cast <chrono::nanoseconds> (stop - start).count());
	double my_time = elapsed_time_ns / 1e9;
	wright_score(my_time);

	gotoxy(50, 4);
	cout << "Congratulations, you have solved the puzzle in: " << my_time << " seconds";
	gotoxy(50, 5);
	cout << "Press any key to continue";
	_getch();
	system("cls");
}


int main()
{
	int set[] = { 7,7,7,7 }; //DEFAULT COLOR
	int counter = 2;
	char key;

	int kraj = 0;

	while (kraj != 4)
	{
		gotoxy(10, 0);
		color(10);
		cout << "Main Menu";

		gotoxy(0, 2);
		color(set[0]);
		cout << "Start Game";

		gotoxy(0, 4);
		color(set[1]);
		cout << "Rules";

		gotoxy(0, 6);
		color(set[2]);
		cout << "High Score";

		gotoxy(0, 8);
		color(set[3]);
		cout << "Quit Game";

		key = _getch();
		if (key == 72 && (counter >= 2 && counter <= 4)) // UP ARROW KEY
		{
			--counter;
		}
		if (key == 80 && (counter >= 1 && counter <= 3)) // DOWN ARROW KEY
		{
			++counter;
		}
		if (key == '\r') // CARRIAGE RETURN = RETURN KEY
		{
			system("cls");
			if (counter == 1)
			{
				play_game();
			}

			if (counter == 2)
			{
				show_rules();
			}

			if (counter == 3)
			{
				show_scores();
			}
			if (counter == 4)
			{
				kraj = 4;
			}

		}
		set[0] = 7; //DEFAULT COLOR 7 IS WHITE
		set[1] = 7;
		set[2] = 7;
		set[3] = 7;

		if (counter == 1)
		{
			set[0] = 10; // 10 IS COLOR GREEN
		}

		if (counter == 2)
		{
			set[1] = 10; 
		}

		if (counter == 3)
		{
			set[2] = 10;
		}

		if (counter == 4)
		{
			set[3] = 10;
		}
	}
	color(0);
}