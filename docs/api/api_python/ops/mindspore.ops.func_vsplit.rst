mindspore.ops.vsplit
=====================

.. py:function:: mindspore.ops.vsplit(x, indices_or_sections)

    垂直地将输入Tensor分割成多个子Tensor。等同于 `axis=0` 时的 `ops.tensor_split` 。

    参数：
        - **x** (Tensor) - 待分割的Tensor。
        - **indices_or_sections** (Union[int, tuple(int), list(int)]) - 参考 :func:`mindspore.ops.tensor_split`.

    返回：
        tuple[Tensor]。
