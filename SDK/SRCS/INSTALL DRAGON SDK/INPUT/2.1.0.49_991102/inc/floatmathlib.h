  #ifdef __cplusplus
  extern "C" {
  #endif
    float sinhs(float rVal);
    float coshs(float rVal);
    float tanhs(float rVal);
    float exps(float rVal);
    float logs(float rVal);
    float log10s(float rVal);
    float acoss(float);
    float asins(float);
    float atans(float);
    float atan2s(float, float);
    float fmods(float, float);
    float coss(float);
    float tans(float);
    float frnds(float);
    float sins(float);
    float sqrts(float);
    float pows(float, float);
    float floors(float);
    float ceils(float);
  #ifdef __cplusplus
  };
  #endif

#define fmod(x, y)  fmods((x), (y))
#define sin(x)      sins(x)
#define cos(x)      coss(x)
#define tan(x)      tans(x)
#define frnd(x)     frnds(x)
#define sqrt(x)     sqrts(x)
#define asin(x)     asins(x)
#define acos(x)     acoss(x)
#define atan(x)     atans(x)
#define atan2(x, y) atan2s((x), (y))
#define pow(x, y)   pows((x), (y))
#define floor(x)    floors(x)
#define fceil(x)    ceils(x)
#define fabs(x)     ((x) < 0 ? -(x) : (x))
#define log(x)      logs(x)
#define log10(x)    log10s(x)
#define sinh(x)     sinhs(x)
#define cosh(x)     coshs(x)
#define tanh(x)     tanhs(x)
