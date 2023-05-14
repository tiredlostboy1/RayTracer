#include "Scene.hpp"
#include <limits>

Scene::Scene()
{
    // configure the camera
    m_camera.SetPosition(qbVector<double>{std::vector<double>{0.0, -10.0, 0.0}});
    m_camera.SetLookAt(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}});
    m_camera.SetUp(qbVector<double>{std::vector<double>{0.0, 0.0, 1.0}});
    m_camera.SetHorizontalSize(0.25);
    m_camera.SetAspect(16.0 / 9.0);
    m_camera.UpdateCameraGeometry();

    // Construct a test sphere
    m_objectVec.push_back(std::make_shared<ObjSphere>(ObjSphere()));
    m_objectVec.push_back(std::make_shared<ObjSphere>(ObjSphere()));
    m_objectVec.push_back(std::make_shared<ObjSphere>(ObjSphere()));

    // Modify the spheres
    GTform testMatrix1, testMatrix2, testMatrix3;
    testMatrix1.SetTransform(qbVector<double>{std::vector<double>{-1.5, 0.0, 0.0}}, qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                             qbVector<double>{std::vector<double>{0.5, 0.5, 0.75}});

    testMatrix2.SetTransform(qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}}, qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                             qbVector<double>{std::vector<double>{0.75, 0.5, 0.5}});

    testMatrix2.SetTransform(qbVector<double>{std::vector<double>{1.5, 0.0, 0.0}}, qbVector<double>{std::vector<double>{0.0, 0.0, 0.0}},
                             qbVector<double>{std::vector<double>{0.75, 0.75, 0.75}});

    m_objectVec.at(0)->SetTransformMatrix(testMatrix1);
    m_objectVec.at(1)->SetTransformMatrix(testMatrix2);
    m_objectVec.at(2)->SetTransformMatrix(testMatrix3);

    m_objectVec.at(0)->m_baseColor = qbVector<double>{std::vector<double>{64.0, 128.0, 200.0}};
    m_objectVec.at(1)->m_baseColor = qbVector<double>{std::vector<double>{255.0, 128.0, 0.0}};
    m_objectVec.at(2)->m_baseColor = qbVector<double>{std::vector<double>{255.0, 200.0, 0.0}};

    // construct a test light
    m_lightVec.push_back(std::make_shared<PointLight>(PointLight()));
    m_lightVec.at(0)->m_location = qbVector<double>{std::vector<double>{5.0, -10.0, -5.0}};
    m_lightVec.at(0)->m_color = qbVector<double>{std::vector<double>{255.0, 255.0, 255.0}};
}

bool Scene::Render(Image &outputImage)
{
    // get the dimensions of the output image
    int xSize = outputImage.GetXSize();
    int ySize = outputImage.GetYSize();

    // loop over each pixel in our image
    Ray cameraRay;
    qbVector<double> intPoint{3};
    qbVector<double> localNormal{3};
    qbVector<double> localColor{3};

    double xFact = 1.0 / (static_cast<double>(xSize) / 2.0); // gives us value between [0;2]
    double yFact = 1.0 / (static_cast<double>(ySize) / 2.0); // gives us value between [0;2]
    double minDist = std::numeric_limits<double>::max();
    double maxDist = std::numeric_limits<double>::min();

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
            for (const auto &currentObject : m_objectVec)
            {
                bool validInt = currentObject->TestIntersections(cameraRay, intPoint, localNormal, localColor);
                if (validInt)
                {
                    // Compute intensity of illumination
                    double intensity;
                    qbVector<double> color{3};
                    bool validIllum = false;
                    for (auto currentLight : m_lightVec)
                    {
                        validIllum = currentLight->ComputeIllumination(intPoint, localNormal, m_objectVec, currentObject, color, intensity);
                    }

                    // compute the distance between the camera and the point of intersection
                    double dist = (intPoint - cameraRay.m_point1).norm();
                    minDist = std::min(minDist, dist);
                    maxDist = std::max(maxDist, dist);

                    if (validIllum)
                    {
                        // outputImage.SetPixel(x, y, 255.0 * intensity, 0.0, 0.0);
                        outputImage.SetPixel(x, y, localColor.GetElement(0) * intensity, localColor.GetElement(1) * intensity,
                                                 localColor.GetElement(2) * intensity);
                    }
                    else
                    {
                        //leave this pixel unchanged
                        //outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
                    }
                }
                else
                {
                    //leave this pixel unchanged
                    //outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
                }
            }
        }
    }

    std::cout << "Minimum distance: " << minDist << std::endl;
    std::cout << "Maximum distance: " << maxDist << std::endl;

    return true;
}
