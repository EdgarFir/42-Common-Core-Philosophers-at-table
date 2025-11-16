# 🧠 Philosophers

**Philosophers** is a 42 project that introduces essential concepts of **concurrency**, **threads**, **synchronization**, and **race conditions**, through the classical “Dining Philosophers Problem”.

The goal is to implement a simulation where several philosophers eat, think, and sleep while competing for shared resources (forks), ensuring no philosopher dies from starvation and avoiding deadlocks.

---

## 📘 Project Goal

You must implement the behavior of the philosophers following these rules:

- Philosophers alternate between **eating**, **thinking**, and **sleeping**.
- To eat, a philosopher must pick up **two forks**: one on the left and one on the right.
- Each philosopher has a maximum amount of time they can stay without eating before dying.
- The simulation must stop when:
  - A philosopher dies, **or**
  - Every philosopher has eaten the required number of times (optional argument).

---

### Description

| Argument | Meaning |
|----------|---------|
| `number_of_philosophers` | Number of philosophers (and forks) |
| `time_to_die` | Time (ms) before a philosopher dies without eating |
| `time_to_eat` | Time (ms) a philosopher spends eating |
| `time_to_sleep` | Time (ms) a philosopher spends sleeping |
| `number_of_times_each_philosopher_must_eat` (optional) | Simulation ends when all philosophers reach this count |

---

## 🔧 Implementation Rules

- Philosophers must be represented as **threads**.
- Forks must be represented using **mutexes**.
- **Deadlocks must be avoided**.
- Output to the terminal must be **properly synchronized**.
- Time management must be **accurate** (`gettimeofday()` / `usleep()` recommended).

---

## 🧠 Key Concepts

- Threads (`pthread_create`, `pthread_join`)
- Mutexes (`pthread_mutex_lock`, `pthread_mutex_unlock`)
- Race conditions
- Deadlocks and starvation
- Output synchronization
- Time accuracy in concurrent systems

---

## 🧪 Common Mistakes to Avoid

- Philosophers dying unexpectedly due to poor timing logic
- Deadlocks when all philosophers try to pick the same fork first
- Using large `usleep()` values, creating imprecise behavior
- Mixed or corrupted terminal outputs
- Forgetting to lock the printing mutex

---

## 📚 About

This project is part of the **42** curriculum and aims to teach the fundamentals of concurrency and parallel programming.

