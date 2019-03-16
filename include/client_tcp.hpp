#ifndef LOCALIZATOR_CLIENT_TCP_HPP_
#define LOCALIZATOR_CLIENT_TCP_HPP_

#include <string>
#include <vector>

#include <netinet/in.h>

#include "socket.hpp"

namespace sl {
namespace connection {

class ClientTCP {
 public:
  ClientTCP(const std::string &address_ip, int port);
  ~ClientTCP();

  bool Connect();
  void Send(const std::string &data);
  void SetAddress(const std::string &address_ip, int port);
 private:
  struct sockaddr_in address_;
  std::string address_str_;
  Socket socket_;
};

} // namespace connection
} // namespace sl

#endif // LOCALIZATOR_CLIENT_TCP_HPP_
