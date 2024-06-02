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
std::unordered_map<int, std::string> cooking_orders; // id посетителя -> заказ

enum class OrderStatus {
    Waiting,
    Taken,
    Cooking,
    Ready
};

std::unordered_map<int, OrderStatus> order_status; // id посетителя -> статус заказа

void waiter() {
    std::unique_lock<std::mutex> lock(mtx);

    while (true) {
        // Ждем, пока не появится новый заказ или не будет готов конкретный заказ
        cv_waiter.wait(lock, [&] {
            return !orders.empty() || std::any_of(order_status.begin(), order_status.end(), [](const auto& pair) {
                return pair.second == OrderStatus::Ready;
                });
            });

        if (!orders.empty()) {
            // Берем копию первого заказа из очереди
            auto order = orders.front();
            orders.pop();

            // Передаем заказ повару
            std::cout << "Официант передал заказ повару для посетителя " << order.first << ": " << order.second << std::endl;
            cooking_orders[order.first] = order.second;
            order_status[order.first] = OrderStatus::Cooking;
            cv_cook.notify_one();
        }
        else {
            // Если заказ готов, доставляем его посетителю
            auto it = std::find_if(order_status.begin(), order_status.end(), [](const auto& pair) {
                return pair.second == OrderStatus::Ready;
                });
            int customer_id = it->first;
            std::string order = cooking_orders[customer_id];

            std::cout << "Официант доставил заказ посетителю " << customer_id << ": " << order << std::endl;
            cooking_orders.erase(customer_id);
            order_status[customer_id] = OrderStatus::Waiting; // Сбрасываем статус заказа обратно в Waiting
        }
    }
}

void cook() {
    std::unique_lock<std::mutex> lock(mtx);

    while (true) {
        // Ждем, пока официант не передаст заказ
        cv_cook.wait(lock, [] {return !cooking_orders.empty(); });

        // Берем первый заказ из очереди
        auto it = cooking_orders.begin();
        int customer_id = it->first;
        std::string order = it->second;

        // Готовим заказ
        std::cout << "Повар готовит заказ для посетителя " << customer_id << ": " << order << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        // Заказ готов, сигнализируем об этом официанту
        order_status[customer_id] = OrderStatus::Ready;
        cv_waiter.notify_one();
    }
}

void customer(int id) {
    std::lock_guard<std::mutex> lock(mtx);

    // Делаем заказ
    std::string order = "Заказ от посетителя " + std::to_string(id);
    std::cout << "Посетитель " << id << " сделал заказ: " << order << std::endl;
    orders.push(std::make_pair(id, order));
    order_status[id] = OrderStatus::Waiting;
    cv_waiter.notify_one();
}

int main() {
    system("chcp 1251 > nul");
    std::thread t1(waiter);
    std::thread t2(cook);

    // Создаем несколько посетителей
    std::vector<std::thread> customers;
    for (int i = 1; i <= 5; i++) {
        customers.emplace_back(customer, i);
    }

    // Ждем завершения всех потоков
    for (auto& t : customers) {
        t.join();
    }
    t1.join();
    t2.join();

    return 0;
}