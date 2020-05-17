#ifndef SNAKES_H
#define SNAKES_H

#include<iostream>
#include <fstream>
using namespace std;




class QueueNode
{
public:
	int pPosition;								
	int pNumber;								
	QueueNode* next;								
};

class Queue
{
public:
	QueueNode* frontp;								
	QueueNode* rearp;							
	Queue(int players = 2)						
	{
		frontp = NULL; 
		rearp = NULL;	
		for (int i = 1; i <= players; i++)		
		{
			QueueNode* temp;
			if (frontp == NULL)						
			{
				temp = new QueueNode;
				temp->pNumber = i;
				temp->pPosition = 0;
				frontp = temp;
				frontp->next = frontp;					
				rearp = frontp;
			}
			else									
			{
				temp = new QueueNode;
				temp->pNumber = i;
				temp->pPosition = 0;
				rearp->next = temp;
				temp->next = frontp;
				rearp = temp;
			}
		}
	}
	int front()
	{
		return frontp->pNumber;			
	}
	int back()
	{
		return rearp->pNumber;
	}
	QueueNode deQueue()					
	{

		QueueNode temp=*frontp;
		delete frontp;
		frontp = temp.next;
		rearp->next = frontp;
		return temp; 

	}
	void nextTurn()							
	{
		
		frontp  = frontp->next;

		rearp = rearp->next;
		return ;									

	}
	bool is_empty()
	{
		return (frontp == NULL);						
	}
	void reverseQueue()								
	{
		{
			return;
		}
		
	}
	QueueNode* queueHead()							
	{
		return frontp;
	}
};







struct StackNode	
{
	int dicenum;
	StackNode* next;									
};
class RollStack									
{
	StackNode* Top;
	
public:
	RollStack() 
	{
		Top = NULL;
	}

	void push_roll(int value) 
	{                     
		if (Top == NULL)
		{
			Top = new StackNode;
			Top->dicenum = value;
			Top->next = NULL;
		}
		else
		{
			StackNode* temp = new StackNode;
			temp->dicenum = value;
			temp->next = Top;
			Top = temp;
		}
	}
	int top()										
	{
		return Top->dicenum;
	}	

	int pop()										 
	{												
		int temproll = Top->dicenum;
		StackNode* temp = Top->next;
		delete Top;
		Top = temp;
		return temproll;
	}

	bool is_empty()									
	{
		return (Top==NULL);
	}

	void empty()									 
	{													
		while (!is_empty())
		{
			pop();
		}
	}
};





class Tile 
{
public:
	int number;
	Tile *next, *previous, *up, *down;

};


class Game {
	Queue turnQueue;								
	Tile* board_head;
	Tile* board_tail;
public:
	Game(const string& filename, int num_players):turnQueue(num_players)
	{		
		board_head = NULL;
		board_tail = NULL;
		for (int i = 1; i <= 100; i++)
		{
			if (i == 1)								

			{
				Tile* temp = new Tile;
				temp->number = i;
				temp->next = temp->down = temp->up = NULL;
				temp->previous = NULL;
				board_tail = temp;
				board_head = temp;
			}
			if (i > 10 && i % 10 == 1)				
			{
				Tile* temp = new Tile;
				temp->number = i;
				temp->up = temp->next = temp->previous = NULL;
				temp->down = board_tail;
				board_tail->up = temp;
				board_tail = temp;
			}
			if (i > 1 && i % 10 != 1)				
			{
				Tile* temp = new Tile;
				temp->number = i;
				temp->down = temp->up = temp->next = NULL;
				temp->previous = board_tail;
				board_tail->next = temp;
				board_tail = temp;
			}
		}
		ifstream ayesha;								
		ayesha.open(filename);
		string tile;
		int pos;

		while (ayesha.is_open() && !ayesha.eof())
		{
			ayesha >> tile;							

			if (tile == "S1" || tile == "S2")		
			{
				
				string copyTile = tile;
				pos = ayesha.tellg();
				int prev, next;
				ayesha.seekg(pos - 6);
				ayesha >> tile;
				prev = stoi(tile);
				ayesha.seekg(pos);
				ayesha >> tile;
				next = stoi(tile);
				int upNumber = (prev + next) / 2;	
			

				int downNumber = 0;
				ayesha.seekg(pos + 29);
				ayesha >> tile;
				if (tile == copyTile)
				{
					ayesha.seekg(pos + 32);
					ayesha>> tile;
					prev = stoi(tile);
					ayesha.seekg(pos + 26);
					ayesha>> tile;
					next = stoi(tile);
					downNumber = (prev + next) / 2;
				}
				ayesha.seekg(pos + 26);
				ayesha >> tile;
				if (tile == copyTile)
				{
					ayesha.seekg(pos + 29);
					ayesha >> tile;
					prev = stoi(tile);
					ayesha.seekg(pos + 32);
					ayesha>> tile;
					next = stoi(tile);
					downNumber = prev + (prev - next);
				}
				ayesha.seekg(pos + 32);
				ayesha>> tile;
				if (tile == copyTile)
				{
					ayesha.seekg(pos + 29);
					ayesha >> tile;
					prev = stoi(tile);
					ayesha.seekg(pos + 26);
					ayesha >> tile;
					next = stoi(tile);
					downNumber = prev + (prev - next);
				}
				if (upNumber > 0 && downNumber > 0)			
				{
					Tile* upTile = Game::GetTile(upNumber);
					Tile* downTile = Game::GetTile(downNumber);
					upTile->down = downTile;
					downTile->up = upTile;
				}
				ayesha.seekg(pos);
			}
			
			if (tile == "L1" || tile == "L2")				
			{
			
				string copyTile = tile;
				pos = ayesha.tellg();
				int prev, next;
				ayesha.seekg(pos - 6);
				ayesha >> tile;
				prev = stoi(tile);
				ayesha.seekg(pos);
				ayesha>> tile;
				next = stoi(tile);
				int upNumber = (prev + next) / 2;
				


				int downNumber = 0;
				ayesha.seekg(pos + 29);
				ayesha >> tile;
				if (tile == copyTile)
				{
					ayesha.seekg(pos + 32);
					ayesha>> tile;
					prev = stoi(tile);
					ayesha.seekg(pos + 26);
					ayesha >> tile;
					next = stoi(tile);
					downNumber = (prev + next) / 2;
				}
				ayesha.seekg(pos + 26);
				ayesha >> tile;
				if (tile == copyTile)
				{
					ayesha.seekg(pos + 29);
					ayesha >> tile;
					prev = stoi(tile);
					ayesha.seekg(pos + 32);
					ayesha >> tile;
					next = stoi(tile);
					downNumber = prev + (prev - next);
				}
				ayesha.seekg(pos + 32);
				ayesha >> tile;
				if (tile == copyTile)
				{
					ayesha.seekg(pos + 29);
					ayesha >> tile;
					prev = stoi(tile);
					ayesha.seekg(pos + 26);
					ayesha >> tile;
					next = stoi(tile);
					downNumber = prev + (prev - next);
				}
				if (upNumber > 0 && downNumber > 0)					
				{
					Tile* upTile = Game::GetTile(upNumber);
					Tile* downTile = Game::GetTile(downNumber);
					downTile->up = upTile;
					upTile->down = downTile;
				}
				ayesha.seekg(pos);
			}
			
			if (tile == "11")
			{
				break;
			}
		}
		ayesha.close();							
	}
	
	Queue& GetTurnQueue() {

		return turnQueue;
	}

	Tile* GetTile(int pos) {
		
		Tile* temp = board_head;
		for (int i = 1; i != pos; i++)
		{
			if (i % 10 == 0)					
			{
				temp = temp->up;
			}
			else
			{
				temp = temp->next;				
			}
		}
		return temp;
	}

	bool IsLadder(int pos)
	{


		Tile* temp = Game::GetTile(pos);		
		return (temp->up!=NULL);				
	}

	bool IsSnake(int pos) 
	{

		Tile* temp = Game::GetTile(pos);		
		return (temp->down!=NULL);			

	}
	
	int TraverseBoard(int current_pos, RollStack& stack) 
	{
		
		Tile* temp = Game::GetTile(current_pos);
		int totalsum = 0;
		while (!stack.is_empty())
		{
			totalsum += stack.pop();
		}
		for (int i = 1; i <= totalsum; i++)				
		{
			if ((temp->number) % 10 == 0)
			{
				temp = temp->up;
			}
			else
			{
				temp = temp->next;
			}
		}

		if (temp->up!=NULL)								
		{
			while (temp->up != NULL)
			{
				temp = temp->up;
			}
			return temp->number;						
		}

		if (temp->down != NULL)							
		{
			while (temp->down != NULL)
			{
				temp = temp->down;
			}
			return temp->number;						
		}

		return temp->number;							
	}

	void RollDice(int value)							
	{

		if (value == 6 && GetTurnQueue().queueHead()->pPosition == 0)		
		{
			GetTurnQueue().queueHead()->pPosition=1;						
			turnQueue.nextTurn();												
		}
		if (value % 3 == 0 && GetTurnQueue().queueHead()->pPosition != 0)	
		{
			GetTurnQueue().reverseQueue();									
		}
		return;
	}

	void Play() {																
	}

	~Game() {

	}
};


#endif
