#ifndef TRANSPORT_H
#define TRANSPORT_H

#include <string>

class Transport {
protected:
    double speed;

public:
    Transport(double speed) : speed(speed) {}
    virtual double calculateTime(double distance) const = 0;
    virtual std::string getName() const = 0;
    virtual ~Transport() {}
};

#endif // TRANSPORT_H