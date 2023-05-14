#include "ObjSphere.hpp"
#include <cmath>

ObjSphere::ObjSphere()
{
}

ObjSphere::~ObjSphere()
{
}

bool ObjSphere::TestIntersections(const Ray &castRay, qbVector<double> &intPoint,
                                  qbVector<double> &localNormal, qbVector<double> &localColor)
{
    // compute the values of a,b and c
    qbVector<double> vhat = castRay.m_lab;
    vhat.Normalize();

    // note that a is equal to the squared magnitude of the
    // direction of the cast ray. As this will be a unit vector,
    // we can conclude that the value of 'a' will always be 1
    // a = 1.0

    // calculate b
    double b = 2.0 * qbVector<double>::dot(castRay.m_point1, vhat);

    // calculate c
    double c = qbVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

    // test whether we actually have an intersection
    // discriminant
    double intTest = (b * b) - 4.0 * c;

    if (intTest > 0.0)
    {
        double numSQRT = sqrt(intTest);
        double t1 = (-b + numSQRT) / 2.0;
        double t2 = (-b - numSQRT) / 2.0;

        // if either t1 or t2 are negative, then at least part of the object
        // is behing the camera and so we'll ignore it
        if ((t1 < 0.0) || (t2 < 0.0))
        {
            return false;
        }
        else
        {
            // Determine which point of intersection was closest to the camera
            if (t1 < t2)
            {
                intPoint = castRay.m_point1 + (vhat * t1);
            }
            else
            {
                intPoint = castRay.m_point1 + (vhat * t2);
            }

            //Compute the local Normal
            localNormal = intPoint;
            localNormal.Normalize();
        }
        return true;
    }
    else
    {
        return false;
    }
}
