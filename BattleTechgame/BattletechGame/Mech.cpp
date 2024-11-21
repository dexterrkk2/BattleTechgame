#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "fileIO.h"
#include "Mech.h"
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::regex;
using std::smatch;
using std::ostream;

void Limb::takeDamage(int damageTaken) {
	if (armor > armorDamage) {
		armorDamage += damageTaken;
		if (armorDamage > armor) {
			structureDamage = armorDamage - armor;
			armorDamage = armor;
		}
	}
	else {
		structureDamage += damageTaken;
	}
	cout << "You dealt " << damageTaken << " damage" << endl;
	if (structureDamage >= structure) {
		isDestroyed = true;
	}
}

void Mech::displayMech() {
	cout << "Name: " << ID << endl;
	cout << "Heat: " << heat << endl;
	cout << "Limb Armor(Stucture)" << endl << "xxxxxxxxxxxxxxxxxxx" << endl;
	cout << "Head: " << L[H].getArmor() - L[H].getArmorDamage() << "(" << L[H].getStructure() - L[H].getStructureDamgage() << ")" << endl;
	cout << "Torso: " << L[CT].getArmor() - L[CT].getArmorDamage() << "(" << L[CT].getStructure() - L[CT].getStructureDamgage() << ")" << endl;
	cout << "Left Arm: " << L[LA].getArmor() - L[LA].getArmorDamage() << "(" << L[LA].getStructure() - L[LA].getStructureDamgage() << ")" << endl;
	cout << "Right Arm: " << L[RA].getArmor() - L[RA].getArmorDamage() << "(" << L[RA].getStructure() - L[RA].getStructureDamgage() << ")" << endl;
	cout << "Left Leg: " << L[LL].getArmor() - L[LL].getArmorDamage() << "(" << L[LL].getStructure() - L[LL].getStructureDamgage() << ")" << endl;
	cout << "Right Leg: " << L[RL].getArmor() - L[RL].getArmorDamage() << "(" << L[RL].getStructure() - L[RL].getStructureDamgage() << ")" << endl;
	cout << "Weapon(shots)" << endl << "xxxxxxxxxxxxxxxxxxx" << endl;
	for (int i = 0; i < L.size(); ++i) {
		if (L[i].getWeapons().size() > 0) {
			for (int j = 0; j < L[i].getWeapons().size(); ++j) {
				cout << L[i].getWeapons()[j] << "(" << L[i].getWeapons()[j].getAmmo().getShots() << ")" << endl;
			}

		}
	}
}

Mech Mech::makeMech(string fileName) {
	vector<string> MP = readData(fileName);
	string ID = MP[0];
	int move = stoi(MP[1]);
	int weight = stoi(MP[2]);

	vector<Limb> parts(6);
	vector<vector<Weapon>> mechWeapons(6);
	vector<vector<Ammo>> mechAmmo(6);

	regex ammoRegex(R"(AC(\d+)Ammo)");
	regex weaponRegex(R"(AC(\d+))");


	int i = 3; // Must be initialized outside the loop so we can find the location where we stop building vectors
	int j = 0;
	for (i; i < MP.size(); ++i) {
		if (MP[i] == "***") {
			++j;
			if (j == 6) {
				break;
			}
		}
		smatch match;
		if (regex_search(MP[i], match, ammoRegex)) {
			int type = stoi(match[1]);
			if (type == 2) {
				mechAmmo[j].push_back(AC2Ammo());
			}
			else if (type == 5) {
				mechAmmo[j].push_back(AC5Ammo());
			}
			else if (type == 10) {
				mechAmmo[j].push_back(AC10Ammo());
			}
			else if (type == 20) {
				mechAmmo[j].push_back(AC20Ammo());
			}
		}
	}

	j = 0;
	int k = 0;
	for (i; i < MP.size(); ++i) {
		if (MP[i] == "xxx") {
			++j;
			if (j == 6) {
				break;
			}
			k = 0;
		}
		// With another round of regex searching we can find the ammo bin associated with each weapon
		// but for now we'll just have to have each bin be in the same location as the weapon
		smatch match;
		if (regex_search(MP[i], match, weaponRegex)) {
			int type = stoi(match[1]);
			if (type == 2) {
				mechWeapons[j].emplace_back(AC2(mechAmmo[j][k]));
				++k;
			}
			else if (type == 5) {
				mechWeapons[j].emplace_back(AC5(mechAmmo[j][k]));
				++k;
			}
			else if (type == 10) {
				mechWeapons[j].emplace_back(AC10(mechAmmo[j][k]));
				++k;
			}
			else if (type == 20) {
				mechWeapons[j].push_back(AC20(mechAmmo[j][k]));
				++k;
			}
		}
	}
	++i; //Enters the mech section of the text file
	Limb head(stoi(MP[i]), stoi(MP[i + 1]), mechWeapons[0]);
	parts[H] = head;
	i += 2;
	Limb torso(stoi(MP[i]), stoi(MP[i + 1]), mechWeapons[1]);
	parts[CT] = torso;
	i += 2;
	Limb leftArm(stoi(MP[i]), stoi(MP[i + 1]), mechWeapons[2]);
	parts[LA] = leftArm;
	i += 2;
	Limb rightArm(stoi(MP[i]), stoi(MP[i + 1]), mechWeapons[3]);
	parts[RA] = rightArm;
	i += 2;
	Limb leftLeg(stoi(MP[i]), stoi(MP[i + 1]), mechWeapons[4]);
	parts[LL] = leftLeg;
	i += 2;
	Limb rightLeg(stoi(MP[i]), stoi(MP[i + 1]), mechWeapons[5]);
	parts[RL] = rightLeg;
	i += 2;

	Mech finishedMech(move, 0, weight, 0, ID, parts);

	return finishedMech;
}

