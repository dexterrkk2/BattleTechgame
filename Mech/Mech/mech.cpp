#include<iostream>
#include <string>
#include <vector>

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
	Ammo(int d = 0, int s = 0,int l = 0) : shots(s), damage(d), location(l) {}
	void removeAmmo() {
		if (shots > 0) {
			--shots;
		}
	}
};
// Derived Classes
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
	Weapon(std::string n, Ammo a,int d = 0, int h = 0, int r = 0, int mr = 0) :
		name(n), heatGenerated(h), damage(d), range(r), minRange(mr), ammoType(a)  {
	}
	virtual int getDamage() const {
		return damage;
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
// Derived Weapons
class AC2 : public Weapon {
public:
	AC2(Ammo a) : Weapon("AC2", a, 2, 1, 24, 4) {}
};
class AC5: public Weapon{
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
	Limb(int a = 0, int struc = 1, bool d = false, int c = 0) : armor(a), structure(struc),isDestroyed(d),weaponCount(c) {}
	static friend std::ostream& operator<<(std::ostream& os, const Limb& l) {
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
	Limb L[6]; //Limbs
public:
	void fireWeapon();
	void walk();
	void melee();
	void destroyMech(); // if CT or H is destroyed, remove the mech from play
	Limb getLimb(int i) const {
		return L[i];
	}
	void display() {
		for (int i = 0; i < 6; ++i) {
			std::cout << "Armor is " << L[i].getArmor() << std::endl;
			std::cout << "Structure is " << L[i].getStructure() << std::endl;
		}
	};
	Mech(Limb* l, int m = 0, int w = 0, int h = 0) : walkSpeed(m), weight(w), heat(h) {
		for (int i = 0; i < 6; ++i) {
			L[i] = l[i];
		}
		walkSpeed = m;
		weight = w;
		heat = h;
		}
};
void Mech::fireWeapon() {
	//Pick a target

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
	do{
		//Auto exits the loop when the user runs out of weapons
		if (weaponsAvailable.size() == 0) {
			break;
		}
		for (int i = 0; i < weaponsAvailable.size(); ++i) {
			std::cout << i+1 << ". " << *weaponsAvailable[i];
		}
		std::cout << "Select a weapon to fire or 0 to confirm" << std::endl;
		std::cin >> weaponSelection;

		// If the user picks a valid number, add it to the weapons selected vector and remove it from the weapons available vector
		// There is some index adjusting that needed to be done on weaponSelection.
		if (weaponSelection > 0 && weaponSelection <= weaponsAvailable.size()) {
			weaponsSelected.push_back(weaponsAvailable[weaponSelection - 1]);
			weaponsAvailable.erase(weaponsAvailable.begin() + weaponSelection - 1);
		}
	} while (weaponSelection != 0);

	//Remove Ammo
	for (int i = 0; i < weaponsSelected.size(); ++i) {
		weaponsSelected[i]->removeAmmo();
	}
	//Roll Dice for each one 
	//Get damage
}

//int gator(/*Weapon Type,Target Range, Target Movement*/) {
//	int hit = 4;
//	if (/*Target is short range (range < Maxrange /3 )*/) {
//		hit += 0;
//	}
//	else if (/*Target is medium range (range < Maxrange /2 )*/) {
//		hit += 2;
//	}
//	else if(/*Target is long range (range < Maxrange )*/) {
//		hit += 4;
//	}
//	else {
//		hit = 13; //Some arbitrarly high number to make a shot impossible.
//	}
//}

int main() {
	AC20Ammo bin1(CT);
	Weapon AC5("AC5_1", bin1, 5, 3, 5, 0);
	Weapon AC5_1("AC5_2", bin1, 5, 3, 5, 0);
	Weapon AC5_2("AC5_3", bin1, 5, 3, 5, 0);
	Limb parts[6];
	Limb head;
	Limb torso;
	Limb leftLeg;
	Limb rightLeg;
	Limb leftArm;
	Limb rightArm;
	//test Code
	leftArm.addWeapon(AC5);
	rightArm.addWeapon(AC5_1);
	head.addWeapon(AC5_2);
	parts[H] = head;
	parts[CT] = torso;
	parts[LA] = leftArm;
	parts[RA] = rightArm;
	parts[LL] = leftLeg;
	parts[RL] = rightLeg;
	
	Mech testMech(parts, 5, 30);
	testMech.fireWeapon();
	return 0;

}