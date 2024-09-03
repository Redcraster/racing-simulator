#ifndef GROUNDTRANSPORT_H
#define GROUNDTRANSPORT_H

#include "Transport.h"

class GroundTransport : public Transport {
protected:
    double moveTime;  // Время, которое транспорт может двигаться до первого отдыха
    double restDuration;  // Продолжительность отдыха

public:
    GroundTransport(double speed, double moveTime)
        : Transport(speed), moveTime(moveTime) {}

    double calculateTime(double distance) const override {
        double travelTime = distance / speed;
        double totalTime = travelTime;
        int restCount = static_cast<int>(travelTime / moveTime);

        for (int i = 1; i <= restCount; ++i) {
            totalTime += calculateRestDuration(i);
        }

        return totalTime;
    }

    virtual double calculateRestDuration(int restCount) const = 0;
};

class Camel : public GroundTransport {
public:
    Camel() : GroundTransport(10, 30) {}

    double calculateRestDuration(int restCount) const override {
        return (restCount == 1) ? 5 : 8;
    }

    std::string getName() const override {
        return "Верблюд";
    }
};

class FastCamel : public GroundTransport {
public:
    FastCamel() : GroundTransport(40, 10) {}

    double calculateRestDuration(int restCount) const override {
        if (restCount == 1) return 5;
        if (restCount == 2) return 6.5;
        return 8;
    }

    std::string getName() const override {
        return "Верблюд-быстроход";
    }
};

class Centaur : public GroundTransport {
public:
    Centaur() : GroundTransport(15, 8) {}

    double calculateRestDuration(int restCount) const override {
        return 2;
    }

    std::string getName() const override {
        return "Кентавр";
    }
};

class BootsAllTerrain : public GroundTransport {
public:
    BootsAllTerrain() : GroundTransport(6, 60) {}

    double calculateRestDuration(int restCount) const override {
        return (restCount == 1) ? 10 : 5;
    }

    std::string getName() const override {
        return "Ботинки-вездеходы";
    }
};

#endif // GROUNDTRANSPORT_H