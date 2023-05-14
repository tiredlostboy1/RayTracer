#ifndef LIGHTBASE_H
#define LIGHTBASE_H

#include <memory>
#include "../Math/vector.h"
#include "../Ray/Ray.hpp"
#include "../Objects/Objectbase.hpp"

class LightBase
{
public:
    LightBase();
    virtual ~LightBase();

    virtual bool ComputeIllumination(const qbVector<double> &intPoint,
                                     const qbVector<double> &localNormal,
                                     const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                     const std::shared_ptr<ObjectBase> &currentObject,
                                     qbVector<double> &color, double &intensity);


    qbVector<double> m_color{3};
    qbVector<double> m_location{3};
    double m_intensity;
};

#endif