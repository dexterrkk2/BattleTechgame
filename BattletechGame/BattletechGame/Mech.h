#pragma once
#include <iostream>
#include <string>
#include<vector>
using std::cout;
using std::endl;
using std::string;
using std::cin;

enum forMech {
	H, //Head 
	CT, //Center Torse
	LA, //Left Arm
	RA, //Right Arm
	LL, //Left Leg
	RL, //Right Leg
};
class Ammo {
private:
	int shots;
	const int damage;
	const int location;
public:
	virtual int getShots() const {
		return shots;
	}
	virtual int getExplosion() const {
		int explosion = 0;
		explosion = shots * damage;
		return explosion;
	}
	virtual int getDamage() const {
		return damage;
	}
	Ammo(int d = 0, int s = 0, int l = 0) : shots(s), damage(d), location(l) {}
	void removeAmmo() {
		if (shots > 0) {
			--shots;
		}
	}
};
class AC2Ammo : public Ammo {
public:
	AC2Ammo(int l) :Ammo(2, 45, l) {}
};
class AC5Ammo : public Ammo {
public:
	AC5Ammo(int l) :Ammo(5, 20, l) {}
};
class AC10Ammo : public Ammo {
public:
	AC10Ammo(int l) :Ammo(10, 10, l) {}
};
class AC20Ammo : public Ammo {
public:
	AC20Ammo(int l) :Ammo(20, 5, l) {}
};

class Weapon {
private:
	std::string name;
	int heatGenerated;
	Ammo ammoType;
	int range;
	int minRange;
	int damage;
	bool canFire = true;
public:
	Weapon(std::string n, Ammo a, int d = 0, int h = 0, int r = 0, int mr = 0) :
		name(n), heatGenerated(h), damage(d), range(r), minRange(mr), ammoType(a) {
	}
	virtual int getDamage() const {
		return damage;
	}
	virtual int getrange() const {
		return range;
	}
	virtual Ammo getAmmo() const {
		return ammoType;
	}
	virtual bool getCanFire() const {
		return ammoType.getShots() > 0;
	}
	static friend std::ostream& operator<<(std::ostream& os, const Weapon& w) {
		os << w.name << std::endl;
		return os;
	}
	virtual void removeAmmo() {
		ammoType.removeAmmo();
	}
};
class AC2 : public Weapon {
public:
	AC2(Ammo a) : Weapon("AC2", a, 2, 1, 24, 4) {}
};
class AC5 : public Weapon {
public:
	AC5(Ammo a) : Weapon("AC5", a, 5, 1, 18, 3) {}
};
class AC10 : public Weapon {
public:
	AC10(Ammo a) : Weapon("AC10", a, 10, 3, 15, 0) {}
};
class AC20 : public Weapon {
public:
	AC20(Ammo a) : Weapon("AC20", a, 20, 7, 9, 0) {}
};

class Limb {
private:
	int armor;
	int structure;
	const static int maxWeapons = 6;
	Weapon* weapons[maxWeapons];
	int weaponCount;
	bool isDestroyed;
public:
	int armorDamage = 0;
	int structureDamage = 0;
	int getArmor() const {
		return armor;
	}
	int getStructure() const {
		return structure;
	}
	bool getIsDestroyed() const {
		return isDestroyed;
	}
	int getWeaponCount() const {
		return weaponCount;
	}
	Weapon* getWeapon(int index) const {
		if (index >= 0 && index < maxWeapons) {
			return(weapons[index]);
		}
		else
			return nullptr;
	}
	void addWeapon(Weapon& w) {
		if (weaponCount < maxWeapons) {
			weapons[weaponCount] = &w;
			++weaponCount;
		}
		else {
			std::cout << "ERROR!!!" << std::endl;
		}
	}
	void takeDamage(int d);
	Limb(int a = 0, int struc = 1, bool d = false, int c = 0) : armor(a), structure(struc), isDestroyed(d), weaponCount(c) {}
	static friend std::ostream& operator<<(std::ostream& os, const Limb& l) {
		os << "The armor of this limb is " << l.armor << std::endl;
		os << "The internal structure of this limb is " << l.structure << std::endl;
		return os;
	}

};
inline void Limb::takeDamage(int d) {
	if (armor > armorDamage) {
		armorDamage += d;
		if (armorDamage > armor) {
			structureDamage = armorDamage - armor;
			armorDamage = armor;
		}
	}
	else {
		structureDamage += d;
	}

	cout << "You dealt " << d << " damage" << endl;
	if (structureDamage >= structure) {
		isDestroyed = true;
	}
}

class Mech {
private:
	int walkSpeed;
	int heat;
	int weight;
	string image;
	int amountMovedThisTurn;
	Limb L[6];
public:
	//uses a generic to represent a drawn hex, because hex requires mech to be defined
	template <class T>
	void fireWeapon(T& targetSquare);
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
	void destroyMech() 
	{
		walkSpeed = -1;
		cout << "Mech Destroyed" << endl;
	}
	void melee() 
	{

	}
	void setSpeed(int walkSpeed) 
	{
		this->walkSpeed = walkSpeed;
	}
	int getSpeed() 
	{
		return walkSpeed;
	}
	string getImage() {
		return image;
	}
	Mech() :walkSpeed(-1), heat(0), weight(0), amountMovedThisTurn(0), image("   ") {};
	Mech(Limb* l, int m = 0, int w = 0, int h = 0) : walkSpeed(m), weight(w), heat(h) {
		for (int i = 0; i < 6; ++i) {
			L[i] = l[i];
		}
		walkSpeed = m;
		weight = w;
		heat = h;
		amountMovedThisTurn = 0;
		string image = "   ";
	}
	void setImage(string image) 
	{
		this->image = image;
	}
	void setAmountMoved(int amountMoved) 
	{
		amountMovedThisTurn = amountMoved;
	}
	int getAmountMoved() 
	{
		return amountMovedThisTurn;
	}
};

inline int rollDice()
{
	int diceRoll = (rand() % 6) + 1;
	diceRoll += (rand() % 6) + 1;
	return diceRoll;
}

//Weapon w, Heat h, Range r, Enemy Movement EM
inline int gator(Weapon w, int h, int r, int EM) {
	// Gunnery
	int hit = 4;
	// Attacker Move
	/*If stood still +0 */
	// Target Move
	if (EM == 0) {
		//Hit stays the same if the target doesn't move
	}
	else {
		//Hit advances every two tiles of movement after the first
		hit = hit + ((EM - 1) / 2);
	}
	// Other
	if (h < 8) {
		hit += 0;
	}
	else if (h < 13) {
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
	}
	// Range
	if (r <= w.getrange() / 3) {
		hit += 0;
	}
	else if (r <= w.getrange() * 2 / 3) {
		hit += 2;
	}
	else if (r <= w.getrange()) {
		hit += 4;
	}
	else {
		hit = 13; //Some arbitrarly high number to make a shot impossible.
	}
	return hit;
}


template <class T>
void Mech::fireWeapon(T& targetSquare) {
	//Pick a target
	Mech& Enemy = targetSquare.getHex().getMech();
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
	int x = targetSquare.getX() + targetSquare.getY(); // test code
	for (int i = 0; i < weaponsSelected.size(); ++i) {
		int result = rollDice();
		cout << "You rolled a " << result << " to hit" << endl;
		if (result >= gator(*weaponsSelected[i], heat, x, targetSquare.getHex().getMech().getAmountMoved())) {
			weaponDamage.push_back(weaponsSelected[i]->getDamage());
		}
	}
	//Get hit location
	for (int i = 0; i < weaponDamage.size(); ++i) {
		int hitLocationDice = rollDice();
		if (hitLocationDice == 12) {
			cout << "You Hit the Head!" << endl;
			Enemy.L[H].takeDamage(weaponDamage[i]);
			if (Enemy.L[H].getIsDestroyed()) 
			{
				Enemy.destroyMech();
			}
		}
		else if (hitLocationDice == 10 || hitLocationDice == 11) {
			cout << "You Hit the Left Arm" << endl;
			Enemy.L[LA].takeDamage(weaponDamage[i]);
		}
		else if (hitLocationDice == 9) {
			cout << "You Hit the Left Leg" << endl;
			Enemy.L[LL].takeDamage(weaponDamage[i]);
		}
		else if (hitLocationDice == 5) {
			cout << "You Hit the Right Leg" << endl;
			Enemy.L[RL].takeDamage(weaponDamage[i]);
		}
		else if (hitLocationDice == 3 || hitLocationDice == 4) {
			cout << "You Hit the Right Arm" << endl;
			Enemy.L[RA].takeDamage(weaponDamage[i]);
		}
		else {
			cout << "You Hit the Torso" << endl;
			Enemy.L[CT].takeDamage(weaponDamage[i]);
			if (Enemy.L[CT].getIsDestroyed())
			{
				Enemy.destroyMech();
			}
		}
	}
}
