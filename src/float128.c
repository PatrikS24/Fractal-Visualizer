#include "float128.h"

#define _SPLITTER 8193.0f           // = 2^13i + 1
#define _SPLIT_THRESH 1.8446744e19f // = 2^64

typedef struct TwoSumResult
{
  float value;
  float error;
} TwoSumResult;

typedef struct ThreeSumResult
{
  float value;
  float error1;
  float error2;
} ThreeSumResult;

typedef struct SplitResult
{
  float hi;
  float lo;
} SplitResult;

// Assumes |a| >= |b|
TwoSumResult quickTwoSum(float a, float b)
{
  float s = a + b;
  float e = b - (s - a);
  return (TwoSumResult){s, e};
}

TwoSumResult twoSum(float a, float b)
{
  float s = a + b;
  float v = s - a;
  float e = (a - (s - v)) + (b - v);
  return (TwoSumResult){s, e};
}

ThreeSumResult threeSum(float a, float b, float c)
{
  TwoSumResult uv = twoSum(a, b);
  TwoSumResult r0w = twoSum(uv.value, c);
  TwoSumResult r1r2 = twoSum(uv.error, r0w.error);

  return (ThreeSumResult){r0w.value, r1r2.value, r1r2.error};
}

TwoSumResult threeSumFast(float a, float b, float c)
{
  TwoSumResult uv = twoSum(a, b);
  TwoSumResult r0w = twoSum(uv.value, c);

  return (TwoSumResult){r0w.value, r0w.error + uv.error};
}

/* Computes hi word and lo word of a */
SplitResult split(float a)
{
  float temp, hi, lo;

  if (a > _SPLIT_THRESH || a < -_SPLIT_THRESH)
  {
    a *= 6.103515625e-05f; // 2^-14

    temp = _SPLITTER * a;
    hi = temp - (temp - a);
    lo = a - hi;

    hi *= 16384.0f; // 2^14
    lo *= 16384.0f; // 2^14
  }
  else
  {
    temp = _SPLITTER * a;
    hi = temp - (temp - a);
    lo = a - hi;
  }

  return (SplitResult){hi, lo};
}

/* Computes fl(a*b) and err(a*b). */
TwoSumResult twoProd(float a, float b)
{
  float p = a * b;
  SplitResult aSplit = split(a);
  SplitResult bSplit = split(b);
  float err = ((aSplit.hi * bSplit.hi - p) + aSplit.hi * bSplit.lo + aSplit.lo * bSplit.hi) + aSplit.lo * bSplit.lo;
  return (TwoSumResult){p, err};
}

float128 renormalize(float c0, float c1, float c2, float c3, float c4)
{
  float s0, s1, s2 = 0.0f, s3 = 0.0f;

  // if (isinf(c0))
  //     return (float128){c0, c1, c2, c3};

  TwoSumResult q;

  q = quickTwoSum(c3, c4);
  s0 = q.value;
  c4 = q.error;

  q = quickTwoSum(c2, s0);
  s0 = q.value;
  c3 = q.error;

  q = quickTwoSum(c1, s0);
  s0 = q.value;
  c2 = q.error;

  q = quickTwoSum(c0, s0);
  c0 = q.value;
  c1 = q.error;

  s0 = c0;
  s1 = c1;

  if (s1 != 0.0f)
  {
    q = quickTwoSum(s1, c2);
    s1 = q.value;
    s2 = q.error;

    if (s2 != 0.0f)
    {
      q = quickTwoSum(s2, c3);
      s2 = q.value;
      s3 = q.error;

      if (s3 != 0.0f)
        s3 += c4;
      else
      {
        q = quickTwoSum(s2, c4);
        s2 = q.value;
        s3 = q.error;
      }
    }
    else
    {
      q = quickTwoSum(s1, c3);
      s1 = q.value;
      s2 = q.error;

      if (s2 != 0.0f)
      {
        q = quickTwoSum(s2, c4);
        s2 = q.value;
        s3 = q.error;
      }
      else
      {
        q = quickTwoSum(s1, c4);
        s1 = q.value;
        s2 = q.error;
      }
    }
  }
  else
  {
    q = quickTwoSum(s0, c2);
    s0 = q.value;
    s1 = q.error;

    if (s1 != 0.0f)
    {
      q = quickTwoSum(s1, c3);
      s1 = q.value;
      s2 = q.error;

      if (s2 != 0.0f)
      {
        q = quickTwoSum(s2, c4);
        s2 = q.value;
        s3 = q.error;
      }
      else
      {
        q = quickTwoSum(s1, c4);
        s1 = q.value;
        s2 = q.error;
      }
    }
    else
    {
      q = quickTwoSum(s0, c3);
      s0 = q.value;
      s1 = q.error;

      if (s1 != 0.0f)
      {
        q = quickTwoSum(s1, c4);
        s1 = q.value;
        s2 = q.error;
      }
      else
      {
        q = quickTwoSum(s0, c4);
        s0 = q.value;
        s1 = q.error;
      }
    }
  }

  return (float128){
      s0,
      s1,
      s2,
      s3};
}

float128 float128Add(float128 a, float128 b)
{
  float s0, s1, s2, s3;
  float t0, t1, t2, t3;

  float v0, v1, v2, v3;
  float u0, u1, u2, u3;
  float w0, w1, w2, w3;

  s0 = a.a0 + b.a0;
  s1 = a.a1 + b.a1;
  s2 = a.a2 + b.a2;
  s3 = a.a3 + b.a3;

  v0 = s0 - a.a0;
  v1 = s1 - a.a1;
  v2 = s2 - a.a2;
  v3 = s3 - a.a3;

  u0 = s0 - v0;
  u1 = s1 - v1;
  u2 = s2 - v2;
  u3 = s3 - v3;

  w0 = a.a0 - u0;
  w1 = a.a1 - u1;
  w2 = a.a2 - u2;
  w3 = a.a3 - u3;

  u0 = b.a0 - v0;
  u1 = b.a1 - v1;
  u2 = b.a2 - v2;
  u3 = b.a3 - v3;

  t0 = w0 + u0;
  t1 = w1 + u1;
  t2 = w2 + u2;
  t3 = w3 + u3;

  TwoSumResult ts = twoSum(s1, t0);
  s1 = ts.value;
  t0 = ts.error;

  ThreeSumResult th = threeSum(s2, t0, t1);
  s2 = th.value;
  t0 = th.error1;
  t1 = th.error2;

  TwoSumResult th2 = threeSumFast(s3, t0, t2);
  s3 = th2.value;
  t0 = th2.error;

  t0 = t0 + t1 + t3;

  return renormalize(s0, s1, s2, s3, t0);
}

float128 float128MulFast(float128 a, float128 b)
{
  float p0, p1, p2, p3, p4, p5;
  float q0, q1, q2, q3, q4, q5;
  float t0, t1;
  float s0, s1, s2;

  TwoSumResult tp;
  TwoSumResult ts2;
  ThreeSumResult ts3;

  tp = twoProd(a.a0, b.a0);
  p0 = tp.value;
  q0 = tp.error;

  tp = twoProd(a.a0, b.a1);
  p1 = tp.value;
  q1 = tp.error;
  tp = twoProd(a.a1, b.a0);
  p2 = tp.value;
  q2 = tp.error;

  tp = twoProd(a.a0, b.a2);
  p3 = tp.value;
  q3 = tp.error;
  tp = twoProd(a.a1, b.a1);
  p4 = tp.value;
  q4 = tp.error;
  tp = twoProd(a.a2, b.a0);
  p5 = tp.value;
  q5 = tp.error;

  /* Start Accumulation */
  ts3 = threeSum(p1, p2, q0);
  p1 = ts3.value;
  p2 = ts3.error1;
  q0 = ts3.error2;

  /* Six-Three Sum of p2, q1, q2, p3, p4, p5 */
  ts3 = threeSum(p2, q1, q2);
  p2 = ts3.value;
  q1 = ts3.error1;
  q2 = ts3.error2;

  ts3 = threeSum(p3, p4, p5);
  p3 = ts3.value;
  p4 = ts3.error1;
  p5 = ts3.error2;

  /* compute (s0, s1, s2) = (p2, q1, q2) + (p3, p4, p5) */
  ts2 = twoSum(p2, p3);
  s0 = ts2.value;
  t0 = ts2.error;

  ts2 = twoSum(q1, p4);
  s1 = ts2.value;
  t1 = ts2.error;

  s2 = q2 + p5;

  ts2 = twoSum(s1, t0);
  s1 = ts2.value;
  t0 = ts2.error;

  s2 += (t0 + t1);

  /* O(eps^3) order terms */
  s1 += a.a0 * b.a3 + a.a1 * b.a2 + a.a2 * b.a1 + a.a3 * b.a0 + q0 + q3 + q4 + q5;

  return renormalize(p0, p1, s0, s1, s2);
}

float128 float128Neg(float128 a)
{
  return (float128){-a.a0, -a.a1, -a.a2, -a.a3};
}

float128 float128Sub(float128 a, float128 b)
{
  return float128Add(a, float128Neg(b));
}

float128 float128MulScalar(float128 a, float b)
{
  float p0, p1, p2, p3;
  float q0, q1, q2;
  float s0, s1, s2, s3, s4;

  TwoSumResult tp;
  TwoSumResult ts;
  ThreeSumResult th;

  tp = twoProd(a.a0, b);
  p0 = tp.value;
  q0 = tp.error;
  tp = twoProd(a.a1, b);
  p1 = tp.value;
  q1 = tp.error;
  tp = twoProd(a.a2, b);
  p2 = tp.value;
  q2 = tp.error;
  p3 = a.a3 * b;

  s0 = p0;

  ts = twoSum(p1, q0);
  s1 = ts.value;
  s2 = ts.error;

  th = threeSum(s2, q1, p2);
  s2 = th.value;
  q1 = th.error1;
  p2 = th.error2;

  s3 = q1;
  ts = threeSumFast(s3, q2, p3);
  s3 = ts.value;
  q2 = ts.error;

  s4 = q2 + p3;

  return renormalize(s0, s1, s2, s3, s4);
}

float128 float128DivFast(float128 a, float128 b)
{
  float q0, q1, q2, q3;
  float128 r;

  q0 = a.a0 / b.a0;
  r = float128Sub(a, float128MulScalar(b, q0));

  q1 = r.a0 / b.a0;
  r = float128Sub(r, float128MulScalar(b, q1));

  q2 = r.a0 / b.a0;
  r = float128Sub(r, float128MulScalar(b, q2));

  q3 = r.a0 / b.a0;

  return renormalize(q0, q1, q2, q3, 0.0f);
}
