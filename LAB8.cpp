//============================================================================
// Name        : LAB8.cpp
// Author      : QIAN Shiyi & JIN Menghe
// Version     :
// Copyright   : Your copyright notice
// Description : LAB8
//============================================================================

/*
Mamba-Bomba! You are Minion Stuart! You and your Bomb Transporter buddies Dave and Bob
are playing a game of Mamba-Bomba (which in Minion means “Mother of all Bombs”). It’s
similar to the cardgame Blackjack, but with bombs instead of cards. The rules are simple – even
Bob can play it! While blindfolded, each player picks 2 bombs at random. The firepower of each
bomb ranges from 1 to 10, where the mini 1-bomb also has a special nuclear setting that allows
a super-firepower of 11. You can choose to use it at 1 or 11. Then, one-by-one, each player
must decide to Hit or Hold. Hit means you punch your buddy (hard!) and pick another bomb at
random. Hold means you pass. You want your total firepower as close to 21 as possible without
going over, in which case you’re Blasted and lose! If you get 21, set off you bombs and shout
Mamba Bomba! – you immediately win! Hit as often as possible, but don’t get Blasted!
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
	int Status; // 0: <21, 1: =21, 2: >21, 3: <21 and pass
	int Cards[21];
};

void GetCard(Minion& x, int count);
bool Pass(Minion& x, int count);
void OnePlayer(Minion& x, int count);
bool OneRound(Minion& x, Minion& y, Minion& z, int count);
void Display(Minion& x, int count);
void GameOver(Minion& x, int s);
void GameOver(Minion& x, Minion& y, Minion& z);

int main() {
	Minion Stuart={"Stuart", 0, 0, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	Minion Dave={"Dave", 0, 0, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	Minion Bob={"Bob", 0, 0, {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}};
	srand(time(NULL));
	init(Stuart, Dave, Bob);
	int count=2;
	bool over=false;
	do {
		cout<<"\nROUND "<<count<<"\n"<<endl;
		over=OneRound(Stuart, Dave, Bob, count);
		count=count+1;
	} while (over==false);
	return 0;
}

void init(Minion& x, Minion& y, Minion& z){
	GetCard(x, 0);
	GetCard(y, 0);
	GetCard(z, 0);
	GetCard(x, 1);
	GetCard(y, 1);
	GetCard(z, 1);
}

void GetCard(Minion& x, int count){
	int card = rand()%11;
	if (card==0){
		char superOne;
		cout<<"Hey, "<<x.Name<<"! You've got a Super One! You can use it as 1 or 11!"<<endl;
		cout<<"What number do you want this Super One be?"<<endl;
		do {
			cout<<"Enter \"o\" to use it as 1, enter \"e\" to use it as 11: ";
			cin>>superOne;
		} while ((superOne!='o')&&(superOne!='e'));
		if (superOne=='o'){
			card=1;
		}
		else {
			card=11;
		}
		cout<<endl;
	}
	else {
		cout<<x.Name<<", you've got a(an) "<<card<<".\n"<<endl;
	}
	x.Cards[count] = card;
	x.Sum += card;
	if (x.Sum==21){
		cout<<"Mamba Bomba! You got exactly 21!\n"<<endl;
		x.Status = 1;
	}
	else if (x.Sum>21){
		cout<<"Ooops! The sum of you cards is "<<x.Sum<<".\nSomething bad might have happened...\n"<<endl;
		x.Status = 2;
	}
}

bool Pass(Minion& x, int count){
	if (x.Sum>=21){
		Display(x, count);
		cout<<"The sum of your cards is "<<x.Sum<<". You cannot have more cards...\n"<<endl;
		return true;
	}
	else {
		char pass;
		Display(x, count);
		cout<<"Above is your cards and their sum."<<endl;
		cout<<"Do you want to pass or get a new card?"<<endl;
		do {
			cout<<"Enter \"p\" to pass, enter \"n\" to get a new card: ";
			cin>>pass;
		} while ((pass!='p')&&(pass!='n'));
		cout<<endl;
		if (pass=='p'){
			x.Status=3;
			return true;
		}
		else {
			return false;
		}
	}
	return false;
}

void OnePlayer(Minion& x, int count){
	bool pass = Pass(x, count);
	if (pass==false){
		GetCard(x, count);
	}
}

bool OneRound(Minion& x, Minion& y, Minion& z, int count){
	OnePlayer(x, count);
	bool check1 = ((x.Status==3)||(x.Status==2))&&((y.Status==3)||(y.Status==2))&&((z.Status==3)||(z.Status==2))
				  &&(!((x.Status==2)&&(y.Status==2)&&(z.Status==2)));
	if (x.Status==1) {
		GameOver(x, 1);
		return true;
	}
	else if ((x.Status==2)&&(y.Status==2)&&(z.Status==2)){
		GameOver(x, 2);
		return true;
	}
	else if (check1){
		GameOver(x, y, z);
		return true;
	}
	else {
		OnePlayer(y, count);
		bool check2 = ((x.Status==3)||(x.Status==2))&&((y.Status==3)||(y.Status==2))&&((z.Status==3)||(z.Status==2))
						  &&(!((x.Status==2)&&(y.Status==2)&&(z.Status==2)));
		if (y.Status==1) {
			GameOver(y, 1);
			return true;
		}
		else if ((x.Status==2)&&(y.Status==2)&&(z.Status==2)){
			GameOver(y, 2);
			return true;
		}
		else if (check2){
			GameOver(x, y, z);
			return true;
		}
		else {
			OnePlayer(z, count);
			bool check3 = ((x.Status==3)||(x.Status==2))&&((y.Status==3)||(y.Status==2))&&((z.Status==3)||(z.Status==2))
							  &&(!((x.Status==2)&&(y.Status==2)&&(z.Status==2)));
			if (z.Status==1) {
				GameOver(z, 1);
				return true;
			}
			else if ((x.Status==2)&&(y.Status==2)&&(z.Status==2)){
				GameOver(z, 2);
				return true;
			}
			else if (check3){
				GameOver(x, y, z);
				return true;
			}
		}
	}
	return false;
}

void Display(Minion& x, int count){
	cout<<"\nPlayer: "<<x.Name<<"\t\t Sum of Your Cards: "<<x.Sum<<endl;
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

void GameOver(Minion& x, Minion& y, Minion& z){
	cout<<"It seems that none of you cannot have or don't want to have another card."<<endl;
	cout<<"Let's compare you sum!"<<endl;
	int sumx = (x.Sum>21)?0:x.Sum;
	int sumy = (y.Sum>21)?0:y.Sum;
	int sumz = (z.Sum>21)?0:z.Sum;

	if (sumx>sumy){
		if (sumz>sumx){
			cout<<z.Name<<" has the largest sum. "<<endl;
			GameOver(z, 1);
		}
		else if (sumz==sumx){
			cout<<x.Name<<" and "<<z.Name<<" have won the game!"<<endl;
		}
		else {
			cout<<x.Name<<" has the largest sum. "<<endl;
			GameOver(x, 1);
		}
	}
	else if (sumx==sumy){
		if (sumz>sumx){
			cout<<z.Name<<" has the largest sum. "<<endl;
			GameOver(z, 1);
		}
		else if (sumz==sumy){
			cout<<"What's a coincidence! Your sum happen to be the same!"<<endl;
		}
		else {
			cout<<x.Name<<" and "<<y.Name<<" have won the game!"<<endl;
		}
	}
	else {
		if (sumz>sumy){
			cout<<z.Name<<" has the largest sum. "<<endl;
			GameOver(z, 1);
		}
		else if (sumz==sumy){
			cout<<y.Name<<" and "<<z.Name<<" have won the game!"<<endl;
		}
		else {
			cout<<y.Name<<" has the largest sum. "<<endl;
			GameOver(y, 1);
		}

	}
}

