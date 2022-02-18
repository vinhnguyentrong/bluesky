
#include <iostream>
#include <mutex>
#include <thread>
#include <ctime>
#include <condition_variable>


/******************************************************************************/
/* 8.4 Avoiding using recursive mutex
 *
 ******************************************************************************/
class foo_rec
{
  std::mutex m_mutex;
  int m_data;

public:
  foo_rec(int const d = 0) : m_data(d) {};
  
  void internal_update(int const d) {m_data = d;}

  void update(int const d)
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    internal_update(d);
  }

  int update_return(int const d)
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto temp = m_data;
    internal_update(d);
    return temp;
  }

};

void using_foo_rec1(foo_rec &foo)
{
  foo.update(20);
  std::cout << "update value: " << 20 << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "update and return: " << foo.update_return(200) << std::endl;
}

void using_foo_rec2(foo_rec &foo)
{
  std::cout << "update and return: " << foo.update_return(300) << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(2));
  foo.update(30);
  std::cout << "update value: " << 30 << std::endl;
}

int main_84()
{

  foo_rec foo1(1000);

  std::thread t1(using_foo_rec1, std::ref(foo1));
  std::thread t2(using_foo_rec2, std::ref(foo1));

  t1.join();
  t2.join();
  return 0;
}

/******************************************************************************/
/* 8.5: Sending notifications between threads
 *
 ******************************************************************************/



int main_85()
{
  std::condition_variable cv;
  std::mutex cv_mutex;
  std::mutex io_mutex;

  int data = 0;

  std::thread tcv1([&] () {

    std::cout << "[producer]: producing data" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    {
      std::unique_lock<std::mutex> lock(cv_mutex);
      data = 42;
    }

    {
      std::lock_guard<std::mutex> l1(io_mutex);
      std::cout << "[producer]: produced data and sent notify to consumer "
                << data << std::endl;
      cv.notify_one();
    }

  });

  std::thread tcv2([&] () {

    std::cout << "[consumer]: wait for the signal from producer" << std::endl;
    // wait for notification
    {
      std::unique_lock<std::mutex> lock(cv_mutex); // cannot use lock_guard,
                      //the condition variable associated with std::unique_lock()
      cv.wait(lock);
    }

    {
      std::lock_guard<std::mutex> lock(io_mutex);
      std::cout << "[consumer]: consumed data: " << data << std::endl;
    }

  });

  tcv1.join();
  tcv2.join();

////////////////////////////////////////////////////////////////////////////////

  std::thread master([&] () {
    std::cout << "[Master] process data" << std::endl;
    {
      std::lock_guard<std::mutex> l1(cv_mutex);
      data = 1000;
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "[Master] send notify" << std::endl;
    {
      cv.notify_all();
    }
  });

  std::thread slave1([&] () {
    std::cout << "[Slave1]: wait for notification" << std::endl;
    {
      std::unique_lock<std::mutex> l1(cv_mutex);
      cv.wait(l1);
      // at here l1 is still locking 
      // because after wake up the thread require imediately the lock l1
      // l1.lock(); // --> deadlock cannot call.
      // std::cout << "still can lock l1, not deadlock" << std::endl;
      // l1.unlock(); // don't need to call
    }
    std::cout << "[Slave1]: consumed data: " << data << std::endl;
  });

  std::thread slave2([&] () {
    std::cout << "[Slave2]: wait for notification" << std::endl;
    {
      std::unique_lock<std::mutex> l1(cv_mutex);
      cv.wait(l1);
    }
    std::cout << "[Slave2]: consumed data: " << data << std::endl;
  });

  std::thread slave3([&] () {
    std::cout << "[Slave3]: wait for notification" << std::endl;
    {
      std::unique_lock<std::mutex> l1(cv_mutex);
      cv.wait(l1);
    }
    std::cout << "[Slave3]: consumed data: " << data << std::endl;
  });

  master.join();
  slave1.join();
  slave2.join();
  slave3.join();

  return 0;

}



/******************************************************************************/
/* 8.6
 *
 ******************************************************************************/
#include <queue>
#include <random> // std::mt19973, std::seed_seq
#include <algorithm> // std::generate

namespace Thread86
  {
    std::mutex g_lockprint;
    std::mutex g_lockqueue;
    std::condition_variable g_queuecheck;
    std::queue<int> g_buffer;
    bool g_done;

    void producer(int const id,
        std::mt19937& generator,
        std::uniform_int_distribution<int>& dsleep,
        std::uniform_int_distribution<int>& dcode)
    {
      for (int i = 0; i < 5; ++i)
      {
        // simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(dsleep(generator)));

        // generate data
        {
          std::unique_lock<std::mutex> l1(g_lockqueue);
          int value = id * 100 + dcode(generator);      // loop until end is signaled
          g_buffer.push(value);

          {
            std::unique_lock<std::mutex> l2(g_lockprint);
            std::cout << "[produced(" << id << ")]: " << value << std::endl;
          }
        }

        // notify consumers
        g_queuecheck.notify_one();
      }
    }

    void consumer()
    {
      // loop until end is signaled
      while (!g_done)
      {
        std::unique_lock<std::mutex> l1(g_lockqueue);
        g_queuecheck.wait_for(l1, std::chrono::seconds(1),
            [&] () { return !g_buffer.empty(); });

        // if there are value in queue process them
        while (!g_done && !g_buffer.empty())
        {
          std::unique_lock<std::mutex> l2(g_lockprint);
          std::cout << "[consumer]: " << g_buffer.front() << std::endl;
          g_buffer.pop();
        }
      }
    }
}
int main_86()
{
  auto seed_data = std::array<int, std::mt19937::state_size> {};
  std::random_device rd {};
  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));

  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));

  auto generator = std::mt19937{seq};
  auto dsleep = std::uniform_int_distribution<> {100, 500};
  auto dcode = std::uniform_int_distribution<> {1, 99};

  std::cout << "start producing and consumming..." << std::endl;

  std::thread consumerThread(Thread86::consumer);
  std::vector<std::thread> producerThreads;

  for (int i = 0; i < 5; ++i)
  {
    producerThreads.emplace_back(Thread86::producer,
        i + 1,
        std::ref(generator),
        std::ref(dsleep),
        std::ref(dcode));
  }

  // work for the worker to finish
  for (auto& t : producerThreads)
  {
    t.join();
  }
  // notify the logger to finish and wait for it
  Thread86::g_done = true;
  consumerThread.join();
  std::cout << "done producing and consuming" << std::endl;



  return 0;
}

/******************************************************************************/
/* Main func
 *
 ******************************************************************************/

int main()
{
  return main_86();
  // return main_85();
  // return main_84();
}