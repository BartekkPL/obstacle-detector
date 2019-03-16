#include "socket.hpp"

#include <cerrno>

#include <sys/socket.h>
#include <sys/types.h>

#include "easylogging++.hpp"

namespace sl {
namespace connection {

Socket::Socket() {
  descriptor_ = socket(AF_INET, SOCK_STREAM, 0);
  if (IsValid()) {
    LOG(INFO) << "Successfully created socket: " << descriptor_;
  } else {
    LOG(WARNING) << "Failed to create socket: " << std::strerror(errno);
  }
}

Socket::~Socket() {
  if (shutdown(descriptor_, SHUT_RDWR)) {
    LOG(WARNING) << "Failed to shut down socket: " << descriptor_ << ", "
                 << std::strerror(errno);
  } else {
    LOG(INFO) << "Successfully shutdown of socket: " << descriptor_;
  }
}

bool Socket::IsValid() const {
  return descriptor_ != -1;
}

int Socket::GetDescriptor() const {
  return descriptor_;
}

} // namespace connection
} // namesapce sl
