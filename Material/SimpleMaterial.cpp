#include "SimpleMaterial.hpp"

SimpleMaterial::SimpleMaterial()
{
}

SimpleMaterial::~SimpleMaterial()
{
}

qbVector<double> SimpleMaterial::ComputeColor(const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                              const std::vector<std::shared_ptr<LightBase>> &lightVec,
                                              const std::shared_ptr<ObjectBase> &currentObject, const qbVector<double> &intPoint,
                                              const qbVector<double> &localNormal, const Ray &cameraRay)
{
    qbVector<double> matColor{3};
    qbVector<double> refColor{3};
    qbVector<double> diffColor{3};
    qbVector<double> spcColor{3};

    // using diffuse intensity formulas here

    diffColor = ComputeDiffuseColor(objectVec, lightVec, currentObject, intPoint, localNormal, m_baseColor);

    if (m_shininess > 0.0)
    {
        spcColor = ComputeSpecular(objectVec, lightVec, intPoint, localNormal, cameraRay);
    }

    matColor = diffColor + spcColor;

    return matColor;
}

qbVector<double> SimpleMaterial::ComputeSpecular(const std::vector<std::shared_ptr<ObjectBase>> &objectVec,
                                                 const std::vector<std::shared_ptr<LightBase>> &lightVec,
                                                 const qbVector<double> &intPoint,
                                                 const qbVector<double> &localNormal, const Ray &cameraRay)
{
    qbVector<double> spcColor{3};
    double red = 0.0;
    double green = 0.0;
    double blue = 0.0;

    for (auto currentLight : lightVec)
    {
        // check for intersections with all objects in the scene
        double intensity = 0.0;

        // construct a vector pointing from the intersection point to the light
        qbVector<double> lightDir = (currentLight->m_location - intPoint).Normalized();

        // compute a start point
        qbVector<double> startPoint = intPoint + (lightDir * 0.001);

        // construct a ray from the point of intersection to the light
        Ray lightRay(startPoint, startPoint + lightDir);

        // looping through all objects in the scene to check if any obstruct light from this source
        qbVector<double> poi{3};
        qbVector<double> poiNormal{3};
        qbVector<double> poiColor{3};
        bool validInt = false;

        for (auto sceneObject : objectVec)
        {
            if (sceneObject->TestIntersections(lightRay, poi, poiNormal, poiColor))
            {
                validInt = true;
                break;
            }
        }
        // no intersection found, proceed wih computing the specular component
        if (!validInt)
        {
            qbVector<double> d = lightRay.m_lab;
            //???????????????????????????????????????????????????????????????????????????????????????????????????????????????????
            qbVector<double> r = d - 2.0 * (qbVector<double>::dot(d, localNormal) * localNormal);
            r.Normalize();

            // compute the dot product
            qbVector<double> v = cameraRay.m_lab;
            v.Normalize();
            double dotProduct = qbVector<double>::dot(r, v);

            // only proceed if the dot product is positive
            if (dotProduct > 0.0)
            {
                intensity = m_reflectivity * std::pow(dotProduct, m_shininess);
            }
        }

        red += currentLight->m_color.GetElement(0) * intensity;
        green += currentLight->m_color.GetElement(1) * intensity;
        blue += currentLight->m_color.GetElement(2) * intensity;
    }
    spcColor.SetElement(0, red);
    spcColor.SetElement(1, green);
    spcColor.SetElement(2, blue);
    return spcColor;
}