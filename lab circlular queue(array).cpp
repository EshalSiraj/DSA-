#include<iostream>
using namespace std;
const int size=5;
class Queue{
	private:
	int arr[size];
	int front;
	int rear;
	int count;
	
	public:
	Queue(){
		front=rear=count=0;
	}
	
	void enqueue(int val){
	if (count==size)
		{
			cout<<"Queue if full"<<endl;
		}
		else{
		
		arr[rear] = val;
		rear = (rear + 1) % size;
		count++;
	}
	}

	
	void dequeue()
{
	if (count!=0)	{
		cout<<"Dequeue:"<<arr[front]<<endl;
	    front = (front + 1) % size;
         count--;
         }
	else
		cout<<"queue is Empty"<<endl;
           
}

bool isFull()
{
	if (count == size)
		return true;
	else
		return false;
}

bool isEmpty()
{
	if (count == 0)
		return true;
	else
		return false;
}

void display(){
	cout<<"Elements of queue:"<<endl;
	for (int i = 0; i < count; i++) { 
	cout << arr[i ] << " "; }

cout<<endl;
}
};

int main(){
	Queue q;
	
	q.enqueue(10);
	q.enqueue(15);
	q.enqueue(20);
	q.enqueue(25);
	q.enqueue(30);
	q.enqueue(35);
	q.display();
	q.dequeue();
	q.dequeue();
	q.display();

	
	
}



