#ifndef COLLECTIONOFLAMPS_H
#define COLLECTIONOFLAMPS_H
#include <fstream>
#include "lamps.h"
#include "ledlamps.h"
class CollectionOfLamps
{
public:
    int check=0;
    static const float minHeight;
    static const float defaultHeight;
    static const float maxHeight;
    CollectionOfLamps();
    CollectionOfLamps(int n, int m, Lamps &pur);
    CollectionOfLamps(const CollectionOfLamps &other);
    CollectionOfLamps& operator=(const CollectionOfLamps &other) = delete;

    double getIlluminance(const float x, const float y, const float z, const float height = defaultHeight) const;
    double getNowForce(const int i=0,const int j=0) const;
    void setLamp(const int x, const int y, Lamps &lamp);
    void setLampLED(const int x, const int y, LEDLamps &lamp);
    Lamps &getLamp(const int x, const int y) const;
    LEDLamps &getLampLED(const int x, const int y) const;
    void outputCollect(int x, int y, int &p, int &in);
     int outputCollectLED(int x, int y,int &p, int &r,int &g, int &b);
     void outputCollectFile(int x, int y);
    int getLength() const;
    int getWidth() const;
    CollectionOfLamps getFile(std::string Str, int &count, double &x, double &y, double &z) const;
    CollectionOfLamps getFileLED(std::string StrLED, int &count) const;
    double calculateLamps(int n, int m, int aIntensity[],int aPower[],int aX[],int aY[], int x, int y, int z, int c) const;
    void getFileLEDSize(std::string StrLED, int &n, int &m) const;
    void giveFile(int n, int m,double g, CollectionOfLamps square, int x, int y, int z, int height) const;
    ~CollectionOfLamps();
private:
    Lamps ***collect{nullptr};
    LEDLamps **collectLED{nullptr};
    int nn{0}, mm{0};
};

#endif // COLLECTIONOFLAMPS_H

