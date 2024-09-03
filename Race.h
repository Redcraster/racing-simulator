#ifndef RACE_H
#define RACE_H

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>
#include "Transport.h"
#include "GroundTransport.h"  // предположим, здесь определены классы BootsAllTerrain, Camel, FastCamel, Centaur
#include "AirTransport.h"     // предположим, здесь определены классы Broom, Eagle, MagicCarpet

class Race {
private:
    double distance;
    int raceType;
    std::vector<std::unique_ptr<Transport>> transports;

public:
    Race(double distance, int raceType) : distance(distance), raceType(raceType) {}

    void registerTransport(std::unique_ptr<Transport> t) {
        transports.push_back(std::move(t));
    }

    bool isTransportRegistered(const std::string& name) const {
        for (const auto& transport : transports) {
            if (transport->getName() == name) {
                return true;
            }
        }
        return false;
    }

    // Метод проверки типа транспортного средства
    bool isCorrectTransportType(int choice) const {
        if (raceType == 1) {  // Наземный транспорт
            return choice == 1 || choice == 3 || choice == 4 || choice == 6;  // Ботинки-вездеходы, Верблюд, Кентавр, Верблюд-быстроход
        } else if (raceType == 2) {  // Воздушный транспорт
            return choice == 2 || choice == 5 || choice == 7;  // Метла, Орел, Ковер-самолет
        }
        return true;  // Для гонки всех типов транспортов
    }

    std::vector<std::pair<std::string, double>> startRace() const {
        std::vector<std::pair<std::string, double>> results;
        for (const auto& transport : transports) {
            results.push_back({transport->getName(), transport->calculateTime(distance)});
        }
        std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });
        return results;
    }

    void showResults(const std::vector<std::pair<std::string, double>>& results) const {
        std::cout << "Результаты гонки:\n";
        for (size_t i = 0; i < results.size(); ++i) {
            std::cout << i + 1 << ". " << results[i].first << ". Время: " << results[i].second << "\n";
        }
    }

    void showTransportOptions() const {
        std::cout << "1. Ботинки-вездеходы\n";
        std::cout << "2. Метла\n";
        std::cout << "3. Верблюд\n";
        std::cout << "4. Кентавр\n";
        std::cout << "5. Орёл\n";
        std::cout << "6. Верблюд-быстроход\n";
        std::cout << "7. Ковёр-самолёт\n";
        std::cout << "0. Закончить регистрацию\n";
        std::cout << "Выберите транспорт или 0 для окончания процесса регистрации: ";
    }

    std::unique_ptr<Transport> createTransport(int choice) const {
        switch (choice) {
            case 1: return std::make_unique<BootsAllTerrain>();
            case 2: return std::make_unique<Broom>();
            case 3: return std::make_unique<Camel>();
            case 4: return std::make_unique<Centaur>();
            case 5: return std::make_unique<Eagle>();
            case 6: return std::make_unique<FastCamel>();
            case 7: return std::make_unique<MagicCarpet>();
            default: return nullptr;
        }
    }

    int getRegisteredCount() const {
        return transports.size();
    }

    std::string getRegisteredTransports() const {
        std::string list;
        for (const auto& transport : transports) {
            if (!list.empty()) list += ", ";
            list += transport->getName();
        }
        return list;
    }

    std::string getLastRegisteredTransportName() const {
        if (!transports.empty()) {
            return transports.back()->getName();
        }
        return "";
    }
};

#endif // RACE_H