#ifndef CAMERA_H
#define CAMERA_H

#include "../Ray/Ray.hpp"
#include "../Math/vector.h"

class Camera
{
public:
    Camera();

    // functions to set camera parameters
    void SetPosition(const qbVector<double> &newPosition);
    void SetLookAt(const qbVector<double> &newLookAt);
    void SetUp(const qbVector<double> &upVector);
    void SetLength(double newLength);
    void SetHorizontalSize(double newSize);
    void SetAspect(double newAspect);

    // funtions to return camera parameters
    qbVector<double> GetPosition();
    qbVector<double> GetLookAt();
    qbVector<double> GetUp();
    qbVector<double> GetU();
    qbVector<double> GetV();
    qbVector<double> GetScreenCentre();
    double GetLength();
    double GetHorizontalSize();
    double GetAspect();

    // funtions to generate a ray
    Ray GenerateRay(float proScreenX, float proScreenY);

    // function to update the camera geometry
    void UpdateCameraGeometry();

private:
    qbVector<double> m_cameraPosition{3};
    qbVector<double> m_cameraLookAt{3};
    qbVector<double> m_cameraUp{3};
    double m_cameraLength;
    double m_cameraHorizontalSize;
    double m_cameraAspectRatio;

    qbVector<double> m_alignmentVector{3};
    qbVector<double> m_projectionScreenU{3};
    qbVector<double> m_projectionScreenV{3};
    qbVector<double> m_projectionScreenCentre{3};
};

#endif