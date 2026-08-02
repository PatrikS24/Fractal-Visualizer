

typedef struct float128
{
  float a0;
  float a1;
  float a2;
  float a3;
} float128;

float128 renormalize(float c0, float c1, float c2, float c3, float c4);
float128 float128Add(float128 a, float128 b);
float128 float128Sub(float128 a, float128 b);
float128 float128Neg(float128 a);
float128 float128MulFast(float128 a, float128 b);
float128 float128MulScalar(float128 a, float b);
float128 float128DivFast(float128 a, float128 b);
