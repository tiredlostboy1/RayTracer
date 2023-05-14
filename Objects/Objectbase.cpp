#include "Objectbase.hpp"
#include <cmath>
#include <limits>

ObjectBase::ObjectBase() {}

ObjectBase::~ObjectBase() {}

bool ObjectBase::TestIntersections(const Ray &castRay, qbVector<double> &intPoint,
                                   qbVector<double> &localNormal, qbVector<double> &localColor)
{
    return false;
}

bool ObjectBase::CloseEnough(const double f1, const double f2){
    return std::fabs(f1 - f2) < std::numeric_limits<double>::epsilon();
}