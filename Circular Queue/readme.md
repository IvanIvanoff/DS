#Circular Queue

* This header file contains all the declarations and definitions of the *Circular Queue*

If you change the initial capacity it must be a power of two.

This circular queue is a linear data structure that uses an array to store the data. If there are no more free cells 
at the end of the array but there are free at the begining the queue applies MOD2 to the tail index and starts writing to the beggining of the array. When the head and 
tail indices meet then the array is resized.

##How to use it?

Include the header:
```C++
#include "~path/cqueue.h"
```

Create an object:
```C++
CQueue<int> cqueue;
```

> Note: The Circular Queue class is a template class. 

Use the **enqueue(elem)** method to add elements:
```C++
for(int i = 0; i<10; i++)
	cqueue.enqueue(i);
```

Use **front()** to get the current element without removing it. To remove the element at the front use **dequeue()**
To check if the queue is empty use **empty()**
```C++
while(!cqueue.empty()){}
	std::cout<<cqueue.front()<<std::endl;
	cqueue.deque();
}
```

## Example:
```C++
#include <iostream>
#include <string>
#include <vector>
#include "libs/cqueue.h"

using std::vector;
using std::string;
	
int main(){
	vector<string> names;
	names.push_back("Ivan");
	names.push_back("Moni");
	names.push_back("Hurin");
	names.push_back("Olorin");
	names.push_back("Mithrandir");
	
	cqueue<std::string> cq;

	for(int i = 0; i < 10; i++){
		cq.enqueue(names[ rand() % names.size() ]);
	}
	
	while(!sq.empty()){
		std::cout<<cq.front()<<std::endl;
		cq.dequeue();
	}

	return 0;
}

```