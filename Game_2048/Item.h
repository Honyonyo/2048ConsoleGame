#pragma once

#include <iostream>

class Item
{
private:
	char* name="";
	int ea=0;

public:

	virtual void active()=0;
	void eaPluse() { ea++; }
	int getEa() { return ea; }

	Item(char* name) {
		this->name = name;
	}

	~Item() {
		delete[] name;
	}
};

