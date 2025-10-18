#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string>
#include <algorithm>
#include <cctype>

class Mp3Node : public rclcpp::Node {
public:
  Mp3Node() : Node("mp3_node") {
    port_ = "/dev/ttyAMA0";
    volume_ = 25;

    // UART 초기화
    if (!init_serial()) {
      RCLCPP_ERROR(get_logger(), "Failed to open %s", port_.c_str());
      rclcpp::shutdown();
      return;
    }

    rclcpp::sleep_for(std::chrono::milliseconds(300));
    select_tf();
    rclcpp::sleep_for(std::chrono::milliseconds(100));
    set_volume(volume_);

    sub_ = this->create_subscription<std_msgs::msg::String>(
      "/mp3_cmd", 10,
      std::bind(&Mp3Node::onMsg, this, std::placeholders::_1));

    RCLCPP_INFO(get_logger(), "🎧 MP3 node ready. Waiting for /mp3_cmd (e.g., '0001.mp3')...");
  }

  ~Mp3Node() override { if (serial_fd_ >= 0) close(serial_fd_); }

private:
  int serial_fd_ = -1;
  std::string port_;
  int volume_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_;

  bool init_serial() {
    serial_fd_ = open(port_.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_fd_ < 0) return false;

    termios tty{};
    tcgetattr(serial_fd_, &tty);
    cfmakeraw(&tty);
    cfsetispeed(&tty, B9600);
    cfsetospeed(&tty, B9600);
    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB; tty.c_cflag &= ~CSTOPB; tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8; tty.c_cflag &= ~CRTSCTS;
    tty.c_cc[VMIN] = 0; tty.c_cc[VTIME] = 10;
    tcflush(serial_fd_, TCIFLUSH);
    tcsetattr(serial_fd_, TCSANOW, &tty);
    return true;
  }

  void send_frame(uint8_t cmd, uint16_t param = 0) {
    if (serial_fd_ < 0) return;
    uint8_t ph = (param >> 8) & 0xFF, pl = param & 0xFF;
    uint16_t sum = (0xFF + 0x06 + cmd + 0x00 + ph + pl) & 0xFFFF;
    uint16_t chk = (0xFFFF - sum + 1) & 0xFFFF;
    uint8_t buf[10] = {0x7E,0xFF,0x06,cmd,0x00,ph,pl,(uint8_t)(chk>>8),(uint8_t)chk,0xEF};
    write(serial_fd_, buf, 10);
    usleep(100000);
  }

  void select_tf()             { send_frame(0x09, 0x0002); }
  void set_volume(int vol)     { send_frame(0x06, std::min(vol,30)); }
  void play_track(uint16_t no) { send_frame(0x03, no); }

  int parse_track(std::string s) {
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    if (s.size() >= 4 && s.substr(s.size()-4) == ".MP3") s.erase(s.size()-4);
    auto nz = s.find_first_not_of('0');
    s = (nz == std::string::npos) ? "0" : s.substr(nz);
    if (std::all_of(s.begin(), s.end(), ::isdigit)) return std::stoi(s);
    return -1;
  }

  void onMsg(const std_msgs::msg::String::SharedPtr msg) {
    int track = parse_track(msg->data);
    if (track <= 0) {
      RCLCPP_WARN(get_logger(), "Invalid track: %s", msg->data.c_str());
      return;
    }
    RCLCPP_INFO(get_logger(), "▶ Playing track %d", track);
    play_track(track);
  }
};

int main(int argc, char **argv) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<Mp3Node>());
  rclcpp::shutdown();
  return 0;
}

