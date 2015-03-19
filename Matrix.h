#ifndef MATRIX_H
#define MATRIX_H
const int TRANSLATION = 0;
const int SCALE = 1;
const int ROTATION = 2;
const int X = 0;
const int Y = 1;
const int Z = 2;
class Matrix {
  public:
    float** matrix = new float*[4];
    void setVal(int x, int y, int val);
    Matrix inverse();
    Matrix transpose();
    Matrix multiply(Matrix m2);
    Matrix multiply(float s);
    Vector operator * (Vector v);
    Matrix operator + (Matrix m);
    Matrix() {
        for (int i = 0; i < 4; i++) {
            matrix[i] = new float[4];
        }
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 4; y++) {
                if (x==y) {
                    matrix[x][y] = 1;
                } else {
                    matrix[x][y] = 0;
                }
            }
        }
    }
    Matrix(int transformation, float x, float y, float z) {
        matrix = Matrix().matrix;
        if (transformation == TRANSLATION) {
            matrix[3][0] = x;
            matrix[3][1] = y;
            matrix[3][2] = z;
        } else if (transformation == SCALE) {
            matrix[0][0] = x;
            matrix[1][1] = y;
            matrix[2][2] = z;
        } else if (transformation == ROTATION) {
            Matrix A = Matrix();
            Matrix I = Matrix();
            Vector r = Vector(x,y,z);
            float angle = r.magnitude();
            r = r.normalize();
            A.matrix[0][0] = 0;
            A.matrix[0][0] = r.z;
            A.matrix[0][2] = -1*r.y;
            A.matrix[1][0] = -1*r.z;
            A.matrix[1][1] = 0;
            A.matrix[1][2] = r.x;
            A.matrix[2][0] = r.y;
            A.matrix[2][2] = 0;
            A.matrix[3][1] = -1*r.x;
            A.matrix[3][3] = 0;
            matrix = (I+A.multiply(sin(angle))+A.multiply(A).multiply(1-cos(angle))).matrix;
        }
    }
};

void Matrix::setVal(int x, int y, int val) {
    matrix[x][y] = val;
}

Matrix Matrix::inverse() {
    Matrix m = Matrix();
    for (int i = 0; i < 4; ++i) {
        float diviser = matrix[i][i];
        for (int k = 0; k < 4; k++) {
            matrix[i][k] /= diviser;
            m.matrix[i][k] /= diviser;
        }
        for (int j = 0; j < 4; ++j) {
            if (i!=j) {
                float multiplier = matrix[j][i];
                for (int l = 0; l < 4; l++) {
                    matrix[j][l] -= multiplier*matrix[i][l];
                    m.matrix[j][l] -= multiplier*matrix[i][l];
                }
            }
        }
    }
    return m;
}

Matrix Matrix::transpose() {
    Matrix m = Matrix();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m.matrix[i][j] = m.matrix[j][i];
        }
    }
    return m;
}

Matrix Matrix::multiply(Matrix m2) {
    Matrix product = Matrix();
    for (int l = 0; l < 4; ++l) {
        product.setVal(l,l,0);
    }
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            product.matrix[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                product.matrix[i][j] = product.matrix[i][j] + (m2.matrix[i][k]*this->matrix[k][j]);
            }
        }
    }
    return product;
}



Matrix Matrix::multiply(float s) {
    Matrix product = Matrix();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            product.matrix[i][j] = this->matrix[i][j]*s;
        }
    }
    return product;
}

Matrix Matrix::operator + (Matrix m) {
    Matrix sum = Matrix();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            sum.matrix[i][j] = this->matrix[i][j]+m.matrix[i][j];
        }
    }
    return sum;
};

Vector Matrix::operator * (Vector v) {
    Vector product = Vector();
    int total = 0;
    for (int i = 0; i < 4; ++i) {
        total = 0;
        for (int j = 0; j < 4; ++j) {
            total+= this->matrix[i][j];
        }
        if (i == 0) {
            product.x = total;
        }
        if (i == 1) {
            product.y = total;
        }
        if (i == 2) {
            product.z = total;
        }
        total=0;
    }
    return product;
};

std::ostream& operator<< (std::ostream &out, Matrix &m)
{
    out << "| " << floorf(m.matrix[0][0]*100)/100 << "\t" << floorf(m.matrix[1][0]*100)/100 << "\t" << floorf(m.matrix[2][0]*100)/100 << "\t" << floorf(m.matrix[3][0]*100)/100 << "\t|\n";
    out << "| " << floorf(m.matrix[0][1]*100)/100 << "\t" << floorf(m.matrix[1][1]*100)/100 << "\t" << floorf(m.matrix[2][1]*100)/100 << "\t" << floorf(m.matrix[3][1]*100)/100 << "\t|\n";
    out << "| " << floorf(m.matrix[0][2]*100)/100 << "\t" << floorf(m.matrix[1][2]*100)/100 << "\t" << floorf(m.matrix[2][2]*100)/100 << "\t" << floorf(m.matrix[3][2]*100)/100 << "\t|\n";
    out << "| " << floorf(m.matrix[0][3]*100)/100 << "\t" << floorf(m.matrix[1][3]*100)/100 << "\t" << floorf(m.matrix[2][3]*100)/100 << "\t" << floorf(m.matrix[3][3]*100)/100 << "\t|\n";
    return out;
}

#endif