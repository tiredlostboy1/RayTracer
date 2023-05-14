#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "LightBase.hpp"

class PointLight : public LightBase
{
public:
    PointLight();
    virtual ~PointLight() override;

    virtual bool ComputeIllumination(const qbVector<double> &intPoint,
                                     const qbVector<double> &localNormal,
                                     const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                     const std::shared_ptr<ObjectBase> &currentObject,
                                     qbVector<double> &color, double &intensity) override;

    
};

#endif