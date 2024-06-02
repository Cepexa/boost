#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <String>

std::mutex mtx;
std::condition_variable cv_waiter, cv_cook;
std::queue<std::pair<int, std::string>> orders;
std::unordered_map<int, std::string> cooking_orders; // id ���������� -> �����

enum class OrderStatus {
    Waiting,
    Taken,
    Cooking,
    Ready
};

std::unordered_map<int, OrderStatus> order_status; // id ���������� -> ������ ������

void waiter() {
    std::unique_lock<std::mutex> lock(mtx);

    while (true) {
        // ����, ���� �� �������� ����� ����� ��� �� ����� ����� ���������� �����
        cv_waiter.wait(lock, [&] {
            return !orders.empty() || std::any_of(order_status.begin(), order_status.end(), [](const auto& pair) {
                return pair.second == OrderStatus::Ready;
                });
            });

        if (!orders.empty()) {
            // ����� ����� ������� ������ �� �������
            auto order = orders.front();
            orders.pop();

            // �������� ����� ������
            std::cout << "�������� ������� ����� ������ ��� ���������� " << order.first << ": " << order.second << std::endl;
            cooking_orders[order.first] = order.second;
            order_status[order.first] = OrderStatus::Cooking;
            cv_cook.notify_one();
        }
        else {
            // ���� ����� �����, ���������� ��� ����������
            auto it = std::find_if(order_status.begin(), order_status.end(), [](const auto& pair) {
                return pair.second == OrderStatus::Ready;
                });
            int customer_id = it->first;
            std::string order = cooking_orders[customer_id];

            std::cout << "�������� �������� ����� ���������� " << customer_id << ": " << order << std::endl;
            cooking_orders.erase(customer_id);
            order_status[customer_id] = OrderStatus::Waiting; // ���������� ������ ������ ������� � Waiting
        }
    }
}

void cook() {
    std::unique_lock<std::mutex> lock(mtx);

    while (true) {
        // ����, ���� �������� �� �������� �����
        cv_cook.wait(lock, [] {return !cooking_orders.empty(); });

        // ����� ������ ����� �� �������
        auto it = cooking_orders.begin();
        int customer_id = it->first;
        std::string order = it->second;

        // ������� �����
        std::cout << "����� ������� ����� ��� ���������� " << customer_id << ": " << order << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // ����� �����, ������������� �� ���� ���������
        order_status[customer_id] = OrderStatus::Ready;
        cv_waiter.notify_one();
    }
}

void customer(int id) {
    std::lock_guard<std::mutex> lock(mtx);

    // ������ �����
    std::string order = "����� �� ���������� " + std::to_string(id);
    std::cout << "���������� " << id << " ������ �����: " << order << std::endl;
    orders.push(std::make_pair(id, order));
    order_status[id] = OrderStatus::Waiting;
    cv_waiter.notify_one();
}

int main() {
    system("chcp 1251 > nul");
    std::thread t1(waiter);
    std::thread t2(cook);

    // ������� ��������� �����������
    std::vector<std::thread> customers;
    for (int i = 1; i <= 5; i++) {
        customers.emplace_back(customer, i);
    }

    // ���� ���������� ���� �������
    for (auto& t : customers) {
        t.join();
    }
    t1.join();
    t2.join();

    return 0;
}