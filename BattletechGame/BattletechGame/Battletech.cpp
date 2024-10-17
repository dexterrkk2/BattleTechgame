#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::cin;
int rollInitiative() 
{
	int diceRoll = (rand() % 6) + 1;
	diceRoll += (rand() % 6) + 1;
	return diceRoll;
}
int main() 
{
	srand(time(0));
	int test = rollInitiative();
	cout << test<<endl;
	return 0;
}