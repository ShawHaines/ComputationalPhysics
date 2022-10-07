# Homework #1 无量纲化

## 无量纲化质能方程和洛伦兹力方程

### 质能方程

$$
W = \sqrt{m_0^2c^4+p^2c^2}
$$

Let

$$
\begin{aligned}
W_u\equiv m_0c^2, p_u\equiv m_0c\\
W'=\frac{W}{W_u}, p'=\frac{p}{p_u}
\end{aligned}
$$

then

$$
\begin{aligned}
W' &=\frac{\sqrt{m_0^2 c^4+p^2c^2}}{m_0 c^2}\\
   &=\sqrt{1+\left(\frac{p' m_0c\cdot c}{m_0 c^2}\right)^2}\\
   &=\sqrt{1+p'^2}
\end{aligned}
$$

### 洛伦兹力方程

$$
\frac{\mathrm{d}\vec{P}}{\mathrm{d}t} =  = -e(\vec{E}+\vec{v}\times\vec{B})
$$

Let
$$
\begin{aligned}
    &P_u=m_0 c, &t_u=1/\omega_0, &v_u=c& \\
    &\vec{P'}\equiv\vec{P}/P_u,  &t'\equiv t/t_u, &\vec{v'}\equiv\vec{v}/v_u&
\end{aligned}
$$

$$
\begin{aligned}
    \frac{\mathrm{d}\vec{P'}}{\mathrm{d}t'}
    &=\frac{\mathrm{d}\vec{P}}{\mathrm{d}t}\cdot \frac{1/\omega_0}{m_0 c}\\
    &=-\frac{e}{\omega_0m_0c}(\vec{E}+\vec{v'}c \times \vec{B})\\
    &=-(\vec{E'}+\vec{B'})
\end{aligned}
$$

where we define the corresponding Electric and Magnetic Field Units

$$
\begin{aligned}
    \vec{E'}\equiv \frac{\vec{E'}}{\omega_0m_0c/e},& \vec{B'}=\frac{\vec{B}}{\omega_0m_0c}\\
\end{aligned}
$$

## 计算光波长$\lambda = 0.8\mu \mathrm{m}$对应的相对论电场阈值和强度阈值

$$
E_u=\frac{m_ec\omega_0}{e}=\frac{2\pi m_ec^2}{\lambda e}
$$

代入数据计算得
$$
E_u=4.02\times 10^{12} \mathrm{V/m}
$$

能流密度阈值为

$$
s_u=\varepsilon_0E_u^2=1.43\times10^{14}\mathrm{W/m^3}
$$

