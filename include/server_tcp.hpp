#ifndef LOCALIZATOR_SERVER_TCP_HPP_
#define LOCALIZATOR_SERVER_TCP_HPP_

#include <mutex>
#include <string>
#include <vector>

#include <netinet/in.h>

#include "json.hpp"
#include "socket.hpp"

namespace sl {
namespace connection {

class ServerTCP {
 public:
  ServerTCP(int port);
  ~ServerTCP();

  nlohmann::json GetData();

  std::vector<unsigned char> GetRawData();

  bool IsStopped();

  void Run();

  bool Start();

  void Stop();

 private:
  struct sockaddr_in address_;
  std::string address_str_;
  std::vector<unsigned char> buffer_;
  std::mutex buffer_mutex_;
  int received_;
  std::mutex stopped_mutex_;
  Socket socket_;
  bool stopped_;

  const size_t MAX_BUFFER_SIZE = 5000000;
};

} // namespace connection
} // namespace sl

#endif // LOCALIZATOR_SERVER_TCP_HPP_
