#include "MaterialBase.hpp"

MaterialBase::MaterialBase()
{
    m_maxReflectionRays = 50;
    m_reflectionRayCount = 0;
}

MaterialBase::~MaterialBase()
{
}

qbVector<double> MaterialBase::ComputeColor(const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                            const std::vector<std::shared_ptr<LightBase>> &lightVec,
                                            const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint,
                                            const qbVector<double> &localNormal, const Ray &cameraRay)
{
    // define an initial material color
    qbVector<double> matColor{3};

    return matColor;
}

qbVector<double> MaterialBase::ComputeDiffuseColor(const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                                   const std::vector<std::shared_ptr<LightBase>> &lightVec,
                                                   const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint,
                                                   const qbVector<double> &localNormal, const qbVector<double> &baseColor)
{
    // compute the color due to diffuse illumination
    qbVector<double> diffuseColor{3};
    double intensity;
    qbVector<double> color{3};
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;
    bool validIllum = false;
    bool illumFound = false;

    for (auto currentLight : lightVec)
    {
        validIllum = currentLight->ComputeIllumination(intPoint, localNormal, objectVec, currentObject, color, intensity);
        if (validIllum)
        {
            illumFound = true;
            red += color.GetElement(0) * intensity;
            green += color.GetElement(1) * intensity;
            blue += color.GetElement(2) * intensity;
        }
    }
    if (illumFound)
    {
        diffuseColor.SetElement(0, red * baseColor.GetElement(0));
        diffuseColor.SetElement(1, green * baseColor.GetElement(1));
        diffuseColor.SetElement(2, blue * baseColor.GetElement(2));
    }

    // return the material color
    return diffuseColor;
}

qbVector<double> MaterialBase::ComputeReflectionColor(const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                                      const std::vector<std::shared_ptr<LightBase>> &lightVec,
                                                      const std::shared_ptr<ObjectBase> &currentObject,
                                                      const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                                      const Ray &incidentRay)
{
    qbVector<double> reflectionColor{3};

    // compute the reflection vector
    qbVector<double> d = incidentRay.m_lab;
    qbVector<double> reflectionVector = d - 2.0 * (qbVector<double>::dot(d, localNormal)) * localNormal;

    // construct the reflection ray
    Ray reflectionRay(intPoint, intPoint + reflectionVector);

    // cast this ray into the scene and find the closest obj that it intersects with
    std::shared_ptr<ObjectBase> closestObject;
    qbVector<double> closestIntPoint{3};
    qbVector<double> closestLocalNormal{3};
    qbVector<double> closestLocalColor{3};
    bool intersectionFound = CastRay(reflectionRay, objectVec, currentObject, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);

    // compute the illumination for the closest object assuming that there was a valid intersection
    qbVector<double> matColor{3};
    if (intersectionFound && m_reflectionRayCount < m_maxReflectionRays)
    {
        m_reflectionRayCount++;

        // check if a material has been assigned
        if (closestObject->m_hasMaterial)
        {
            // use the material to compute the color
            matColor = closestObject->m_pMaterial->ComputeColor(objectVec, lightVec, closestObject, closestIntPoint, closestLocalNormal, reflectionRay);
        }
        else
        {
            matColor = MaterialBase::ComputeDiffuseColor(objectVec, lightVec, closestObject, closestIntPoint, closestLocalColor, closestLocalColor);
        }
    }
    else
    {
        // leave the matColor as it is
    }
    reflectionColor = matColor;
    return reflectionColor;
}

bool MaterialBase::CastRay(const Ray &castRay, const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                           const std::shared_ptr<ObjectBase> &thisObject, std::shared_ptr<ObjectBase> &closestObject, qbVector<double> &closestIntPoint,
                           qbVector<double> &closestLocalNormal, qbVector<double> &closestLocalColor)
{
    qbVector<double> intPoint{3};
    qbVector<double> localNormal{3};
    qbVector<double> localColor{3};
    double minDist = std::numeric_limits<double>::max();
    bool intersectionFound = false;
    for (auto currentObject : objectVec)
    {
        if (currentObject != thisObject)
        {
            bool validInt = currentObject->TestIntersections(castRay, intPoint, localNormal, localColor);
            if (validInt)
            {
                // set the flag to indicate that we found an intersection
                intersectionFound = true;

                // compute the distance between the camera and the point of intersection
                double dist = (intPoint - castRay.m_point1).norm();

                if (dist < minDist)
                {
                    minDist = dist;
                    closestObject = currentObject;
                    closestIntPoint = intPoint;
                    closestLocalNormal = localNormal;
                    closestLocalColor = localColor;
                }
            }
        }
    }
    return intersectionFound;
}