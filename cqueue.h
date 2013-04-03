#pragma once
#include <queue>
//#include <deque>

template<class T> 
class cqueue : public std::queue<T>
{
private:
	typedef std::queue<T> q;
	int maxSize;
public:
	cqueue(int size) {
		maxSize = size;
	}
	
	void push(T element){
		q::push(element);
		if((int)q::size() > maxSize)
			q::pop();
	}
	
	bool find(T element){
		//std::deque<T> d = q::c;
		//T e = d.at(1);
		bool result = false;
		for(int i = 0; i < (int)q::c.size(); i++)
			if(q::c.at(i) == element){
				result = true;
				break;
			}
		return result;
	}

	bool find(char *element){
		bool result = false;
		for(int i = 0; i < (int)q::c.size(); i++)
			if(strcmp(q::c.at(i), element) == 0){
				result = true;
				break;
			}
		return result;
	}

	bool find(T element, int (*comparer)(T, T)){
		bool result = false;
		for(int i = 0; i < (int)q::c.size(); i++)
			if(comparer(q::c.at(i), element) == 0){
				result = true;
				break;
			}
		return result;
	}
};

