#include "PointLight.hpp"

PointLight::PointLight()
{
    m_color = qbVector<double>{std::vector<double>{1.0, 1.0, 1.0}};
    m_intensity = 1.0;
}

PointLight::~PointLight() {}

bool PointLight::ComputeIllumination(const qbVector<double> &intPoint,
                                     const qbVector<double> &localNormal,
                                     const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                     const std::shared_ptr<ObjectBase> &currentObject,
                                     qbVector<double> &color, double &intensity)
{
    // Construct a vector pointing from the intersection point to the light
    qbVector<double> lightDir = (m_location - intPoint).Normalized();

    // Compute a starting point
    qbVector<double> startPoint = intPoint;

    // Compute the angle between the local normal and the light ray
    // we assume that the localNormal is a unit vector
    double angle = acos(qbVector<double>::dot(localNormal, lightDir)); // skipping the /|a|*|b| as they = 1

    // if the normal is pointing away from the light, then we don't have illumination
    if (angle > 1.5708)
    { // 1.5708 is pi/2
        // no illumination
        color = m_color;
        intensity = 0.0;
        return false;
    }
    else
    {
        // we do have illumination
        color = m_color;
        intensity = m_intensity * (1.0 - (angle / 1.5708));
        return true;
    }
    return true;
}