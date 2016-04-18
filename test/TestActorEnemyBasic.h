

/// Testcases for the Actor

#ifndef __TESTACTOR_H
#define __TESTACTOR_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "actorEnemyBasic.h"

class TestActorEnemyBasic : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(TestActorEnemyBasic);
	CPPUNIT_TEST(testInitializeActor0);
	CPPUNIT_TEST(testInitializeActor1);
	CPPUNIT_TEST(testInitializeActor2);
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
		ps->ActorEnemyBasic("Resources/spaceship.png", 50, 50, 20, 20, 0);
		CPPUNIT_ASSERT(3 == ps->getMaxHeal());
	}
	
	void testInitializeActor1() {
		ps->Actor("Resources/spaceship.png", 50, 50, 20, 20, 3);
		CPPUNIT_ASSERT(50 == ps->GetXCoord());
	}
	
	void testInitializeActor2() {
		ps->Actor("Resources/spaceship.png", 50, 50, 20, 20, 3);
		CPPUNIT_ASSERT(50 == ps->GetYCoord());
	}
	
	
};

#endif
