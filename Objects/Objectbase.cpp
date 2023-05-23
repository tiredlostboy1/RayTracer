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

bool ObjectBase::CloseEnough(const double f1, const double f2)
{
    return std::fabs(f1 - f2) < std::numeric_limits<double>::epsilon();
}

void ObjectBase::SetTransformMatrix(const GTform& transformMatrix){
    m_transformMatrix = transformMatrix;
}

bool ObjectBase::AssignMaterial(const std::shared_ptr<MaterialBase>& objectMaterial){
    m_pMaterial = objectMaterial;
    m_hasMaterial = true;
    return m_hasMaterial;
}