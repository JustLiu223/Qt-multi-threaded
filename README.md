# Qt-multi-threaded
Mastering the use of multithreading in a Qt environment with a sorting example
- The first version of the solution is to create multi-threaded subclasses and rewrite the run function to realize different functions
- The second version of the solution is separate task objects and threads, create different task objects, then create sub-threads as needed, and assign a task to each sub-thread
- The third version of the solution is use thread pool to manage sub-threads, through multiple inheritance to rewrite the run function to realize different functions
---

### Code writing ideas are taken from website tutorials:
[Qt中多线程-线程池的使用-C/C++/qt:爱编程的大丙](https://www.bilibili.com/video/BV1iN411f7dY?p=1&vd_source=2f6285ca5e3f3d647eb1742c99cf1127)