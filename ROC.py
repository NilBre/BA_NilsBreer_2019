import numpy as np
import matplotlib.pyplot as plt

# datenfiles fuer ROC Kurven
# a: links vom cut, b: rechts vom cut
j, aDR1, bDR1, ax1, bx1 = np.genfromtxt("ssbar_werte.txt", unpack=True)
j, aDR2, bDR2, ax2, bx2 = np.genfromtxt("ddbar_werte.txt", unpack=True)
j, aDR3, bDR3, ax3, bx3 = np.genfromtxt("uubar_werte.txt", unpack=True)

# auswertung der roc daten
# fuer deltaR:
totalssbar_DR = sum(aDR1) + sum(bDR1)
totalddbar_DR = sum(aDR2) + sum(bDR2)
totaluubar_DR = sum(aDR3) + sum(bDR3)
# for ssbar - uubar comparison
tp_ssuu = []
fp_ssuu = []
tn_ssuu = []
fn_ssuu = []
positiveRatio1 = []
negativeRatio1 = []
sens1 = []
spec1 = []
# for ssbar - ddbar comparison
tp_ssdd = []
fp_ssdd = []
tn_ssdd = []
fn_ssdd = []
positiveRatio2 = []
negativeRatio2 = []
sens2 = []
spec2 = []

# fill the right arrays:
# calc all important variables
for i in range(len(aDR1)):
    tp_ssuu.append(bDR3[i])
    fp_ssuu.append(bDR1[i])
    tn_ssuu.append(aDR1[i])
    fn_ssuu.append(aDR3[i])

# fill FPR and TPR
for i in range(len(aDR1)):
    positiveRatio1.append(bDR3[i] / totaluubar_DR)
    negativeRatio1.append(bDR1[i] / totalssbar_DR)

# calc ROC with other way
for i in range(len(aDR1)):
    calc_sens1 = tp_ssuu[i] / (tp_ssuu[i] + fn_ssuu[i])
    calc_spec1 = 1 - (tn_ssuu[i] / (fp_ssuu[i] + tn_ssuu[i]))
    sens1.append(calc_sens1)
    spec1.append(calc_spec1)

# calc important values
for i in range(len(aDR1)):
    tp_ssdd.append(bDR2[i])
    fp_ssdd.append(bDR1[i])
    tn_ssdd.append(aDR1[i])
    fn_ssdd.append(aDR2[i])

# fill FPR and TPR
for i in range(len(aDR1)):
    positiveRatio2.append(bDR2[i] / totalddbar_DR)
    negativeRatio2.append(bDR1[i] / totalssbar_DR)

# calc ROC with other way
for i in range(len(aDR1)):
    calc_sens2 = tp_ssdd[i] / (tp_ssdd[i] + fn_ssdd[i])
    calc_spec2 = 1 - (tn_ssdd[i] / (fp_ssdd[i] + tn_ssdd[i]))
    sens2.append(calc_sens2)
    spec2.append(calc_spec2)

plt.plot(spec1, sens1, "b--", label="roc punkte DR (s-u)")
plt.plot(spec2, sens2, "k--", label="roc punkte DR (s-d)")
plt.plot([1,0], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.xlabel("1 - specificity")
plt.ylabel("sensitivity")
plt.savefig("py_output/ROC_DeltaR.pdf")
plt.clf()

plt.plot(negativeRatio1, positiveRatio1, "b--", label="alt. DR (s-u)")
plt.plot(negativeRatio2, positiveRatio2, "k--", label="alt. DR (s-d)")
plt.plot([1,0], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.savefig("py_output/ROC_DeltaR_alt.pdf")
plt.clf()

# fuer XLambda
totalssbar_XL = sum(ax1) + sum(bx1)
totalddbar_XL = sum(ax2) + sum(bx2)
totaluubar_XL = sum(ax3) + sum(bx3)
# for ssbar - uubar comparison
tp_su_x = []
fp_su_x = []
tn_su_x = []
fn_su_x = []
pr1 = [] # TPR
nr1 = [] # FPR
SE1 = [] # sensitivity
SP1 = [] # specificity
# for ssbar - ddbar comparison
tp_sd_x = []
fp_sd_x = []
tn_sd_x = []
fn_sd_x = []
pr2 = []
nr2 = []
SE2 = []
SP2 = []

# fill the right arrays:
# calc all important variables
for i in range(len(ax1)):
    tp_su_x.append(bx1[i])
    fp_su_x.append(bx3[i])
    tn_su_x.append(ax3[i])
    fn_su_x.append(ax1[i])

# fill FPR and TPR
for i in range(len(ax1)):
    pr1.append(bx1[i] / totalssbar_XL)
    nr1.append(bx3[i] / totaluubar_XL)

# calc ROC with other way
for i in range(len(ax1)):
    sensXL1 = tp_su_x[i] / (tp_su_x[i] + fn_su_x[i])
    specXL1 = 1 - (tn_su_x[i] / (fp_su_x[i] + tn_su_x[i]))
    SE1.append(sensXL1)
    SP1.append(specXL1)

# calc important values
for i in range(len(ax1)):
    tp_sd_x.append(bx1[i])
    fp_sd_x.append(bx2[i])
    tn_sd_x.append(ax1[i])
    fn_sd_x.append(ax1[i])

# fill FPR and TPR
for i in range(len(ax1)):
    pr2.append(bx1[i] / totalssbar_XL)
    nr2.append(bx2[i] / totalddbar_XL)

# calc ROC with other way
for i in range(len(aDR1)):
    sensXL2 = tp_ssdd[i] / (tp_ssdd[i] + fn_ssdd[i])
    specXL2 = 1 - (tn_ssdd[i] / (fp_ssdd[i] + tn_ssdd[i]))
    SE2.append(sensXL2)
    SP2.append(specXL2)

plt.plot(SP1, SE1, "b--", label="roc punkte XLambda (s-u)")
plt.plot(SP2, SE2, "k--", label="roc punkte XLambda (s-d)")
plt.plot([1,0], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.xlabel("1 - specificity")
plt.ylabel("sensitivity")
plt.savefig("py_output/ROC_XLambda.pdf")
plt.clf()

plt.plot(nr1, pr1, "b--", label="alt. XLambda (s-u)")
plt.plot(nr2, pr2, "k--", label="alt. XLambda (s-d)")
plt.plot([1,0], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.savefig("py_output/ROC_XLambda_alt.pdf")
plt.clf()
