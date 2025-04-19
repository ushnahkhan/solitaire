
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>


#define RED 12
#define RESET 7

using namespace std;
class DLL;
class Card
{
private:
	char* suit;
	char* colour;
	int rank;
	bool isup;

public:
	Card(const Card& c)
	{
		suit = new char[strlen(c.suit) + 1];
		strcpy_s(suit, strlen(c.suit) + 1, c.suit);
		colour = new char[strlen(c.colour) + 1];
		strcpy_s(colour, strlen(c.colour) + 1, c.colour);
		rank = c.rank;
		isup = c.isup;
	}
	Card()
	{
		suit = 0;
		colour = 0;
		rank = 0;
		isup = false;
	}
	Card& operator=(const Card& c)
	{
		if (this == &c)
			return *this;
		if (suit)
			delete[]suit;
		if (colour)
			delete[]colour;
		if (c.suit && c.colour)
		{
			suit = new char[strlen(c.suit) + 1];
			strcpy_s(suit, strlen(c.suit) + 1, c.suit);
			colour = new char[strlen(c.colour) + 1];
			strcpy_s(colour, strlen(c.colour) + 1, c.colour);
			rank = c.rank;
			isup = c.isup;
		}
		return*this;
	}
	Card(const char* s, const char* c, int r)
	{
		suit = new char[strlen(s) + 1];
		strcpy_s(suit, strlen(s) + 1, s);
		colour = new char[strlen(c) + 1];
		strcpy_s(colour, strlen(c) + 1, c);
		rank = r;
		isup = false;
	}
	bool IsValid()
	{
		if (suit && colour)
		{
			if ((((!(strcmp(suit, "Heart")) || !(strcmp(suit, "Diamond"))) && !(strcmp(colour, "Red"))) || ((!(strcmp(suit, "Spade")) || !(strcmp(suit, "Club"))) && !(strcmp(colour, "Black"))))
				&& (rank == 1 || rank == 2 || rank == 3 || rank == 4 || rank == 5 || rank == 6 || rank == 7
					|| rank == 8 || rank == 9 || rank == 10 || rank == 11 || rank == 12 || rank == 13))
				return true;
			return false;
		}
		return false;
	}
	bool CompareSuit(char*& s)
	{
		if (!(strcmp(s, suit)))
			return true;
		return false;
	}
	bool CheckRank(int r)
	{
		if (rank == r)
			return true;
		return false;
	}
	void flip()
	{
		isup = !isup;
	}
	void CopySuit(char*& s)
	{
		if (suit)
		{
			s = new char[strlen(suit) + 1];
			strcpy_s(s, strlen(suit) + 1, suit);
		}
	}
	bool Isflipped()
	{
		return isup;
	}
	bool IsCorrectSequenceInFoundation(Card& c)
	{
		if (c.IsValid())
		{
			if (!(strcmp(suit, c.suit)))
			{
				if (!(strcmp(colour, "Black")) || !(strcmp(c.colour, "Black")))
				{
					if (c.rank == rank + 1)
						return true;
					return false;
				}
				else if (!(strcmp(colour, "Red")) && !(strcmp(c.colour, "Red")))
				{
					if (c.rank == rank + 1)
						return true;
					return false;
				}
				return false;
			}
			return false;
		}
		return false;
	}
	bool IsCorrectSequenceInTableau(Card& c)
	{
		if (c.IsValid())
		{
			if (rank == c.rank + 1)
			{
				if (!(strcmp(colour, "Black")))
				{
					if (!(strcmp(c.colour, "Red")))
					{
						return true;
					}
					return false;
				}
				else if (!(strcmp(colour, "Red")))
				{
					if (!(strcmp(c.colour, "Black")))
					{
						return true;
					}
					return false;
				}
				return false;
			}
			return false;
		}
		return false;
	}
	void Print()
	{
		if (IsValid())
		{
			if (isup)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				if (!(strcmp(suit, "Heart")) || !(strcmp(suit, "Diamond")))
				{
					SetConsoleTextAttribute(hConsole, RED);
				}

				if (!strcmp(suit, "Spade"))
					cout << "\u2660";
				else if (!strcmp(suit, "Heart"))
					cout << "\u2665";
				else if (!strcmp(suit, "Club"))
					cout << "\u2663";
				else if (!strcmp(suit, "Diamond"))
					cout << "\u2666";
				if (rank == 1)
					cout << " A ";
				else if (rank == 11)
					cout << " J ";
				else if (rank == 12)
					cout << " Q ";
				else if (rank == 13)
					cout << " K ";
				else

					cout << " " << rank << " ";
				SetConsoleTextAttribute(hConsole, RESET);
			}
			else
			{
				cout << "[ ]";
			}
		}
	}
	bool IsKing()
	{
		if (IsValid())
		{
			if (rank == 13)
				return true;
			return false;
		}
		return false;
	}
	~Card()
	{
		if (suit)
			delete[]suit;
		if (colour)
			delete[]colour;
	}
};

class DLL
{
private:
	struct Node
	{
	public:
		Node* next;
		Node* prev;
		Card data;
		Node(const Card& d, Node* p = 0, Node* n = 0) :data(d)
		{
			prev = p;
			next = n;
		}
		~Node()
		{
			next = 0;
			prev = 0;
		}
	};
	Node* head;
	Node* tail;
	class Listiterator
	{
		Node* current;
	public:
		Listiterator(Node* c = 0)
		{
			current = c;
		}
		Listiterator& operator++()
		{
			if (current)
				current = current->next;
			return (*this);
		}
		Listiterator operator++(int)
		{
			Listiterator temp(current);
			if (current)
				current = current->next;
			return temp;
		}
		bool IsNull()
		{
			if (!current)
				return true;
			return false;
		}
		Listiterator& operator--()
		{
			if (current)
				current = current->prev;
			return (*this);
		}
		Listiterator operator--(int)
		{
			Listiterator temp(current);
			if (current)
			{
				current = current->prev;
			}
			return temp;
		}
		Card& operator*()
		{
			if (current)
				return current->data;
		}
		bool operator==(const Listiterator& l) const
		{
			return current == l.current;
		}
		bool operator!=(const Listiterator& l)const
		{
			return current != l.current;
		}
		~Listiterator()
		{
			current = 0;
		}
	};
	int columnno;
	int size;
public:
	typedef Listiterator Iterator;
	DLL(int s = 0)
	{
		head = tail = 0;
		columnno = s;
		size = 0;
	}
	Iterator begin() const
	{
		Iterator i(head);
		return i;
	}
	Iterator end() const
	{
		Iterator i(tail);
		return i;
	}
	bool AddList(Node* ptr, bool undo = false)
	{
		if (head)
		{
			if (ptr)
			{
				Node* ptr1 = ptr;
				Node* ptr2 = tail;
				bool flag = false;
				if (tail->data.IsCorrectSequenceInTableau(ptr->data))
				{
					if (ptr->data.Isflipped())
						flag = true;
				}
				if (undo)
				{
					if (!tail->data.IsCorrectSequenceInTableau(ptr->data))
					{
						tail->data.flip();
					}
				}
				if (flag || undo)
				{
					if (ptr->data.Isflipped())
					{
						int c = 1;
						tail->next = ptr;
						ptr->prev = tail;
						while (ptr->next)
						{
							ptr = ptr->next;
							c++;
						}
						tail = ptr;
						size += c;
						return true;
					}
					return false;
				}
				return false;
			}
			return false;
		}
		else
		{
			if (ptr->data.Isflipped())
			{
				head = ptr;
				int c = 1;
				while (ptr->next)
				{
					if (!ptr->data.Isflipped())
						return false;
					ptr = ptr->next;
					c++;
				}
				tail = ptr;
				size += c;
				return true;
			}
		}
		return false;
	}

	int GetNo()
	{
		return columnno;
	}
	Node* RemoveList(int n, bool undo = false)
	{
		if (head)
		{
			Node* ptr = tail;
			for (int i = 0;i < n - 1 && ptr;i++)
			{
				if (ptr)
					ptr = ptr->prev;
			}
			if (ptr)
			{
				if (ptr != head)
				{
					if (ptr->prev)
					{
						if (undo)
						{
							if (!ptr->prev->data.IsCorrectSequenceInTableau(ptr->data) && ptr->prev->data.Isflipped())
								ptr->prev->data.flip();
						}
						else
						{
							if (!ptr->prev->data.Isflipped())
								ptr->prev->data.flip();
						}
						size -= n;
						ptr->prev->next = 0;
						tail = ptr->prev;
						tail->next = 0;
						ptr->prev = 0;
					}
				}
				else
				{
					size -= n;
					head = tail = 0;
				}
			}

			return ptr;
		}
		return 0;
	}
	int Getsize()
	{
		return size;
	}
	bool MatchList(const DLL& l, int n, bool undo)
	{
		if (head)
		{
			Node* ptr = l.tail;
			for (int i = 0;i < n - 1 && ptr && ptr->data.Isflipped();i++)
			{
				if (ptr)
					ptr = ptr->prev;
			}
			if (ptr)
			{
				if (ptr->data.Isflipped() && !undo)
				{
					if (tail && tail->data.IsCorrectSequenceInTableau(ptr->data))
						return true;
				}
				else if (undo)
				{
					if (tail)
					{
						if (ptr->data.Isflipped())
						{
							return true;
						}
					}
				}
				return false;
			}
			return false;
		}
		else
		{
			Node* ptr = l.tail;
			for (int i = 0;i < n - 1 && ptr;i++)
			{
				if (ptr)
					ptr = ptr->prev;
			}
			if (ptr)
			{
				if (ptr->data.IsKing() && ptr->data.Isflipped() && !undo)
					return true;
				if (undo)
				{
					return true;
				}
			}
			return false;
		}
		return false;
	}
	void FlipLastNode()
	{
		if (tail)
			tail->data.flip();
	}
	void FlipSecondLastNode()
	{
		if (tail)
		{
			if (tail->prev)
				tail->prev->data.flip();
		}
	}
	void PrintSize()
	{
		cout << "(" << size << " cards)\t";
	}
	bool AddNode(Card& c, bool undo = false)
	{
		if (head && !undo)
		{
			if (tail->data.IsCorrectSequenceInTableau(c))
			{
				if (c.Isflipped())
				{
					tail->next = new Node(c, tail, tail->next);
					tail = tail->next;
					size++;
					return true;
				}
			}
			return false;
		}
		else if (head && undo)
		{
			if (c.Isflipped())
			{
				tail->next = new Node(c, tail, tail->next);
				tail = tail->next;
				size++;
				return true;
			}
		}
		else if (!head && !undo)
		{
			if (c.IsKing() && c.Isflipped())
			{
				head = tail = new Node(c, 0, 0);
				size++;
				return true;
			}
			return false;
		}
		else if (!head && undo)
		{
			if (c.IsValid() && c.Isflipped())
			{
				head = tail = new Node(c, 0, 0);
				size++;
				return true;
			}
		}
		return false;
	}

	void InitialiseTableau(const Card& c)
	{
		if (head)
		{
			tail->next = new Node(c, tail, 0);
			size++;
			tail = tail->next;
		}
		else
		{
			head = tail = new Node(c, 0, 0);
			size++;
		}
	}
	bool GetLastNode(Card& c)
	{
		if (tail)
		{
			c = tail->data;
			return true;
		}
		return false;
	}
	bool GetSecondLastNode(Card& c)
	{
		if (tail->prev)
		{
			c = tail->prev->data;
			return true;
		}
		return false;
	}
	bool RemoveNode(bool undo = false)
	{
		if (head)
		{
			if (head != tail && !undo)
			{
				Node* ptr = tail;
				tail = tail->prev;
				tail->next = 0;
				size--;
				if (tail)
				{
					if (!tail->data.Isflipped())
					{
						tail->data.flip();
					}
				}
				delete ptr;

			}
			else if (head != tail && undo)
			{
				Node* ptr = tail;
				tail = tail->prev;
				tail->next = 0;
				size--;
				delete ptr;
			}
			else
			{
				size--;
				delete tail;
				head = tail = 0;
			}
			return true;
		}
		return false;
	}

	bool IsEmpty()
	{
		if (!head)
			return true;
		return false;
	}
	~DLL()
	{
		if (head)
		{
			Node* ptr = head;
			while (ptr)
			{
				head = head->next;
				delete ptr;
				ptr = head;
			}
		}
	}
};
class Stack
{
private:
	class Node
	{
	public:
		Card data;
		Node* next;
		Node(const Card& d, Node* n = 0) :data(d)
		{
			next = n;
		}
		~Node()
		{
			next = 0;
		}
	};
	Node* top;
protected:
	int capacity;
	int occupied;
public:
	Stack(int c = 0)
	{
		capacity = c;
		occupied = 0;
		top = 0;
	}
	void Setcapacity(int c)
	{
		capacity = c;
	}
	void MoveWaste(Card& c)
	{
		c.flip();
		Push(c);
	}
	int Getoccupied()
	{
		return occupied;
	}
	virtual void Print()
	{
		if (!IsEmpty())
		{
			if (top->data.Isflipped())
				top->data.Print();
			cout << "\t\t\t\t";
		}
		else
		{
			cout << "[  ]\t\t\t\t";
		}
	}
	virtual void PrintNumbers()
	{
		cout << "(" << occupied << " cards)";
	}
	virtual ~Stack()
	{
		if (top)
		{
			Node* ptr = top;
			while (ptr)
			{
				top = top->next;
				delete ptr;
				ptr = top;
			}
		}
	}
	bool Push(Card& val)
	{
		if (IsFull())
		{
			return false;
		}
		else if (!top)
		{
			top = new Node(val);
			occupied++;
			return true;
		}
		else
		{

			top = new Node(val, top);
			occupied++;
			return true;
		}
	}
	bool Pop()
	{
		if (IsEmpty())
		{
			return false;
		}
		else
		{
			Node* ptr = top;
			top = top->next;
			occupied--;
			delete ptr;
			return true;
		}
	}
	bool Top(Card& c)
	{
		if (IsEmpty())
		{
			return false;
		}
		else if (top)
		{
			c = top->data;
			return true;
		}
		return false;
	}
	bool IsEmpty()
	{
		if (occupied == 0)
			return true;
		return false;
	}
	bool IsFull()
	{
		if (capacity == occupied)
			return true;
		return false;
	}
	void SwapIndex(int a, int b)
	{
		if (a > b)
			swap(a, b);
		if (a == 0 && b == capacity - 1)
		{
			Node* ptr = top;
			for (int i = 0;i < capacity - 2;i++)
			{
				if (ptr)
					ptr = ptr->next;
			}
			if (ptr)
			{
				if (ptr->next)
				{
					Node* temp = ptr->next;
					ptr->next = top;
					ptr->next->next = 0;
					temp->next = top->next;
					top = temp;

				}
			}
		}
		else if (b - a == 1)
		{
			if (a > 0)
			{
				Node* ptr = top;
				for (int i = 0;i < a - 1;i++)
				{
					if (ptr)
						ptr = ptr->next;
				}
				Node* ptr2 = top;
				for (int i = 0;i < b - 1;i++)
				{
					if (ptr2)
						ptr2 = ptr2->next;
				}
				if (ptr && ptr2)
				{
					if (ptr->next && ptr2->next)
					{
						ptr->next = ptr2->next;
						Node* temp = ptr2->next->next;
						ptr2->next->next = ptr2;
						ptr2->next = temp;
					}
				}
			}
			else if (a == 0)
			{
				Node* temp = top->next;
				top->next = temp->next;
				temp->next = top;
				top = temp;
			}
		}
		else if (a == 0)
		{
			Node* ptr = top;
			for (int i = 0;i < b - 1;i++)
			{
				if (ptr)
					ptr = ptr->next;
			}
			if (ptr)
			{
				if (ptr->next)
				{
					Node* temp = top->next;
					top->next = ptr->next->next;
					ptr->next->next = temp;
					temp = top;
					top = ptr->next;
					ptr->next = temp;
				}
			}

		}
		else
		{
			Node* ptr = top;
			for (int i = 0;i < a - 1;i++)
			{
				if (ptr)
					ptr = ptr->next;
			}
			Node* ptr2 = top;
			for (int i = 0;i < b - 1;i++)
			{
				if (ptr2)
					ptr2 = ptr2->next;
			}
			if (ptr && ptr2)
			{
				if (ptr2->next && ptr->next)
				{
					Node* temp = ptr->next;
					ptr->next = ptr2->next;
					ptr2->next = temp;
					temp = ptr->next->next;
					ptr->next->next = ptr2->next->next;
					ptr2->next->next = temp;
				}
			}
		}

	}

};
class Stock :public Stack
{
public:
	Stock() :Stack(52)
	{

		for (int i = 1;i <= 13;i++)
		{
			Card c("Heart", "Red", i);
			if (c.IsValid())
				Push(c);
		}
		for (int i = 1;i <= 13;i++)
		{
			Card c("Diamond", "Red", i);
			if (c.IsValid())
				Push(c);
		}
		for (int i = 1;i <= 13;i++)
		{
			Card c("Club", "Black", i);
			if (c.IsValid())
				Push(c);
		}
		for (int i = 1;i <= 13;i++)
		{
			Card c("Spade", "Black", i);
			if (c.IsValid())
				Push(c);
		}
	}
	int GetOccupied()
	{
		return occupied;
	}
	void Print()
	{
		cout << "[  ]";
	}
	void PrintNumber()
	{
		cout << "(" << occupied << " cards)";
	}
	~Stock()
	{

	}
	void Shuffle()
	{
		srand(time(0));
		for (int i = 0;i < capacity;i++)
		{
			int a = rand() % 52;
			int b = rand() % 52;
			SwapIndex(a, b);
		}
	}
	void Distribute(DLL** tableaus, int n)
	{
		for (int i = 0;i < n;i++)
		{
			for (int j = 0;j < tableaus[i]->GetNo();j++)
			{
				if (occupied > 0)
				{
					Card c;
					if (Top(c))
					{
						if (c.IsValid())
						{
							tableaus[i]->InitialiseTableau(c);
							Pop();
						}
					}
				}
			}
			tableaus[i]->FlipLastNode();
		}
	}
};
class Foundation : public Stack
{
	char* suit;
public:
	Foundation() :Stack(13)
	{
		suit = 0;
	}
	bool AddCard(Card& c)
	{
		if (suit)
		{
			if (c.CompareSuit(suit))
			{
				Card c1;
				if (Top(c1))
				{
					if (c1.IsCorrectSequenceInFoundation(c))
					{
						Push(c);
						return true;
					}
					return false;
				}
				return false;
			}
			return false;
		}
		else
		{
			if (c.CheckRank(1))
			{
				c.CopySuit(suit);
				Push(c);
				return true;
			}
			return false;
		}
		return false;
	}
	void Print()
	{
		if (occupied > 0)
		{
			Card c;
			if (Top(c))
			{
				if (c.IsValid())
					c.Print();
			}
		}
		else
		{
			cout << "[  ]";
		}
	}
	void PrintNumber()
	{
		cout << "(" << occupied << " cards)";
	}
	bool CheckComplete()
	{
		if (occupied > 0)
		{
			Card c;
			if (Top(c))
			{
				if (c.IsValid())
				{
					if (c.IsKing() && IsFull())
						return true;
				}
				return false;
			}
			return false;
		}
		return false;
	}
	void deletesuit()
	{
		if (suit)
		{
			delete[]suit;
			suit = 0;
		}

	}
	~Foundation()
	{
		if (suit)
			delete suit;
	}
};
class Game;
class Command
{
	friend class Game;
private:
	char instruction;
	class operand
	{
	public:
		char a;
		int no;
		operand(char b = 0, int n = 0)
		{
			a = b;
			no = n;
		}
		bool IsValid()
		{
			if (a == 'c')
			{
				if (no > 0 && no < 8)
					return true;
				return false;
			}
			else if (a == 'w')
			{
				if (no == 0)
					return true;
				return false;
			}
			return false;
		}
	};
	operand op1;
	operand op2;
	int num;
public:
	Command(char a = 0, char b = 0, int c = 0, char d = 0, int e = 0, int n = 0) :op1(b, c), op2(d, e)
	{
		instruction = a;
		num = n;
	}
	bool CheckIfop1IsColumn()
	{
		if (op1.a == 'c')
			return true;
		return false;
	}
	bool CheckIfop2IsColumn()
	{
		if (op2.a == 'c')
			return true;
		return false;
	}
	bool CheckIfop1IsFoundation()
	{
		if (op1.a == 'f')
			return true;
		return false;
	}
	bool CheckIfop2IsFoundation()
	{
		if (op2.a == 'f')
			return true;
		return false;
	}
	bool CheckIfop1IsWaste()
	{
		if (op1.a == 'w')
			return true;
		return false;
	}
	bool CheckIfop2IsWaste()
	{
		if (op2.a == 'w')
			return true;
		return false;
	}
	bool CheckIfUndo()
	{
		if (instruction == 'z')
			return true;
		return false;
	}
	bool CheckIfQuit()
	{
		if (instruction == 'q')
			return true;
		return false;
	}
	bool CheckIfDraw()
	{
		if (instruction == 's')
			return true;
		return false;
	}
	bool CheckIfMove()
	{
		if (instruction == 'm')
			return true;
		return false;
	}
	int Getop1num()
	{
		return op1.no;
	}
	int Getop2num()
	{
		return op2.no;
	}
	int Getnum()
	{
		return num;
	}
	Command ReversedCommand()
	{
		Command c(instruction, op2.a, op2.no, op1.a, op1.no, num);
		return c;
	}
	bool IsValid()
	{
		if (instruction == 'm')
		{
			if (op1.IsValid() && op2.IsValid() && num < 53 && num>0)
				return true;
			return false;
		}
		else if (instruction == 'z' || instruction == 's')
			return true;
		return false;
	}
};
class CommandStack
{
	class Node
	{
	public:
		Command data;
		Node* next;
		Node(const Command& d, Node* n = 0) :data(d)
		{
			next = n;
		}
		~Node()
		{
			next = 0;
		}
	};
	Node* top;
	int size;
public:
	CommandStack()
	{
		top = 0;
		size = 0;
	}
	~CommandStack()
	{
		if (top)
		{
			while (top)
			{
				Node* ptr = top;
				top = top->next;
				delete ptr;
			}
		}
	}
	void Push(Command& c)
	{
		if (top)
		{
			top = new Node(c, top);
			size++;
		}
		else
		{
			top = new Node(c, 0);
			size++;
		}

	}
	bool Pop(Command& c)
	{
		if (size > 0 && top)
		{
			c = top->data;
			Node* ptr = top;
			top = top->next;
			delete ptr;
			size--;
			return true;
		}
		return false;
	}
};

class Game
{
	DLL** Tableaus;
	Foundation* foundations;
	Stock stock;
	Stack waste;
	CommandStack commands;
public:
	Game() :waste(stock.GetOccupied())
	{
		Tableaus = new DLL * [7];
		for (int i = 1;i <= 7;i++)
		{
			Tableaus[i - 1] = new DLL(i);
		}
		foundations = new Foundation[4];
		stock.Shuffle();
		stock.Distribute(Tableaus, 7);
	}
	void Print()
	{
		cout << "Stock\t\tWaste\t\t\t\tFoundation1\tFoundation2\tFoundation3\tFoundation4\n";
		stock.Print();
		cout << "\t\t";
		waste.Print();
		for (int i = 0;i < 4;i++)
		{
			foundations[i].Print();
			cout << "\t\t";
		}
		cout << endl;
		stock.PrintNumbers();
		cout << "\t";
		waste.PrintNumbers();
		cout << "\t\t\t";
		for (int i = 0;i < 4;i++)
		{
			foundations[i].PrintNumbers();
			cout << "\t";
		}
		cout << endl << endl;
		cout << "Tableau1\tTableau2\tTableau3\tTableau4\tTableau5\tTableau6\tTableau7\n";
		DLL::Iterator it1 = Tableaus[0]->begin();
		DLL::Iterator it2 = Tableaus[1]->begin();
		DLL::Iterator it3 = Tableaus[2]->begin();
		DLL::Iterator it4 = Tableaus[3]->begin();
		DLL::Iterator it5 = Tableaus[4]->begin();
		DLL::Iterator it6 = Tableaus[5]->begin();
		DLL::Iterator it7 = Tableaus[6]->begin();
		for (int i = 0;i < 7;i++)
		{
			Tableaus[i]->PrintSize();
		}
		cout << endl;
		while (!it1.IsNull() || !it2.IsNull() || !it3.IsNull()
			|| !it4.IsNull() || !it5.IsNull() || !it6.IsNull() || !it7.IsNull())
		{
			PrintByIterator(it1);
			PrintByIterator(it2);
			PrintByIterator(it3);
			PrintByIterator(it4);
			PrintByIterator(it5);
			PrintByIterator(it6);
			PrintByIterator(it7);
			cout << endl;
		}
		for (int i = 0;i < 13;i++)
			cout << endl;
	}
	void PrintByIterator(DLL::Iterator& it)
	{
		if (!it.IsNull())
		{
			(*it).Print();
			it++;
			cout << "\t\t ";
		}
		else
		{
			cout << "\t\t ";
		}
	}

	bool CheckCommand(char* s, char& inst, char& st1, char& st2, int& no1, int& no2, int& num)
	{
		int i = 0;
		bool flag = true;
		while (flag && i < strlen(s))
		{
			if (s[i] == 'm')
			{
				inst = s[i];
				i++;
				while (s[i] == ' ')
					i++;
				if (s[i] == 'c')
				{
					st1 = s[i];
					i++;
					if (s[i] >= '1' && s[i] <= '7')
					{
						no1 = s[i] - 48;
						i++;
						if (s[i] == ',')
						{
							i++;
							if (s[i] == 'c')
							{
								st2 = s[i];
								i++;
								if (s[i] >= '1' && s[i] <= '7')
								{
									no2 = s[i] - 48;
									i++;
									if (s[i] == ',')
									{
										i++;
										if (s[i] >= '1' && s[i] <= '9' && s[i] != 0)
										{
											num = s[i] - 48;
											i++;
											if (s[i] >= '1' && s[i] <= '9' && s[i] != 0)
											{
												num = num * 10;
												num += s[i] - 48;
												i++;
												if (s[i] != 0)
													flag = false;
											}
											else if (s[i] != 0)
												flag = false;
										}
										else
										{
											flag = false;
										}
									}
									else
									{
										flag = false;
									}
								}
								else
								{
									flag = false;
								}
							}
							else if (s[i] == 'f')
							{
								st2 = s[i];
								i++;
								if (s[i] >= '1' && s[i] <= '4')
								{
									no2 = s[i] - 48;
									i++;
									if (s[i] == ',')
									{
										i++;
										if (s[i] == '1')
										{
											num = s[i] - 48;
											i++;
											if (s[i] != 0)
												flag = false;
										}
										else
										{
											flag = false;
										}
									}
									else
									{
										flag = false;
									}
								}
								else
									flag = false;
							}
							else
								flag = false;
						}
						else
						{
							flag = false;
						}
					}
					else
						flag = false;
				}
				else if (s[i] == 'w')
				{
					st1 = s[i];
					no1 = 0;
					i++;
					if (s[i] == ' ')
					{
						i++;
						while (s[i] == ' ')
							i++;
						if (s[i] == 'c')
						{
							st2 = s[i];
							i++;
							if (s[i] >= '1' && s[i] <= '7')
							{
								no2 = s[i] - 48;
								i++;
								if (s[i] == ',')
								{
									i++;
									if (s[i] >= '1' && s[i] <= '9' && s[i] != 0)
									{
										num = s[i] - 48;
										i++;
										if (s[i] != 0)
											flag = false;
									}
									else
									{
										flag = false;
									}
								}
								else
								{
									flag = false;
								}
							}
							else
							{
								flag = false;
							}
						}
						else if (s[i] == 'f')
						{
							st2 = s[i];
							i++;
							if (s[i] >= '1' && s[i] <= '4')
							{
								no2 = s[i] - 48;
								i++;
								if (s[i] == ',')
								{
									i++;
									if (s[i] >= '1' && s[i] <= '9' && s[i] != 0)
									{
										num = s[i] - 48;
										i++;
										if (s[i] != 0)
											flag = false;
									}
									else
									{
										flag = false;
									}
								}
								else
								{
									flag = false;
								}
							}
							else
							{
								flag = false;
							}
						}
						else
						{
							flag = false;
						}

					}
					else
					{
						flag = false;
					}
				}
				else
				{
					flag = false;
				}

			}
			else if (s[i] == 'z')
			{
				inst = s[i];
				i++;
				if (s[i] != 0)
					flag = false;
			}
			else if (s[i] == 's')
			{
				inst = s[i];
				i++;
				if (s[i] != 0)
					flag = false;
			}
			else if (s[i] == 'q')
			{
				inst = s[i];
				i++;
				if (s[i] != 0)
					flag = false;
			}
			else
			{
				return false;
			}
		}
		return flag;
	}
	bool IsFinished()
	{
		Command c;
		if (commands.Pop(c))
		{
			if (c.CheckIfQuit())
				return true;
			else
				commands.Push(c);
		}
		bool foundflag = true;
		for (int i = 0;i < 4 && foundflag;i++)
		{
			if (!foundations[i].CheckComplete())
				foundflag = false;
		}
		if (!foundflag)
		{
			bool flag = true;
			if (stock.IsEmpty() && waste.IsEmpty())
			{
				for (int i = 0;i < 7 && flag;i++)
				{
					for (int j = 0;j < 4 && flag;j++)
					{
						Card c;
						if (foundations[j].Top(c))
						{
							if (c.IsValid())
							{
								Card t;
								if (Tableaus[i]->GetLastNode(t) && !Tableaus[i]->IsEmpty())
								{
									if (t.IsValid() && t.Isflipped())
									{
										if (c.IsCorrectSequenceInFoundation(t))
											flag = false;
									}
								}
							}
						}
					}
				}
				for (int i = 0;i < 7 && flag;i++)
				{
					for (int j = 0;j < 7 && flag;j++)
					{
						Card c;
						if (Tableaus[i]->GetLastNode(c) && c.Isflipped() && c.IsValid())
						{
							Card c2;
							if (Tableaus[j]->GetLastNode(c2) && c2.Isflipped() && c2.IsValid())
							{
								if (c2.IsCorrectSequenceInTableau(c))
								{
									flag = false;
								}
							}
						}
					}
				}
			}
			else if (!waste.IsEmpty())
			{
				for (int i = 0;i < 7 && flag;i++)
				{
					for (int j = 0;j < 4 && flag;j++)
					{
						Card c;
						if (foundations[j].Top(c))
						{
							if (c.IsValid())
							{
								Card t;
								if (Tableaus[i]->GetLastNode(t) && !Tableaus[i]->IsEmpty())
								{
									if (t.IsValid())
									{
										if (c.IsCorrectSequenceInFoundation(t))
											flag = false;
									}
								}
							}
						}
					}
					if (flag)
					{
						for (int i = 0;i < 7 && flag;i++)
						{
							for (int j = 0;j < 7 && flag;j++)
							{
								Card c;
								if (Tableaus[i]->GetLastNode(c) && c.Isflipped() && c.IsValid())
								{
									Card c2;
									if (Tableaus[j]->GetLastNode(c2) && c2.Isflipped() && c2.IsValid())
									{
										if (c2.IsCorrectSequenceInTableau(c))
										{
											flag = false;
										}
									}
								}
							}
						}
					}
				}
				if (flag)
				{
					for (int j = 0;j < 4 && flag;j++)
					{
						Card c1, c2;
						if (waste.Top(c1))
						{
							if (foundations[j].Top(c2))
							{
								if (c1.IsValid() && c2.IsValid())
								{
									if (c2.IsCorrectSequenceInFoundation(c1))
										flag = false;
								}
							}
							else if (c1.CheckRank(1))
							{
								flag = false;
							}
						}
					}
					if (flag)
					{
						for (int j = 0;j < 7 && flag;j++)
						{
							Card c1, c2;
							if (waste.Top(c1))
							{
								if (Tableaus[j]->GetLastNode(c2) && !Tableaus[j]->IsEmpty())
								{
									if (c1.IsValid() && c2.IsValid())
									{
										if (c2.IsCorrectSequenceInTableau(c1))
											flag = false;
									}
								}
								else if (Tableaus[j]->IsEmpty() && c1.IsKing())
									flag = false;
							}
						}
					}

				}
			}
			if (stock.IsEmpty())
			{
				for (int i = 0;i < 7 && flag;i++)
				{
					for (int j = 0;j < 7 && flag;j++)
					{
						Card c;
						if (Tableaus[i]->GetLastNode(c) && c.Isflipped() && c.IsValid())
						{
							Card c2;
							if (Tableaus[j]->GetLastNode(c2) && c2.Isflipped() && c2.IsValid())
							{
								if (c2.IsCorrectSequenceInTableau(c))
								{
									flag = false;
								}
							}
						}
					}
				}
				if (flag)
				{
					Stack newwaste(waste.Getoccupied());
					int j = waste.Getoccupied();
					for (int i = 0;i < j;i++)
					{
						Card c;
						waste.Top(c);
						waste.Pop();
						newwaste.Push(c);
					}
					while (!newwaste.IsEmpty() && flag)
					{
						for (int j = 0;j < 7 && flag;j++)
						{
							Card c1, c2;
							if (newwaste.Top(c1))
							{
								if (Tableaus[j]->GetLastNode(c2) && !Tableaus[j]->IsEmpty())
								{
									if (c1.IsValid() && c2.IsValid())
									{
										if (c2.IsCorrectSequenceInTableau(c1))
										{
											flag = false;
										}
									}
								}
								else if (Tableaus[j]->IsEmpty() && c1.IsKing())
									flag = false;
							}
						}
						Card c1;
						newwaste.Top(c1);
						newwaste.Pop();
						waste.Push(c1);
					}
					if (!newwaste.IsEmpty())
					{
						while (!newwaste.IsEmpty())
						{
							Card c1;
							newwaste.Top(c1);
							newwaste.Pop();
							waste.Push(c1);
						}
					}
					if (flag)
					{
						Stack newwaste(waste.Getoccupied());
						int j = waste.Getoccupied();
						for (int i = 0;i < j;i++)
						{
							Card c;
							waste.Top(c);
							waste.Pop();
							newwaste.Push(c);
						}
						while (!newwaste.IsEmpty() && flag)
						{
							for (int j = 0;j < 4 && flag;j++)
							{
								Card c1, c2;
								if (newwaste.Top(c1))
								{
									if (foundations[j].Top(c2))
									{
										if (c1.IsValid() && c2.IsValid())
										{
											if (c2.IsCorrectSequenceInFoundation(c1))
												flag = false;
										}
									}
									else if (c1.CheckRank(1))
									{
										flag = false;
									}
								}
							}
							Card c1;
							newwaste.Top(c1);
							newwaste.Pop();
							waste.Push(c1);
						}
						if (!newwaste.IsEmpty())
						{
							while (!newwaste.IsEmpty())
							{
								Card c1;
								newwaste.Top(c1);
								newwaste.Pop();
								waste.Push(c1);
							}
						}
					}
				}
			}
			if (!stock.IsEmpty() && flag)
			{

				flag = false;
			}
			return flag;
		}
		else
		{
			cout << "\n\nYOU WON!!\n\n";
		}
		return true;
	}
	bool ExecuteCommand(Command& c, bool undo = false)
	{
		if (c.CheckIfMove())
		{
			if (c.CheckIfop1IsWaste())
			{
				if (!waste.IsEmpty())
				{
					if (c.CheckIfop2IsColumn())
					{
						if (c.Getnum() == 1)
						{
							Card t;

							if (waste.Top(t))
							{
								if (t.IsValid())
								{
									if (Tableaus[c.Getop2num() - 1]->AddNode(t, undo))
									{
										waste.Pop();
										if (!undo)
											commands.Push(c);
										return true;
									}
									return false;
								}
								return false;
							}
							return false;
						}
						return false;
					}
					else if (c.CheckIfop2IsFoundation())
					{
						if (c.Getnum() == 1)
						{
							Card t;
							if (waste.Top(t))
							{
								if (t.IsValid())
								{
									if (foundations[c.Getop2num() - 1].AddCard(t))
									{
										waste.Pop();
										if (!undo)
											commands.Push(c);
										return true;
									}
									return false;
								}
								return false;
							}
							return false;
						}
						return false;
					}
					return false;
				}
				else
				{
					cout << "\nCommand can not be executed!\n";
					return false;
				}
			}
			else if (c.CheckIfop1IsColumn())
			{
				if (c.CheckIfop2IsColumn())
				{
					if (c.Getnum() == 1 && !undo)
					{
						Card t;
						if (Tableaus[c.Getop1num() - 1]->GetLastNode(t))
						{
							if (t.IsValid() && t.Isflipped())
							{
								Card t1;
								if (Tableaus[c.Getop2num() - 1]->GetLastNode(t1))
								{
									if (t1.IsValid() && t1.IsCorrectSequenceInTableau(t))
									{
										if (Tableaus[c.Getop2num() - 1]->AddNode(t, undo))
										{
											Card t2;
											if (Tableaus[c.Getop1num() - 1]->GetSecondLastNode(t2))
											{
												if (!t2.Isflipped())
													Tableaus[c.Getop1num() - 1]->FlipSecondLastNode();
											}
											Tableaus[c.Getop1num() - 1]->RemoveNode(undo);
											commands.Push(c);
											return true;
										}
										return false;
									}
									return false;
								}
								else if (t.IsKing() && Tableaus[c.Getop2num() - 1]->IsEmpty())
								{
									if (Tableaus[c.Getop2num() - 1]->AddNode(t, undo))
									{
										Tableaus[c.Getop1num() - 1]->RemoveNode(undo);
										commands.Push(c);
										return true;
									}
									return false;
								}
								return false;
							}
							return false;
						}
						return false;
					}
					else if (c.Getnum() > 1 && !undo)
					{
						if (Tableaus[c.Getop2num() - 1]->MatchList(*Tableaus[c.Getop1num() - 1], c.Getnum(), undo))
						{
							Tableaus[c.Getop2num() - 1]->AddList(Tableaus[c.Getop1num() - 1]->RemoveList(c.Getnum(), undo), undo);
							commands.Push(c);
							return true;
						}
						return false;
					}
					else if (c.Getnum() == 1 && undo)
					{
						Card t;
						if (Tableaus[c.Getop1num() - 1]->GetLastNode(t))
						{
							if (t.IsValid())
							{
								Card t1;
								if (Tableaus[c.Getop2num() - 1]->GetLastNode(t1))
								{
									if (t1.IsCorrectSequenceInTableau(t))
									{
										if (Tableaus[c.Getop2num() - 1]->AddNode(t, undo))
										{
											Tableaus[c.Getop1num() - 1]->RemoveNode(undo);
											return true;
										}
										return false;
									}
									else
									{

										if (Tableaus[c.Getop2num() - 1]->AddNode(t, undo))
										{
											Card t2;
											if (Tableaus[c.Getop2num() - 1]->GetSecondLastNode(t2))
											{
												if (t2.Isflipped())
													Tableaus[c.Getop2num() - 1]->FlipSecondLastNode();
												if (Tableaus[c.Getop1num() - 1]->GetSecondLastNode(t2))
												{
													if (t2.Isflipped())
													{
														if (!t2.IsCorrectSequenceInTableau(t))
															Tableaus[c.Getop1num() - 1]->FlipSecondLastNode();
													}
												}
											}
											Tableaus[c.Getop1num() - 1]->RemoveNode(undo);
											return true;
										}
										return false;
									}
								}
								else if (Tableaus[c.Getop2num() - 1]->IsEmpty())
								{
									if (Tableaus[c.Getop2num() - 1]->AddNode(t, undo))
									{
										Tableaus[c.Getop1num() - 1]->RemoveNode(undo);
										return true;
									}
									return false;
								}
								return false;
							}
							return false;
						}
						return false;
					}
					else if (c.Getnum() > 1 && undo)
					{
						if (!Tableaus[c.Getop2num() - 1]->IsEmpty())
						{
							if (Tableaus[c.Getop2num() - 1]->MatchList(*Tableaus[c.Getop1num() - 1], c.Getnum(), undo))
							{
								Tableaus[c.Getop2num() - 1]->AddList(Tableaus[c.Getop1num() - 1]->RemoveList(c.Getnum(), undo), undo);
								return true;
							}
						}
						else
						{
							Tableaus[c.Getop2num() - 1]->AddList(Tableaus[c.Getop1num() - 1]->RemoveList(c.Getnum(), undo), undo);
							return true;
						}
						return false;
					}
					return false;
				}
				else if (c.CheckIfop2IsFoundation())
				{

					if (c.Getnum() == 1)
					{
						Card temp;
						if (Tableaus[c.Getop1num() - 1]->GetLastNode(temp))
						{
							if (temp.IsValid())
							{

								if (foundations[c.Getop2num() - 1].AddCard(temp))
								{
									if (undo)
									{
										Card t2;
										if (Tableaus[c.Getop1num() - 1]->GetSecondLastNode(t2))
										{
											if (!t2.IsCorrectSequenceInTableau(temp) && t2.Isflipped())
												Tableaus[c.Getop1num() - 1]->FlipSecondLastNode();
										}

									}
									Tableaus[c.Getop1num() - 1]->RemoveNode();
									if (!undo)
										commands.Push(c);
									return true;
								}
								return false;
							}
							return false;
						}
						return false;
					}
					return false;
				}
				else if (c.CheckIfop2IsWaste() && undo)
				{
					if (c.Getnum() <= Tableaus[c.Getop1num() - 1]->Getsize())
					{
						for (int i = 0;i < c.Getnum();i++)
						{
							Card temp;
							if (Tableaus[c.Getop1num() - 1]->GetLastNode(temp))
							{
								temp.flip();
								waste.MoveWaste(temp);
								Tableaus[c.Getop1num() - 1]->RemoveNode(undo);
								Card t;
								if (Tableaus[c.Getop1num() - 1]->GetLastNode(t))
								{
									if (!t.IsCorrectSequenceInTableau(temp))
										Tableaus[c.Getop1num() - 1]->FlipLastNode();
								}

							}
							else
								return false;
						}
						return true;
					}
					return false;
				}
				return false;
			}
			else if (c.CheckIfop1IsFoundation() && undo)
			{

				if (c.Getnum() == 1)
				{
					if (c.CheckIfop2IsWaste())
					{
						Card t;
						if (foundations[c.Getop1num() - 1].Top(t))
						{
							t.flip();
							waste.MoveWaste(t);
							foundations[c.Getop1num() - 1].Pop();
							if (t.CheckRank(1))
							{
								foundations[c.Getop1num() - 1].deletesuit();
							}
							return true;
						}
						return false;
					}
					else if (c.CheckIfop2IsColumn())
					{
						Card t;
						if (foundations[c.Getop1num() - 1].Top(t))
						{

							if (Tableaus[c.Getop2num() - 1]->AddNode(t, undo))
							{
								Card temp;
								if (Tableaus[c.Getop2num() - 1]->GetSecondLastNode(temp))
								{
									if (!temp.IsCorrectSequenceInTableau(t))
										Tableaus[c.Getop2num() - 1]->FlipSecondLastNode();
								}
								foundations[c.Getop1num() - 1].Pop();
								if (t.CheckRank(1))
								{
									foundations[c.Getop1num() - 1].deletesuit();
								}
								return true;
							}
						}
						return false;
					}

				}
				return false;
			}
			return false;
		}
		else if (c.CheckIfUndo())
		{
			Command lastc;
			if (commands.Pop(lastc))
			{

				if (lastc.CheckIfMove())
				{
					Command reverse = lastc.ReversedCommand();
					if (ExecuteCommand(reverse, true))
					{
						return true;
					}
					else
					{
						cout << "Command can not be executed\n";
						return false;
					}
				}
				else if (lastc.CheckIfDraw())
				{
					Card c;
					if (waste.Top(c));
					{
						c.flip();
						stock.Push(c);
						waste.Pop();
						return true;
					}
					return false;
				}
				return false;
			}
			return false;
		}
		else if (c.CheckIfDraw())
		{
			if (!stock.IsEmpty())
			{
				Card t;
				if (stock.Top(t))
				{
					if (t.IsValid())
					{
						waste.MoveWaste(t);
						stock.Pop();
						commands.Push(c);
						return true;
					}
					return false;
				}
				return false;
			}
			else
			{
				Card t;
				while (waste.Top(t))
				{
					stock.MoveWaste(t);
					waste.Pop();
				}
				if (stock.Top(t))
				{
					if (c.IsValid())
					{
						waste.MoveWaste(t);
						stock.Pop();
						commands.Push(c);
						return true;
					}
					return false;
				}
				return false;
			}
		}
		else if (c.CheckIfQuit())
		{
			commands.Push(c);
			return true;
		}
		return false;
	}
	void Play()
	{
		Print();
		while (!IsFinished())
		{
			cout << "Enter Command: ";
			char com[100];
			cin.getline(com, 100);
			char inst = 0, st1 = 0, st2 = 0;
			int no1 = 0, no2 = 0, num = 0;
			if (!CheckCommand(com, inst, st1, st2, no1, no2, num))
			{
				bool flag = false;
				while (!flag)
				{
					cout << "Invalid Command\nEnter new Command: ";
					cin.getline(com, 100);
					inst = st1 = st2 = 0;
					no1 = no2 = num = 0;
					if (CheckCommand(com, inst, st1, st2, no1, no2, num))
						flag = true;
				}
			}
			Command c(inst, st1, no1, st2, no2, num);
			if (!ExecuteCommand(c, c.CheckIfUndo()))
			{
				bool flag1 = false;
				while (!flag1)
				{
					bool flag = false;
					while (!flag)
					{
						cout << "\nEnter new Command: ";
						cin.getline(com, 100);
						inst = st1 = st2 = 0;
						no1 = no2 = num = 0;
						if (CheckCommand(com, inst, st1, st2, no1, no2, num))
							flag = true;
					}
					Command c(inst, st1, no1, st2, no2, num);
					if (ExecuteCommand(c, c.CheckIfUndo()))
						flag1 = true;
				}
			}
			Print();
		}

	}
	~Game()
	{
		if (Tableaus)
		{
			delete[]Tableaus;
		}
		if (foundations)
		{
			delete[]foundations;
		}
	}

};
int main()
{
	SetConsoleOutputCP(CP_UTF8);
	Game solitaire;
	solitaire.Play();
	return 0;
}
