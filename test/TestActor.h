

/// Testcases for the Actor

#ifndef __TESTACTOR_H
#define __TESTACTOR_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "actor.h"

class TestActor : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(TestActor);
	CPPUNIT_TEST(testInitializeActor0);
	CPPUNIT_TEST(testInitializeActor1);
	CPPUNIT_TEST(testInitializeActor2);
	CPPUNIT_TEST(testInitializeActor3);
	CPPUNIT_TEST(testInitializeActor4);
	CPPUNIT_TEST(testInitializeActor5);
	CPPUNIT_TEST(testCanPlayerShoot0);
	CPPUNIT_TEST(testCanPlayerShoot1);
	CPPUNIT_TEST(testCanPlayerShoot2);
	CPPUNIT_TEST_SUITE_END();
	
private:
	Actor ps;
public:
	void setUp() {
		ps = new ActorImpl;
	}

	void tearDown() {
		delete ps;
	}

	/// the test function. Should display 3 for maxHealth
	void testInitializeActor0() {
		ps->Actor("Resources/spaceship.png", 50, 50, 20, 20, 0);
		CPPUNIT_ASSERT(3 == ps->getHealth());
	}
	
	/// the test function. Should display 1 for maxHealth
	void testInitializeActor1() {
		ps->Actor("Resources/spaceship.png", 50, 50, 20, 20, 1);
		CPPUNIT_ASSERT(1 == ps->getHealth());
	}
	
	/// the test function. Should display 2 for maxHealth
	void testInitializeActor2() {
		ps->Actor("Resources/spaceship.png", 50, 50, 20, 20, 2);
		CPPUNIT_ASSERT(2 == ps->getHealth());
	}
	
	/// the test function. Should display 3 for maxHealth
	void testInitializeActor3() {
		ps->Actor("Resources/spaceship.png", 50, 50, 20, 20, 3);
		CPPUNIT_ASSERT(3 == ps->getHealth());
	}
	
	void testInitializeActor4() {
		ps->Actor("Resources/spaceship.png", 50, 50, 20, 20, 3);
		CPPUNIT_ASSERT(50 == ps->GetXCoord());
	}
	
	void testInitializeActor5() {
		ps->Actor("Resources/spaceship.png", 50, 50, 20, 20, 3);
		CPPUNIT_ASSERT(50 == ps->GetYCoord());
	}
	
	void testCanPlayerShoot0() {
		ps->canPlayerShoot(0);
		CPPUNIT_ASSERT(true);
	}
	
	void testCanPlayerShoot1() {
		ps->canPlayerShoot(1);
		CPPUNIT_ASSERT(false);
    }
	
	void testCanPlayerShoot2() {
		ps->canPlayerShoot(2);
		CPPUNIT_ASSERT(false);
    }
};

#endif
