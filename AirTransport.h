#ifndef AIRTRANSPORT_H
#define AIRTRANSPORT_H

#include "Transport.h"

class AirTransport : public Transport {
public:
    AirTransport(double speed) : Transport(speed) {}

    double calculateTime(double distance) const override {
        double reducedDistance = calculateReducedDistance(distance);
        return reducedDistance / speed;
    }

    virtual double calculateReducedDistance(double distance) const = 0;
};

class MagicCarpet : public AirTransport {
public:
    MagicCarpet() : AirTransport(10) {}

    double calculateReducedDistance(double distance) const override {
        if (distance < 1000) return distance;
        if (distance < 5000) return distance * 0.97;
        if (distance < 10000) return distance * 0.9;
        return distance * 0.95;
    }

    std::string getName() const override {
        return "Ковёр-самолёт";
    }
};

class Eagle : public AirTransport {
public:
    Eagle() : AirTransport(8) {}

    double calculateReducedDistance(double distance) const override {
        return distance * 0.94;
    }

    std::string getName() const override {
        return "Орёл";
    }
};

class Broom : public AirTransport {
public:
    Broom() : AirTransport(20) {}

    double calculateReducedDistance(double distance) const override {
        int thousands = static_cast<int>(distance / 1000);
        return distance * (1 - 0.01 * thousands);
    }

    std::string getName() const override {
        return "Метла";
    }
};

#endif // AIRTRANSPORT_H