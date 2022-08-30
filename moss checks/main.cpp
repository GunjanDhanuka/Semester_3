#include <iostream>

using namespace std;

//Dont worry about corner cases
//New cases will be created only once
//Handle pop from empty or push to full
class ArrayADT
{
    public:
        ArrayADT(){
            capacity=0;
            elements=nullptr;
        }

        ArrayADT(int arraySize){
            capacity = arraySize;
            elements = new int[arraySize];
        }

        bool setElement(int index, int value){
            elements[index] = value;
            return true;
        }
        int getElement(int index){
            return elements[index];
        }
        int getCapacity(){
            return capacity;
        }

        virtual ~ArrayADT(){
            //dtor
        }

    protected:

    private:
        int capacity;
        int* elements;
};

class Stack{

    public:
        Stack()=delete;
        
        Stack(int capacity) : members(capacity){
            valueCount = 0;
        }

        bool push_norm(int value){
            if(isFull()){
                cout << "Stack full. Cannot push " << value << endl;
                return false;
            }
            members.setElement(valueCount, value);
            valueCount++;
            //cout << "push-normed " << value << ", now size is " << valueCount << endl;
            return true;
        }

        bool push(int value){
            if(isFull()){
                cout << "Stack full. Cannot push " << value << endl;
                return false;
            }
            reverseStack();
            members.setElement(valueCount, value);
            valueCount++;
            //cout << "pushed " << value << ", now size is " << valueCount << endl;
            return true;
        }
        
        int pop_norm(){
            if(isEmpty()){
                cout << "Stack is empty. Nothing to pop" << endl;
                return -1;
            }
            valueCount--;
            return members.getElement(valueCount);
        }

        int pop(){
            if(isEmpty()){
                cout << "Stack is empty. Nothing to pop" << endl;
                return -1;
            }
            valueCount--;
            reverseStack();
            return members.getElement(valueCount);
        }

        bool isEmpty(){
            if(valueCount==0){
                return true;
            }
            return false;
        }

        bool isFull(){
            if(valueCount==members.getCapacity()){
                return true;
            }
            return false;
        }

        void printStack(){
            cout << valueCount << " elements: ";
            for(int i = 0; i < valueCount; i++){
                cout << members.getElement(i) << " ";
            }
            cout << endl;
        }

        void reverseStack(){
            int size = valueCount;
            ArrayADT store(size);

            for(int i = 0; i < size; i++){
                store.setElement(i, pop_norm());
            }

            for(int i = 0; i < size; i++){
                push_norm(store.getElement(i));
            }
        }


        virtual ~Stack(){
            //dtor
        }

    private:
        int valueCount;
        ArrayADT members;

};

int main(){
    
    int code;
    cin >> code;
    int sizeStack;
    cin >> sizeStack;
    //cout << "size of stack = " << sizeStack << endl;

    Stack s(sizeStack);

    while(cin >> code){
        
        switch(code){
            case 2:
                int value;
                cin >> value;
                s.push(value);
                break;

            case 3: 
                s.pop();
                break;

            case 7:
                s.printStack();
                break;

            default:
                break;

        }
    }
}