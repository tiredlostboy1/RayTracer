#include "LightBase.hpp"

LightBase::LightBase()
{
}

LightBase::~LightBase()
{
}

bool LightBase::ComputeIllumination(const qbVector<double> &intPoint,
                                    const qbVector<double> &localNormal,
                                    const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                    const std::shared_ptr<ObjectBase> &currentObject,
                                    qbVector<double> &color, double &intensity)
{
    return false;
}