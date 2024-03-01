#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

struct RandState {
  const int mod1;
  const int mod2;
  const int mul1;
  const int mul2;
  int64_t  seed1;
  int64_t  seed2;
};

static const struct RandState default_state = {
  2147483563,
  2147483399,
  40014,
  40692,
  12345,
  67890
};

void rand_seed(struct RandState *state, int64_t seed) {
  if (seed < 0)
    seed = -seed;
  if (seed == 0) {
    state->seed1 = 12345;
    state->seed2 = 67890;
  } else {
    state->seed1 = (state->mul1 * seed ) % state->mod1;
    state->seed2 = seed % state->mod2;
  }
}

double randv(struct RandState *state) {
  state->seed1 = (state->seed1 * state->mul1) % state->mod1;
  state->seed2 = (state->seed2 * state->mul2) % state->mod2;
  double res = (double)(state->seed1 - state->seed2) / (double)state->mod1;
  return res < 0.0 ? res + 1.0 : res;
}

double *randn(struct RandState *state, int64_t n) {
  if (n < 0)
    return NULL;

  double *vals = malloc(sizeof(double) * n);
  if (vals == NULL)
    return NULL;

  for(int64_t i = 0; i < n; i++)
    vals[i] = randv(state);
  return vals;
}

int64_t randInt(struct RandState *state, int64_t lower, int64_t upper) {
  if (lower > upper) {
    int64_t temp = lower;
    lower = upper;
    upper = temp;
  }
  return lower + floor(randv(state) * (upper - lower + 1));
}

int64_t *randIntn(struct RandState *state, int64_t lower, int64_t upper, int64_t n) {
  if (n < 0)
    return NULL;

  if (lower > upper) {
    int64_t temp = lower;
    lower = upper;
    upper = temp;
  }

  int64_t *vals = malloc(sizeof(int64_t) * n);
  if (vals == NULL)
    return NULL;

  for (int64_t i = 0; i < n; i++)
    vals[i] = randInt(state, lower, upper);
  return vals;
}

int64_t *randIntNoRep(struct RandState *state, int64_t lower, int64_t upper, int64_t n) {
  if (lower > upper) {
    int64_t temp = lower;
    lower = upper;
    upper = temp;
  }
  if (n > upper - lower + 1)
    n = upper - lower + 1;

  int64_t *vals = malloc(sizeof(int64_t) * n);
  if (vals == NULL)
      return NULL;

  for (int64_t i = 0; i < n; ) {
    int64_t val = randInt(state, lower, upper);
    int8_t flag = 1;
    for (int64_t j = i - 1; j >= 0; j--) {
      if (vals[j] == val) {
        flag = 0;
        break;
      }
    }
    if (flag)
      vals[i++] = val;
  }
  return vals;
}

int64_t randBin(struct RandState *state, int64_t n, double p) {
  double *vals = randn(state, n);
  int64_t res = 0;
  for (int64_t i = 0; i < n; i++) {
    if (p > vals[i])
      res++;
  }
  free(vals);
  return res;
}

int64_t *randBinn(struct RandState *state, int64_t n, double p, int64_t rep) {
  if (rep < 0)
    return NULL;
  int64_t *vals = malloc(sizeof(int64_t) * rep);
  if (vals == NULL)
    return NULL;
  for (int64_t i = 0; i < rep; i++)
    vals[i] = randBin(state, n, p);
  return vals;
}

/* randNorm(mean, stdev) = mean - stdev * invNorm(rand()) */
/* randM is randInt(-9,9) from bottom right, moving left, row to row */

int main(void) {
  struct RandState foo = default_state;
  int64_t *test = randBinn(&foo, 10, 0.189, 10);
  for (int64_t i = 0; i < 10; i++)
    printf("%ld\n", test[i]);
  free(test);
  return 0;
}
