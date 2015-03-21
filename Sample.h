#ifndef SAMPLE_H
#define SAMPLE_H

class Sample {
  public:
    Sample () {};
    float x;
    float y;
    Sample(float x, float y) : x(x), y(y) {}
};
std::ostream& operator<< (std::ostream &out, Sample &sample)
{
    out << "(" << sample.x << ", " <<
        sample.y << ")\n";
    return out;
}
#endif
