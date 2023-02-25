#include <random>
#include <mutex>
#include <iostream>
#include <thread>

bool cupcake = true;
int count = 0;
std::mutex m;
int whosturn = 0;
bool active = true;



void pickPerson() {

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type>dist6(1, 10);


    while (active) {
        m.lock();
        if (count == 10) {
            active = false;
            m.unlock();
            break;
        }

        if (whosturn == 0) {
            int ran = dist6(rng);
            whosturn = ran;
        }
        m.unlock();
    }
}

void counter() {

    while (active) {

        m.lock();
        if (count == 10) {
            active = false;
            m.unlock();
            break;
        }
        else
            m.unlock();

        if (cupcake) {
            cupcake = false;
            count++;
            std::cout << count;
        }
    }
}

void turn(int person) {
    bool active = true;
    bool visited = false;

    while (active) {

        m.lock();
        if (count == 10) {
            active = false;
            m.unlock();
            break;
        }
        else
            m.unlock();


        m.lock();
        if (person == whosturn) {
            m.unlock();
            if (!visited) {
                if (!cupcake) {
                    cupcake = true;
                }
                visited = true;
            }
        }
        else
            m.unlock();

        m.lock();
        whosturn = 0;
        m.unlock();
    }

}
int main(int argc, char* argv[]) {
    std::thread minotaur(pickPerson);
    std::thread first(counter);
    std::thread second(turn, 2);
    std::thread third(turn, 3);
    std::thread four(turn, 4);
    std::thread five(turn, 5);
    std::thread six(turn, 6);
    std::thread seven(turn, 7);
    std::thread eight(turn, 8);
    std::thread nine(turn, 9);
    std::thread ten(turn, 10);

    minotaur.join();
    first.join();
    second.join();
    third.join();
    four.join();
    five.join();
    six.join();
    seven.join();
    eight.join();
    nine.join();
    ten.join();

    std::cout << "done";
}