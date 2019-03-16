#ifndef LOCALIZATOR_SOCKET_HPP_
#define LOCALIZATOR_SOCKET_HPP_

namespace sl {
namespace connection {

class Socket {
 public:
  Socket();
  ~Socket();
  int GetDescriptor() const;
  bool IsValid() const;
 private:
  int descriptor_;
};

} // namespace connection
} // namespace sl

#endif // LOCALIZATOR_SOCKET_HPP_
