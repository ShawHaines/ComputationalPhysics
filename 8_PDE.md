# PDE

## 证明抛物线型方程FTCS方法的稳定条件

Let $\delta_{n}(x)=\sum_{k} \delta_{k}^{n} e^{i k x}$

substitute into equation

$$
u_{j, n+1}=(1-2 \beta) u_{j,n}+\beta\left(u_{j^{\prime}, n}+u_{j^{\prime}, n}\right)
$$
where $\beta=\frac{D \Delta t}{\Delta x^{2}}$

We then have

$$
\delta_{k}^{n+1} e^{i k x_{j+1}}=(1-2 \beta) \delta_{k}^{n} e^{i k x_{j}}+\beta\left(\delta_{k}^{n} e^{i k x_{j-1}}+\delta_{k}^{n} e^{i k x_{j+1}}\right)
$$

the stable condition requires that $\forall k, \quad|g| \leqslant 1$

$$
\begin{aligned}
\Rightarrow &|g|=\left(1-4 \beta \sin ^{2} \frac{k \Delta x}{2}\right)^{2} \leqslant 1 \\
\Rightarrow & \beta \sin ^{2} \frac{k \Delta x}{2}\left(1-2 \beta \sin ^{2} \frac{k x}{2}\right) \geqslant 0 \\
\text { in extreme condition } \sin \frac{k \Delta x}{2}=1 \\
\Rightarrow & 0 \leq \beta \leq \frac{1}{2}, \quad \text{i.e.}\\
& \frac{D \Delta t}{\Delta x^{2}} \leqslant \frac{1}{2}
\end{aligned}
$$

