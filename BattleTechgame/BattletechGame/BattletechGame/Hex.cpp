#include "Hex.h"
//sets what the hex is pointing to
void Hex::Rotate(Hex& hex) 
{
	*pointingTo = hex;
}