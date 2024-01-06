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

#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

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

void tcp_server_function(void){
  
  bool shutdown = false;
  int sockfd, newsockfd, portno;
  socklen_t clilen;
  char buffer[256];
  struct sockaddr_in serv_addr, cli_addr;
  int n;

  // create a socket
  // socket(int domain, int type, int protocol)
  sockfd =  socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
  {
    perror("ERROR opening socket\r\n");
  }
    // clear address structure
  bzero((char *) &serv_addr, sizeof(serv_addr));

  portno = 2112;

  /* setup the host_addr structure for use in bind call */
  // server byte order
  serv_addr.sin_family = AF_INET;  

  // automatically be filled with current host's IP address
  serv_addr.sin_addr.s_addr = INADDR_ANY;  

  // convert short integer value for port must be converted into network byte order
  serv_addr.sin_port = htons(portno);

    // bind(int fd, struct sockaddr *local_addr, socklen_t addr_length)
    // bind() passes file descriptor, the address structure, 
    // and the length of the address structure
    // This bind() call will bind  the socket to the current IP address on port, portno
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
    perror("ERROR on binding\r\n");
  }

  // This listen() call tells the socket to listen to the incoming connections.
  // The listen() function places all incoming connection into a backlog queue
  // until accept() call accepts the connection.
  // Here, we set the maximum size for the backlog queue to 5.
  listen(sockfd, 2);

    // The accept() call actually accepts an incoming connection
  clilen = sizeof(cli_addr);

  // This accept() function will write the connecting client's address info 
  // into the the address structure and the size of that structure is clilen.
  // The accept() returns a new socket file descriptor for the accepted connection.
  // So, the original socket file descriptor can continue to be used 
  // for accepting new connections while the new socker file descriptor is used for
  // communicating with the connected client.
  newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
  if (newsockfd < 0) {
    perror("ERROR on accept\r\n");
  } 
  else {

    printf("Connection established\r\n");
  }
    //printf("server: got connection from %s port %d\n", inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));


  // This send() function sends the 13 bytes of the string to the new socket
  const char hello[] = "Hello, client!\r\n";
  const char bye[] = "Goodbye, client!\r\n";
  send(newsockfd, &hello, sizeof(hello), 0);

  bzero(buffer,256);


  while(true != shutdown)
  {
    n = read(newsockfd,buffer,1);
    if (n < 0) 
    {
      shutdown = true;
      perror("ERROR reading from socket");
    } else {
      if(buffer[0] == 0x71){shutdown = true;}
      
      printf("Received: %d\r\n",buffer[0] &0xFFFFFFFF);

      send(newsockfd, &buffer, 1, 0);
    }


  }

  send(newsockfd, &bye, sizeof(bye), 0);
  sleep(2);
  close(newsockfd);
  close(sockfd);

}



#ifdef __cplusplus
extern "C"
{
#endif

void init_network(void);

#ifdef __cplusplus
}
#endif


#include <rtems/thread.h>

int main(int argc, char* argv[])
{
  
  rtems_recursive_mutex mutex;
  char mtx_name[] = "asdsadaddssad";

  rtems_recursive_mutex_init( &mutex, (const char*) &mtx_name);

  std::mutex mtx;
  std::vector<std::thread> threads(N_CPU+1);
  init_network();

  for (int32_t i = 0; i < N_CPU; i++) {
    threads[i] = std::thread(thread_function, std::ref(mtx), i * 500 );
      
      cpu_set_t cpuset;
      CPU_ZERO(&cpuset);
      CPU_SET(i, &cpuset);
      int rc = pthread_setaffinity_np(threads[i].native_handle(),
                                      sizeof(cpu_set_t), &cpuset);
      if (rc != 0) {
        std::cout << "Error calling pthread_setaffinity_np: " << rc << std::endl;
      }    
  }

  threads[N_CPU] = std::thread(tcp_server_function );

  for (auto& t : threads) {
    t.join();
  }

  return 0;
}
