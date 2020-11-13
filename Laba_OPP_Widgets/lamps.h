#ifndef LAMPS_H
#define LAMPS_H
class Lamps
{
public:
    Lamps(const int power=0, const int intensity=0);
    Lamps(const Lamps &lamp);
    void output() const;
    int getPower() const;
    virtual int getPowerLED() const;
    virtual int getIntensityRed() const;
    virtual int getIntensityGreen() const;
    virtual int getIntensityBlue() const;
     int getIntensity() const;
    void setPower(const int power);
    void setIntensity(const int intensity);
     virtual void setIntensityRed(const int intensityRed);
private:
    int intensity, power, intensityRed, intensityGreen, intensityBlue, powerLED;
};

#endif // LAMPS_H

