#ifndef SCENE_H
#define SCENE_H

#include <memory>
#include <vector>
#include <SDL2/SDL.h>
#include "../Image/Image.hpp"
#include "../Camera/Camera.hpp"
#include "../Objects/ObjSphere.hpp"
#include "../Objects/ObjectPlane.hpp"
#include "../Light/PointLight.hpp"
#include "../Material/SimpleMaterial.hpp"

class Scene
{
public:
    Scene();

    // function to perform the rendering
    bool Render(Image &outputImage);

    // function to cast a ray into the scene
    bool CastRay(Ray &castRay, std::shared_ptr<ObjectBase> &closestObject, qbVector<double> &closestIntPoint, qbVector<double> &closestLocalNormal, qbVector<double> &closestLocalColor);

private:
    // the camera that we will use
    Camera m_camera;

    // the vector of pointers to objects in the scene
    std::vector<std::shared_ptr<ObjectBase>> m_objectVec;

    // vector of lights
    std::vector<std::shared_ptr<LightBase>> m_lightVec;
};

#endif