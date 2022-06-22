#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct Character
{
	int strength;
	int intelligence;
	int mana;
	int health;
	char charname[256];
	char playername[256];
} Character;


// Global Variables
Character character = { 8, 13, 100, 100, "", "" };

int damageBoost;

// Functions
void game(FILE* fp);

void pickCharacter(Character* char1);
void input(int*);
void stringInput(char*);

void goodspirit(Character* char1);

bool charTurn(int*, Character* char1);
void heavyAttack(int*, Character*);
void lightAttack(int*);
void concentrate(Character* char1);

bool skeletonFight(Character* char1);
void skeletonTurn(int*);

bool poisonFight(Character* char1);
void poisonTurn(int* charHealth);

bool dragonFight(Character* char1);
void dragonTurn(int*);

bool necromancerFight(Character* char1);
void necromancerTurn(int*);

bool threeDoors(Character* char1);

void lookAround();

void hallway();

bool finalEnding();

void blue();
void red();
void green();
void reset();

void badInput()
{
	printf("\033[0;31m");
	printf("Bad Input! Please try again.\n");
	reset();
}

void areYouReady()
{
	while (true)
	{
		printf("Are you ready for the adventure?\n\t1.Yes\n\t2.No\n");
		int userInput;
		input(&userInput);
		switch (userInput)
		{
		case 1:
			return;
		case 2:
			printf("Come on! Take a deep breath.\n");
			continue;
		default:
			badInput();
		}
	}
}

void willYouStop(Character* char1)
{
	while (true)
	{
		printf("\t1. Stop and interrogate him\n\t2. Banish him to the dark realm\n");
		int userInput;
		input(&userInput);
		switch (userInput)
		{
		case 1:
			printf("You stop and let him speak.\n");
			printf("\"I am not the one operating these activities.\nI am forced by Zarius, the disbanded dragon.\nOnce upon a time I used to live peacefully in my dungeon.\nEvery other creature used to respect me.\nBut one day, Zarius, the disbanded dragon, invaded our dungeon.\nWe lost.\nHe became the king of the dungeon and made every creature work for him.\nHe was the one who made me leave my dungeon and capture the humans.\"\n");
			printf("\n\"What does he do with those humans?\", You interrupt him.\n");
			printf("\n\"He rapes and tortures them for his entertainment and pleasure. Occasionally, whenever he is bored with his everyday meal he even eats a few of them.\", He answers.\n");
			printf("\n\"Do you know about a woman named Scarlett, whom you captured a few days ago.\", You ask.\n");
			printf("\n\"I don't know the names of the people I capture. However, if she has been captured only a few days ago then she must be safe till now.\", He replies.\n");
			printf("\"That dragon is going to regret ever entering this dungeon.\", You say angrily.\n");
			printf("\"That dragon has humiliated me very much.\nMaking me work for him.\nBeing too weak, I couldn't take my revenge on him.\nBut I believe you can.\nI will give you my powerful staff, capable of casting more powerfull spells and can even deal more damage physically.\nBut you must slay that dragon.\", he says looking at you hopefully.\n");
			printf("You didn't expect being offered help by an evil. But you will need any help you can get right now to be able to defeat Zarius.\nNecromancer slowly hands over his staff to you and collapses into the floor.\n");
			damageBoost += 8;
			printf("Your attacks will now deal 5 more damage.\n");
			return;
		case 2:
			printf("You ignore his cries for mercy and caste your spell and his soul gets banished to the dark realm. His soulless body drops to the floor.\n\"These evil bastards have on place on this realm\", You say to yourself.\n");
			char1->mana -= 25;
			printf("You lost 25 mana.\n");
			return;
		default:
			badInput();
		}
	}
}

void areYouBluffing(Character* char1)
{
	while (true)
	{
		printf("Do you banish him to the dark realm?\n\t1. Yes (Costs 25 mana)\n\t2. No\n");
		int userInput;
		input(&userInput);
		switch (userInput)
		{
		case 1:
			if (char1->mana >= 25)
			{
				printf("You start casting the spell to banish him.\nThe Necromancer quickly begs for your mercy.\n");
				willYouStop(&character);
			}
			else
			{
				printf("You don't have sufficient mana.\n");
				continue;
			}
			return;
		case 2:
			printf("You decide it is not worth wasting your mana on him and let him die.\n");
			return;
		default:
			badInput();
		}
	}
}

void tryToOpenTheGate()
{
	int choice;
	input(&choice);
	while (choice < 1 || choice > 2)
	{
		badInput();
		input(&choice);
	}
	if (choice == 1)
	{
		printf("You run towards the gate, trying to lift it back up, but it's no good.\nWith your ordinary strength, you can't get the gate back open.\n");
	}
}

void doYouExamine()
{
	while (true)
	{
		printf("\t1. Examine the cave\n\t2. Enter the hallway\n");
		int userInput;
		input(&userInput);
		switch (userInput)
		{
		case 1:
			lookAround();
			return;
		case 2:
			printf("You believe that it is not worth wasting time messing aroung and enter the hallway.\n");
			return;
		default:
			badInput();
		}
	}
}

void game(FILE* fp)
{
	srand(time(NULL));

	printf("Welcome to the '");
	printf("\033[0;32m");
	printf("Mystery of the dungeon");
	reset();
	printf("'.\nPlease tell us a little about yourself.\n");
	printf("What is your name? \n");
	stringInput(character.playername);
	fp = fopen("dungeon.txt", "a");
	fprintf(fp, "Playername : %s\n", character.playername);
	fclose(fp);
	pickCharacter(&character);
	printf("\nWelcome %s! You are a %s.\n", character.playername, character.charname);
	printf("As a %s, your stats are\n\tStrength: %d\n\tIntelligence: %d\n\tHealth: %d\n\tMana: %d\n", character.charname, character.strength, character.intelligence, character.health, character.mana);
	areYouReady();
	printf("\nThere has been something really mysterious about the forests to the north of Kacheta, a small town.\nAnyone who goes there just disappears mysteriouly.\nLegends say that they are kidnapped by the Necromancer living in the dungeon hidden in the middle of the forest.\nNo one has ever dared to go into that dungeon.\nBeing quite respected adventurer in Kacheta, you have been requested several times by the people to go to the dungeon in search of their families.\nBut no reward has been big enough to attract you to embark on the most dangerous adventure of your life.\nHowever, when your wife disappeared into that forest in the same mysterious way, you felt lost.\nYou were ashamed of your cowardice to have not gone to explore the dungeons earlier which could have potentially saved your very beloved wife, Scarlett.\nHaving been left with no other option you decide to put an end to the mystery of this dungeon and potentially find your wife.\n");
	printf("\nAfter doing some research, you found that people have been going missing near the centre of the forest.\nWasting no time you headed towards the centre of the forest.\nYour journey was mostly uneventful, which surprised you because central forests are generally occupied by the goblin hordes.\n\"Goblins must have left this place due to being terrorised by the necromaner\", You say.\nIt started getting dark, and you find an empty cave which you decide to spend the night in.\nUpon entering the cave you found that it is actually a dungeon whose walls were made up of skeletons.\nThe second you make it all the way inside, an iron gate crashes down behind you, locking you in.\nDo you try and escape, or continue forward into the dungeon?\n\t1. Try to escape\n\t2. Observe your surroundings\n");
	tryToOpenTheGate();
	printf("\nYou start observing the gate.\nYou were interrupted by noice of some strange footsteps, which surely were not of a human.\nUpon turning around you were greeted by a charging skeleton.\n");

	if (skeletonFight(&character) == 0)
	{
		printf("\033[7;31m");
		printf("Oh no!\n");
		printf("%s is slain by the skeleton.\n", character.playername);
		fp = fopen("dungeon.txt", "a");
		fprintf(fp, "Result : %s is slain by the skeleton.\n\n", character.playername);
		fclose(fp);
		printf("They lived a wonderful life.\nFeel free to play again!\n");
		reset();
		return;
	}

	printf("\nThat skeleton was no match for you.\nYou think for a moment about how many skeletons would it take to kill you.\nUnfortunately, The Necromancer, who had raised the skeleton you just fought, was there to willingly answer your query.\nHe raises his staff and more skeletons came out from the wall making the walls shake.\nYou realise that you need to do something before the walls crumble.\n");

	if (necromancerFight(&character) == 0)
	{
		printf("\033[7;31m");
		printf("Oh no!\n");
		printf("%s has died, overrun by skeletons. Maybe one day their body will decompose, and join the ranks of the skeletons.\n", character.playername);
		fp = fopen("dungeon.txt", "a");
		fprintf(fp, "Result : %s has died, overrun by skeletons. Maybe one day their body will decompose, and join the ranks of the skeletons.\n\n", character.playername);
		fclose(fp);
		printf("They lived a wonderful life.\nFeel free to play again!\n");
		reset();
		return;
	}

	printf("\nKnowing that the necromancer is no position to harm you now, you walk up to him and ask, \"Why did you capture of the humans roaming around this area?\"\n");
	printf("\n\"Why do you expect me to answer you? I have been defeated and about to be dead. I have nothing to lose now and will not help you in any way?\"\n");
	printf("\"I expect you to answer me because I am sure you would not like to be banished to the dark realm.\"\n");
	printf("\"You are bluffing! You surely don't know how to do that!\"\n");
	areYouBluffing(&character);
	goodspirit(&character);
	printf("You see that the area from where necromancer summoned the skeletons have left an opening to a hallway.\n");
	doYouExamine();
	hallway();

	if (poisonFight(&character) == 0)
	{
		printf("\033[7;31m");
		printf("Oh no!\n");
		printf("%s has perished to the posion and the mysterious figure.\n", character.playername);
		fp = fopen("dungeon.txt", "a");
		fprintf(fp, "Result : %s has perished to the posion and the mysterious figure.\n\n", character.playername);
		fclose(fp);
		printf("They lived a wonderful life.\nFeel free to play again!\n");
		reset();
		return;
	}
	goodspirit(&character);

	printf("You proceed through the door with the writing.\n");

	if (threeDoors(&character) == 0)
	{
		printf("\033[7;31m");
		printf("Oh no!\n");
		printf("%s has died. They lived a wonderful life.", character.playername);
		fp = fopen("dungeon.txt", "a");
		fprintf(fp, "Result : %s has died. They lived a wonderful life.\n\n", character.playername);
		printf("They lived a wonderful life.\nFeel free to play again!\n");
		reset();
		return;
	}

	if (dragonFight(&character) == 0)
	{
		printf("\033[7;31m");
		printf("Oh no!\n");
		printf("%s was slain by the dragon.\n", character.playername);
		fp = fopen("dungeon.txt", "a");
		fprintf(fp, "Result : %s was slain by the dragon.\n\n", character.playername);
		fclose(fp);
		printf("They lived a wonderful life.\nFeel free to play again!\n");
		reset();
		return;
	}
	goodspirit(&character);
	printf("You look around the room hoping to see your wife somewhere but she or any other human was no where to be seen.\nNow, you begin to all of your hope of ever finding your wife again.\n\"Fighting Zarius, exploring the mysterious dungeon and taking the biggest risk of my life all for nothing.\" You scream at the top of your lungs.\nWith nowhere else to go, you go back to the room you came in from, the one with three doors.\n");

	if (finalEnding(&character) == 0)
	{
		printf("\033[7;31m");
		printf("Oh no!\n");
		printf("%s has died.\n", character.playername);
		fp = fopen("dungeon", "a");
		fprintf(fp, "Result : %s has died.\n\n", character.playername);
		fclose(fp);
		printf("They lived a wonderful life.\nFeel free to play again!\n");
		reset();
		return;
	}
}

bool playAgain()
{
	int* ptr = &character.mana;
	*ptr = 100;
	int* ptr1 = &character.health;
	*ptr1 = 100;
	damageBoost = 0;
	while (true)
	{
		printf("Would you like to play again:\n\t1. Yes\n\t2. No\n");
		int userInput;
		input(&userInput);
		switch (userInput)
		{
		case 1:
			return 1;
		case 2:
			return 0;
		default:
			badInput();
		}
	}
}

int main()
{
	FILE* fp = NULL;
	do
		game(fp);
	while (playAgain());
	printf("Thank you for playing!\n");
	return 0;
}

void pickCharacter(Character* char1)
{
	char* choices[4] = { "Wizard", "Rogue", "Demon", "Ranger" };

MENU:printf("Please choose a race from the following list:\n");
	printf("\t1. Wizard\n\t2. Rogue\n\t3. Demon\n\t4. Ranger\n");

	char choiceString[20] = "";
	int choice = -1;
	input(&choice);

	if (choice > 4 || choice < 1)
	{
		badInput();
		goto MENU;
	}
	else
	{
		switch (choice)
		{
		case 1:
		{
			strcpy(choiceString, "Wizard");
			puts("Wizard is a man who has magical powers.\nIs this what you want to be? (Enter 1 for yes, or 2 for no)");
			int confirm;
			input(&confirm);
			while (confirm < 1 || confirm > 2)
			{
				badInput();
				input(&confirm);
			}
			if (confirm == 2)
			{
				goto MENU;
			}
			break;
		}
		case 2:
		{
			strcpy(choiceString, "Rogue");
			printf("Rogue is a dihonest and unprincipled man.\n");
			printf("\033[0;31m");
			puts("This character is still under development.\nIf you want to play using this character please support us by donating something and we will surely speed up the development process.\nWe accept donations via GooglePay, PayTM, PhonePay.\nContact Akshat Singh Raghuwanshi, Aditya Pratap Singh or Ayush Kumar Sehgal for further details.\n");
			printf("\033[0m");
			goto MENU;
			break;
		}
		case 3:
		{
			strcpy(choiceString, "Demon");
			printf("Demon is an evil spirit capable of possessing another person.\nIn his/her/their free time, he/she/it acts as a tormentor in hell.\n");
			printf("\033[0;31m");
			puts("This character is still under development.\nIf you want to play using this character please support us by donating something and we will surely speed up the development process.\nWe accept donations via GooglePay, PayTM, PhonePay.\nContact Akshat Singh Raghuwanshi, Aditya Pratap Singh or Ayush Kumar Sehgal for further details.\n");
			printf("\033[0m");
			goto MENU;
			break;
		}
		case 4:
		{
			strcpy(choiceString, "Ranger");
			printf("Rangers are the keeper of this world.\nThey have sworn to protect this world from the evil.\n");
			printf("\033[0;31m");
			puts("This character is still under development.\nIf you want to play using this character please support us by donating something and we will surely speed up the development process.\nWe accept donations via GooglePay, PayTM, PhonePay.\nContact Akshat Singh Raghuwanshi, Aditya Pratap Singh or Ayush Kumar Sehgal for further details.\n");
			printf("\033[0m");
			goto MENU;
			break;
		}
		}

		strcpy(char1->charname, choiceString);
	}

	return;
}

void input(int* Ptr)
{
	printf("\033[0;33m");
	char hold[256];
	scanf(" %[^\n]s", hold);
	int holdint = atoi(hold);
	if (holdint)
	{
		*Ptr = holdint;
	}
	else
	{
		*Ptr = -1;
	}
	printf("\033[0m");
}

void stringInput(char* Ptr)
{
	printf("\033[0;33m");
	scanf(" %[^\n]s", Ptr);
	printf("\033[0m");
}

void blue()
{
	printf("\033[0;36m");
}

void green()
{
	printf("\033[0;32m");
}

void red()
{
	printf("\033[0;31m");
}

void reset()
{
	printf("\033[0m");
}


bool charTurn(int* enemyHealth, Character* char1)
{
	printf("You have %d health and opponent has %d health remaining.\n", char1->health, *enemyHealth);
	printf("It's your turn to act!\n");
	int choice;
	while (true)
	{
		printf("\t1. What do my attacks do?\n\t2. Attack with sword\n\t3. Attack with a fireball\n\t4. Rest and concentrate\n\t5. How much health and mana do I have left?\n");
		input(&choice);
		while (choice < 1 || choice > 5)
		{
			badInput();
			input(&choice);
		}
		if (choice == 1)
		{
			printf("'Attack with sword' does %d damage.\n'Attack with fireball' does %d-%d damage and costs 40 mana.\n'Rest and concentrate' restores 35 mana.\nWhat would you like to do?\n", 5 + damageBoost, 0 + damageBoost, 20 + damageBoost);
			input(&choice);
			if (choice == 1)
				continue;
			while (choice < 2 || choice > 5)
			{
				badInput();
				input(&choice);
			}
		}
		if (choice == 2)
		{
			printf("You slash with your sword!\n");
			lightAttack(enemyHealth);
			return 0;
		}
		if (choice == 3)
		{
			printf("You attack with fireball!\n");
			heavyAttack(enemyHealth, &character);
			return 0;
		}
		if (choice == 4)
		{
			printf("You sit down and concentrate.\n");
			concentrate(&character);
			return 0;
		}
		if (choice == 5)
		{
			printf("You have %d health and %d mana remaining.\n", char1->health, char1->mana);
			continue;
		}
	}

	return 0;
}

void heavyAttack(int* enemyHealth, Character* char1)
{
	if (char1->mana >= 40)
	{
		int damage = (rand() % 20) + damageBoost;
		*enemyHealth -= damage;
		char1->mana -= 40;
		printf("You deal %d damage and used 40 mana.\n", damage);
	}
	else
		printf("You try to attack with a fireball, but are unable to generate one due to insufficient mana.\n");
}

void lightAttack(int* enemyHealth)
{
	int damage = 5 + damageBoost;
	*enemyHealth -= damage;
	printf("You deal %d damage.\n", damage);
}

void concentrate(Character* char1)
{
	char1->mana += 35;
	printf("You restored 35 mana.\n");
}

bool skeletonFight(Character* char1)
{
	int skeletonHealth = 5;
	while (char1->health > 0 && skeletonHealth > 0)
	{
		charTurn(&skeletonHealth, char1);
		if (skeletonHealth > 0)
		{
			skeletonTurn(&char1->health);
		}
	}
	if (char1->health <= 0)
		return 0;
	else
	{
		int choice;
		printf("With that blow, the skeleton collapses into a pile of bones. He's been defeated!\n\t1. Hooray!\n");
		input(&choice);
		while (choice != 1)
		{
			badInput();
			input(&choice);
		}
		return 1;
	}
}

void skeletonTurn(int* charHealth)
{
	int damage;
	damage = rand() % 4 + 1;
	*charHealth -= damage;
	green();
	printf("The skeleton takes a swing at your face, dealing %d damage.\n", damage);
	reset();
}

bool necromancerFight(Character* char1)
{
	int necromancerHealth = 40;
	int skeletonsHealth = 40;
	while (char1->health > 0 && necromancerHealth > 0 && skeletonsHealth > 0)
	{

		int choice;
	MENU:printf("Choose a target for your turn:\n");
		printf("\t1. Necromancer\n\t2. Skeletons\n");
		input(&choice);
		if (choice < 1 || choice > 2)
		{
			badInput();
			goto MENU;
		}
		if (choice == 1)
		{
			charTurn(&necromancerHealth, char1);
			if (necromancerHealth > 0)
			{
				necromancerTurn(&char1->health);
			}
		}
		else
		{
			charTurn(&skeletonsHealth, char1);
			if (skeletonsHealth > 0)
			{
				printf("The skeleton you hit falls to the ground, but more come to take it's place.\n");
				necromancerTurn(&char1->health);
			}
		}
	}
	if (char1->health <= 0)
		return 0;
	else if (skeletonsHealth <= 0)
	{
		printf("As you take out another skeleton, more crawl forward from the walls. There aren't enough skeletons left at this point to continue supporting the room, and the walls start to crumble. You don't have enough time to escape, and are crushed by the ceiling as it caves in.\n");
		return 0;
	}
	else
	{
		printf("Your last attack shatters the necromancer's skull, and all the enemies crumble into dust.\nThe walls that were crumbling have stabilized, and the room is safe.\n\t1. Awesome!\n");
		int choice;
		input(&choice);
		while (choice != 1)
		{
			badInput();
			input(&choice);
		}
		return 1;
	}
}

void necromancerTurn(int* charHealth)
{
	int move = rand() % 3;
	int damage;
	if (move == 0)
	{
		damage = rand() % 14 + 1;
		*charHealth -= damage;
		green();
		printf("The necromancer levels his staff at you, shooting a bolt of energy that deals %d damage.\n", damage);
		reset();
	}
	if (move == 1)
	{
		damage = rand() % 4 + 1;
		*charHealth -= damage;
		green();
		printf("A skeleton walks up to you and hits you in the back of the head, dealing %d damage.\n", damage);
		reset();
	}
	if (move == 2)
	{
		damage = rand() % 14 + 1;
		*charHealth -= damage;
		green();
		printf("3 skeletons come up on all sides of you and take a poke at you, dealing %d damage.\n", damage);
		reset();
	}
}

bool poisonFight(Character* char1)
{
	int poisonHealth = 32;
	int turnCount = 0;
	while (char1->health > 0 && poisonHealth > 0 && turnCount < 5)
	{
		charTurn(&poisonHealth, char1);
		if (poisonHealth > 0)
		{
			poisonTurn(&char1->health);
		}
		if (turnCount == 2)
		{
			printf("You are running out of breath, you realise at this rate you won't be able to last much longer.\n");
		}
		if (turnCount == 3)
		{
			printf("You are very low on breath right now, you realise if you have to do something you need to do it right now.\n");
		}
		if (turnCount == 4)
		{
			printf("You can feel your body breaking. You can't hold your breath any longer--you need to breathe.\n");
			printf("You take a breath, and it is your last. The air you gulp contains a poison unlike any other, and it works instantly.\n");
			return 0;
		}
		++turnCount;
	}
	if (char1->health <= 0)
		return 0;
	else
	{
		printf("Your last attack seemed to do it, and the mysterious figure falls like a sack of potatoes. The gas becomes normal air, and you can finally take a breath.\n\t1. Breathe\n");
		int choice;
		input(&choice);
		while (choice != 1)
		{
			badInput();
			input(&choice);
		}
		return 1;
	}
}

void poisonTurn(int* charHealth)
{
	int move = rand() % 3;
	int damage;
	if (move == 0)
	{
		damage = rand() % 9 + 1;
		*charHealth -= damage;
		green();
		printf("The figure hits you with a small vial of acid, dealing %d damage.\n", damage);
		reset();
	}
	if (move == 1)
	{
		damage = rand() % 19 + 1;
		*charHealth -= damage;
		green();
		printf("The figure lashes out with a dagger, dealing %d damage.\n", damage);
		reset();
	}
	if (move == 2)
	{
		damage = rand() % 14 + 1;
		*charHealth -= damage;
		green();
		printf("You breathe in just a tiny bit of the poison in the air, taking %d damage.\n", damage);
		reset();
	}
}

bool dragonFight(Character* char1)
{
	int dragonHealth = 100;
	while (char1->health > 0 && dragonHealth > 0)
	{
		charTurn(&dragonHealth, char1);
		if (dragonHealth > 0)
		{
			dragonTurn(&char1->health);
		}
	}
	if (char1->health <= 0)
		return 0;
	else
	{
		int choice;
		printf("With that final blow, the dragon lets out a roar and collapses into the ground. He's been defeated!\n\t1. Hooray!\n");
		input(&choice);
		while (choice != 1)
		{
			badInput();
			input(&choice);
		}
		return 1;
	}
}

void dragonTurn(int* charHealth)
{
	int move = rand() % 3;
	int damage;
	if (move == 0)
	{
		damage = rand() % 25 + 1;
		*charHealth -= damage;
		green();
		printf("The dragon roars and bites at you with his skeletal teeth, dealing %d damage.\n", damage);
		reset();
	}
	if (move == 1)
	{
		damage = rand() % 4 + 1;
		*charHealth -= damage;
		green();
		printf("The dragon spins around and swings his tail at you, dealing %d damage.\n", damage);
		reset();
	}
	if (move == 2)
	{
		damage = rand() % 15 + 1;
		*charHealth -= damage;
		green();
		printf("The dragon flies up in the air, then tries to slam down on top of you, dealing %d damage.\n", damage);
		reset();
	}
}

bool threeDoors(Character* char1)
{
	printf("You look into the dark, and see a staircase leading downwards.\nWith no other choice, you begin to descend.\nAs you go down the stairs, magical torches light up on either side of you.\nOnce you reach the bottom, you find yourself in a small room with three doors.\n\t1. Examine the doors\n");
	int choice;
	input(&choice);
	while (choice != 1)
	{
		badInput();
		input(&choice);
	}
	printf("Door 1 is covered in blood, and the ground in front of it is littered with bones.\nDoor 2 shines with a beautiful golden light.\nDoor 3 is so dark you can hardly make it out next to the dark walls.\n\nYou feel like you have some sort of hint for which door you should pick. Which door will you go through?\n\t1. Door 1\n\t2. Door 2\n\t3. Door 3\n");
	input(&choice);
	while (choice < 1 || choice > 3)
	{
		badInput();
		input(&choice);
	}
	if (choice == 3)
	{
		printf("You walk up to door 3, and manage to find the knob in the darkness.\nYou open the door to reveal a dark, shadowy place.\nAs you step forward, you realize that there isn't any ground, only a dark abyss.\n\t1. Uh-oh\n");
		input(&choice);
		while (choice != 1)
		{
			badInput();
			input(&choice);
		}
		printf("You try to jump backwards, but you've already lost your footing on the ground behind you.\nYou start to fall into the abyss.\nYou try to turn and grab the edge of the floor behind you, but you just barely miss.\nNothing can save you now, as you fall to your death.\n");
		return 0;
	}
	if (choice == 2)
	{
		printf("You walk up to door 2, still shining a bright gold.\nYou open the door, and are blinded by how bright it is inside.\nYou immediately notice that it's hot, so hot.\n\t1. This can't be good\n");
		input(&choice);
		while (choice != 1)
		{
			badInput();
			input(&choice);
		}
		printf("You realize that somehow, this door led to something as hot as the sun, maybe even the sun itself.\n");
		printf("Not even a second later, you find yourself vaporized by the heat, now only a pile of ash in front of the door.\n");
		return 0;
	}
	if (choice == 1)
	{
		printf("You walk up to door 1, trying not to step on too many of the bones on the ground.\nYou open the door to find another room up ahead.\nStepping forward into the room, you see Zarius, the disbanded dragon, staring right at you.\nYou know that you have no choice but to fight it.\n\t1. Let's go!\n");
		input(&choice);
		while (choice != 1)
		{
			badInput();
			input(&choice);
		}
		return 1;
	}
}

void lookAround()
{	
	int response;
	printf("You decide to take a moment and observe the skeleton walled cave.\n\"I can use any hint that I can get while in this dungeon.\", You say to yourself.\nUpon exploring you accidently step on a skull crushing it.\n\"");
	blue();
	blue();
	printf("It is the gift of the gods, granted to everyone at birth, appreciated by the just and neglected by the wicked.");
	reset();
	printf("\", a skelton in the wall says.\n\"That crushed skull must have triggered it.\", You say to yourself.\nIt must be a riddle of some kind.\nDo you try to solve it?\n\t1. Yes\n\t2. No\n");
	input(&response);
	while (response > 2 || response < 1)
	{
		badInput();
		input(&response);
	}
	{
		if (response == 1)
		{
			printf("You think of many possible answers in your mind.\nWhat can be the answer to this riddle?\n(Hint: answer is 4 letters)\n");
			int tries = 0;
			char answer[256];

			while (tries < 3)
			{
				stringInput(answer);
				if (strcmp(answer, "life") == 0 || strcmp(answer, "LIFE") == 0)
				{
					strcpy(answer, "Life");
				}
				if (strcmp(answer, "Life") == 0)
				{
					printf("\"Life\", You say. Upon hearing the words the skeleton speaks again, \"Opposite of light, you must go where you find evidence of death, along with the color of gore, the color of violence and where there is more.\"\n");
					printf("Confused what to decipher of that message you decide to keep it in mind hoping it is not just any random bullshit.\n");
					break;
				}
				else if (tries < 2)
				{
					printf("");
					printf("Nothing happened.\nThat doesn't seem to be the right password.\nWhat else could it be?\n");
				}
				else if (tries == 2)
				{
					printf("Nothing happened.\nThat doesn't seem to be the right password.\n");
					printf("You were never very good at riddles, and decide to give up and move on.\n");
				}
				tries++;
			}
		}
		else
		{
			printf("You decide not to bother with the weird symbols.\n");
		}
		printf("Without wasting anymore time in the cave, you enter the hallway.\n");
	}
}


void hallway()
{
	int choice;
	printf("The walls seem to be constructed with piles of bones, and torches made of skulls light the path.\nAt the end of the hallway is a door, with a message hastily carved into it.\n\t1.Read it\n");
	input(&choice);
	while (choice != 1)
	{
		badInput();
		input(&choice);
	}
	blue();
	printf("\"DON'T BREATHE.\"\n");
	reset();
	printf("Immediately, green gas starts to fill the hallway from the far end, which you recognize as poison.\nYou notice a figure in the gas approaching you. \nYou can't let yourself breathe, or else you'll inhale the poison, but you know you have no choice but to fight.\n\t1. Hold your breath and prepare for battle\n");
	input(&choice);
	while (choice != 1)
	{
		badInput();
		input(&choice);
	}
}

void goodspirit(Character* char1)
{
	int userInput;
	printf("A spirit appears from where was the collapsed body of the evil you just killed.\nIt says, \"Thank you for freeing me.\nI am made up of all the good my body had consumed in his quest for evil.\nI would like to thank you by gifting you something that I am capable of.\nDo you want to heal some of your scars?\nOr do you want a high amount of mana?\nOr do you want to have more powerfull attacks?\nWhatever it is, just ask away.\"\n\t1. Heal your scars(increases health by 43)\n\t2. Large amount of mama(increases mana by 180)\n\t3. More powerfull attacks(your attacks deal 8 more damage)\n");
	input(&userInput);
	while (userInput < 1 || userInput> 3)
	{
		badInput();
		input(&userInput);
	}
	if (userInput == 1) {
		char1->health += 43;
		printf("You restore 43 health.\n");
	}
	else if (userInput == 2) {
		char1->mana += 180;
		printf("You gain 180 mana.\n");
	}
	else if (userInput == 3)
	{
		damageBoost += 8;
		printf("Your attacks now deal 8 more damage.\n");
	}

	else {
		badInput();
	}
	printf("The spirit disappears in the same mysterious way it appeared.\n");
}

bool finalEnding()
{
	FILE* fp;
	printf("You notice that the 3rd door, which used to be dark and shadowy, now appears to be just a normal door.\nYou now have three options to go to.\n\t1. Door 2\n\t2. Door 3\n\t3. Staircase you came in here from\n");
	int choice;
	input(&choice);
	while (choice < 1 || choice > 3)
	{
		badInput();
		input(&choice);
	}
	if (choice == 1)
	{
		printf("You walk up to door 2, still shining a bright gold. You open the door, and are blinded by how bright it is inside. You immediately notice that it's hot, so hot.\n\t1. This can't be good\n");
		input(&choice);
		while (choice != 1)
		{
			badInput();
			input(&choice);
		}
		printf("You realize that somehow, this door led to something as hot as the sun, maybe even the sun itself.\n");
		printf("Not even a second later, you find yourself vaporized by the heat, now only a pile of ash in front of the door.\n");
		return 0;
	}
	if (choice == 2)
	{
		printf("You walk inside the 3rd door.\nYou are surprised upon seeing hundreds of people tied up there.\nAnd among them is Scarlett.\nYour eyes brighten upon seeing her.\nYou quickly untie and kiss her.\nTears of happiness rolling down your eyes.\n\t1. Get intimate.\n\t2. Control yourself and free everyone\n");
		input(&choice);
		while (choice < 1 || choice>2)
		{
			badInput();
			input(&choice);
		}
		while (choice == 1)
		{
			red();
			printf("This choice is a part of our premium subscription, available at only Rs. 299 per year.\nFor further details on how to subscribe, contact Akshat Singh Raghuwanshi, Aditya Pratap Singh or Ayush Kumar Sehgal.\n");
			reset();
			printf("\n\t1. Get intimate.\n\t2. Control yourself and free everyone\n");
			input(&choice);
		}
		if (choice == 2)
		{
			printf("You somehow control your emotions and free everyone.\nYou all go back to the skeleton walled dungeon entrance.\nIron gate was still closed.\nBut with the strength of hundreds of people, you all dig your way out from underneath the gate.\nYou have never ever felt happier upon seeing the sunshine before.\n\nKacheta town became normal.\nPeople started living their normal lives back again.\nYour life also became boring.\nUntil one day, when the King along with his escort was found dead on the road.\nAnd you gear yourself up for another adventure.\n\n");
			printf("\033[0;35m");
			printf("Congratulations! %s has won the game.\n", character.playername);
			fp = fopen("dungeon.txt", "a");
			fprintf(fp, "Result : %s has won the game.\n\n", character.playername);
			fclose(fp);
			reset();
		}
	}
	if (choice == 3)
	{
		printf("Having lost all of your motivation and hope, you climp up the staircase to go back to the long hallway and then to the skelton walled dungeon entrance.\nThe iron gate was still closed.\nUnwilling to go back to the dungeon, you started digging underneath the gate with your bare hands.\nBut the gate went deep inside the ground.\nWith no food and water, you became very tired.\nInspite of almost no energy, you kept digging with whatever you had.\nEventually you collapse to a never ending sleep.\n");
		return 0;
	}
}