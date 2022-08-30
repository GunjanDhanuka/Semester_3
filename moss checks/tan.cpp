#include <iostream>
using namespace std;

class Node
{
public:
	int val;
	Node* prev,*next;
	Node()
	{
		val = 0;
		prev = nullptr;
		next = nullptr;
	}
	Node(int r)
	{
		val = r;
		prev = nullptr;
		next = nullptr;
	}
};

class CircularDLL
{
	int size;
	Node* head;
	Node* tail;
public:
	CircularDLL()
	{
		size=0;
		head = nullptr;
		tail = nullptr;
	}

	void addB(int r)
	{
		Node* newnode;
		newnode = new Node(r);

		if(size==0)
		{
			newnode->prev = newnode;
			newnode->next = newnode;
			head = tail = newnode;
			size++;
			return;
		}
		head->prev = newnode;
		tail->next = newnode;
		newnode->next = head;
		newnode->prev = tail;
		head = newnode;
		size++;
	}

	void addE(int r)
	{
		Node* newnode;
		newnode = new Node(r);

		if(size==0)
		{
			newnode->prev = newnode;
			newnode->next = newnode;
			head = tail = newnode;
			size++;
			return;
		}
		head->prev = newnode;
		tail->next = newnode;
		newnode->next = head;
		newnode->prev = tail;
	    tail = newnode;
		size++;
	}

	void findMirrorPoints()
	{
		int cnt=0;
		bool check[size];
		Node* curr;
		curr = head;
		for(int i=0;i<size;i++)
		{
			check[i]=0;
			Node* frontSide;
			Node* backSide;
			frontSide = backSide = curr;
			bool pos=1;
			for(int j=1;j<size;j++)
			{
				frontSide = frontSide->next;
				backSide = backSide->prev;
				if(frontSide->val != backSide->val)
				{
					pos=0;
					break;
				}
			}
			if(pos)
			{
				cnt++;
				check[i]=1;
			}
			curr = curr->next;
		}

		cout<<"Total mirror points: "<<cnt<<" Indices:";
		for(int i=0;i<size;i++)
		{
			if(check[i])
				cout<<" "<<i;
		}
		cout<<endl;
	}
};


int main()
{
	int t;
	cin>>t;
	if(t==1)
	{
		CircularDLL q;
		int ty;
		while(cin>>ty)
		{
			if(ty==2)
			{
				int r;
				cin>>r;
				q.addB(r);
			}
			else if(ty==3)
			{
				int r;
				cin>>r;
				q.addE(r);
			}
			else if(ty==4)
			{
				q.findMirrorPoints();
			}
		}
	}
	return 0;
}
