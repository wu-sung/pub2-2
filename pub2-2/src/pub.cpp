#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/vector3.hpp"
#include <memory>
#include <iostream>

using namespace std::chrono_literals;

// 클래스명 및 노드 이름 변경
class Pub2Node : public rclcpp::Node
{
public:
    Pub2Node() : Node("pub2_2")
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Vector3>("mytopic", rclcpp::QoS(rclcpp::KeepLast(10)));
        timer_ = this->create_wall_timer(100ms, std::bind(&Pub2Node::callback, this));
    }

private:
    rclcpp::Publisher<geometry_msgs::msg::Vector3>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;

    void callback()
    {
        auto message = std::make_shared<geometry_msgs::msg::Vector3>(); // 토픽 메시지 타입 변경
        std::cout << "Enter three float values separated by space: ";
        std::cin >> message->x >> message->y >> message->z;
        RCLCPP_INFO(this->get_logger(), "Publish: x=%.2f, y=%.2f, z=%.2f", message->x, message->y, message->z);
        publisher_->publish(*message);
    }
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Pub2Node>(); // 클래스명 변경

    rclcpp::spin(node); //무한루프
    rclcpp::shutdown(); 
    return 0;
}