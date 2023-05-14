#ifndef OBJSPHERE_H
#define OBJSPHERE_H
#include "Objectbase.hpp"
#include "../Ray/Ray.hpp"

class ObjSphere : public ObjectBase
{
public:
    // default constructor
    // this will define a unit sphere at the origin
    ObjSphere();

    // destructor
    virtual ~ObjSphere() override;

    virtual bool TestIntersections(const Ray &castRay, qbVector<double> &intPoint,
                                   qbVector<double> &localNormal, qbVector<double> &localColor);

private:
};

#endif