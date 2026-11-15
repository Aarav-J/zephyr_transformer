#include "attention.h"

#include <math.h>

void linear(const float x[SEQ_LEN][D_MODEL],
            const float w[D_MODEL][D_K],
            const float b[D_K],
            float out[SEQ_LEN][D_K])
{
    /* TODO: out = x @ w + b */

    for(int i = 0; i < SEQ_LEN; i++) { 
        for(int j = 0; j < D_K; j++) { 
            out[i][j] = b[j]; 
            for(int k = 0; k < D_MODEL; k++) { 
                out[i][j] += x[i][k] * w[k][j]; 

            }
        }
    }
}

void softmax(const float x[SEQ_LEN][SEQ_LEN],
             float out[SEQ_LEN][SEQ_LEN])
{
    /* TODO: numerically-stable row-wise softmax, same idea as the NumPy version */

     for (int i = 0; i < SEQ_LEN; i++) {
        float max_val = x[i][0];
        for (int j = 1; j < SEQ_LEN; j++) {
            if (x[i][j] > max_val) {
                max_val = x[i][j];
            }
        }

        float sum_exp = 0.0f;
        for (int j = 0; j < SEQ_LEN; j++) {
            out[i][j] = expf(x[i][j] - max_val);
            sum_exp += out[i][j];
        }

        for (int j = 0; j < SEQ_LEN; j++) {
            out[i][j] /= sum_exp;
        }
    }
}

void scaled_dot_product_attention(const float q[SEQ_LEN][D_K],
                                   const float k[SEQ_LEN][D_K],
                                   const float v[SEQ_LEN][D_K],
                                   float out[SEQ_LEN][D_K])
{
    /* TODO: scores = q @ k^T / sqrt(D_K); out = softmax(scores) @ v */

    float scores[SEQ_LEN][SEQ_LEN] ;

    for (int i = 0; i < SEQ_LEN; i++) {
        for (int j = 0; j < SEQ_LEN; j++) {
            scores[i][j] = 0.0f;
            for (int x = 0; x < D_K; x++) {
                scores[i][j] += q[i][x] * k[j][x];
            }
            scores[i][j] /= sqrtf(D_K);
        }
    }
    softmax(scores, scores); 
    for(int i = 0; i < SEQ_LEN; i++) {
        for (int j = 0; j < D_K; j++) {
            out[i][j] = 0.0f;
            for (int x = 0; x < SEQ_LEN; x++) {

                out[i][j] += scores[i][x] * v[x][j];
            }
        }
    }

}
