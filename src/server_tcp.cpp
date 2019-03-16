#include "server_tcp.hpp"

#include <chrono>
#include <thread>

#include <sys/socket.h>
#include <sys/types.h>

#include <opencv2/opencv.hpp>

#include "easylogging++.hpp"

using namespace std::chrono_literals;

namespace sl {
namespace connection {

ServerTCP::ServerTCP(int port) {
  address_.sin_family = AF_INET;
  address_.sin_port = htons(port);
  address_.sin_addr.s_addr = htons(INADDR_ANY);
  received_ = 0;
}

ServerTCP::~ServerTCP() {

}

nlohmann::json ServerTCP::GetData() {
  std::lock_guard<std::mutex> lock(buffer_mutex_);

  nlohmann::json result = {};

  try {
    result = nlohmann::json::parse(buffer_.data());
  } catch (std::exception &e) {
    LOG(ERROR) << "Problem with parse JSON from server buffer: " << e.what();
  }

  return result;
}

std::vector<uchar> ServerTCP::GetRawData() {
  std::lock_guard<std::mutex> lock(buffer_mutex_);

  std::vector<uchar> result(buffer_.begin(), buffer_.begin() + received_);
  received_ = 0;
  return result;
}


bool ServerTCP::IsStopped()
{
    std::lock_guard<std::mutex> lock(stopped_mutex_);
    return stopped_;
}

void ServerTCP::Run() {
  stopped_ = false;
  LOG(INFO) << "Waiting for connection...";

  struct sockaddr_in client = { };
  socklen_t len;

  int client_socket = accept(socket_.GetDescriptor(),
                            (struct sockaddr *) &client, &len);

  if (client_socket < 0) {
    LOG(ERROR) << "Accept connection problem: " << std::strerror(errno);
    return;
  } else {
    LOG(INFO) << "Accepted connection from client " << client_socket;
  }

  cv::namedWindow("Display window", cv::WINDOW_NORMAL);// Create a window for display.
  cv::resizeWindow("Display window", cv::Size(600, 600));

  while (!IsStopped()) {
    buffer_mutex_.lock();
    buffer_.clear();
    buffer_.reserve(MAX_BUFFER_SIZE);

    int32_t num = 0;

    int recv_num = recv(client_socket, &num, 4,
                        MSG_WAITALL);

    num = ntohl(num);

    if (recv_num < 0) {
      LOG(ERROR) << "Receiving data problem: " << std::strerror(errno);
      break;
    } else if (recv_num == 0) {
      LOG(INFO) << "Transmission end";
      break;
    }

    received_ = 0;

    while (received_ < num) {
      LOG(DEBUG) << "Receiving...";

      recv_num = recv(client_socket, buffer_.data(), num, MSG_WAITALL);
      if (recv_num < 0) {
        LOG(ERROR) << "Receiving data problem: " << std::strerror(errno);
        break;
      } else if (recv_num == 0) {
        LOG(INFO) << "Transmission end";
        break;
      }
      received_ += recv_num;
    }

    // std::stringstream ss;
    // for (int i = 0; i < received; ++i)
    //     ss << std::setfill('0') << std::setw(2) << std::hex << (int)buffer_[i];
    // std::string mystr = ss.str();
    // LOG(DEBUG) << "Data: " << mystr;

    LOG(DEBUG) << "Message from client:\n" << num << " (" << received_ << ")";

    // std::ofstream o("plik.jpeg");
    // o.write((const char*)&buffer_[0], received_);

    // o.close();

    // std::vector<uchar> raw_image(buffer_.begin(), buffer_.begin() + received_);

    // cv::Mat img = cv::imdecode(raw_image, cv::IMREAD_ANYCOLOR);
    // if (img.empty()) {
    //   LOG(ERROR) << "Cannot decode image";
    // }


    // cv::imshow("Display window", img);
    // cv::waitKey(1500);

    buffer_mutex_.unlock();
    std::this_thread::sleep_for(10ms);
  }
  shutdown(client_socket, SHUT_RDWR);
}

bool ServerTCP::Start() {
  if (bind(socket_.GetDescriptor(), (struct sockaddr *)&address_,
      sizeof(address_))) {
    LOG(WARNING) << "Cannot start server on port " << ntohs(address_.sin_port)
                 << " : " << std::strerror(errno);
    return false;
  } else {
    LOG(INFO) << "Successfully started server on port "
              << ntohs(address_.sin_port);
  }

  if (listen(socket_.GetDescriptor(), 1)) {
    LOG(WARNING) << "Cannot start listening on port "
                 << ntohs(address_.sin_port) << " : " << std::strerror(errno);
    return false;
  } else {
    LOG(INFO) << "Successfully start listening on port "
              << ntohs(address_.sin_port);
  }

  return true;
}

void ServerTCP::Stop() {
  std::lock_guard<std::mutex> lock(stopped_mutex_);
  stopped_ = true;
}

} // namespace connection
} // namespace sl


// FF             D8FF           E1      CC5F45786966000049492A00080000000A000F01020008000000   960000001001020009000000   9E0000001201030001000000010000001A01050001000000   860000001B01050001000000   8E000000280103000100000002000000310102000E00
// ffffffffffffffd8ffffffffffffffe1ffffffcc5f45786966  0049492a  08000    a0  f 1 2  08000ffffff96000   10 1 20  9000ffffff9e000   12 1 30  1000    1000   1a 1 50  1000ffffff86000   1b 1 50  1000ffffff8e000   28 1 30  1000    2000   31 1 20  e0


// FFD8FFE1CC9145786966000049492A00080000000A000F010200080000009600000010010200090000009E0000001201030001000000010000001A01050001000000860000001B010500010000008E000000280103000100000002000000310102000E00
// ffd8ffe1cc914578696600  49492a0  8000    a  0f 1 20  8000   960001012090009e00012130100010001a1501000860001b15010008e000281301000200031120e0


// FFD8FFE1CC9145786966000049492A00080000000A000F010200080000009600000010010200090000009E0000001201030001000000010000001A01050001000000860000001B010500010000008E000000280103000100000002000000310102000E00
// ffd8ffe1cb2445786966000049492a00080000000a000f010200080000009600000010010200090000009e0000001201030001000000010000001a01050001000000860000001b010500010000008e000000280103000100000002000000310102000e00
