//============================================================================
// Name        : LAB8.cpp
// Author      : QIAN Shiyi & JIN Menghe
// Version     :
// Copyright   : Your copyright notice
// Description : LAB8
//============================================================================

/*
Mamba-Bomba! You are Minion Stuart! You and your Bomb Transporter buddies Dave and Bob
are playing a game of Mamba-Bomba (which in Minion means ¡§Mother of all Bombs¡¨). It¡¦s
similar to the cardgame Blackjack, but with bombs instead of cards. The rules are simple ¡V even
Bob can play it! While blindfolded, each player picks 2 bombs at random. The firepower of each
bomb ranges from 1 to 10, where the mini 1-bomb also has a special nuclear setting that allows
a super-firepower of 11. You can choose to use it at 1 or 11. Then, one-by-one, each player
must decide to Hit or Hold. Hit means you punch your buddy (hard!) and pick another bomb at
random. Hold means you pass. You want your total firepower as close to 21 as possible without
going over, in which case you¡¦re Blasted and lose! If you get 21, set off you bombs and shout
Mamba Bomba! ¡V you immediately win! Hit as often as possible, but don¡¦t get Blasted!
Make it simple, clear, and fun. Use the struct Minion which contains the Minion name, the
number of bombs currently held, their total firepower, and an array containing the firepower of
each bomb held (make the array size 21 so it will always be big enough).
Bonus: Have an even more explosive idea? Then devise you own Mamba-Bomba game! Make
the story, rules, and interface simple, clear, and fun to make it truly devastating! Games
hilarious enough for a class demo will get a bonus! Games hilarious enough to truly blow
everyone away will get a double bonus!
Work in groups of 1-2 people. When done, demo for your TA in your lab session. As a last resort
if not finished by the end of the lab period, submit to Canvas by Thursday (include the names of
group members at the top of the file).
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Minion{
	char Name[10];
	int Sum;
	int Status; // 0: <21, 1: =21, 2: >21;
	int Cards[21];
}

int main() {
	srand(time(NULL));
	int count=0;
	Minion Stuart={"Stuart", 0, 0}, Dave={"Dave", 0, 0}, Bob={"Bob", 0, 0};
	bool over=false;
	do {
		over=OneRound(Stuart, Dave, Bob, count);
		count=count+1;
	} while (over==false);
	return 0;
}

void GetCard(Minion& x, int count){
	int card = rand()%11;
	if (card==0){
		char superOne;
		cout<<"Hey, "<<x.Name<<"! You've got a Super One! You can use it as 1 or 11!"<<endl;
		cout<<"What number do you want this Super One be?"<<endl;
		do {
			cout<<"\"o\": use it as \"1\", \"e\": use it as \"11\": ";
			cin>>superOne;
		} while ((superOne!='o')&&(superOne!='e'));
		if (superOne=='o'){
			card=1;	
		}
		else {
			card=11;	
		}
	}
	x.Cards[count] = card;
	x.Sum += card;
	if (x.Sum==21){
		cout<<"Mamba Bomba! I got exactly 21!"<<endl;
		x.Status = 1;
	}
	else if (x.Sum>21){
		cout<<"I feel something bad..."<<endl;
		x.Status = 2;
	}
}

bool Pass(Minion& x, int count){
	if (x.Sum>=21){
		cout<<"You cannot more cards..."<<endl;
		return true;	
	}
	else {
		char pass;
		// Display
		cout<<"Above is your cards and their sum."<<endl;
		cout<<"Do you want to pass or get a new card?"<<endl;
		do {
			cout<<"Enter \"p\" to pass, enter \"n\" to get a new card: ";
			cin>>pass;
		} while ((pass!='p')&&(pass!='n'));
		if (pass=='p'){
			return true;	
		}
		else {
			return false;	
		}
	}
}

void OnePlayer(Minion& x, int count){
	bool pass = Pass(x, count);
	if (pass==false){
		GetCard(x, count);	
	}
}

bool OneRound(Minion& x, Minion& y, Minion& z, int count){
	OnePlayer(x, count);
	if (x.Status==1) {
		Gameover(x, 1);
		return true;
	}
	else if ((x.Status==2)&&(y.Status==2)&&(z.Status==2)){
		Gameover(x, 2);
		return true;
	}
	else {
		OnePlayer(y, count);
		if (y.Status==1) {
			Gameover(y, 1);
			return true;
		}
		else if ((x.Status==2)&&(y.Status==2)&&(z.Status==2)){
			Gameover(y, 2);
			return true;
		}
		else {
			OnePlayer(z, count):
			if (z.Status==1) {
				Gameover(z, 1);
				return true;
			}
			else if ((x.Status==2)&&(y.Status==2)&&(z.Status==2)){
				Gameover(z, 2);
				return true;
			}
		}
	}
	return false;
}

void Display(Minion& x, int count){
	cout<<"Player: "<<x.Name<<"\t\t Sum of Your Cards: "<<x.Sum<<endl;
	cout<<"Cards you have now: ";
	for (int i=0; i<=count; i++){
		cout<<x.Cards[count]<<"  ";	
	}
	cout<<endl;
}

void GameOver(Minion& x, int s){
	if (s==1){
		cout<<"Congratulations! "<<x.Name<<" has won the game!"<<endl;
	}
	else if (s==2){
		cout<<"Oh, what a pity! None of you wins..."<<endl;	
	}
}
