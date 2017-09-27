#ifndef _BO_CIRCULAR_QUEUE_H_
#define _BO_CIRCULAR_QUEUE_H_

template<typename T, size_t MAX_SIZE>
class Queue
{
private:
    T mItem[MAX_SIZE];
    size_t mHead;
    size_t mTail;
public:
    Queue();
    void enqueue(T);
    T dequeue();
    size_t size();
    bool empty();
    bool full();

};
 
Queue::Queue()
{
	mHead = 0;
	mTail = 0;
}

void Queue::enqueue(T data)
{
	mItem[mTail] = data;
	mTail = (tail+1)%MAX_SIZE;
}

int Queue::dequeue()
{
	int temp;
	temp = mItem[mHead];
	mHead = (head+1)%MAX_SIZE;
	return temp;
}
 
 
int Queue::size()
{
	return mTail - mHead;
}
 
void Queue::display(){
    int i;
    if(!empty())
    {
        for(i=mHead; i!=mTail; i=(i+1)%MAX_SIZE){
            cout<<mItem[i]<<endl;
        }
    }
    else{
        cout<<"Queue Underflow"<<endl;
    }
}
 
 
bool Queue::empty(){
	if(abs(mHead == mTail))
	{
	    return true;
	}
    else
	{
	    return false;
	}
}
 
bool Queue::full(){
	if(mHead==(mTail+1)%MAX_SIZE)
	{
		return true;
	}
    else
	{
		return false;  
	}
}

#endif
