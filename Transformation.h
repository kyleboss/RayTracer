#ifndef TRANSFORM_H
#define TRANSFORM_H
Matrix transMatrix = Matrix();
class Transform {
  public:
    static std::vector<Transform *> transforms;
    float x;
    float y;
    float z;
    float angle;
    int transformation;
    int axis;
    Matrix matrix;
    Coord performTransform(Coord loc);
    void calcTransMatrix();
    void emptyTransforms();
    Transform(int transformation, float x, float y, float z) : transformation(transformation), x(x), y(y), z(z) {
        transforms.push_back(this);
        matrix = Matrix(this->transformation, this->x, this->y, this->z);
        calcTransMatrix();
    }
    Transform(int transformation, int axis, float angle) : transformation(transformation), axis(axis), angle(angle) {
        transforms.push_back(this);
        matrix = Matrix(this->transformation, this->axis, this->angle);
        calcTransMatrix();
    }
};

void Transform::calcTransMatrix() {
    Matrix transformation;
    if ((Transform::transforms).size() == 0) {
        transMatrix = transformation;
        return;
    }
    for(std::vector<Transform *>::iterator itor=(Transform::transforms).end(); itor!=Transform::transforms.begin(); --itor) {
        if ((*itor) == *Transform::transforms.end()) {
            transformation = (*itor)->matrix;
        } else {
            transformation = transformation.multiply((*itor)->matrix);
        }
    }
    transMatrix = transformation;
}

void Transform::emptyTransforms() {
    Transform::transforms.clear();
}

Coord Transform::performTransform(Coord loc) {
    Coord toReturn = Coord();
    Matrix m = transMatrix;
    toReturn.x = m.matrix[0][0]*loc.x+m.matrix[1][0]*loc.y+m.matrix[2][0]*loc.z+m.matrix[3][0];
    toReturn.y = m.matrix[0][1]*loc.x+m.matrix[1][1]*loc.y+m.matrix[2][1]*loc.z+m.matrix[3][1];
    toReturn.x = m.matrix[0][2]*loc.x+m.matrix[1][2]*loc.y+m.matrix[2][2]*loc.z+m.matrix[3][2];
    return toReturn;
}

std::ostream& operator<< (std::ostream &out, Transform &trans)
{
    out << "Transformation: " << trans.transformation <<
        "\n(x,y,z) (if not rotation): (" << trans.x << ", " << trans.y << ", " << trans.z << ")\n" <<
        "angle (if rotation): " << trans.angle << "\n" <<
        "Matrix: \n" << trans.matrix;
    return out;
}

std::vector<Transform *> Transform::transforms;
#endif