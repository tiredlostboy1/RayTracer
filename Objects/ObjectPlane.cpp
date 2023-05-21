#include "ObjectPlane.hpp"
#include <cmath>

ObjPlane::ObjPlane()
{
}

ObjPlane::~ObjPlane()
{
}

bool ObjPlane::TestIntersections(const Ray &castRay, qbVector<double> &intPoint,
                                 qbVector<double> &localNormal, qbVector<double> &localColor)
{
    // copy the ray and apply the backwards transform
    Ray bcRay = m_transformMatrix.Apply(castRay, BCKTFORM);

    // copy the m_lab vector from bckRay and normalize it
    qbVector<double> k = bcRay.m_lab;
    k.Normalize();

    // check if there is an intersection, if the castRay is not parallel to the plane
    if (!CloseEnough(k.GetElement(2), 0.0))
    {
        // there is an intersection
        double t = bcRay.m_point1.GetElement(2) / -k.GetElement(2);

        // if t is negative then the intersection point must be behind
        if (t > 0.0)
        {
            // compute the values for u and v
            double u = bcRay.m_point1.GetElement(0) + (k.GetElement(0) * t);
            double v = bcRay.m_point1.GetElement(1) + (k.GetElement(1) * t);

            // if the magnitude of both u and v is less or equal to one then we must be in the plane
            if (abs(u) < 1.0 && abs(v) < 1.0)
            {
                // compute the point of intersection
                qbVector<double> poi = bcRay.m_point1 + t * k;

                // transform the poi back to world coords
                intPoint = m_transformMatrix.Apply(poi, FWDTFORM);

                // compute the local normal
                qbVector<double> localOrigin{std::vector<double>{0.0, 0.0, 0.0}};
                qbVector<double> normalVector{std::vector<double>{0.0, 0.0, -1.0}};
                qbVector<double> globalOrigin = m_transformMatrix.Apply(localOrigin, FWDTFORM);

                localNormal = m_transformMatrix.Apply(normalVector, FWDTFORM) - globalOrigin;
                localNormal.Normalize();

                // return to the base color
                localColor = m_baseColor;

                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return false;
}
