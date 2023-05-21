#ifndef PLANE_H
#define PLANE_H

#include "Objectbase.hpp"
#include "../Gtfm/Gtfm.hpp"

class ObjPlane : public ObjectBase
{

public:
    ObjPlane();

    virtual ~ObjPlane();

    // override the function to test for intersections
    virtual bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint,
                                   qbVector<double> &localNormal, qbVector<double> &localColor) override;

private:
    
};

#endif // PLANE_H