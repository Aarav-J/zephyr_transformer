import attention
import numpy as np
import torch

if __name__ == "__main__":
    np.random.seed(42)
    seq_len, d_model, d_k = 4, 8, 8

    x = np.random.randn(seq_len, d_model)
    w_q, w_k, w_v = (np.random.randn(d_model, d_k) for _ in range(3))
    b_q, b_k, b_v = (np.random.randn(d_k) for _ in range(3))

    Q = attention.linear(x, w_q, b_q)
    V = attention.linear(x, w_v, b_v)
    K = attention.linear(x, w_k, b_k)

    out_numpy = attention.scaled_dot_product_attention(Q, K, V)
    Q = torch.tensor(Q, dtype=torch.float32)
    K = torch.tensor(K, dtype=torch.float32)
    V = torch.tensor(V, dtype=torch.float32)
    out_torch = torch.nn.functional.scaled_dot_product_attention(Q, K, V)
    print("Output comparison:", np.allclose(out_numpy, out_torch.numpy(), atol=1e-5))
