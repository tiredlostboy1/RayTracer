#ifndef GTFM_H
#define GTFM_H

#include "../Math/vector.h"
#include "../Math/matrix.h"
#include "../Ray/Ray.hpp"

// Define direction flag values forwardtransform/backwardstransform
constexpr bool FWDTFORM = true;
constexpr bool BCKTFORM = false;

class GTform
{
public:
    GTform();
    ~GTform();

    // Construct from a pair of matrixes
    GTform(const qbMatrix2<double> &fwd, const qbMatrix2<double> &bck);

    // to set translation, rotation and scale components
    void SetTransform(const qbVector<double> &translation,
                      const qbVector<double> &rotation,
                      const qbVector<double> &scale);

    // getters
    qbMatrix2<double> GetForward();
    qbMatrix2<double> GetBackward();

    // to apply the transform
    Ray Apply(const Ray &inputRay, bool dirFlag);
    qbVector<double> Apply(const qbVector<double> &inputVector, bool dirFlag);

    // overload operators

    //*
    friend GTform operator*(const GTform &lhs, const GTform &rhs);

    //=
    GTform& operator=(const GTform &rhs);

    // to print transform matrix to STDOUT
    void PrintMatrix(bool dirFlag);

    // to allow printing of vectors
    static void PrintVector(const qbVector<double> &vector);

private:
    void Print(const qbMatrix2<double>& matrix);

    qbMatrix2<double> m_fwdtfm {4, 4};
    qbMatrix2<double> m_bcktfm {4, 4};
};

#endif