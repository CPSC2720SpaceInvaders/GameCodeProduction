// main test module

#include <cppunit/ui/text/TestRunner.h>
#include "TestActor.h"
#include "TestBullet.h"

int main() {
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(TestActor::suite());
	runner.addTest(TestActorEnemyBasic::suite());
	runner.addTest(TestBullet::suite());
	runner.addTest(TestProjectile::suite());
	runner.addTest(TestProjectileBullet::suite());
	
	runner.run();
	return 0;
}
