#include <boost/test/unit_test.hpp>
#include <pose3d_editor/Dummy.hpp>

using namespace pose3d_editor;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    pose3d_editor::DummyClass dummy;
    dummy.welcome();
}
