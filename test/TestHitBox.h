

/// Testcases for the Actor

#ifndef __TESTACTOR_H
#define __TESTACTOR_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "Hitbox.h"

class TestHitbox : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(TestHitbox)
	CPPUNIT_TEST(testInitializeHitBox0);
	CPPUNIT_TEST(testInitializeHitBox1);
	CPPUNIT_TEST(testInitializeHitBox2);
	CPPUNIT_TEST(testInitializeHitBox3);
	CPPUNIT_TEST(testMoveHitbox0);
	CPPUNIT_TEST(testMoveHitbox1);
	
	
	CPPUNIT_TEST_SUITE_END();
	
private:
	Hitbox ps;
	Hitbox ps1;
	Hitbox ps2;
public:
	void setUp() {
		ps = new HitboxImpl;
		ps1 = new HitboxImpl(50,50,30,40);
		ps2 = new HitboxImpl(10,10,20,30);

	}

	void tearDown() {
		delete ps;
	}

	/// the test function. Should display 3 for maxHealth
	void testInitializeHitBox0() {
		ps->Hitbox(50, 60, 20, 30);
		CPPUNIT_ASSERT(50 == ps->GetHitboxX());
	}
	
	/// the test function. Should display 1 for maxHealth
	void testInitializeHitBox1() {
		ps->Actor(50, 60, 20, 30);
		CPPUNIT_ASSERT(60 == ps->GetHitboxY());
	}
	
	/// the test function. Should display 2 for maxHealth
	void testInitializeActor2() {
		ps->Actor(50, 60, 20, 30);
		CPPUNIT_ASSERT(20 == ps->GetHitboxWidth());
	}
	
	void testInitializeActor3() {
		ps->Actor(50, 60, 20, 30);
		CPPUNIT_ASSERT(30 == ps->GetHitboxHeight());
	}
	
	
	void testMoveHitbox0() {
		ps->Actor(50, 60, 20, 30);
		ps->MoveHitbox(10,10);
		CPPUNIT_ASSERT(60 == ps->GetHitboxX());
	}
	
	void testMoveHitbox1() {
		ps->Actor(50, 60, 20, 30);
		ps->MoveHitbox(10,10);
		CPPUNIT_ASSERT(70 == ps->GetHitboxX());
	}
	
	void testCheckForCollision0(){
			ps -> CheckForCollision(p1);
			CPPUNIT_ASSERT(true);
	}
	
	void testCheckForCollision1(){
			ps -> CheckForCollision(p2);
			CPPUNIT_ASSERT(false);
	}
};

#endif
