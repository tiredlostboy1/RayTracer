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

    //copy the ray and apply the backwards transform
    //from world coords to local coords
    Ray bckRay = m_transformMatrix.Apply(castRay, BCKTFORM);

    // compute the values of a,b and c
    qbVector<double> vhat = bckRay.m_lab;
    vhat.Normalize();

    // note that a is equal to the squared magnitude of the
    // direction of the cast ray. As this will be a unit vector,
    // we can conclude that the value of 'a' will always be 1
    // a = 1.0

    // calculate b
    double b = 2.0 * qbVector<double>::dot(bckRay.m_point1, vhat);

    // calculate c
    double c = qbVector<double>::dot(bckRay.m_point1, bckRay.m_point1) - 1.0;

    // test whether we actually have an intersection
    // discriminant
    double intTest = (b * b) - 4.0 * c;

    //point of intersection
    qbVector<double> poi;

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
                poi = bckRay.m_point1 + (vhat * t1);
            }
            else
            {
                poi = bckRay.m_point1 + (vhat * t2);
            }

            //we need to transform the intersection back to world coords
            intPoint = m_transformMatrix.Apply(poi, FWDTFORM);


            //Compute the local Normal
            qbVector<double> objOrigin = qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}};
            qbVector<double> newobjOrigin= m_transformMatrix.Apply(objOrigin, FWDTFORM);
            localNormal = intPoint - newobjOrigin;
            localNormal.Normalize();

            //return the base color
            localColor = m_baseColor;
        }
        return true;
    }
    else
    {
        return false;
    }
}
