/* SPDX-License-Identifier: BSD-2-Clause */
/*
 * Copyright (C) 2023 Bernd Moessner
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#define  _GNU_SOURCE
#include <errno.h>
#include <pthread.h>
#include <sched.h>
#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include <rtems/score/smp.h>




#define N_CPU 2 


void print_hello(int32_t cpu)
{
  std::cout << "Hello from CPU: " << std::to_string(cpu) << std::endl;
}


void thread_function(std::mutex &mtx, int32_t startup_delay){
  
  std::this_thread::sleep_for(std::chrono::milliseconds(startup_delay));

  for (int32_t i=0; i<10; i++)
  {
    mtx.lock();
    print_hello((int32_t) _SMP_Get_current_processor());
    mtx.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}



int main(int argc, char* argv[])
{
  /*
  while(1)
  {
    std::cout << "Hello from CPU: " << std::to_string(1) << std::endl;

  }
 */
  std::mutex mtx;
  std::vector<std::thread> threads(N_CPU);

  for (int32_t i = 0; i < N_CPU; i++) {
    threads[i] = std::thread(thread_function, std::ref(mtx), i * 500 );
      /*
      cpu_set_t cpuset;
      CPU_ZERO(&cpuset);
      CPU_SET(i, &cpuset);
      int rc = pthread_setaffinity_np(threads[i].native_handle(),
                                      sizeof(cpu_set_t), &cpuset);
      if (rc != 0) {
        std::cout << "Error calling pthread_setaffinity_np: " << rc << std::endl;
      }
      */
  }

  for (auto& t : threads) {
    t.join();
  }

  return 0;
}
