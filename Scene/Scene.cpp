#include "Scene.hpp"
#include <limits>

Scene::Scene()
{
    // create material
    auto TestMaterial = std::make_shared<SimpleMaterial>(SimpleMaterial());

    // setup the material
    TestMaterial->m_baseColor = qbVector<double>{std::vector<double>{0.25, 0.5, 0.8}};
    TestMaterial->m_reflectivity = 0.5;
    TestMaterial->m_shininess = 10.0;

    // configure the camera
    m_camera.SetPosition(qbVector<double>{std::vector<double>{5.0, -10.0, -1.0}});
    m_camera.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
    m_camera.SetUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
    m_camera.SetHorizontalSize(0.25);
    m_camera.SetAspect(16.0 / 9.0);
    m_camera.UpdateCameraGeometry();

    // Construct a test sphere
    m_objectVec.push_back(std::make_shared<ObjSphere>(ObjSphere()));
    m_objectVec.push_back(std::make_shared<ObjSphere>(ObjSphere()));
    m_objectVec.push_back(std::make_shared<ObjSphere>(ObjSphere()));

    // Construct a plane
    m_objectVec.push_back(std::make_shared<ObjPlane>(ObjPlane()));
    // color
    m_objectVec.at(3)->m_baseColor = qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}};

    // transform the plane
    GTform planeMatrix;
    planeMatrix.SetTransform(qbVector<double>{std::vector<double>{0, 0.0, 0.75}},
                             qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                             qbVector<double>{std::vector<double>{4.0, 4.0, 1.0}});

    // set the transformation
    m_objectVec.at(3)->SetTransformMatrix(planeMatrix);

    // Modify the spheres
    GTform testMatrix1, testMatrix2, testMatrix3;
    testMatrix1.SetTransform(qbVector<double>{std::vector<double>{-1.75, 0.0, 0.0}},
                             qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                             qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

    testMatrix2.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                             qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                             qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

    testMatrix3.SetTransform(qbVector<double>{std::vector<double>{2.0, 0.0, 0.0}},
                             qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                             qbVector<double>{std::vector<double>{0.5, 0.5, 0.5}});

    m_objectVec.at(0)->SetTransformMatrix(testMatrix1);
    m_objectVec.at(1)->SetTransformMatrix(testMatrix2);
    m_objectVec.at(2)->SetTransformMatrix(testMatrix3);

    m_objectVec.at(0)->m_baseColor = qbVector<double>{std::vector<double>{0.25, 0.5, 0.8}};
    m_objectVec.at(1)->m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.5, 0.0}};
    m_objectVec.at(2)->m_baseColor = qbVector<double>{std::vector<double>{1.0, 0.8, 0.0}};

    //assign the materials to objects
    m_objectVec.at(0)-> AssignMaterial(TestMaterial);



    // Construct a test light.
    m_lightVec.push_back(std::make_shared<PointLight>(PointLight()));
    m_lightVec.at(0)->m_location = qbVector<double>{std::vector<double>{5.0, -10.0, -5.0}};
    m_lightVec.at(0)->m_color = qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}};

    m_lightVec.push_back(std::make_shared<PointLight>(PointLight()));
    m_lightVec.at(1)->m_location = qbVector<double>{std::vector<double>{-5.0, -10.0, -5.0}};
    m_lightVec.at(1)->m_color = qbVector<double>{std::vector<double>{1.0, 0.0, 0.0}};

    m_lightVec.push_back(std::make_shared<PointLight>(PointLight()));
    m_lightVec.at(2)->m_location = qbVector<double>{std::vector<double>{0.0, -10.0, -5.0}};
    m_lightVec.at(2)->m_color = qbVector<double>{std::vector<double>{0.0, 1.0, 0.0}};
}

bool Scene::Render(Image &outputImage)
{
    // get the dimensions of the output image
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    // loop over each pixel in our image
    Ray cameraRay;
    qbVector<double> intPoint(3);
    qbVector<double> localNormal(3);
    qbVector<double> localColor(3);

    double xFact = 1.0 / (static_cast<double>(xSize) / 2.0); // gives us value between [0;2]
    double yFact = 1.0 / (static_cast<double>(ySize) / 2.0); // gives us value between [0;2]

    for (int x = 0; x < xSize; ++x)
    {
        for (int y = 0; y < ySize; ++y)
        {
            // Normalize the x and y coordinates
            double normX = (static_cast<double>(x) * xFact) - 1.0;
            double normY = (static_cast<double>(y) * yFact) - 1.0;

            // Generate Ray for that pixel
            m_camera.GenerateRay(normX, normY, cameraRay);

            // test for intersections with all objects in the scene
            std::shared_ptr<ObjectBase> closestObject;
            qbVector<double> closestIntPoint{3};
            qbVector<double> closestLocalNormal{3};
            qbVector<double> closestLocalColor{3};
            bool intersectionFound = CastRay(cameraRay, closestObject, closestIntPoint, closestLocalNormal, closestLocalColor);

            // compute the illumination for the closest object, assuming there was a valid intersection
            if (intersectionFound)
            {
                // check if the object has a material
                if (closestObject->m_hasMaterial)
                {
                    // use the material to compute the color
                    qbVector<double> color = closestObject->m_pMaterial->ComputeColor(m_objectVec, m_lightVec,
                                                                                      closestObject, closestIntPoint,
                                                                                      closestLocalNormal, cameraRay);
                    outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
                }
                else
                {
                    // use the basic method to compute the color
                    qbVector<double> matColor = MaterialBase::ComputeDiffuseColor(m_objectVec, m_lightVec,
                                                                                  closestObject, closestIntPoint,
                                                                                  closestLocalNormal, closestObject->m_baseColor);
                    outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
                }
            }
        }
    }
    return true;
}

bool Scene::CastRay(Ray &castRay, std::shared_ptr<ObjectBase> &closestObject, qbVector<double> &closestIntPoint,
                    qbVector<double> &closestLocalNormal, qbVector<double> &closestLocalColor)
{
    qbVector<double> intPoint{3};
    qbVector<double> localNormal{3};
    qbVector<double> localColor{3};
    double minDist = std::numeric_limits<double>::max();
    bool intersectionFound = false;
    for (auto currentObject : m_objectVec)
    {
        bool validInt = currentObject->TestIntersections(castRay, intPoint, localNormal, localColor);
        if (validInt)
        {
            // set the flag to indicate that we found an intersection
            intersectionFound = true;

            // compute the distance between the camera and the point of intersection
            double dist = (intPoint - castRay.m_point1).norm();

            // if this object is closer to the camera than any other that we see, then store a reference to it
            if (dist < minDist)
            {
                minDist = dist;
                closestObject = currentObject;
                closestIntPoint = intPoint;
                closestLocalNormal = localNormal;
                closestLocalColor = localColor;
            }
        }
    }
    return intersectionFound;
}