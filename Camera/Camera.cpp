#include "Camera.hpp"
#include "../Ray/Ray.hpp"
#include <cmath>

Camera::Camera()
    : m_cameraPosition(qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}}), m_cameraLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}), m_cameraUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}}), m_cameraLength(1.0), m_cameraHorizontalSize(1.0), m_cameraAspectRatio(1.0)
{
}

// setters
void Camera::SetPosition(const qbVector<double> &newPosition)
{
    m_cameraPosition = newPosition;
}

void Camera::SetLookAt(const qbVector<double> &newLookAt)
{
    m_cameraLookAt = newLookAt;
}

void Camera::SetUp(const qbVector<double> &upVector)
{
    m_cameraUp = upVector;
}

void Camera::SetLength(double newLength)
{
    m_cameraLength = newLength;
}

void Camera::SetHorizontalSize(double newSize)
{
    m_cameraHorizontalSize = newSize;
}

void Camera::SetAspect(double newAspect)
{
    m_cameraAspectRatio = newAspect;
}

// Getters
qbVector<double> Camera::GetPosition()
{
    return m_cameraPosition;
}
qbVector<double> Camera::GetLookAt()
{
    return m_cameraLookAt;
}
qbVector<double> Camera::GetUp()
{
    return m_cameraUp;
}
qbVector<double> Camera::GetU()
{
    return m_projectionScreenU;
}
qbVector<double> Camera::GetV()
{
    return m_projectionScreenV;
}
qbVector<double> Camera::GetScreenCentre()
{
    return m_projectionScreenCentre;
}
double Camera::GetLength()
{
    return m_cameraLength;
}
double Camera::GetHorizontalSize()
{
    return m_cameraHorizontalSize;
}
double Camera::GetAspect()
{
    return m_cameraAspectRatio;
}

void Camera::UpdateCameraGeometry()
{
    // compute the vector from the camera position to the LookAt position
    m_alignmentVector = m_cameraLookAt - m_cameraPosition;
    m_alignmentVector.Normalize();

    // compute U, V vectors
    m_projectionScreenU = qbVector<double>::cross(m_alignmentVector, m_cameraUp);
    m_projectionScreenU.Normalize();

    m_projectionScreenV = qbVector<double>::cross(m_projectionScreenU, m_alignmentVector);
    m_projectionScreenV.Normalize();

    //compute the position of the centre point of the screen
    m_projectionScreenCentre = m_cameraPosition + (m_cameraLength * m_alignmentVector);

    //modify the U, V vectors to match the size and aspect ratio
    m_projectionScreenU = m_projectionScreenU * m_cameraHorizontalSize;
    m_projectionScreenV = m_projectionScreenV * (m_cameraHorizontalSize / m_cameraAspectRatio);
}

 Ray Camera::GenerateRay(float proScreenX, float proScreenY){
    //compute the location of the screen point in world coordinates
    qbVector<double> screenWorldPart1 = m_projectionScreenCentre + (m_projectionScreenU * proScreenX);
    qbVector<double> screenWorldCoordinate = screenWorldPart1 + (m_projectionScreenV * proScreenY);

    //use this point along with the camera position to compute the ray
    return Ray(m_cameraPosition, screenWorldCoordinate);
}