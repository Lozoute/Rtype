//
// main.cpp for  in /home/sabbah_j/rendu/TEK3/MovieNation/API/API_CondVar/Implementation/API_CondVar_STD
// 
// Made by jordan sabbah
// Login   <sabbah_j@epitech.net>
// 
// Started on  Tue Jul 21 16:06:30 2015 jordan sabbah
// Last update Tue Jul 21 17:15:33 2015 jordan sabbah
//

#include <thread>
#include <iostream>
#include <queue>
#include <chrono>
#include "API_Mutex_STD.hpp"
#include "API_CondVar_STD.hpp"

int main()
{
  std::queue<int>	produced_nums;
  API_Mutex_STD::Mutex	m;
  CondVar		cond_var;
  bool			done = false;
  bool			notified = false;

  std::thread producer([&]() {
      for (int i = 0; i < 5; ++i) {
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::unique_lock<API_Mutex_STD::Mutex> lock(m);
	std::cout << "producing " << i << '\n';
	produced_nums.push(i);
	notified = true;
	cond_var.notifyOne();
      }

      done = true;
      cond_var.notifyOne();
    });

  std::thread consumer([&]() {
      // std::unique_lock<API_Mutex_STD::Mutex> lock(m);
      while (!done) {
	while (!notified) {  // loop to avoid spurious wakeups
	  cond_var.wait(m);
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
