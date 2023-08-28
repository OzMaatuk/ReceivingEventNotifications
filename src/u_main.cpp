// Skelton provided, not woking code.

/*

#include <iostream>
#include <unistd.h>
#include <sys/inotify.h>
#include <string>
#include <thread>
#include <queue>
#include "Config.h"

using namespace std;

// Function to read events from the inotify instance.
void read_events(int inotify_fd, queue<struct inotify_event> *event_queue) {
  // Create a buffer to store events.
  char buffer[1024];

  // Infinite loop to read events.
  while (true) {
    // Read events from the inotify instance.
    int event_size = read(inotify_fd, buffer, sizeof(buffer));

    // Loop through the events.
    for (int i = 0; i < event_size / sizeof(struct inotify_event); i++) {
      // Get the event.
      struct inotify_event *event = (struct inotify_event *)(buffer + i * sizeof(struct inotify_event));

      // Add the event to the queue.
      event_queue->push(event);
    }
  }
}

// Function to process events from the queue.
void process_events(queue<struct inotify_event> *event_queue, int sinterval) {
    while (true) {
        // Process events from the queue.
        while (!event_queue->empty()) {
            // Get the event from the queue.
            struct inotify_event event = event_queue->front();
            event_queue->pop();

            // Check if the event is for a process start or stop.
            if (event->mask & (IN_CREATE | IN_DELETE)) {
            // Get the process name.
            string process_name = event->name;

            // Print the event.
            cout << "Process " << process_name << " " << (event->mask & IN_CREATE ? "started" : "stopped") << endl;
            }
        }
        Sleep(sinterval);
    }
}

*/

int u_main(Config c, int iArgCnt, char ** argv) {
  /*
  // Create an inotify instance.
  int inotify_fd = inotify_init1(IN_CLOEXEC);

  // Create a watch for the /proc/ directory.
  int watch_fd = inotify_add_watch(inotify_fd, "/proc", IN_CREATE | IN_DELETE);

  // Create a queue to store events.
  queue<struct inotify_event> event_queue;

  // Create a thread to read events.
  thread read_thread(read_events, inotify_fd, &event_queue);

  // Create a thread to process events.
  thread process_thread(process_events, &event_queue, c.sleep_inetrval);

  // Join the threads.
  read_thread.join();
  process_thread.join();

  // Close the inotify instance.
  close(inotify_fd);

  */
  return 0;
}

// You are right. There is no `/usr/include` directory on Windows. The inotify library is not available for Windows. You can use the inotify-tools package on Windows, but you will need to compile it from source.

// To compile the inotify-tools package from source on Windows, you can use the following steps:

// 1. Download the inotify-tools source code from the following link:

// ```
// https://github.com/rvoicilas/inotify-tools
// ```

// 2. Extract the inotify-tools source code:

// ```
// tar -xf inotify-tools-3.14.tar.gz
// ```

// 3. Navigate to the inotify-tools-3.14 directory.
// 4. Open a command prompt window in the inotify-tools-3.14 directory.
// 5. Run the following command to compile the inotify-tools package:

// ```
// mingw32-gcc -o inotify-tools inotify-tools.c
// ```

// Once you have compiled the inotify-tools package, you can run it by typing the following command in the command prompt window:

// ```
// inotify-tools
// ```

// The inotify-tools package will not be able to detect file changes on Windows, but you can use it to test your code.

// I hope this helps! Let me know if you have any other questions.