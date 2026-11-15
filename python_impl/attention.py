import numpy as np


def softmax(x, axis=-1):
    max_x = np.max(x, axis=axis, keepdims=True)
    print(max_x.shape)
    z = np.exp(x - max_x)
    return z / np.sum(z, axis=axis, keepdims=True)


def linear(x, w, b):
    return x @ w + b


def scaled_dot_product_attention(q, k, v):
    d_k = q.shape[-1]
    scores = q @ k.T
    scores /= np.sqrt(d_k)
    return softmax(scores) @ v


def test_linear():
    np.random.seed(42)
    seq_len, d_model, d_k = 4, 8, 8

    x = np.random.randn(seq_len, d_model)
    w_q, w_k, w_v = (np.random.randn(d_model, d_k) for _ in range(3))
    b_q, b_k, b_v = (np.random.randn(d_k) for _ in range(3))

    q = linear(x, w_q, b_q)
    k = linear(x, w_k, b_k)
    v = linear(x, w_v, b_v)

    print("Q shape:", q.shape)
    print("K shape:", k.shape)
    print("V shape:", v.shape)

    assert q.shape == (seq_len, d_k)
    assert k.shape == (seq_len, d_k)
    assert v.shape == (seq_len, d_k)
    print("test_linear passed")


if __name__ == "__main__":
    x2 = np.array([[1.0, 2.0, 3.0], [10.0, 20.0, 30.0]])
    try:
        out2 = softmax(x2)
        print("2D Output:\n", out2)
        print("shape:", out2.shape)
        print("row sums: ", out2.sum(axis=-1))
    except Exception as e:
        print("FAILED:", repr(e))
    test_linear()
