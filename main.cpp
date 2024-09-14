#include "task.h"
#include <iostream>
#include <cassert>
#include "scheduler.h"
class Test {
public:
    Test() { reset(); }
    static Test get_instance() { static Test instance; return instance; }
    void reset() {
        test_system = {};
        test_system.add_task("task1");
        test_system.add_task("task2");
        test_system.add_task("task3");
        test_system.add_task("task4");
        test_system.update_task_status("task1", Status::INPROGRESS);
        test_system.update_task_status("task2", Status::COMPLETE);
    }

    void test_get_tasks() {
        assert(test_system.get_all_tasks().size() == 4);
        assert(test_system.get_tasks_with(Status::PENDING).size() == 2);
        assert(test_system.get_tasks_with(Status::INPROGRESS).size() == 1);
        assert(test_system.get_tasks_with(Status::COMPLETE).size() == 1);
        std::cout << "Done testing";
    }
private:
    System test_system;
};



int main() {
    // Test::get_instance().test_get_tasks();
    
    return 1;
}