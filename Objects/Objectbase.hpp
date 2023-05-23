#ifndef OBJECTBASE_H
#define OBJECTBASE_H

#include "../Math/vector.h"
#include "../Ray/Ray.hpp"
#include "../Gtfm/Gtfm.hpp"

//forward declaration of the material base class
class MaterialBase;



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

    //function to assign a material
    bool AssignMaterial(const std::shared_ptr<MaterialBase>& objectMaterial);

    // public member vars
public:
    // the base color of the object
    qbVector<double> m_baseColor{3};

    //the geometric transform applied to the object
    GTform m_transformMatrix;

    //a reference to the material assigned to this object
    std::shared_ptr<MaterialBase> m_pMaterial;

    //flag to indicate whether this object has a material or not 
    bool m_hasMaterial = false;
};

#endif
