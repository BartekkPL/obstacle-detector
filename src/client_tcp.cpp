#include "client_tcp.hpp"

#include <cerrno>
#include <cstring>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>

#include "easylogging++.hpp"

namespace sl {
namespace connection {

ClientTCP::ClientTCP(const std::string &address_ip, int port) {
  SetAddress(address_ip, port);
}

ClientTCP::~ClientTCP() {

}

bool ClientTCP::Connect() {
  if (connect(socket_.GetDescriptor(), (struct sockaddr *)&address_,
      sizeof(address_))) {
    LOG(WARNING) << "Cannot connect socket to address " << address_str_ << ":"
                 << ntohs(address_.sin_port) << " : " << std::strerror(errno);
    return false;
  } else {
    LOG(INFO) << "Successfully connected socket to address " << address_str_
              << ":" << ntohs(address_.sin_port);
    return true;
  }
}

void ClientTCP::Send(const std::string &data) {
  int bytes_send = send(socket_.GetDescriptor(), data.data(), data.size(), 0);
  if (bytes_send <= 0) {
    LOG(ERROR) << "Client (" << socket_.GetDescriptor()
               << ") cannot send data: " << std::strerror(errno);
  } else {
    LOG(INFO) << "Client send data";
  }
}

void ClientTCP::SetAddress(const std::string &address_ip, int port) {
  address_str_ = address_ip;
  address_.sin_family = AF_INET;
  address_.sin_port = htons(port);
  inet_pton(AF_INET, address_ip.c_str(), &address_.sin_addr);
}

} // namespace connection
} // namespace sl
