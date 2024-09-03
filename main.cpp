#include <iostream>
#include "Race.h"
#include "GroundTransport.h"
#include "AirTransport.h"

int main() {
    std::cout << "Добро пожаловать в гоночный симулятор!\n";
    std::cout << "1. Гонка для наземного транспорта\n";
    std::cout << "2. Гонка для воздушного транспорта\n";
    std::cout << "3. Гонка для наземного и воздушного транспорта\n";
    std::cout << "Выберите тип гонки: ";
    int raceType;
    std::cin >> raceType;

    std::cout << "Укажите длину дистанции (должна быть положительна): ";
    double distance;
    std::cin >> distance;

    Race race(distance, raceType);
    int action = 1;
    do {
        if (race.getRegisteredCount() < 2) {
            std::cout << "Должно быть зарегистрировано хотя бы 2 транспортных средства\n";
        }
        std::cout << "1. Зарегистрировать транспорт\n";
        if (race.getRegisteredCount() >= 2) {
            std::cout << "2. Начать гонку\n";
        }
        std::cout << "Выберите действие: ";
        std::cin >> action;

        if (action == 1) {
            while (true) {
                std::cout << "Гонка для ";
                if (raceType == 1) {
                    std::cout << "наземного";
                } else if (raceType == 2) {
                    std::cout << "воздушного";
                } else {
                    std::cout << "наземного и воздушного";
                }
                std::cout << " транспорта. Расстояние: " << distance << "\n";
                std::cout << "Зарегистрированные транспортные средства: " << race.getRegisteredTransports() << "\n";
                race.showTransportOptions();
                int transportChoice;
                std::cin >> transportChoice;

                if (transportChoice != 0) {
                    if (!race.isCorrectTransportType(transportChoice)) {
                        std::cout << "Попытка зарегистрировать неправильный тип транспортного средства!\n";
                    } else {
                        std::string chosenTransportName = race.createTransport(transportChoice)->getName();
                        if (race.isTransportRegistered(chosenTransportName)) {
                            std::cout << chosenTransportName << " уже зарегистрирован!\n";
                        } else {
                            auto transport = race.createTransport(transportChoice);
                            if (transport) {
                                race.registerTransport(std::move(transport));
                                std::cout << race.getLastRegisteredTransportName() << " успешно зарегистрирован!\n";
                            } else {
                                std::cout << "Ошибка регистрации транспортного средства!\n";
                            }
                        }
                    }
                } else {
                    break;
                }
            }
        }
    } while (action != 2 || race.getRegisteredCount() < 2);

    auto results = race.startRace();
    race.showResults(results);

    // Добавим меню выбора действия после завершения гонки
    std::cout << "1. Провести ещё одну гонку\n2. Выйти\nВыберите действие: ";
    int nextAction;
    std::cin >> nextAction;

    if (nextAction == 1) {
        main();  // Перезапускаем игру
    }

    return 0;
}