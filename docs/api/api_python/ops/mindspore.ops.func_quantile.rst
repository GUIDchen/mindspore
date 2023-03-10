mindspore.ops.quantile
======================

.. py:function:: mindspore.ops.quantile(x, q, axis=None, keepdims=False)

    计算 `x` 中所有元素的第 `q` 分位数，如果第 `q` 分位数位于两个数据点之间，则返使用线性插值计算结果。

    参数：
        - **x** (Tensor) - 输入Tensor。其shape为 :math:`(x_1, x_2, ..., x_R)` 。支持的数据类型为：float32、float64。
        - **q** (Union[float, Tensor]) - 标量或1D Tensor。其值范围在[0, 1]，支持的数据类型为：float32、float64。
        - **axis** (int，可选) - 要减少的维度。默认情况下 `axis` 为None，导致输入Tensor在计算前被展平。默认值：None。
        - **keepdims** (bool，可选) - 输出Tensor是否保留维度。默认值：False。

    返回：
        输入Tensor，数据类型与 `input` 一致。

        假设 `x` 的shape为 :math:`(m, x_0, x_1, ..., x_i, ..., X_R)` ， `axis` = :math:`i` ，m为 `q` 中的总元素个数。
        
        - 如果 `q` 为标量且 `keepdims` 为True，则输出shape为 :math:`(x_0, x_1, ..., 1, ..., X_R)` 。
        - 如果 `q` 为标量且 `keepdims` 为False，则输出shape为 :math:`(x_0, x_1, ..., X_R)` 。
        - 如果 `q` 为1D Tensor且 `keepdims` 为True，则输出shape为 :math:`(m, x_0, x_1, ..., 1, ..., X_R)` 。
        - 如果 `q` 为1D Tensor且 `keepdims` 为False，则输出shape为 :math:`(m, x_0, x_1, ..., X_R)` 。

    异常：
        - **TypeError** - `x` 不是Tensor。
        - **TypeError** - `q` 不是Tensor或float类型。
        - **TypeError** - `x` 的数据类型float32或float64。
        - **TypeError** - `q` 的数据类型float32或float64。
        - **TypeError** - `x` 和 `q` 的数据类型不一致。
        - **ValueError** - `q` 的值不在[0, 1]范围内。
        - **ValueError** - `axis` 的值不在有效范围内。
