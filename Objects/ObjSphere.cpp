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
    //compute the values of a,b and c
    qbVector<double> vhat = castRay.m_lab;
    vhat.Normalize();

    //note that a is equal to the squared magnitude of the
    //direction of the cast ray. As this will be a unit vector,
    //we can conclude that the value of 'a' will always be 1
    //a = 1.0

    //calculate b
    double b = 2.0 * qbVector<double>::dot(castRay.m_point1, vhat);

    //calculate c
    double c = qbVector<double>::dot(castRay.m_point1, castRay.m_point1) - 1.0;

    //test whether we actually have an intersection
    //discriminant
     double intTest = (b*b) - 4.0 * c;
    
    if(intTest > 0.0){
        return true;
    }
    else{
        return false;
    }
}
