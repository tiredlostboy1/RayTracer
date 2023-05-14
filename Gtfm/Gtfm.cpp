#include "Gtfm.hpp"

GTform::GTform()
{
    m_fwdtfm.SetToIdentity();
    m_bcktfm.SetToIdentity();
}

GTform::GTform(const GTform &other)
    : m_fwdtfm(other.m_fwdtfm), m_bcktfm(other.m_bcktfm)
{
}

GTform::~GTform()
{
}

GTform::GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck)
{
    // verify that the inputs are 4x4
    if ((fwd.GetNumRows() != 4) || (fwd.GetNumCols() != 4) ||
        (bck.GetNumRows() != 4) || (bck.GetNumCols() != 4))
    {
        throw std::invalid_argument("Cannot construct, inputs are not 4x4");
    }
    m_fwdtfm = fwd;
    m_bcktfm = bck;
}

void GTform::SetTransform(const qbVector<double> &translation,
                          const qbVector<double> &rotation,
                          const qbVector<double> &scale)
{
    // Define a matrix for each component of the transform
    qbMatrix2<double> translationMatrix{4, 4};
    qbMatrix2<double> rotationMatrixX{4, 4};
    qbMatrix2<double> rotationMatrixY{4, 4};
    qbMatrix2<double> rotationMatrixZ{4, 4};
    qbMatrix2<double> scaleMatrix{4, 4};

    // set these to identity
    translationMatrix.SetToIdentity();
    rotationMatrixX.SetToIdentity();
    rotationMatrixY.SetToIdentity();
    rotationMatrixZ.SetToIdentity();
    scaleMatrix.SetToIdentity();

    // populate these with the appropriate values
    // first the translation matrix
    translationMatrix.SetElement(0, 3, translation.GetElement(0));
    translationMatrix.SetElement(1, 3, translation.GetElement(1));
    translationMatrix.SetElement(2, 3, translation.GetElement(2));

    // rotation matrix
    rotationMatrixZ.SetElement(0, 0, cos(rotation.GetElement(2)));
    rotationMatrixZ.SetElement(0, 1, -sin(rotation.GetElement(2)));
    rotationMatrixZ.SetElement(1, 0, sin(rotation.GetElement(2)));
    rotationMatrixZ.SetElement(1, 1, cos(rotation.GetElement(2)));

    rotationMatrixY.SetElement(0, 0, cos(rotation.GetElement(1)));
    rotationMatrixY.SetElement(0, 2, sin(rotation.GetElement(1)));
    rotationMatrixY.SetElement(2, 0, -sin(rotation.GetElement(1)));
    rotationMatrixY.SetElement(2, 2, cos(rotation.GetElement(1)));

    rotationMatrixX.SetElement(1, 1, cos(rotation.GetElement(0)));
    rotationMatrixX.SetElement(1, 2, -sin(rotation.GetElement(0)));
    rotationMatrixX.SetElement(2, 1, sin(rotation.GetElement(0)));
    rotationMatrixX.SetElement(2, 2, cos(rotation.GetElement(0)));

    // scale matrix
    scaleMatrix.SetElement(0, 0, scale.GetElement(0));
    scaleMatrix.SetElement(1, 1, scale.GetElement(1));
    scaleMatrix.SetElement(2, 2, scale.GetElement(2));

    // combine to give the final forward transform matrix
    m_fwdtfm = translationMatrix *
               scaleMatrix *
               rotationMatrixX *
               rotationMatrixY *
               rotationMatrixZ;

    // compute the backwards transform
    m_bcktfm = m_fwdtfm;
    m_bcktfm.Inverse();
}

qbMatrix2<double> GTform::GetForward()
{
    return m_fwdtfm;
}

qbMatrix2<double> GTform::GetBackward()
{
    return m_bcktfm;
}

Ray GTform::Apply(const Ray &inputRay, bool dirFlag)
{
    Ray outputRay;
    // Create an output object
    if (dirFlag)
    {
        // apply the forward transform
        outputRay.m_point1 = this->Apply(inputRay.m_point1, FWDTFORM);
        outputRay.m_point2 = this->Apply(inputRay.m_point2, FWDTFORM);
        outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
    }

    else
    {
        outputRay.m_point1 = this->Apply(inputRay.m_point1, BCKTFORM);
        outputRay.m_point2 = this->Apply(inputRay.m_point2, BCKTFORM);
        outputRay.m_lab = outputRay.m_point2 - outputRay.m_point1;
    }

    return outputRay;
}

qbVector<double> GTform::Apply(const qbVector<double> &inputVector, bool dirFlag)
{
    // Convert inputVector to a 4-element vector
    std::vector<double> tempData{inputVector.GetElement(0), inputVector.GetElement(1), inputVector.GetElement(2), 1.0};
    qbVector<double> tempVector{tempData};

    // create a vector for the result
    qbVector<double> resultVector;

    if (dirFlag)
    {
        // apply the forward transform
        resultVector = m_fwdtfm * tempVector;
    }

    else
    {
        // apply the backward transform
        resultVector = m_bcktfm * tempVector;
    }

    // reform the output as a 3-element vector
    return qbVector<double>{std::vector<double>{resultVector.GetElement(0), resultVector.GetElement(1), resultVector.GetElement(2)}};
    ;
}

GTform operator*(const GTform &lhs, const GTform &rhs)
{
    // form the product of the two forward transforms
    qbMatrix2<double> fwdResult = lhs.m_fwdtfm * rhs.m_fwdtfm;

    // compute the backward transform as the inverse of the forward transform
    qbMatrix2<double> bckResult = fwdResult;
    bckResult.Inverse();

    // form the final result

    return GTform(fwdResult, bckResult);
}

GTform &GTform::operator=(const GTform &rhs)
{
    if (this != &rhs)
    {
        m_fwdtfm = rhs.m_fwdtfm;
        m_bcktfm = rhs.m_bcktfm;
    }

    return *this;
}

void GTform::PrintMatrix(bool dirFlag)
{
    if (dirFlag)
    {
        Print(m_fwdtfm);
    }
    else
    {
        Print(m_bcktfm);
    }
}

void GTform::Print(const qbMatrix2<double> &matrix)
{
    int nRows = matrix.GetNumRows();
    int nCols = matrix.GetNumCols();
    for (int row = 0; row < nRows; ++row)
    {
        for (int col = 0; col < nCols; ++col)
        {
            std::cout << std::fixed << std::setprecision(3) << matrix.GetElement(row, col) << " ";
        }
        std::cout << std::endl;
    }
}

void GTform::PrintVector(const qbVector<double> &vector)
{
    int nRows = vector.GetNumDims();
    for (int row = 0; row < nRows; ++row)
    {
        std::cout << std::fixed << std::setprecision(3) << vector.GetElement(row) << " ";
    }
}
