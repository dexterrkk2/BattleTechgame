#include<iostream>
#include <string>

enum forMech {
	H,
	CT,
	LT,
	RT,
	LA,
	RA,
	LL,
	RL,
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
	Ammo(int d = 0, int s = 0,int l = 0) : shots(s), damage(d), location(l) {}
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
	int heatGenerated;
	Ammo ammoType;
	int slots;
	int range;
	int minRange;
	int location;
	int damage;
public:
	void removeAmmo();
	Weapon(Ammo a,int d = 0, int h = 0, int r = 0, int mr = 0, int l = 0) :
		heatGenerated(h), damage(d), range(r), minRange(mr), location(l), ammoType(a) {
	}
	int getDamage() const {
		return damage;
	}
};
class Limb {
private:
	int armor;
	int structure;
	int slots;
public:
	int getArmor() const {
		return armor;
	}
	int getStructure() const {
		return structure;
	}
	int getSlots() const {
		return slots;
	}
	Limb(int a = 0, int struc = 1, int s = 0) : armor(a), structure(struc), slots(s) {
		armor = a;
		structure = struc;
		slots = s;
	}
	friend std::ostream& operator<<(std::ostream& os, const Limb& l) {
		os << "The armor of this limb is " << l.armor << std::endl;
		os << "The internal structure of this limb is " << l.structure << std::endl;
		return os;
	}
};

class Mech {
private:
	int walkSpeed;
	int heat;
	int weight;
	int facing;
	Limb L[8]; //Limbs
	//Limb H; //Head
	//Limb CT; // Center Torso
	//Limb LT; // Left Torso
	//Limb RT; // Rigth Torso
	//Limb LA; // Left Arm
	//Limb RA; // Right Arm
	//Limb LL; // Left Leg
	//Limb RL; // Right Arm

public:
	void fireWeapon();
	void walk();
	void run();
	void jump();
	void melee();
	void destroyMech();
	Limb getLimb(int i) {
		return L[i];
	}
	void display() {
		for (int i = 0; i < 8; ++i) {
			std::cout << "Armor is " << L[i].getArmor() << std::endl;
			std::cout << "Structure is " << L[i].getStructure() << std::endl;
			std::cout << "Slots are " << L[i].getSlots() << std::endl;
		}
	};
	Mech(Limb* l, int m = 0, int w = 0, int f = 1 , int h = 0) : walkSpeed(m), weight(w), facing(f),heat(h) {
		for (int i = 0; i < 8; ++i) {
			L[i] = l[i];
		}
		walkSpeed = m;
		weight = w;
		facing = f;
		heat = h;
		}
};


int main() {
	
	AC2Ammo Bin1(LL);
	std::cout << Bin1.getShots() << std::endl;
	Weapon AC10(Bin1,Bin1.getDamage(), 3, 15, 0, RT);
	std::cout << AC10.getDamage() << std::endl;
	return 0;

}