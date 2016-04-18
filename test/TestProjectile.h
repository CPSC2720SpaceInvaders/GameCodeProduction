

/// Testcases for the Actor

#ifndef __TESTACTOR_H
#define __TESTACTOR_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Projectile.h"

class TestProjectile : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(TestProjectile)
	CPPUNIT_TEST(testInitializeProjectile0);
	CPPUNIT_TEST(testInitializeProjectile1);
	
	
	CPPUNIT_TEST(testAssignment0);
	CPPUNIT_TEST(testAssignment1);
	
	
	CPPUNIT_TEST_SUITE_END();
	
private:
	Projectile ps;
	Projectile ps1;
public:
	void setUp() {
		ps = new ProjectileImpl;
		ps1 = new ProjectileImpl(50,40,4,"Resources/spaceship.png"，30);

	void tearDown() {
		delete ps;
	}

	/// the test function. Should display 3 for maxHealth
	void testInitializeProjectile0() {
		ps->Projectile(100, 200, 5, "Resources/spaceship.png"，30);
		CPPUNIT_ASSERT(100 == ps->GetXCoord());
	}
	
	void testInitializeProjectile1() {
		ps->Projectile(100, 200, 5, "Resources/spaceship.png"，30);
		CPPUNIT_ASSERT(200 == ps->GetYCoord());
	}
	
	void testAssignment0() {
		ps->Projectile(p2);
		CPPUNIT_ASSERT(50 == ps->GetXCoord());
	}
	
	void testAssignment1() {
		ps->Projectile(p2);
		CPPUNIT_ASSERT(40 == ps->GetYCoord());
	}
	
};

#endif
