#include<iostream>
#include<stdlib.h>
#include<ctime>
using namespace std;

string welcome = "\n\n############### WELCOME TO GUESS THE DAY ###############\n\n";
string menu_label = "                      Select Menu\n\n";
string menus[4] = {"START GAME", "FIND THE DAY", "TUTORIAL", "EXIT"};
string game_welcome = "################# YOU ARE NOW PLAYING ##################\n\n";
string guess_label = "            Guess the day of the given date\n";

string days[7] = {"Sunday", "Moday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
string months[12] = {"January", "february", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
string day30[4] = {"April", "June", "September", "November"};
string day31[7] = {"January", "March", "May", "July", "August", "October", "December"};

int month_code[12] = {6, 2, 2, 4, 0, 3, 5, 1, 4, 6, 2, 4};
int decade_code[10] = {1, 6, 5, 3, 2, 0, 6, 4, 3, 1};
int even[10] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2};
int odd[10] = {0, 0, 1, 1, 1, 1, 2, 2, 2, 2};


bool is_leap_year(int year)
{
	if(year % 4 == 0)
	{
		if(year % 100 == 0)
		{
			if(year % 400 == 0)
			{
				return true;
			}
		}
	}
	return false;
}

int year_code(int year)
{
	int one = year % 10;
	int ten = (year % 100) / 10;
	int hundred = year / 100;
	int total = 0;
	
	switch(hundred)
	{
		case 18:
			total += 2;
			break;
		case 19:
			total += 0;
			break;
		case 20:
			total += 6;
	}
	
	total += (decade_code[ten] + 1);
	
	if(ten % 2 == 0)
	{
		total += even[one];
	}
	else
	{
		total += odd[one];
	}
	
	return total;
}

int get_date_range(string m, int y)
{
	int day = 0;
	
	for(int i=0; i<4; i++)
	{
		if(m == day30[i])
		{
			day = 30;
			break;
		}
	}
	if(day == 0)
	{
		for(int i=0; i<7; i++)
		{
			if(m == day31[i])
			{
				day = 31;
				break;
			}
		}
	}
	if(day == 0)
	{
		if(is_leap_year(y))
		{
			day = 28;
		}
		else
		{
			day = 29;
		}
	}
	
	return day;
}

void play()
{
	srand(time(NULL));
	bool playing = true;
	cout << game_welcome;
	
	while(playing)
	{
		int month = rand() % 12;
		int year = 1900 - rand() % (2000 - 1900);
		int date = rand() % get_date_range(months[month], year);
		int right_day, guessed_day;
		
		cout << guess_label << "\n\n";
		cout << months[month] << " " << date << ", " << year << "\n\n";
		for(int i=0; i<7; i++) cout << i << ". " << days[i] << "\n";
		cout << "7. EXIT\n\n";
		
		cin >> guessed_day;
		
		if(guessed_day == 7)
		{
			playing = false;
		}
		else
		{
			right_day = (month_code[month] + date + year_code(year)) % 7;  
		}
		
		if(is_leap_year(year) && (month == 1 or month == 2)) right_day -= 1;
		
		if(right_day == guessed_day)
		{
			cout << "Correct!!!\n\n";
		}
		else
		{
			cout << "Wrong!!! It's " << days[right_day] << "\n\n";
		}
		
		int more;
		
		cout << "1. Play More\n" << "2. Exit\n";
		cin >> more;
		
		switch(more)
		{
			case 1:
				playing = true;
				break;
			case 2:
				playing = false;
		}
	}
}

int main()
{
	bool running = true;
	cout << welcome;
	
	while(running)
	{
		int selected_menu;
		cout << menu_label;
		
		for(int i=0; i<4; i++) cout << i+1 << ". " << menus[i] << "\n";
		cin >> selected_menu;
		
		switch(selected_menu)
		{
			case 1:
				play();
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				running = false;
		}
		
	}	
	return 0;
}
