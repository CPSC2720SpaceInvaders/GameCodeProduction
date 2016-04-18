

/// Testcases for the Bullet

#ifndef __TESTBULLET_H
#define __TESTBULLET_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include "bullet.h"

class TestBullet : public CppUnit::TestFixture {
	CPPUNIT_TEST_SUITE(TestBullet);
	CPPUNIT_TEST(test5CentsIs2Min);
	
	CPPUNIT_TEST_SUITE_END();
	
private:
	BULLET bt;
public:
	void setUp() {
		bt = new BulletImpl;
	}

	void tearDown() {
		delete bt;
	}

	/// the test function. Should display 2 minutes for 5 cents
	void test5CentsIs2Min() {
		ps->addPayment(5);
		CPPUNIT_ASSERT(5/5 * 2 == ps->readDisplay());
	};

	
};

#endif
