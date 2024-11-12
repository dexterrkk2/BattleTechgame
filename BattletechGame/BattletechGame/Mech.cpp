#include <iostream>
#include <string>
#include <vector>
#include "Mech.h"
//Check rollDice Code
int rollDice()
{
	int diceRoll = (rand() % 6) + 1;
	diceRoll += (rand() % 6) + 1;
	return diceRoll;
}
template <class T>
void Mech::fireWeapon(T& targetSquare) {
	//Pick a target
	Mech Enemy = targetSquare.getMech();
	//Get weapons available and pack them into a vector
	std::vector<Weapon*> weaponsAvailable;
	for (int i = 0; i < RL; ++i) {
		if (!L[i].getIsDestroyed()) {
			for (int j = 0; j < L[i].getWeaponCount(); ++j) {
				Weapon* weapon = L[i].getWeapon(j);
				// This line checks that the weapon is not a null pointer, and that it can fire (has ammo)
				if (weapon && weapon->getCanFire()) {
					weaponsAvailable.push_back(weapon);
				}
			}
		}
	}

	//Pick a weapon (would be nice if displayed hit chance)	
	int weaponSelection = -1; // -1 to initizalize to some number that won't break anything
	std::vector<Weapon*> weaponsSelected;
	do {
		//Auto exits the loop when the user runs out of weapons
		if (weaponsAvailable.size() == 0) {
			break;
		}
		for (int i = 0; i < weaponsAvailable.size(); ++i) {
			std::cout << i + 1 << ". " << *weaponsAvailable[i];
		}
		std::cout << "Select a weapon to fire or 0 to confirm" << std::endl;
		std::cin >> weaponSelection;

		// If the user picks a valid number, add it to the weapons selected vector and remove it from the weapons available vector
		// There is some index adjusting that needed to be done on weaponSelection.
		if (weaponSelection > 0 && weaponSelection <= weaponsAvailable.size())
		{
			weaponsSelected.push_back(weaponsAvailable[weaponSelection - 1]);
			weaponsAvailable.erase(weaponsAvailable.begin() + weaponSelection - 1);
		}
	} while (weaponSelection != 0);

	//Remove Ammo
	for (int i = 0; i < weaponsSelected.size(); ++i) {
		weaponsSelected[i]->removeAmmo();
	}
	
	//Roll Dice for each one and get damage
	std::vector<int> weaponDamage;
	int x = targetSquare.getX() + targetSquare.getY();
	for (int i = 0; i < weaponsSelected.size(); ++i) {
		if (rollDice() >= gator(weaponsSelected[i], heat, x, targetSquare.getMech().getAmountMoved())) {
			weaponDamage.push_back(weaponsSelected[i]->getDamage);
		}
	}
	//Get hit location
	for (int i = 0; i < weaponDamage.size(); ++i) {
		int hitLocationDice = rollDice();
		if (hitLocationDice == 12) {
			Enemy.L[H].armorDamage + weaponDamage[i];
		}
	}
}

int gator(Weapon w, int h,int r, int EM) {
	// Gunnery
	int hit = 4;
	// Attacker Move
	/*If stood still +0 */
	// Target Move
	hit = hit + EM / 2 - 1; // FIX THIS GARBAGE MATH LATER
	// Other
	if (h < 8) {
		hit += 0;
	} else if (h < 13) {
		hit += 1;
	}
	else if (h < 17) {
		hit += 2;
	}
	else if (h < 24) {
		hit += 3;
		}
	else {
		hit += 4;
	}// I DON'T LOGIC THIS LOGIC! CHECK LATER
	// Range
	if (r <= w.getrange()/3) {
		hit += 0;
	}
	else if (r <= w.getrange() *2/3) {
		hit += 2;
	}
	else if(r < w.getrange()) {
		hit += 4;
	}
	else {
		hit = 13; //Some arbitrarly high number to make a shot impossible.
	}
	return hit;
}
