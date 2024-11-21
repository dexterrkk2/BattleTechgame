#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "fileIO.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::regex;
using std::smatch;
using std::ostream;

enum forMech {
	H,
	CT,
	LA,
	RA,
	LL,
	RL
};

class Limb;
class Ammo;
class Weapon;

class Mech {
private:
	int walkSpeed;
	int heat;
	int weight;
	string ID;
	int moved;
	vector<Limb> L;
public:
	//Returns the walk speed.
	int getWalk() const {
		return walkSpeed;
	}
	//Returns the walk speed.
	int getHeat() const {
		return heat;
	}
	//Returns the Weight.
	int getWeight() const {
		return weight;
	}
	//Returns the Mech Name and Image.
	string getID() const {
		return ID;
	}
	//Returns how fast the mech walked in a turn.
	int getMoved() const {
		return moved;
	}
	//Returns the entire Limb vector.
	vector<Limb> getLimbs() const {
		return L;
	}
	
	//Attaches the Name to the Mech.
	void setID(string ID) {
		this->ID = ID;
	}
	//Sets how much the mech moved in one turn.
	void setMoved(int amountMoved) {
		moved = amountMoved;
	}
	//Creates a mech from a text file
	Mech makeMech(string fileName);
	//Sets the mechs walkspeed to one, which removes the mech in Hex.
	void destroyMech() {
		walkSpeed = -1;
		cout << "Mech Destroyed" << endl;
	}
	//Displays all the information about the mech, along with the weapons and status of each limb.
	void displayMech();
	//Allows a player to fire a weapon at a target mech
	template <class T> void fireWeapon(T& targetSquare);

	//Default constructor
	Mech(int w = -1, int h = 0, int lb = 0, int m = 0, string i = "   ", vector<Limb> l = {})
		:walkSpeed(w), heat(h), weight(lb), ID(i), moved(m), L(l) {}
	//Copy Constructor
	Mech(const Mech& old) : walkSpeed(old.walkSpeed), heat(old.heat), weight(old.weight), ID(old.ID), moved(old.moved) {
		for (int i = 0; i < old.L.size(); ++i) {
			L.push_back(old.L[i]);
		}
	}
	//Deconstructor
	~Mech() {}
};

class Limb {
private:
	int armor;
	int structure;
	int armorDamage;
	int structureDamage;
	vector<Weapon> weaponsOnLimb;
	bool isDestroyed;
	static const int maxWeapons = 6;
public:
	int getArmor() const {
		return armor;
	}
	int getStructure() const {
		return structure;
	}
	int getArmorDamage() {
		return armorDamage;
	}
	int getStructureDamgage() {
		return structureDamage;
	}
	vector<Weapon> getWeapons() const {
		return weaponsOnLimb;
	}
	bool getIsDestroyed() const {
		return isDestroyed;
	}
	void takeDamage(int damageTaken);

	Limb(int a = 0, int s = 1, vector<Weapon> w = *new vector<Weapon>(), bool isD = false, int AD = 0, int SD = 0)
		: armor(a), structure(s), weaponsOnLimb(w), structureDamage(SD), armorDamage(AD), isDestroyed(isD) {

	}
	Limb(const Limb& old)
		: armor(old.armor), structure(old.structure), isDestroyed(old.isDestroyed)
		, armorDamage(old.armorDamage), structureDamage(old.structureDamage) {
		for (int i = 0; i < old.weaponsOnLimb.size(); ++i) {
			weaponsOnLimb.push_back(old.weaponsOnLimb[i]);
		}
	}
	~Limb() {}
};

class Ammo {
private:
	int damage;
	int shots;
public:
	virtual int getDamage() const {
		return damage;
	}
	virtual int getShots() const {
		return shots;
	}

	virtual void removeAmmo() {
		--shots;
	}
	Ammo(int d = 0, int s = 0) : damage(d), shots(s) {}
	Ammo(const Ammo& old)
		: damage(old.damage),shots(old.shots){ }
	friend ostream& operator<<(ostream& os, Ammo a)
	{
		os << "Ammo " << a.damage << " " << a.shots;
		return os;
	}
};

//Derived Classes
class AC2Ammo :public Ammo {
public:
	AC2Ammo() :Ammo(2, 45) {};
};
class AC5Ammo :public Ammo {
public:
	AC5Ammo() :Ammo(5, 20) {};
};
class AC10Ammo :public Ammo {
public:
	AC10Ammo() :Ammo(10, 10) {};
};
class AC20Ammo :public Ammo {
public:
	AC20Ammo() :Ammo(20, 5) {};
};

class Weapon {
private:
	string name;
	int damage;
	int heatGenerated;
	Ammo ammoBin;
	int maxRange;
	int minRange;
	bool canFire;
public:
	string getName() const {
		return name;
	}
	virtual int getDamge() const {
		return damage;
	}
	virtual int getHeat() const {
		return heatGenerated;
	}
	virtual int getMaxRange() const {
		return maxRange;
	}
	virtual int getMinRange() const {
		return minRange;
	}
	virtual bool getCanFire() {
		return ammoBin.getShots() > 0;
	}
	virtual Ammo getAmmo() {
		return ammoBin;
	}
	Weapon(string n = "", int h = 0, Ammo a = Ammo(), int maxR = 0, int minR = 0, bool cf = false)
		: name(n), heatGenerated(h), ammoBin(a), maxRange(maxR), minRange(minR), canFire(cf) {
		damage = a.getDamage();
	}
	Weapon(const Weapon& old)
		: name(old.name), damage(old.damage), heatGenerated(old.heatGenerated)
		, ammoBin(old.ammoBin), maxRange(old.maxRange), minRange(old.minRange), canFire(old.canFire) {}
	friend ostream& operator<<(ostream& os, Weapon w) 
	{
		os << w.name;
		return os;
	}
	virtual void displayWeapon() {
		cout << name << " " << damage << " " << heatGenerated << " " << ammoBin << " " << maxRange << " " << minRange << " " << canFire << endl;
	}
};

//Derived Classes
class AC2 :public Weapon {
public:
	AC2(Ammo a) : Weapon("AC2", 1, a, 24, 4, true) {}
};
class AC5 :public Weapon {
public:
	AC5(Ammo a) : Weapon("AC5", 1, a, 18, 3, true) {}
};
class AC10 :public Weapon {
public:
	AC10(Ammo a) : Weapon("AC10", 3, a, 15, 0, true) {}
};
class AC20 :public Weapon {
public:
	AC20(Ammo a) : Weapon("AC20", 7, a, 9, 0, true) {}
};




inline int rollDice() {
	int roll = (rand() % 6) + 1;
	roll += rand() % 6 + 1;
	return roll;
}

// Takes the users weapon, the users heat, the enemies location, and the amount the enemy moved
// in order to calculate number the user needs to roll to land a hit.
inline int gator(Weapon w, int h, int r, int EM, int AM) {
	// Gunnery: Base chance to hit
	int hit = 4;
	// Attacker Move: How did the attacker move
	if (AM > 0) {
		hit += 1;
	}
	// Target Move: How much did the target move
	//Hit stays the same if the target doesn't move
	if (EM == 0) {
	}
	//Hit advances every two tiles of movement after the first
	else {
		hit = hit + ((EM - 1) / 2);
	}
	// Other: Heat modifers
	// Player heat makes it harder for shots to land
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
	// Range: How far away are both mechs
	if (r <= w.getMaxRange() / 3) {
		hit += 0;
	}
	else if (r <= w.getMaxRange() * 2 / 3) {
		hit += 2;
	}
	else if (r <= w.getMaxRange()) {
		hit += 4;
	}
	else {
		hit = 13; //Some arbitrarly high number to make a shot impossible.
	}
	return hit;
}



// This Demon Code Ruined Our Lives
// This code takes a target square and gets the enemy mech from the square. 
// It then allows the user to pick what weapon they want to fire and removes ammo from the weapon they chose.
// Then the code calculates what number the user needs to roll in order to deal damage.
// Finally, the damage is assigned to a limb with a dice roll.
template <class T> inline void Mech::fireWeapon(T& targetPlayer) {
	Mech& Enemy = targetPlayer.getMech();
	std::vector<Weapon> weaponsAvailable;
	for (int i = 0; i < 6; ++i) {
		if (!L[i].getIsDestroyed()) {
			for (int j = 0; j < L[i].getWeapons().size(); ++j) {
				weaponsAvailable.push_back(L[i].getWeapons()[j]);
			}
		}
	}
	for (int i = weaponsAvailable.size()-1; i >= 0; --i) {
		if (!weaponsAvailable[i].getCanFire()) {
			weaponsAvailable.erase(weaponsAvailable.begin() + i);
		}
	}
	int whichWeapon = -1;
	vector<Weapon> weaponsSelected;
	do {
		if (weaponsAvailable.size() == 0) {
			break;
		}
		for (int i = 0; i < weaponsAvailable.size(); ++i) {
			cout << i + 1 << ". " << weaponsAvailable[i] << endl;
		}
		cout << "Select a weapon to fire or 0 to confirm" << endl;
		cin >> whichWeapon;
		while (!cin) {
			cout << "Whole numbers only please" << endl;
			cin.clear();
			cin.ignore();
			cin >> whichWeapon;
		}
		if (whichWeapon > 0 && whichWeapon <= weaponsAvailable.size()) {
			weaponsSelected.push_back(weaponsAvailable[whichWeapon - 1]);
			weaponsAvailable.erase(weaponsAvailable.begin() + whichWeapon - 1);
		}
	} while (whichWeapon != 0);
	for (int i = 0; i < weaponsSelected.size(); ++i) {
		weaponsSelected[i].getAmmo().removeAmmo();
	}

	vector<int> weaponDamage;
	for (int i = 0; i < weaponsSelected.size(); ++i) {
		int result = rollDice();
		cout << "You rolled a " << result << " to hit" << endl;
		// 1 in gator is sample code. We need to calculate range properly
		if (result >= gator(weaponsSelected[i], heat, 1, targetPlayer.getMech().getMoved(),moved)) {
			weaponDamage.push_back(weaponsSelected[i].getDamge());
			cout << "You needed a " << gator(weaponsSelected[i], heat, 1, targetPlayer.getMech().getMoved(), moved) << endl;
		}
	}
	for (int i = 0; i < weaponDamage.size(); ++i) {
		int result = rollDice();
		if (result == 12) {
			cout << "You hit the Head!" << endl;
			Enemy.L[0].takeDamage(weaponDamage[i]);
			if (Enemy.L[0].getIsDestroyed()) {
				Enemy.destroyMech();
			}
		}
		else if (result == 10) {
			cout << "You hit the Left Arm!" << endl;
			Enemy.L[2].takeDamage(weaponDamage[i]);
		}
		else if (result == 9) {
			cout << "You hit the Left Leg!" << endl;
			Enemy.L[4].takeDamage(weaponDamage[i]);
		}
		else if (result == 5) {
			cout << "You hit the Right Leg!" << endl;
			Enemy.L[5].takeDamage(weaponDamage[i]);
		}
		else if (result == 3) {
			cout << "You hit the Right Arm!" << endl;
			Enemy.L[3].takeDamage(weaponDamage[i]);
		}
		else {
			cout << "You hit the Torso!" << endl;
			Enemy.L[1].takeDamage(weaponDamage[i]);
			if (Enemy.L[1].getIsDestroyed()) {
				Enemy.destroyMech();
			}
		}
	}
}

