#include <iostream>
#include <iomanip>
#include <cmath>  // 用于计算e的指数

using namespace std;

// 计算平均消费c
double calculateAverageConsumption(double alpha, double beta1, double beta2, double h, double p) {
    return alpha + beta1 * h + beta2 * p;
}

// 计算会展或活动的影响因子i（假设是游客数量的某个函数，这里可以根据实际情况调整）
double calculateImpactFactor(int v) {
    // 假设影响因子与游客数量呈线性关系，具体函数可以根据实际情况修改
    return v * 0.1;  // 举个例子，假设i = 0.1 * v
}

// 计算碳排放量E（假设E与游客数量和运输温度相关）
double calculateCarbonEmission(int v, double T_transport) {
    // 假设碳排放量与游客数量和温度呈某种关系，这里采用一个简单的假设公式
    return v * T_transport * 0.5;  // 举个例子，E = v * T_transport * 0.5
}

// 计算冰川体积对时间的导数dG/dt
double calculateGlacierVolumeDerivative(int v, double T, double alpha1, double k) {
    return -alpha1 * v * exp(-k * T);  // 使用指数函数
}

// 计算环境损失E_environment
double calculateEnvironmentalDamage(double E, double dG_dt, double w11, double w12) {
    return w11 * E + w12 * dG_dt;
}

// 计算社会满意度S
double calculateSatisfaction(double h, double s_tourist, double p, double x) {
    double w21 = 0.552, w22 = 0.214, w23 = 0.1015, w24 = 0.237;
    return w21 * h + w22 * s_tourist + w23 * p + w24 * x;
}

// 计算旅游税收Rtax
double calculateRtax(int v, double c, double theta, double t_tax) {
    return v * c * theta * t_tax;
}

// 计算隐形成本Ri
double calculateRi(double i, double p_waste, int v, double d, double l) {
    return i + p_waste * v * (d / l) * 365;
}

// 计算经济效益
double calculateEconomicBenefit(int v, double c, double Rtax, double Ri, double x) {
    return (v * c + Rtax - Ri) * x;
}

// 计算长途旅客碳排放量 El
double calculateLongDistanceEmission(int vl) {
    return vl * 4 / 2 * 10 + 13 * vl * 2 + vl * 84 * 10 + vl * 41 * 1.60934 / 3 * 0.24;
}

// 计算短途旅客碳排放量 Es
double calculateShortDistanceEmission(int vs) {
    return vs * 2 + vs * 1.60934 * 26.8 / 30 * 0.24 + vs * 84 * 10;
}

// 计算总碳排放量 E
double calculateTotalEmission(int vl, int vs) {
    double El = calculateLongDistanceEmission(vl);
    double Es = calculateShortDistanceEmission(vs);
    return El + Es;
}

// 计算朱诺市人口l(t)
double calculatePopulation(double t) {
    // 朱诺市人口模型公式
    return 6925.47555968085 * exp(-pow((t - 2018.716260354647), 2) / (2 * pow(28.12078245655908, 2))) + 2498.8518142892826;
}

int main() {
    // 输入数据
    int v, vl, vs;  // v是总游客数量，vl是长途旅客数量，vs是短途旅客数量
    double c, theta, t_tax, i, p_waste, x, d, l, alpha, beta1, beta2,alpha1, k, w11, w12;
    double T, dG_dt, E, E_environment, Rtax, Ri, economicBenefit, s_tourist, h, S;

    alpha1=0.00000505;
    k=0.124;
    alpha=0;
    beta1=0.925;
    beta2=-0.227;
    d =2.3561472 ;
    w11 =0.7 ;
    w12 =0.3 ;
    theta = 0.55603;

    // 获取用户输入
    cout << "请输入总游客数量 (v), 长途旅客数量 (vl), 短途旅客数量 (vs): ";
    cin >> v >> vl >> vs;

    if (v > 3714361) {
        cout << "游客总数 v 必须小于或等于 3714361." << endl;
        return 1; // 如果游客总数大于限制，程序终止
    }

    cout << "请输入物价 (p): ";
    cin >> p_waste;
    cout << "请输入经济利润中分给游客的比例 (x): ";
    cin >> x;
    cout << "请输入旅游税收的比例 (t_tax): ";
    cin >> t_tax;
    cout << "请输入游客满意度 s_tourist: ";
    cin >> s_tourist;
    cout << "请输入住房占旅游支出的比例 h: ";
    cin >> h;
    cout << "请输入温度 T: ";
    cin >> T;

    // 计算朱诺市人口
    cout << "请输入年份 t: ";
    double t;
    cin >> t;
    l = calculatePopulation(t);  // 计算人口，l = 人口(t)

    // 计算c（平均消费）
    c = calculateAverageConsumption(alpha, beta1, beta2, h, p_waste);

    // 计算i（会展的影响因子）
    i = calculateImpactFactor(v);

    // 计算E（碳排放量）
    E = calculateTotalEmission(vl, vs);

    // 计算冰川体积对时间的导数
    dG_dt = calculateGlacierVolumeDerivative(v, T, alpha1, k);

    // 计算环境损失
    E_environment = calculateEnvironmentalDamage(E, dG_dt, w11, w12);

    // 计算社会满意度S
    S = calculateSatisfaction(h, s_tourist, p_waste, x);

    // 计算旅游税收Rtax和隐形成本Ri
    Rtax = calculateRtax(v, c, theta, t_tax);
    Ri = calculateRi(i, p_waste, v, d, l);

    // 计算经济效益
    economicBenefit = calculateEconomicBenefit(v, c, Rtax, Ri, x);

    // 输出结果
    cout << fixed << setprecision(2); // 设置输出为小数点后两位
    cout << "总碳排放量 E: " << E << endl;
    cout << "环境损失 E_environment: " << E_environment << endl;
    cout << "社会满意度 S: " << S << endl;
    cout << "经济效益: " << economicBenefit << endl;

    return 0;
}