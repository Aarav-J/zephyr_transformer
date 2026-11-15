#ifndef ATTENTION_H
#define ATTENTION_H

#include "golden_vectors.h"

/* Y = X @ W + b
 * x: [SEQ_LEN][D_MODEL], w: [D_MODEL][D_K], b: [D_K], out: [SEQ_LEN][D_K]
 */
void linear(const float x[SEQ_LEN][D_MODEL],
            const float w[D_MODEL][D_K],
            const float b[D_K],
            float out[SEQ_LEN][D_K]);

/* Row-wise numerically-stable softmax over a [SEQ_LEN][SEQ_LEN] matrix. */
void softmax(const float x[SEQ_LEN][SEQ_LEN],
             float out[SEQ_LEN][SEQ_LEN]);

/* scores = (q @ k^T) / sqrt(D_K); out = softmax(scores) @ v */
void scaled_dot_product_attention(const float q[SEQ_LEN][D_K],
                                   const float k[SEQ_LEN][D_K],
                                   const float v[SEQ_LEN][D_K],
                                   float out[SEQ_LEN][D_K]);

#endif /* ATTENTION_H */
