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
    static void invert(Matrix* m);
    Matrix transpose();
    Matrix multiply(Matrix m2);
    Matrix multiply(float s);
    Vector multiplyDir(Vector v);
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

Vector Matrix::multiplyDir(Vector v) {
    Vector product = Vector();
    int total = 0;
    for (int j = 0; j < 4; ++j) {
        total = 0;
        for (int i = 0; i < 4; ++i) {
            if (i == 0) {
                total+= this->matrix[i][j]*v.x;
            }
            if (i == 1) {
                total+= this->matrix[i][j]*v.y;
            }
            if (i == 2) {
                total+= this->matrix[i][j]*v.z;
            }
            if (i == 3) {
                total+= 0;
            }
        }
        if (j == 0) {
            product.x = total;
        }
        if (j == 1) {
            product.y = total;
        }
        if (j == 2) {
            product.z = total;
        }
        total=0;
    }
    return product;
}

//INVERSE FUNCTIONS BROUGHT TO YOU BY:
//https://chi3x10.wordpress.com/2008/05/28/calculate-matrix-inversion-in-c/
// calculate the cofactor of element (row,col)
int GetMinor(float **src, float **dest, int row, int col, int order)
{
    // indicate which col and row is being copied to dest
    int colCount=0,rowCount=0;
 
    for(int i = 0; i < order; i++ )
    {
        if( i != row )
        {
            colCount = 0;
            for(int j = 0; j < order; j++ )
            {
                // when j is not the element
                if( j != col )
                {
                    dest[rowCount][colCount] = src[i][j];
                    colCount++;
                }
            }
            rowCount++;
        }
    }
 
    return 1;
}

// Calculate the determinant recursively.
double CalcDeterminant( float **mat, int order)
{
    // order must be >= 0
    // stop the recursion when matrix is a single element
    if( order == 1 )
        return mat[0][0];
 
    // the determinant value
    float det = 0;
 
    // allocate the cofactor matrix
    float **minor;
    minor = new float*[order-1];
    for(int i=0;i<order-1;i++)
        minor[i] = new float[order-1];
 
    for(int i = 0; i < order; i++ )
    {
        // get minor of element (0,i)
        GetMinor( mat, minor, 0, i , order);
        // the recusion is here!
 
        det += (i%2==1?-1.0:1.0) * mat[0][i] * CalcDeterminant(minor,order-1);
        //det += pow( -1.0, i ) * mat[0][i] * CalcDeterminant( minor,order-1 );
    }
 
    // release memory
    for(int i=0;i<order-1;i++)
        delete [] minor[i];
    delete [] minor;
 
    return det;
}

// matrix inversioon
// the result is put in Y
void MatrixInversion(float **A, int order, float **Y)
{
    // get the determinant of a
    double det = 1.0/CalcDeterminant(A,order);
 
    // memory allocation
    float *temp = new float[(order-1)*(order-1)];
    float **minor = new float*[order-1];
    for(int i=0;i<order-1;i++)
        minor[i] = temp+(i*(order-1));
 
    for(int j=0;j<order;j++)
    {
        for(int i=0;i<order;i++)
        {
            // get the co-factor (matrix) of A(j,i)
            GetMinor(A,minor,j,i,order);
            Y[i][j] = det*CalcDeterminant(minor,order-1);
            if( (i+j)%2 == 1)
                Y[i][j] = -Y[i][j];
        }
    }
 
    // release memory
    //delete [] minor[0];
    delete [] temp;
    delete [] minor;
}

Matrix Matrix::transpose() {
    Matrix m = Matrix();
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m.matrix[i][j] = this->matrix[j][i];
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
    for (int j = 0; j < 4; ++j) {
        total = 0;
        for (int i = 0; i < 4; ++i) {
            if (i == 0) {
                total+= this->matrix[i][j]*v.x;
            }
            if (i == 1) {
                total+= this->matrix[i][j]*v.y;
            }
            if (i == 2) {
                total+= this->matrix[i][j]*v.z;
            }
            if (i == 3) {
                total+= this->matrix[i][j];
            }
        }
        if (j == 0) {
            product.x = total;
        }
        if (j == 1) {
            product.y = total;
        }
        if (j == 2) {
            product.z = total;
        }
        total=0;
    }
    return product;
}

std::ostream& operator<< (std::ostream &out, Matrix &m)
{
    out << "| " << floorf(m.matrix[0][0]*100)/100 << "\t" << floorf(m.matrix[1][0]*100)/100 << "\t" << floorf(m.matrix[2][0]*100)/100 << "\t" << floorf(m.matrix[3][0]*100)/100 << "\t|\n";
    out << "| " << floorf(m.matrix[0][1]*100)/100 << "\t" << floorf(m.matrix[1][1]*100)/100 << "\t" << floorf(m.matrix[2][1]*100)/100 << "\t" << floorf(m.matrix[3][1]*100)/100 << "\t|\n";
    out << "| " << floorf(m.matrix[0][2]*100)/100 << "\t" << floorf(m.matrix[1][2]*100)/100 << "\t" << floorf(m.matrix[2][2]*100)/100 << "\t" << floorf(m.matrix[3][2]*100)/100 << "\t|\n";
    out << "| " << floorf(m.matrix[0][3]*100)/100 << "\t" << floorf(m.matrix[1][3]*100)/100 << "\t" << floorf(m.matrix[2][3]*100)/100 << "\t" << floorf(m.matrix[3][3]*100)/100 << "\t|\n";
    return out;
}

#endif