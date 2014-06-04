#include <sstream>		//converts card number to name
#include <iostream>
#include <string>		//strings for input and names of cards
#include <ctime>		//time in srand
#include <windows.h>	//srand and rand, sleep
#include <fstream>
using namespace std;
void cardname (int&, string&, string&);//takes rand number and turns it to a string
char choose (int);//choice of 1 or 2
int numbers();//candy input
int main()
{
	system("color 71");
	int card1;//players first card
	int card2;//players second card
	int dealer1;// dealers first card -shown first
	int dealer2;// dealer's second card, shown near end
	int dealer3;//the value dealer gets from hit me
	int card3;// the value player gets from hit me
	int cardsum = 0;//sum of cards to check for bust
	int dsum; //sum of dealer cards
	int ace = 0;//counts player aces
	int dace = 0;//counts dealer aces
	int i = 1;//for loop counter, runs once in do while loop (allows exit if bust)
	int money; //money you put into for choosing bets
	int bet;//money you bet
	int addmoney;//money to add
	int quit;//quit with no money
	int dd = 0;//pass to function for double down
	int turn = 0;//your turns
	int dturn = 0;//dealer turns
	int conornot;
	bool morecards = 1;//whether or not to continue dealing
	bool replay = 1;//restart game
	char real;//1 or 2 for choices
	string name;//name of card
	string dname;//dealer 1
	string suit;
	string dsuit;
	ifstream scorein;
	ofstream scoreout;
	
	srand(time(NULL));
	cout << "Welcome to Blackjack!" << endl;
	cout << "NOTE: you will only use 1 or 2 for input, except for values of candy" << endl;
	Sleep(800);
	cout <<"Would you like to"<<endl;
	cout <<"1. Start a new game or\n2. Continue a previous game: ";
	real = choose(dd);
	if(real == '1')
	{
	cout << "How much is your buy-in?" << endl;
	money = numbers();//pool of candy available to bet
}
else
{
	scorein.open("score.txt");
	scorein>>money;
	cout<< "You have "<<money<<" candy"<<endl;
	scorein.close();
}
	do
	{
		
		for(i;i<2;i++)//allows quit 
		{	
		while (money == 0)//asks for more money or quit
		{
			Sleep(1000);
			cout << "You have 0 candy. You have to \n1. Add candy or \n2. Quit the game? :";
			real = choose(dd);
			if (real == '1')
			{
				Sleep(1000);
				cout << "How much candy do you want to add?"<< endl;
				addmoney = numbers();
				money+=addmoney;			
			}
			else
			{
				quit = 1;	
				break;
			}
		}
		if (quit == 1)
		{
			break;
		}	
			cout << "How much candy do you bet this game?"<< endl;
			bet = numbers();
			while(bet>money)
			{
				cout<< "You cannot bet more than you have. You can" << endl;
				cout << "1. Add more candy or\n2. Bet a different amount :";
				real = choose(dd);
				if (real == '1')
				{
					cout << "How much candy do you want to add?"<< endl;
					addmoney = numbers();
					money+=addmoney;
					cout << "How much candy do you bet this game?"<< endl;
					bet = numbers();		
				}
				else
				{
					cout <<"What do you change your bet to?" << endl;
					bet = numbers();
				}
			}
			money-=bet;
			card1 = rand()%52+1;
			card2 = rand()%52+1;
			dealer1 = rand()%52+1;
			dealer2 = rand()%52+1;
			cardname (card1, name, suit);	
			cout << "The first card the dealer hands you is a(n) "<< name <<" of " << suit <<endl;
			if (card1 == 1)
			{
				++ace;
			}
			Sleep(1000);
			cout<< "\nThe dealer puts his first card face down" << endl;
			cardname (card2, name, suit);
			Sleep(1000);
			cout << "\nThe second card the dealer hands you is a(n) "<< name <<" of " << suit <<endl;
			if ((card1==1 &&card2 == 10)||(card1 == 10 && card2 ==1))
			{
				cout << "That's Blackjack! You win!" << endl;
				money+=bet*2.5;
				bet = 0;
				break;
			}
			if (card2 == 1)
			{
				++ace;
			}
			cardsum = card1 + card2;
			cardname (dealer1, dname, dsuit);
			Sleep(1000);
			cout << "\nThe dealer puts down his second card, facing up. This card is a(n)\n" << dname <<" of " << dsuit << endl;
			dsum=dealer1;
			if (dealer1 == 1)
			{
				++dace;
				dsum+=10;
				
			}
			if(money-2*bet>=0)
			dd = 1;
			do
			{
				Sleep(1000);
				cout << "Your card sum is "<< cardsum << endl;
				if(ace>0&&cardsum+10<22)
				{
					cout << "(or " << cardsum+10 << ")"<< endl;
				}
				cout << "The dealer's card is a(n) " << dname <<" of " << dsuit << endl;
				cout << "\nThese are your options. You can" << endl;
				cout << "1.\tHit me(ask for a card)," << endl;
				cout << "2.\tStay(stop) and hope for the better hand,"<< endl;
				if(money-2*bet>=0)
				cout << "3.\tDouble Down(double the money and only one card) :";
				real = choose(dd);
				if (real == '1'||real == '3')
				{	
					morecards = 1;
					++turn;
					if(real == '3')
					{
						money-=bet;
						bet*=2;
						morecards = 0;
					}
					card3 = rand()%52+1;
					cardname (card3, name, suit);
					Sleep(1000);
					cout << "\nThe dealer puts your new card down. This card is a(n) " << name <<" of " << suit << endl; 
					cardsum += card3;
					if (cardsum >21)
					{
						cout << "\nSorry, That's a bust. You lose!"<< endl;
						bet = 0;
						break;	
					}
					if (card3 == 1)
					{
						++ace;
					}
				}
				else
				{	
					morecards = 0;	
				}
			}while (morecards == 1);
			dd = 0;
			if (cardsum >=22)
				{
					break;	
				}
			cardname (dealer2, name, suit);
			cout << "\nThe dealer shows you his last card. This card is a(n) " << name <<" of " << suit << endl;
			dsum += dealer2;
			if (dealer2 == 1)
			{
			++dace;
			}
			if (dace>0&&dsum+10<22)
			{
				dsum+=10;
			}
			while(dsum<17||dsum<cardsum)
			{
				++dturn;
				dealer3 = rand()%52+1;
				cardname (dealer3, name, suit);
				Sleep(1000);
				cout << "\nThe dealer draws a new card. This card is a(n) "<< name<<" of " << suit <<endl;
				dsum+=dealer3;		
				if(dealer3 == 1)
				{				
					++dace;
				}
				if((dealer3 == 1)&&((dsum+10)<22))
				{
					dsum+=10;
				}
				if((dsum>21)&&(dace!=0))
				{
					dsum-=10;
					dace = 0;
				}
				if((dsum >=22))
				{
					Sleep(1000);
					cout << "The dealer busts."<< endl;
					Sleep(1000);
					cout <<"You win!"<< endl;
					Sleep(1000);
					cout <<"You win!"<< endl;
					Sleep(1000);
					cout <<"You win!"<< endl;
					money +=bet*2;
					break;	
				}	
			}
			if ((dsum >=22))
			{
				break;	
			}
			if (ace >= 1&&(cardsum+10)<22)
			{
				Sleep(1000);
				cout << "You have an ace.\nDo you " << endl;
				cout << "1. Want to use this ace as a one, or \n2. an 11? :";
				real = choose(dd);
				if (real == '1')
					cout << "\nYour ace is still worth 1" <<endl;
				else
				{
					cardsum += 10;
					cout << "Your ace is now worth 11" << endl;
				}
			}
			if (cardsum > dsum||(cardsum == dsum&&turn<dturn))
			{
				Sleep(1000);
				cout <<"You win!"<< endl;
				Sleep(1000);
				cout <<"You win!"<< endl;
				Sleep(1000);
				cout <<"You win!"<< endl;
				money += bet*2;
				bet = 0;
			}
			else if (cardsum == dsum&&turn == dturn)
			{
				Sleep(1000);
				cout << "You push with "<< cardsum << endl;
				money+=bet;
				bet = 0;
			}
			else if (cardsum < dsum||(cardsum == dsum&&dturn<turn))
			{
				Sleep(1000);
				cout << "Sorry. You lose. The dealer wins with "<< dsum << endl;
				cout << "Better luck next time." << endl;
				bet = 0;
			}
		}
		Sleep(1000);
		if (quit == 1)
		{
			break;
		}
		cout << "You now have "<<money << " candy" <<endl;
		Sleep(1000);
		cout << "\nDo you want to play again?  \n1.	Yes or \n2.	No? : ";
		real = choose(dd);
		if (real =='1')
		{
			cout << "\nYou are continuing your game.\n"<< endl;
			i = 1;
			quit = 0;
			ace = 0;
			dace = 0;
			Sleep(800);
			system("CLS");
		}
	}while(real == '1');
	Sleep(1000);
	cout << "You end with " << money << " candy" << endl;
	scoreout.open("score.txt");
	scoreout<<money;
	scoreout.close();
	Sleep(1000);
	cout << "\nThanks for playing. Please play again!"<< endl;
	return 0;
}

void cardname (int& card, string& name, string& suit)
{
	
	int suitnum = card%4+1;
	card = card %13+1;
	if(card == 1||card==11||card==12||card==13)
	{
		if (card == 1) name = "ace";
		if (card == 11) name = "jack";
		if (card == 12) name = "queen";
		if (card == 13) name = "king";
	}
	else
	{
		stringstream ss;//create a stringstream
  		ss << card;
  		name = ss.str();
	}
	if (card == 11||card==12||card==13)
		card = 10;
	if(suitnum == 1)
		suit = "spades.";
	if(suitnum == 2)
		suit = "hearts.";
	if(suitnum == 3)
		suit = "clubs.";	
	if(suitnum == 4)
		suit = "diamonds.";
}
char choose(int dd)
{
	string input;
	char real;
	cin >> input;
	for(;;)
	{
		real = input[0];
		if (real == '1')
		return '1';
		if (real == '2')
		return '2';
		if(real == '3'&&dd == 1)
		return '3';
		else cout <<"Invalid input. Try again: ";
		cin >> input;
	}
}
int numbers()
{
	string input;
	unsigned long int strSize;
	unsigned int counter = 0;
	char num[48];
	int numcount = 0;
	int number;
	bool notnum = 0;
	do{
		cin >> input;
		strSize = input.size();
		counter = 0;
		numcount = 0;
		notnum = 0;
		number= 0;
		for(counter; counter<48;++counter)
		{
			num[counter] = ' ';
		}
		counter = 0;
		for (counter; counter<strSize;++counter)
		{
		if(input[counter]>='0'&&input[counter]<='9')
			{
				num[numcount] = input[counter];
				++numcount;
			}
			else if(input[counter]!='0'&&input[counter]!='1'&&input[counter]!='2'&&input[counter]!='3'&&input[counter]!='4'&&input[counter]!='5'&&input[counter]!='6'&&input[counter]!='7'&&input[counter]!='8'&&input[counter]!='9')
			{
				notnum = 1;
				break;
			}	
		}
		if (notnum == 0)
		{
			number = atoi(num);
			if (number == 0) cout <<"Enter something other than 0: ";
		}
		else if(notnum == 1) 
		{
			cout << "Not a valid number. Enter a new one: ";
		}
	}while(notnum == 1 || number == 0);
	return number;
}
