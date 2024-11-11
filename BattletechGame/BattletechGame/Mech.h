#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::cin;

class Mech {
private:
	int walkSpeed =0;
	int heat;
	int weight;
	int jumpSpeed; 
	string image;
	int amountMovedThisTurn;
public:
	void fireWeapon() 
	{

	}
	int walk() 
	{
		return walkSpeed;
	}
	void run() 
	{

	}
	void jump() 
	{

	}
	void melee() 
	{

	}
	void setSpeed(int walkSpeed) 
	{
		this->walkSpeed = walkSpeed;
	}
	string getImage() {
		return image;
	}
	Mech() 
	{
		walkSpeed = -1;
		heat = 0; 
		weight = 0; 
		jumpSpeed = 0;
		image = "   ";
		amountMovedThisTurn = 0;
	}
	void setImage(string image) 
	{
		this->image = image;
	}
	void setAmountMoved(int amountMoved) 
	{
		amountMovedThisTurn = amountMoved;
	}
};


