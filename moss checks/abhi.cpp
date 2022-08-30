#include<iostream>
using namespace std;
class stack
{
	int top;
	int *elements;
	public:
		void set(int);
		void stackmaker(int);
		void  push(int);
		void  pop();
		void rev();
		void printall();
		stack(int size);
};
stack::stack(int size)
{
	top=-1;
	elements=new int[size];
}
void stack::set(int next)
{
	elements[top]=next;
}
void stack::push(int toadd)
{
	if (top>=0) rev();
	top++;
	set(toadd);
}
void stack::pop()
{
	top--;
	if (top>=0) rev();
}
void stack::printall()
{
	cout<<top+1<<" elements: ";
	for(int i=0;i<=top;i++)
	{
		cout<<elements[i]<<' ';
	}
	cout<<'\n';
}
void stack::rev()
{
	int b[top];
	for(int i=0;i<=top;i++)
	{
		b[i]=elements[top-i];
	}
	for(int i=0;i<=top;i++)
	{
		elements[i]=b[i];
	}
}
int main()
{
	int one,size;
	cin>>one>>size;
	stack s(size);
	int query;
	while(cin>>query)
	{		
		switch(query)
		{
			case 2:
				int value;
				cin>>value;
				s.push(value);
				continue;
			case 3:
				s.pop();
				continue;
			default:
				s.printall();
				continue;
		}
	}
}
