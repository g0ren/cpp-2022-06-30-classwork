#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>

using namespace std;

class Bullet {
protected:
	int speed;
public:
	virtual void showType() = 0;
	virtual void shot() = 0;
	virtual ~Bullet() {
	}
};

class SpeedBullet: public Bullet {
public:
	SpeedBullet() {
		speed = 8;
	}
	void showType() {
		cout << "AK-47";
	}
	void shot() {
		for (int i = 0; i < 80 / speed; ++i) {
			for (int j = 0; j < i * speed; ++j) {
				cout << ' ';
			}
			cout << '*';
			sleep(1);
			//system("clear");
		}

	}
};

class MultiBullet: public Bullet {
public:
	MultiBullet() {
		speed = 4;
	}
	void showType() {
		cout << "ShutGun";
	}
	void shot() {
		string delta = "";
		for (int i = 0; i < 80 / speed; ++i) {
			for (int j = 0; j < i * speed; ++j) {
				delta += ' ';
			}
			cout << delta << "*   * " << endl;
			cout << delta << " *" << endl;
			cout << delta << " *    *" << endl;
			sleep(2);
			//system("clear");
		}

	}
};

class Gun {
public:
	virtual Bullet* getBullet() = 0;
	virtual ~Gun() {
	}
};

class GunBuilder {
protected:
	Bullet *bullet;
public:
	virtual Bullet* getBullet()=0;
	virtual void setBulletType()=0;
	virtual void setBulletSpeed()=0;
	virtual ~GunBuilder() {
	}
};

class SpeedGunBuilder: public GunBuilder {
	Bullet* getBullet() {
		return new SpeedBullet;
	}
	void setBulletType() {
	}
	void setBulletSpeed() {
	}
};

class ShotGunBuilder: public GunBuilder {
	Bullet* getBullet() {
		return new MultiBullet;
	}
	void setBulletType() {
	}
	void setBulletSpeed() {
	}
};

class Trooper {
	GunBuilder *builder;
public:
	Trooper(GunBuilder *builder) {
		this->builder = builder;
	}
	void setGun(GunBuilder *builder) {
		this->builder = builder;
	}
	Bullet* makeBullet() {
		return this->builder->getBullet();
	}
};

class SpeedGun: public Gun {
public:
	Bullet* getBullet() {
		return new SpeedBullet();
	}
};

class ShotGun: public Gun {
public:
	Bullet* getBullet() {
		return new MultiBullet();
	}
};

//--------------------------------------------------------------------------------------------------------
class solid {
	Gun *gun;
	vector<Bullet*> bullets;
public:
	Gun* getGun() {
		return this->gun;
	}
	void setGun(Gun *gun) {
		this->gun = gun;
	}

	void setBullets(vector<Bullet*> bullets) {
		this->bullets = bullets;
	}

};

//Абстрактная Фабрика
class trooper {
protected:
	vector<Bullet*> bullets;
public:
	virtual Gun* getGun() = 0;
	virtual vector<Bullet*> getBullets() = 0;
	virtual ~trooper() {
	}
};
//конкретная фабрика
class Assault: public trooper {
public:
	Gun* getGun() {
		return new SpeedGun();
	}
	vector<Bullet*> getBullets() {
		bullets.resize(rand() % 50);
		generate(bullets.begin(), bullets.end(), []() {
			return new SpeedBullet();
		});
		return bullets;
	}
};
//конкретная фабрика
class Medic: public trooper {
public:
	Gun* getGun() {
		return new ShotGun();
	}
	vector<Bullet*> getBullets() {
		bullets.resize(rand() % 10);
		generate(bullets.begin(), bullets.end(), []() {
			return new MultiBullet();
		});
		return bullets;
	}
};
//конкретная фабрика
class Experiment: public trooper {
public:
	Gun* getGun() {
		return new ShotGun();
	}
	vector<Bullet*> getBullets() {
		bullets.resize(rand() % 1000);
		generate(bullets.begin(), bullets.end(), []() {
			return new SpeedBullet();
		});
		return bullets;
	}
};
//Конечный конструктор
class Army {
	trooper *_trooper;
public:
	Army(trooper *_trooper) {
		this->_trooper = _trooper;
	}

	void setFactory(trooper *_trooper) {
		this->_trooper = _trooper;
	}

	solid& makeSolid() {
		solid tmp;
		tmp.setBullets(_trooper->getBullets());
		tmp.setGun(_trooper->getGun());
		return tmp;
	}

};

int main() {
	Army army(new Medic);
	solid medic = army.makeSolid();
	army.setFactory(new Assault);
	solid assault = army.makeSolid();
	medic.getGun()->getBullet()->shot();

//	Trooper trooper(new ShotGunBuilder);
//	trooper.makeBullet()->shot();
//	trooper.setGun(new SpeedGunBuilder);
//	trooper.makeBullet()->shot();
//
//	vector<Gun*> guns = { new SpeedGun, new ShotGun };
//	int command { };
//	int pos { };
//	while (command != 4) {
//		cout << "1. prev gun" << endl;
//		cout << "2. next gun" << endl;
//		cout << "3. fire gun" << endl;
//		cout << "4. exit" << endl;
//		cin >> command;
//		switch (command) {
//		case 1:
//			pos = (guns.size() + pos - 1) % guns.size();
//			break;
//		case 2:
//			pos = (guns.size() + pos + 1) % guns.size();
//			break;
//		case 3:
//			guns[pos]->getBullet()->shot();
//			break;
//		}
//	}
}

