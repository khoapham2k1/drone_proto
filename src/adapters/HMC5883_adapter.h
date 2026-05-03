#ifndef HMC5883L_ADAPTER_H
#define HMC5883L_ADAPTER_H

#include "compass_adapter.h"

class Adafruit_HMC5883_Unified;

/** HMC5883L magnetometer implementation of CompassAdapter (I2C). */
class HMC5883LCompassAdapter : public CompassAdapter {
public:
    HMC5883LCompassAdapter();
    ~HMC5883LCompassAdapter() override;

    void begin() override;
    void update() override;
    bool isHealthy() const override;
    int getRawAzimuth() override;
    int getSmoothedAzimuth() override;

private:
    Adafruit_HMC5883_Unified* compass_;
    float alpha_;
    int smoothedAzimuth_;
};

#endif