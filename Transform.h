#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Matrix.h"
class Transform {
  public:
    static std::vector<Transform *> transforms;
    float x;
    float y;
    float z;
    int transformation;
    int axis;
    Matrix matrix;
    static Coord performTransform(Coord loc, Matrix transMatrix);
    static Matrix calcTransMatrix();
    static Matrix emptyTransforms();
    Transform(int transformation, float x, float y, float z) : transformation(transformation), x(x), y(y), z(z) {
        transforms.push_back(this);
        this->matrix = Matrix(this->transformation, this->x, this->y, this->z);
    }
};

Matrix Transform::calcTransMatrix() {
    Matrix transformation;
    if ((Transform::transforms).size() == 0) {
        return transformation;
    }
    for(std::vector<Transform *>::iterator itor=(Transform::transforms).begin(); true; ++itor) {
        if ((itor) == Transform::transforms.begin()) {
            transformation = (*itor)->matrix;
        } else {
            transformation = transformation.multiply((*itor)->matrix);
        }
        if (itor == std::prev(Transform::transforms.end())) {
            break;
        }
    }
    return transformation;
}

Matrix Transform::emptyTransforms() {
    return Matrix();
}

Coord Transform::performTransform(Coord loc, Matrix transMatrix) {
    if ((Transform::transforms).size() == 0) {
        return loc;
    }
    Coord toReturn = Coord();
    Matrix m = transMatrix;
    toReturn.x = m.matrix[0][0]*loc.x+m.matrix[1][0]*loc.y+m.matrix[2][0]*loc.z+m.matrix[3][0];
    toReturn.y = m.matrix[0][1]*loc.x+m.matrix[1][1]*loc.y+m.matrix[2][1]*loc.z+m.matrix[3][1];
    toReturn.z = m.matrix[0][2]*loc.x+m.matrix[1][2]*loc.y+m.matrix[2][2]*loc.z+m.matrix[3][2];

    return toReturn;
}

std::ostream& operator<< (std::ostream &out, Transform &trans)
{
    out << "Transformation: " << trans.transformation <<
        "\n(x,y,z) (if not rotation): (" << trans.x << ", " << trans.y << ", " << trans.z << ")\n" <<
        "Matrix: \n" << trans.matrix;
    return out;
}

std::vector<Transform *> Transform::transforms;
#endif