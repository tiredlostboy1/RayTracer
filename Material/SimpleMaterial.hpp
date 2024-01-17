#ifndef SIMPLEMATERIAL_H
#define SIMPLEMATERIAL_H

#include "MaterialBase.hpp"

class SimpleMaterial : public MaterialBase
{
public:
    SimpleMaterial();
    virtual ~SimpleMaterial() override;

    virtual qbVector<double> ComputeColor(const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                          const std::vector<std::shared_ptr<LightBase>> &lightVec,
                                          const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint,
                                          const qbVector<double> &localNormal, const Ray &cameraRay);

    qbVector<double> ComputeSpecular(const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                     const std::vector<std::shared_ptr<LightBase>> &lightVec,
                                     const qbVector<double> &intPoint,
                                     const qbVector<double> &localNormal, const Ray &cameraRay);

public:
    qbVector<double> m_baseColor{std::vector<double> {1.0, 0.0, 1.0}};
    double m_reflectivity = 0.0;
    double m_shininess = 0.0;
};

#endif // SIMPLEMATERIAL_H
