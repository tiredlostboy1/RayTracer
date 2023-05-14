#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "../Math/vector.h"
#include "../Ray/Ray.hpp"
#include "../Gtfm/Gtfm.hpp"

class ObjectBase
{

public:
    ObjectBase();
    virtual ~ObjectBase();

    // function to test for intersections
    virtual bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint,
                                   qbVector<double> &localNormal, qbVector<double> &localColor);

    //function to set the transform matrix
    void SetTransformMatrix(const GTform& transformMatrix);

    // function to test whether two floating-point numbers are close to being equal
    bool CloseEnough(const double f1, const double f2);

    // public member vars
public:
    // the base color of the object
    qbVector<double> m_baseColor{3};

    //the geometric transform applied to the object
    GTform m_transformMatrix;
};

#endif
