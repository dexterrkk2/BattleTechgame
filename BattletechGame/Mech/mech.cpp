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
	int heatGenerated;
	Ammo ammoType;
	int range;
	int minRange;
	int damage;
	bool canFire;
public:
	Weapon(Ammo a,int d = 0, int h = 0, int r = 0, int mr = 0, bool cf = true) :
		heatGenerated(h), damage(d), range(r), minRange(mr), ammoType(a), canFire(cf)  {
	}
	int getDamage() const {
		return damage;
	}
	Ammo getAmmo() const {
		return ammoType;
	}
	bool getCanFire() const {
		return ammoType.getShots() > 0;
	}
};
// Derived Weapons
//class AC5: public Weapon{};
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
	void run();
	void jump();
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
	Mech(Limb* l, int m = 0, int w = 0, int f = 1 , int h = 0) : walkSpeed(m), weight(w), heat(h) {
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
	//Get weapons available
	std::vector<Weapon*> weaponsAvaiable;
	for (int i = 0; i < RL; ++i) {
		if (!L[i].getIsDestroyed()) {
			for (int j = 0; j < L[i].getWeaponCount(); ++j) {
				Weapon* weapon = L->getWeapon(j);
				if (weapon && weapon->getCanFire()) {
					weaponsAvaiable.push_back(weapon);
				}
			}
		}
	}
	//TEST CODE
	for (int i = 0; i < weaponsAvaiable.size(); ++i) {
		std::cout << weaponsAvaiable[i] << std::endl;
	}
	//Pick a weapon
	//Check if it's legal to fire
	//Remove Ammo (If applicable)
	//Roll Dice for each one
	//Get damage
}

int main() {
	AC5Ammo bin1(CT);
	Weapon AC5(bin1,5,3,5,0);
	Limb parts[6];
	Limb head;
	Limb torso;
	Limb leftLeg;
	Limb rightLeg;
	Limb leftArm;
	Limb rightArm;
	leftArm.addWeapon(AC5);
	parts[H] = head;
	parts[CT] = torso;
	parts[LA] = leftArm;
	parts[RA] = rightArm;
	parts[LL] = leftLeg;
	parts[RL] = rightLeg;


	return 0;

}