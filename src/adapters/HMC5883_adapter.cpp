#include "HMC5883_adapter.h"
#include "../utils/angle_utils.h"
#include <Adafruit_HMC5883_U.h>
#include <math.h>

HMC5883LCompassAdapter::HMC5883LCompassAdapter()
    : alpha_(0.15f), smoothedAzimuth_(0) {
    compass_ = new Adafruit_HMC5883_Unified(12345);
}

HMC5883LCompassAdapter::~HMC5883LCompassAdapter() {
    delete compass_;
    compass_ = nullptr;
}

void HMC5883LCompassAdapter::begin() {
    if (compass_) {
        compass_->begin();
    }
}

bool HMC5883LCompassAdapter::isHealthy() const {
    return compass_ != nullptr;
}

void HMC5883LCompassAdapter::update() {
    // Adafruit library reads data on demand in getEvent()
    // No separate update needed
}

int HMC5883LCompassAdapter::getRawAzimuth() {
    if (!compass_) return 0;
    
    sensors_event_t event;
    compass_->getEvent(&event);
    
    // Calculate heading from magnetic field x, y
    float heading = atan2(event.magnetic.y, event.magnetic.x) * 180.0f / M_PI;
    if (heading < 0) heading += 360.0f;
    
    return (int)heading;
}

int HMC5883LCompassAdapter::getSmoothedAzimuth() {
    int rawAzimuth = getRawAzimuth();
    smoothedAzimuth_ = (int)((alpha_ * rawAzimuth) + ((1.0f - alpha_) * smoothedAzimuth_));
    return smoothedAzimuth_;
}