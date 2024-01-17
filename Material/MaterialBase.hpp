#ifndef MATERIALBASE_H
#define MATERIALBASE_H

#include <memory>
#include "../Ray/Ray.hpp"
#include "../Objects/Objectbase.hpp"
#include "../Light/LightBase.hpp"
#include "../Math/vector.h"

class MaterialBase
{
public:
    MaterialBase();
    virtual ~MaterialBase();

    // function to return the color of the material
    virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                          const std::vector<std::shared_ptr<LightBase>> &lightVec,
                                          const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint,
                                          const qbVector<double> &localNormal, const Ray &cameraRay);

    // function to compute diffuse color
    static qbVector<double> ComputeDiffuseColor(const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                                const std::vector<std::shared_ptr<LightBase>> &lightVec,
                                                const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint,
                                                const qbVector<double> &localNormal, const qbVector<double> &baseColor);
    // Function to compute the reflection color.
    qbVector<double> ComputeReflectionColor(const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                            const std::vector<std::shared_ptr<LightBase>> &lightVec,
                                            const std::shared_ptr<ObjectBase> &currentObject,
                                            const qbVector<double> &intPoint, const qbVector<double> &localNormal,
                                            const Ray &incidentRay);

    // function to cast a ray into the scene
    bool CastRay(const Ray &castRay, const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                 const std::shared_ptr<ObjectBase> &thisObject, std::shared_ptr<ObjectBase> &closestObject, qbVector<double> &closestIntPoint,
                qbVector<double> &closestLocalNormal, qbVector<double> &closestLocalColor);

public:
//counter for the number of reflection rays
    inline static int m_maxReflectionRays;
    inline static int m_reflectionRayCount;
};

#endif // MATERIALBASE_H