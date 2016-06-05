#Circular Queue

* This header file contains all the declarations and definitions of the *Circular Queue*

##How to use it?

1. Include the header:
```C++
#include "~path/cqueue.h"
```

2. Create an object:
```C++
CQueue<int> cqueue;
```

> Note: The Circular Queue class is a template class. 

3. Use the **enqueue(elem)** method to add elements:
```C++
for(int i = 0; i<10; i++)
	cqueue.enqueue(i);
```

4. Use **front()** to get the current element without removing it. To remove the element at the front use **dequeue()**
To check if the queue is empty use **empty()**
```C++
while(!cqueue.empty()){}
	std::cout<<cqueue.front()<<std::endl;
	cqueue.deque();
}
```
