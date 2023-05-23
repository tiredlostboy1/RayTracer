#include "MaterialBase.hpp"

MaterialBase::MaterialBase()
{
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

    //return the material color
    return diffuseColor;
}
