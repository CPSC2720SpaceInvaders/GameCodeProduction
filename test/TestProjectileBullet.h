

/// Testcases for the Actor

#ifndef __TESTACTOR_H
#define __TESTACTOR_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Bullet.h"

class TestBullet : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(TestBullet)
	CPPUNIT_TEST(testProjectileBullet0);
	CPPUNIT_TEST(testProjectileBullet1);
	CPPUNIT_TEST(testProjectileBullet2);
	
	CPPUNIT_TEST_SUITE_END();
	
private:
	Projectile ps;
public:
	void setUp() {
		ps = new ProjectileImpl;
	}
	
	void tearDown() {
		delete ps;
	}

	/// the test function. Should display 3 for maxHealth
	void testProjectileBullet0() {
		ps->ProjectileBullet(60, 70, 5, "Resources/spaceship.png"，3);
		CPPUNIT_ASSERT(60 == ps->GetXCoord());
	}
	
	void testProjectileBullet1() {
		ps->ProjectileBullet(60, 70, 5, "Resources/spaceship.png"，3);
		CPPUNIT_ASSERT(70 == ps->GetYCoord());
	}
	
	void testProjectileBullet2() {
		ps->ProjectileBullet(60, 70, 5, "Resources/spaceship.png"，3);
		CPPUNIT_ASSERT(30 == ps->GetBulletDamage());
	}
	
	
};

#endif
