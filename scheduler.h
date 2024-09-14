#ifndef _LIBRARY_TASK_MANAGEMENT_SCHEDULER_H
#define _LIBRARY_TASK_MANAGEMENT_SCHEDULER_H

#include <chrono>
#include <functional>
#include <thread>
#include <vector>
class Schedule {
public:
    Schedule() {}
    void addTask(std::function<void>* task, std::chrono::milliseconds delay) { tasks.push_back(std::make_pair(task, delay));}
    void run_task(std::function<void>* task, std::chrono::milliseconds delay) {
        
    }
    void run() {
        for (auto& fun : tasks) {
            std::thread thread_obj(&Schedule::run_task, fun.first, fun.second);
            threads.push_back(&thread_obj);
        }
        for (auto th : threads) {
            th->join();
        }
    }
private:
    std::vector<std::pair<std::function<void>*, std::chrono::milliseconds>> tasks;
    std::vector<std::thread*> threads;
};

#endif