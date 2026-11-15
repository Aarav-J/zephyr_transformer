#include <math.h>
#include <stdio.h>

#include "attention.h"

#define TOL 1e-4f

static int compare(const char *label,
                    const float got[SEQ_LEN][D_K],
                    const float want[SEQ_LEN][D_K])
{
    float max_diff = 0.0f;
    for (int i = 0; i < SEQ_LEN; i++) {
        for (int j = 0; j < D_K; j++) {
            float diff = fabsf(got[i][j] - want[i][j]);
            if (diff > max_diff) {
                max_diff = diff;
            }
        }
    }

    int pass = max_diff < TOL;
    printf("%-10s max_diff=%.8f  %s\n", label, max_diff, pass ? "PASS" : "FAIL");
    return pass;
}

int main(void)
{
    float q[SEQ_LEN][D_K];
    float k[SEQ_LEN][D_K];
    float v[SEQ_LEN][D_K];
    float out[SEQ_LEN][D_K];

    linear(X, W_Q, B_Q, q);
    linear(X, W_K, B_K, k);
    linear(X, W_V, B_V, v);

    int ok = 1;
    ok &= compare("Q", q, EXPECTED_Q);
    ok &= compare("K", k, EXPECTED_K);
    ok &= compare("V", v, EXPECTED_V);

    scaled_dot_product_attention(q, k, v, out);
    ok &= compare("attention", out, EXPECTED_OUTPUT);

    printf("\n%s\n", ok ? "ALL TESTS PASSED" : "SOME TESTS FAILED");
    return ok ? 0 : 1;
}
