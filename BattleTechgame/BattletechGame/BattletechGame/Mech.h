#pragma once
#include <iostream>
#include <string>
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
	void takeDamage(int d) {
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
	}
	Limb(int a = 0, int struc = 1, bool d = false, int c = 0) : armor(a), structure(struc), isDestroyed(d), weaponCount(c) {}
	static friend std::ostream& operator<<(std::ostream& os, const Limb& l) {
		os << "The armor of this limb is " << l.armor << std::endl;
		os << "The internal structure of this limb is " << l.structure << std::endl;
		return os;
	}

};
class Mech {
private:
	int walkSpeed =0;
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
	Mech() :walkSpeed(0), heat(0), weight(0), amountMovedThisTurn(0) {};
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


