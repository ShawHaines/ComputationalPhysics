# Homework#2 误差分析

## 1.4#2

一般而言,(a)的公式更为实用。(b)公式当$x,y$十分接近的时候，一方面$\frac{(y-x)}{2.0}$相近数互减会使有效数字减少，另一方面作差后与$x$相加也可能产生大数吃小数的情况。

## 1.4#3

(a)

$(x-y)(x+y)$ 可以被计算得更加精确。
虽然当$x,y$绝对值较为接近的时候，两条表达式都会出现相近数作差使误差增加的情况，但是相对而言$x^2$数值更大一些，作差得到的结果有效数字位数更少。

(b)

记$\delta=x-y$，当
$$
\frac{|\delta|}{x}\ll 1
$$
时，两者的精度将会有较大差异。

## 1.4#5

(a) 
$$
\begin{aligned}
    x-\sin x
    &=\frac{1}{3!}x^3-\frac{1}{5!}x^5+\cdots\\
    &+\frac{(-1)^{n+1}}{(2n+1)!}x^{2n+1}
\end{aligned}
$$

(b)
$$
\sqrt{x+4}-2=\frac{x}{\sqrt{x+4}+2}
$$

(c)
$$
\begin{aligned}
    \frac{e^{2x}-1}{2} &=\frac{1}{2}(e^x+1)(e^x-1)
\end{aligned}
$$

(d)
$$
\begin{aligned}
    \sin x+\cos x-1
    &=\sqrt{2}\sin(x+\pi/4)-1
\end{aligned}
$$

or near $x=0$ we can write
$$
\begin{aligned}
    \sin x+\cos x-1
    &=\sin x-\sin^2 \frac{x}{2}
\end{aligned}
$$

(e)

near $x=0$ we write

$$
\begin{aligned}
    \arctan x-x
    &=-\frac{1}{3}x^3+\cdots + \frac{(-1)^{n+}}{2n+1}x^{2n+1}
\end{aligned}
$$

## 1.4#7

如果利用结果$e^{0.01}\approx1.0101$，则$f(0.01)=0.0001=1\times 10^{-5}$，虽然原来e指数的估算值有5位有效数字，但是作差后只剩下一位有效数字。

计算得到$f(0.01)=5.0167\times10^{-5}$，两者之间相对误差达到了50%，从这里也可以看到相近数相减对有效数字位数的危害。

## 1.4#8

$$
\begin{aligned}
    \sin\left( \frac{\pi}{4}+h\right)
    &=\frac{1}{\sqrt{2}}\left( 1+\frac{1}{1!}h-\frac{1}{2!}h^2+\cdots+\frac{(-1^{[\frac{n}{2}]})}{n!}h^n\right)
\end{aligned}
$$

$$
\sin(45.0005\degree)=\sin(\frac{\pi}{4}+8.73\times10^{-6})
$$
i.e. 

$$
h=8.726646260\times 10^{-6}
$$

We only need to reserve to term $O(h^2)$, therefore,

$\sin(45.0005\degree)\approx0.707112952$


## Subtractive Cancelation

One instance where subtractive cancelation can occur involves finding the roots of a quadratic equation with the quadratic formula as 

$$
x_{1,2}=\frac{-b\pm \sqrt{b^2-4a c}}{2a}
$$

For cases where $b^2\gg 4ac$, the difference in the numerator can be very small.

In such cases, double precision may be employed; Alternatively, an equivalent formulation can be used to iniize subtractive cancelation, i.e.

$$
x_{1,2} = \frac{-2c}{b\pm\sqrt{b^2-4ac}}
$$

To give an illustration, compute the values of the roots of a quadratic equation with $a=1, b=3000.001$ and $c=3$. Furthermore, check the computed values versus the true roots of $x_1 = -0.001$ and $x_2 = -3000$.
