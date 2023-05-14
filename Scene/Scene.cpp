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
    double miDist = std::numeric_limits<double>::max();
    double maxDist = std::numeric_limits<double>::min();

    for (int x = 0; x < xSize; ++x)
    {
        for (int y = 0; y < ySize; ++y)
        {
            //Normalize the x and y coordinates
            double normX = (static_cast<double>(x) * xFact) - 1.0;
            double normY = (static_cast<double>(y) * yFact) - 1.0;

            //Generate Ray for that pixel
            m_camera.GenerateRay(normX, normY, cameraRay);

            //test if we have valid intersection
            bool validInt = m_testSphere.TestIntersections(cameraRay, intPoint, localNormal, localColor);

            if(validInt){
                outputImage.SetPixel(x, y, 255.0, 0.0, 0.0);
            }
            else{
                outputImage.SetPixel(x, y, 0.0, 0.0, 0.0);
            }
        }
    }

    return true;
}
