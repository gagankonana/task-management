#ifndef LIBRARY_TASK_MANAGEMENT_TASK_H
#define LIBRARY_TASK_MANAGEMENT_TASK_H

/*
Adds a new task to the system.
Removes a task from the system by ID.
Finds and returns a pointer to the task with the given ID. Returns nullptr if
not found. Returns a list of tasks with the given status. Returns a list of all
tasks in the system. Updates the status of a task by ID.


noun and verbs:
ID (integer, unique identifier)
Title (string)
Status (enum: ToDo, InProgress, Done)
Priority (enum: Low, Medium, High)

task:
system: list <tasks*>


*/
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

enum Status { PENDING, INPROGRESS, COMPLETE };

class Task {
public:
  Task(const int _id, const std::string _title)
      : id{_id}, title{_title}, status{Status::PENDING} {}
  [[nodiscard]] Status get_status() { return status; }
  [[nodiscard]] std::string get_title() { return title; }
  [[nodiscard]] const int get_id() { return id; }
  void update_status(Status _status) { status = _status; }

private:
  const int id;
  const std::string title;
  Status status;
};

class System {
public:
  System() : id{0} {}

  void add_task(std::string title) {
    id++;
    std::shared_ptr<Task> task = std::make_shared<Task>(id, title);
    tasks[title] = task;
  }

  void update_task_status(std::string title, Status status) {
    tasks[title]->update_status(status);
  }

  [[nodiscard]] std::vector<std::shared_ptr<Task>>
  get_tasks_with(const Status status) {
    std::vector<std::shared_ptr<Task>> res;
    for (auto &task : tasks) {
      if (task.second->get_status() == status)
        res.push_back(task.second);
    }
    return res;
  }

  [[nodiscard]] std::vector<std::shared_ptr<Task>> get_all_tasks() {
    std::vector<std::shared_ptr<Task>> res;
    std::transform(tasks.begin(), tasks.end(), std::back_inserter(res),
                   [](auto &task) { return task.second; });
    return res;
  }

  [[nodiscard]] std::shared_ptr<Task> get_task_by_id(const int id) {
    for (auto &task : tasks) {
      if (task.second->get_id() == id)
        return task.second;
    }
    return nullptr;
  }

private:
  std::unordered_map<std::string, std::shared_ptr<Task>> tasks;
  int id;
};

#endif
