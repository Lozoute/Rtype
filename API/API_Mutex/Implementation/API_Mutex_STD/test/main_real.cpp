//
// main_real.cpp for  in /home/sabbah_j/rendu/TEK3/MovieNation/API/API_CondVar/Implementation/API_CondVar_STD/test
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jul 21 17:16:53 2015 jordan sabbah
// Last update Tue Jul 21 17:16:54 2015 jordan sabbah
//


#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>
#include <queue>
#include <chrono>

int	main()
{
  std::queue<int> produced_nums;
  std::mutex m;
  std::condition_variable cond_var;
  bool done = false;
  bool notified = false;

  std::thread producer([&]() {
      for (int i = 0; i < 5; ++i) {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::unique_lock<std::mutex> lock(m);
	std::cout << "producing " << i << '\n';
	produced_nums.push(i);
	notified = true;
	cond_var.notify_one();
      }

      done = true;
      cond_var.notify_one();
    });

  std::thread consumer([&]() {
      std::unique_lock<std::mutex> lock(m);
      while (!done) {
	while (!notified) {  // loop to avoid spurious wakeups
	  cond_var.wait(lock);
	}
	while (!produced_nums.empty()) {
	  std::cout << "consuming " << produced_nums.front() << '\n';
	  produced_nums.pop();
	}
	notified = false;
      }
    });

  producer.join();
  consumer.join();
}
