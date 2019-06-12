import numpy as np
import matplotlib.pyplot as plt
# from sklearn import metrics
# from sklearn.metrics import roc_curve

# Notizen an mich:
# Die alternative version ueber TPR und FPR geht bei beiden gut
# warum die andere nicht

# datenfiles fuer ROC Kurven
# a: links vom cut, b: rechts vom cut
j, aDR1, bDR1 = np.genfromtxt("ssbar_werte.txt", unpack=True)
j, aDR2, bDR2 = np.genfromtxt("ddbar_werte.txt", unpack=True)
j, aDR3, bDR3 = np.genfromtxt("uubar_werte.txt", unpack=True)

# auswertung der roc daten
# fuer deltaR:
totalssbar_DR = aDR1[0] + bDR1[0]
totalddbar_DR = aDR2[0] + bDR2[0]
totaluubar_DR = aDR3[0] + bDR3[0]
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
    tp_ssuu.append(bDR1[i])
    fp_ssuu.append(bDR3[i])
    tn_ssuu.append(aDR3[i])
    fn_ssuu.append(aDR1[i])

# fill FPR and TPR
for i in range(len(aDR1)):
    positiveRatio1.append(bDR3[i] / totaluubar_DR) # TPR
    negativeRatio1.append(bDR1[i] / totalssbar_DR) # FPR

# calc ROC with other way
for i in range(len(aDR1)):
    calc_sens1 = tp_ssuu[i] / (tp_ssuu[i] + fn_ssuu[i])
    calc_spec1 = 1 - (tn_ssuu[i] / (fp_ssuu[i] + tn_ssuu[i]))
    sens1.append(calc_sens1)
    spec1.append(calc_spec1)

for i in range(len(aDR1)):
    tp_ssdd.append(bDR1[i])
    fp_ssdd.append(bDR2[i])
    tn_ssdd.append(aDR2[i])
    fn_ssdd.append(aDR1[i])

# fill FPR and TPR
for i in range(len(aDR1)):
    positiveRatio2.append(bDR2[i] / totalddbar_DR) # TPR
    negativeRatio2.append(bDR1[i] / totalssbar_DR) # FPR

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
j, ax1, bx1, a_fake1, b_fake1 = np.genfromtxt("ssbar_werte_XL.txt", unpack=True)
j, ax2, bx2, a_fake2, b_fake2 = np.genfromtxt("ddbar_werte_XL.txt", unpack=True)
j, ax3, bx3, a_fake3, b_fake3 = np.genfromtxt("uubar_werte_XL.txt", unpack=True)

# y = np.array([1, 1, 2, 2])
# scores = np.array([0.1, 0.4, 0.35, 0.8])
# fpr, tpr, thresholds = roc_curve(y, scores, pos_label=2)

totalssbar_XL = ax1[0] + bx1[0]
totalddbar_XL = ax2[0] + bx2[0]
totaluubar_XL = ax3[0] + bx3[0]
# for ssbar
tp_sd_x = []
fp_sd_x = []
tn_sd_x = []
fn_sd_x = []
pr1 = []
nr1 = []
SE1 = []
SP1 = []

# calc important values
for i in range(len(ax1)):
    fp_sd_x.append(b_fake1[i])
    tp_sd_x.append(bx1[i])
    fn_sd_x.append(ax1[i])
    tn_sd_x.append(a_fake1[i])

# fill FPR and TPR
for i in range(len(ax1)):
    nr1.append(b_fake1[i] / totalssbar_XL)
    pr1.append(bx1[i] / totalssbar_XL)

# calc ROC with other way
for i in range(len(ax1)):
    sensXL1 = tp_sd_x[i] / (tp_sd_x[i] + fn_sd_x[i])
    specXL1 = 1 - (tn_sd_x[i] / (fp_sd_x[i] + tn_sd_x[i]))
    SE1.append(sensXL1)
    SP1.append(specXL1)

plt.plot(SP1, SE1, "b--", label="roc punkte XLambda (s-u)")
plt.plot([1,0], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.xlabel("1 - specificity")
plt.ylabel("sensitivity")
plt.savefig("py_output/ROC_XLambda.pdf")
plt.clf()

plt.plot(nr1, pr1, "b--", label="alt. XLambda (s-u)")
plt.plot([1,0], [1,0], "r-", label="random values")
plt.grid()
plt.legend()
plt.savefig("py_output/ROC_XLambda_alt.pdf")
plt.clf()
