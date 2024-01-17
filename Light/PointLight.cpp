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

    // construct a ray from the point of intersection to the light
    Ray lightRay(startPoint, startPoint + lightDir);

    // check for intersections with all of the objects in the scene, except for the current one
    qbVector<double> poi{3};
    qbVector<double> poiNormal{3};
    qbVector<double> poiColor{3};
    bool validInt = false;

    for (auto sceneObject : objectVec)
    {
        if (sceneObject != currentObject)
        {
            validInt = sceneObject->TestIntersections(lightRay, poi, poiNormal, poiColor);
        }

        // if we have intersecion, then there is no point checking further so we can break out of the loop.
        // In other words, this object is blocking light from this light source
        if (validInt)
        {
            break;
        }
    }

    // only continue to compute illumination if the light ray didn't intersect with any objects in the scene.
    // no objects are casting a shadow from this light source
    if (!validInt)
    {
        // compute the angle between the local normal and the light ray.
        // we assume that localNormal is a unit vector
        double angle = acos(qbVector<double>::dot(localNormal, lightDir));

        if (angle > 1.5708) // pi/2
        {
            // no illumination
            color = m_color;
            intensity = 0.0;
            return false;
        }
        else
        {
            color = m_color;
            intensity = m_intensity * (1.0 - (angle / 1.5708));
            return true;
        }
    }
    else
    {
        // shadow, no illumination
        color = m_color;
        intensity = 0.0;
        return false;
    }
}